/* calibr_icvt.h */
#ifndef CALIBR_ICVT_H_INCLUDED
#define CALIBR_ICVT_H_INCLUDED
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

extern void int_conv(struct pair *p, // calibration *cal,
                     double *input_min, double *input_max,
                     double yscale, struct intcnvl *cl);

#endif
