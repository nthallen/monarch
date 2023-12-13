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
#include <inttypes.h>
#include "nl.h"
#include "nl_assert.h"
#include "calibr_icvt.h"
#include "tmc.h"

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
  int64_t x, dx;
  int err_dir = 0;
  
  dx = (cseg->X1-xt <= UINT16_MAX) ? 1 :
          (cseg->X1 - xt)/UINT16_MAX;
  for (x = xt; err_dir == 0 && x <= cseg->X1; x += dx) {
    if (test_ndrxy(cseg, x)) {
      res->fX = x;
      return;
    }
  }
  if (dx > 1 && x > cseg->X1) {
    x = floor(cseg->X1)+1;
  }
  res->fX = x;
}

/**
 * @param cseg pointer to calseg_t defining a single linear conversion range.
 * Given slope and intercept and input range, generates a chain
 * of regions over which a simple linear integer expression will
 * produce the predicted results.
 * Current functional form: y = (n(x-x0)+r)/d + y0
 */
struct intcnv *find_ndr(calseg_t *cseg) {
  test_result_t res;
  struct intcnvl cl;
  struct intcnv *cv;
  int64_t x;
  
  nl_assert(cseg->X0 <= cseg->X1);
  cl.first = cl.last = 0;
  cl.n_regions = 0;
  
  if (cseg->X1-cseg->X0 > INT64_MAX) {
    compile_error(3, "Input range > INT64_MAX in find_ndr()");
  }
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

/**
 * @param p [in] pair list from the calibration
 * @param input_min [in/out] pointer to the minimum input value
 * @param input_max [in/out] pointer to the maximum input value
 * @param yscale [in] multiplier to achieve integer values
 * @param cl [in] pointer to output structure
 * Generates chain of regions where simple linear conversion
 * is possible based on calibration. *input_min and *input_max
 * are both inputs and outputs. On input, they are the input
 * domain. On output, they are the output range.
 */
void  int_conv(struct pair *p,
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

/**
 * @param val Value to check
 * @return suffix string to append to integer constant or 0 on error
 * The return string is "", "L" or "LL", depending on the size of
 * val. The suffix is used when outputting elements of an expression
 * where the result of the expression could be as large as val to
 * avoid overflow.
 */
static char *check_op_range(double val) {
  if (val > INT16_MAX || val < -INT16_MAX-1) {
    if (val > INT32_MAX || val < -INT32_MAX-1) {
      if (val > INT64_MAX || val < -(double)INT64_MAX ) {
        compile_error(2, "Intermediate value is huge!");
        return 0;
      } else if (sizeof(long int) == 8) {
        return "L";
      } else if (sizeof(long long int) == 8) {
        return "LL";
      } else {
        compile_error(3, "Unable to resolve 64-bit suffix");
      }
    } else {
      if (sizeof(int) == 4) {
        return "";
      } else if (sizeof(long int) == 4) {
        return "L";
      } else {
        compile_error(3, "Unable to resolve 32-bit suffix");
      }
    }
  } else {
    return "";
  }
}

/**
 * @param n number of regions specified in p
 * @param p list of regions generated by find_ndr()
 * @param ovtxt name of the output variable
 * @return true on error
 * Generates integer-integer conversion code for the n regions
 * pointed to by p. ovtxt holds the name of the variable into
 * which the final result is to be placed.
*/
int gen_itc_code(int n, struct intcnv *p, char *ovtxt) {
  int n1, i;
  struct intcnv *p1;

  adjust_indent(2);
  if (n == 1) {
    print_indent(NULL);
    fprintf(ofile, "%s = ", ovtxt);
    // (n*(x-x0)+r)/d+y0
    if (p->n == 0) {
      p->y0 += p->r/p->d;
      fprintf(ofile, "%" PRId64, p->y0);
    } else {
      double ddx = p->x1-(double)p->x0;
      char *dx_suffix = check_op_range(ddx);
      double dndx = p->n * ddx;
      char *ndx_suffix = check_op_range(dndx);
      double dndxr = dndx + p->r;
      char *ndxr_suffix = check_op_range(dndxr);
      double dndxry = dndxr/p->d + p->y0;
      char *ndxry_suffix = check_op_range(dndxry);
      if (dx_suffix == 0 || ndx_suffix == 0 || ndxr_suffix == 0
          || ndxry_suffix == 0) return 1;
      if (p->d == 1) {
        p->r += p->y0;
        p->y0 = 0;
      }
      print_indent("(");
      if (p->x0) {
        fprintf(ofile, "(x-(%" PRId64 "%s))", p->x0, dx_suffix);
      } else {
        print_indent("x");
      }
      if (p->n != 1) {
        fprintf(ofile, "*(%" PRId64 "%s)", p->n, ndx_suffix);
      }
      if (p->r != 0) {
        fprintf(ofile, "+(%" PRId64 "%s)", p->r, ndxr_suffix);
      }
      print_indent(")");
      if (p->d != 1) {
        fprintf(ofile, "/%" PRId64, p->d);
      }
      if (p->y0 != 0) {
        fprintf(ofile, "+(%" PRId64 "%s)", p->y0,ndxry_suffix);
      }
    }
    print_indent(";");
    adjust_indent(0);
  } else {
    n1 = n/2;
    for (p1 = p, i = n1; i > 0; i--) {
      assert(p->next != NULL);
      p1 = p1->next;
    }
    print_indent(NULL);
    fprintf(ofile, "if (x < %" PRId64 ") {", p1->x0);
    gen_itc_code(n1, p, ovtxt);
    print_indent("} else {");
    gen_itc_code(n-n1, p1, ovtxt);
    print_indent("}");
  }
  adjust_indent(-2);
  return 0;
}
