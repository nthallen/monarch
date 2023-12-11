/* test_calibr.c */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "nl.h"
#include "nl_assert.h"
#include "calibr.h"

struct intcnv {
  struct intcnv *next;
  int64_t x0, x1;
  int64_t n, r, d, y0;
  int flag;
};
#define ICNV_INT 1
#define ICNV_LINT 2
#define ICNV_LLINT 4

struct intcnvl {
  struct intcnv *first, *last;
  int n_regions;
};

typedef struct {
  struct calibration *cal;
  int64_t n, d, X0, X1, Y0;
  int64_t r_min, r_max;
  int fix_dir; // Direction of r adjustment
  double m, b;
} calseg_t;

typedef struct {
  // int64_t r; // Value of r we were testing
  int64_t fX; // X value where it failed
} test_result_t;

static int64_t gcd(int64_t a, int64_t b) {
  int64_t temp;
  while (b != 0) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

/**
 * @param cseg Calibration segment definition
 * On input, m, b, X0, X1 are defined and cal and
 * fix_dir are initialized.
 * On exit, n, d, r0 and Y0 are defined.
 * The value r0 is very close to the fine remainder
 * value r, but that is adjust on a segment-by-segment
 * basis in test_seg().
 */
static void rationalize(calseg_t *cseg) {
  int64_t n, d, d1, g;
  double prec, dX;
  
  if (cseg->m == 0) {
    cseg->Y0 = round(cseg->b);
    cseg->n = 0;
    cseg->d = 1;
    cseg->r_min = cseg->r_max = 0;
    return;
  }
  dX = cseg->X1 - cseg->X0;
  prec = 0.1/dX;
  d = 1;
  n = round(cseg->m);
  for (;;) {
    double rem = cseg->m - n/(double)d;
    if (fabs(rem) < prec) {
      cseg->n = n;
      cseg->d = d;
      break;
    }
    nl_assert(fabs(rem) < 1.0);
    d1 = round(1/rem);
    n = n*d1 + d;
    d = d*d1;
    g = gcd(n, d);
    n /= g;
    d /= g;
    if (d < 0) {
      n = -n;
      d = -d;
    }
  }
  cseg->n = n;
  cseg->d = d;
  cseg->Y0 = round(cseg->m*cseg->X0+cseg->b) + (n > 0 ? -1 : 1);
  cseg->r_min = 1;
  cseg->r_max = -1;
}

/**
 * @param cseg calibration segment details
 * @param x candidate X parameter
 * Calculates range of r values that work for sample x
 * and updates the cseg structure.
 * @returns true if there is no range of r values that works for x
 */
static int test_ndrxy(calseg_t *cseg, int64_t x) {
  int64_t Yd = round(cseg->m*x + cseg->b);
  int64_t dynd = cseg->d*(Yd-cseg->Y0)-cseg->n*(x-cseg->X0);
  int64_t r_min = dynd + ((cseg->n>0) ? 0 : -cseg->d+1);
  int64_t r_max = dynd + ((cseg->n>0) ? cseg->d-1 : 0);
  if (cseg->r_min <= cseg->r_max) {
    // update the local limits to be the intersection
    if (cseg->r_min > r_min) r_min = cseg->r_min;
    if (cseg->r_max < r_max) r_max = cseg->r_max;
  }
  if (r_min <= r_max) {
    cseg->r_min = r_min;
    cseg->r_max = r_max;
    return 0;
  }
  return 1;
}

/**
 * @param cseg calibration segment details
 * @param r candidate remainder parameter
 * @param xt X value to start testing from
 * @param res Result structure
 */
static void test_seg(calseg_t *cseg, int64_t xt,
                    test_result_t *res) {
  int64_t x;
  int err_dir = 0;
  for (x = xt; err_dir == 0 && x <= cseg->X1; ++x) {
    if (test_ndrxy(cseg, x)) {
      res->fX = x;
      return;
    }
  }
  res->fX = x;
}

/* Given slope and intercept and input range, generates a chain
   of regions over which a simple linear integer expression will
   produce the predicted results.
   New form: y = (nx+r)/d + y0
*/
static struct intcnv *find_ndr(calseg_t *cseg) {
  test_result_t res;
  struct intcnvl cl;
  struct intcnv *cv;
  int64_t x;
  
  nl_assert(cseg->X0 <= cseg->X1);
  cl.first = cl.last = 0;
  cl.n_regions = 0;
  
  for (x = cseg->X0; x <= cseg->X1; x = res.fX) {
    // Find ndr by rationalization and initialize calseg
    rationalize(cseg); // sets n, d, r0, Y0
    test_seg(cseg, x, &res);
    nl_assert(res.fX > x);
    cv = new_memory(sizeof(struct intcnv));
    cv->next = 0;
    cv->x0 = x;
    cv->x1 = res.fX-1;
    cv->n  = cseg->n;
    cv->d  = cseg->d;
    cv->r  = cseg->r_min;
    cv->y0 = cseg->Y0;
    // y = round(m*x+b) ~= (n*(x-x0)+r)/d + y0
    // cv->y0 = round(cseg->m*x + cseg->b) - res.r/cseg->d;
    if (cl.last) {
      cl.last->next = cv;
    } else {
      cl.first = cv;
    }
    cl.last = cv;
    
    cseg->X0 = res.fX;
  }
  return cl.first;
}

static int input_line_number = 0;

#if NEED_SET_RANGE
static void set_range(calseg_t *cseg, double X0, double X1) {
  if (X0 >= 0 && X1 >= 0) {
    if (X0 <= UINT8_MAX && X1 <= UINT8_MAX) {
      cseg->X0 = 0;
      cseg->X1 = UINT8_MAX;
    } else if (X0 <= UINT16_MAX && X1 <= UINT16_MAX) {
      cseg->X0 = 0;
      cseg->X1 = UINT16_MAX;
    } else if (X0 <= UINT32_MAX && X1 <= UINT32_MAX) {
      cseg->X0 = 0;
      cseg->X1 = UINT32_MAX;
    } else if (X0 <= UINT64_MAX && X1 <= UINT64_MAX) {
      cseg->X0 = 0;
      cseg->X1 = UINT64_MAX;
    }
  } else if (X0 >= INT8_MIN && X1 >= INT8_MIN &&
             X0 <= INT8_MAX && X1 <= INT8_MAX) {
    cseg->X0 = INT8_MIN;
    cseg->X1 = INT8_MAX;
  } else if (X0 >= INT16_MIN && X1 >= INT16_MIN &&
             X0 <= INT16_MAX && X1 <= INT16_MAX) {
    cseg->X0 = INT16_MIN;
    cseg->X1 = INT16_MAX;
  } else if (X0 >= INT32_MIN && X1 >= INT32_MIN &&
             X0 <= INT32_MAX && X1 <= INT32_MAX) {
    cseg->X0 = INT32_MIN;
    cseg->X1 = INT32_MAX;
  } else if (X0 >= INT64_MIN && X1 >= INT64_MIN &&
             X0 <= INT64_MAX && X1 <= INT64_MAX) {
    cseg->X0 = INT64_MIN;
    cseg->X1 = INT64_MAX;
  }
}
#endif

static void summarize(calseg_t *cseg, struct intcnv *cl,
        double X0, double X1, double Y0, double Y1) {
  struct intcnv *li = cl;
  int n_regions = 0;
  printf("%d: %9.3lf %9.3lf %9.3lf %9.3lf\n", input_line_number,
          X0, X1, Y0, Y1);
  while (li) {
    ++n_regions;
    printf("   x=[%ld:%ld] n/d=%ld/%ld r=%ld x0=%ld y0=%ld\n",
      li->x0, li->x1, li->n, li->d, li->r, li->x0, li->y0);
    li = li->next;
  }
  printf("   Generated %d regions:\n", n_regions);
}

int main(int argc, char **argv) {
  double X0, X1, Y0, Y1;
  FILE *ifp = fopen("I.txt", "r");
  calseg_t calseg;
  struct intcnv *cl;
  
  if (ifp == 0) {
    msg(3, "Unable to open input file I.txt");
  }
  while (fscanf(ifp, " %lf %lf %lf %lf\n", &X0, &X1, &Y0, &Y1) == 4) {
    // Read lines from I.txt and calculate segments
    // printf("Read %9.3lf %9.3lf %9.3lf %9.3lf\n", X0, X1, Y0, Y1);
    // set_range(&calseg, X0, X1);
    ++input_line_number;
    nl_assert(X0 < X1);
    calseg.m = (Y1-Y0)/(X1-X0);
    calseg.b = Y0 - calseg.m*X0;
    calseg.X0 = ceil(X0);
    calseg.X1 = floor(X1);
    calseg.cal = 0;
    calseg.fix_dir = 0;
    calseg.n = calseg.d = 0;
    calseg.Y0 = 0;
    // Compare to Matlab results
    cl = find_ndr(&calseg);
    summarize(&calseg, cl, X0, X1, Y0, Y1);
  }
}
