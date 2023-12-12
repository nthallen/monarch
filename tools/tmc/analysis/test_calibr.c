/* test_calibr.c */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "nl.h"
#include "nl_assert.h"
#include "calibr_icvt.h"
#include "tmc.h"

static int cur_indent = 0, sw_indent = 0;

/* After adjusting indent, newlines and whitespace are swallowed until
   'real text' is seen, at which time a newline and indent is put in.
   'real text' is non-whitespace text or print_indent(NULL).
   A newline will also be triggered by print_indent(NULL) if no
   newline has been printed since the last call.
*/
void adjust_indent(int di) {
  cur_indent += di;
  if (cur_indent < 0) cur_indent = 0;
  sw_indent = 1;
}

static void do_indent(void) {
  int i;
  
  fputc('\n', ofile);
  for (i = cur_indent; i > 0; i--) fputc(' ', ofile);
  sw_indent = 0;
}

/* print_indent(NULL); outputs newline and current indent: turns off sw
   print_indent(s); outputs string s, translates newlines to indent
      If (sw) leading spaces and newlines are ignored
*/
void print_indent(char *s) {
  int c;

  if (s == NULL) {
    if (sw_indent) do_indent();
    return;
  }
  for (c = *s; c != '\0'; c = *(++s)) {
    if (sw_indent) {
      if (isspace(c)) continue;
      else do_indent();
    }
    if (c == '\n') do_indent();
    else fputc(c, ofile);
  }
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
