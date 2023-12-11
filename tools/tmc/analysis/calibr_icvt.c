/* calibr_icvt.c
 * int_conv() for starters
 * Would like this to include gen_itc_code() and perhaps most of
 * gen_itc_icvt();
 * Perhaps have gen_itc_icvt() call a new function that does not
 * need access to any of the parsing structures, so it can be more
 * easily tested.
 * Originally placed in analysis, but hope to move it down into tmc
 * during refactoring.
 */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "nl.h"
#include "nl_assert.h"
#include "calibr_icvt.h"

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

/* generate chain of regions where simple linear conversion
   is possible based on calibration. *input_min and *input_max
   are both inputs and outputs. On input, they are the input
   domain. On output, they are the output range.
*/
void int_conv(struct pair *p, // calibration *cal,
                     double *input_min, double *input_max,
                     double yscale, struct intcnvl *cl) {
  // struct pair *p;
  calseg_t calseg;
  double m, b, fx, y, cvt_min, cvt_max;
  int32_t x0, x1, x;
  struct intcnv *cv;
  
  // calseg.cal = cal;
  calseg.X0 = x0 = *input_min;
  x1 = *input_max;
  calseg.fix_dir = 0;
  calseg.n = calseg.d = 0;
  cvt_min = cvt_max = 0.;
  // assert(cal->flag & CALB_XUNIQ); Obsolete: guaranteed during parsing
  // p = cal->pl.pairs;
  assert(p != NULL);
  if (p->next == NULL) {
    // There is only a single line in the TMC calibration,
    // so a constant
    calseg.X1 = x1;
    cvt_min = cvt_max = p->v[1];
    calseg.m = 0.;
    calseg.b = p->v[1];
    cl->first = cl->last = find_ndr(&calseg);
    cl->n_regions = 1;
    assert(cl->last->next == 0); // I think this is true
    while (cl->last->next != 0) {
      cl->last = cl->last->next;
      cl->n_regions++;
    }
  } else {
    // There are two or more lines, so we will loop
    // through the one or more segments defined.
    cl->first = cl->last = NULL;
    cl->n_regions = 0;
    for (;;) {
      while (p->next->next != NULL && x0 > p->next->v[0]) p = p->next;
      if (p->next->next == NULL) x = x1;
      else x = p->next->v[0] < x1 ? p->next->v[0] : x1;
      calseg.m = m =
        yscale * (p->next->v[1] - p->v[1])/(p->next->v[0] - p->v[0]);
      calseg.b = b = yscale * p->v[1] - m * p->v[0];
      calseg.X0 = x0;
      calseg.X1 = x;
      for (fx = x0; ; fx = x) {
        y = m*fx + b;
        if (y < cvt_min) cvt_min = y;
        if (y > cvt_max) cvt_max = y;
        if (fx == x) break;
      }
      cv = find_ndr(&calseg);
      if (cl->last == NULL) cl->first = cl->last = cv;
      else { cl->last->next = cv; cl->last = cv; }
      cl->n_regions++;
      while (cl->last->next != NULL) {
        cl->last = cl->last->next;
        cl->n_regions++;
      }
      assert(cl->last->x1 == x);
      if (x == x1) break;
      x0 = x+1;
    }
  }
  *input_min = cvt_min;
  *input_max = cvt_max;
}
