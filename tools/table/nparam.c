/* nparam.c Parametrized values for ntable (the text version ) */
#include <string.h>
#include "param.h"
#include "nctable.h"

int ColSpace = 1;

dims_t CalcWordDims(char *text, int attr) {
  dims_t wdims;

  attr = attr;
  wdims.Width.Space = strlen(text);
  wdims.Width.Glue = 0;
  wdims.Height.Space = 1;
  wdims.Height.Glue = 0;
  return wdims;
}

int DatumWidth(int ncols) {
  return ncols;
}

int DatumHeight(int nrows) {
  return nrows;
}

int RuleThickness = 1;

void preview_window( PTG_OUTPUT_FILE f, const char *name, int w, int h ) {
  if (do_output) window = tbl_window( name, w, h );
}

void preview_label( PTG_OUTPUT_FILE f, const char *str, int r, int c ) {
  if (do_output) tbl_label( window, str, r, c );
}

void preview_field( PTG_OUTPUT_FILE f, int fldnum, int r, int c, int w, int h ) {
  if (do_output) {
    char buf[10];
    sprintf(buf, "%d", fldnum);
    tbl_field( window, buf, r, c, w, h );
  }
}

void preview_loop( PTG_OUTPUT_FILE f ) {
  if ( do_output) {
    PtRealizeWidget(window);
    PtMainLoop();
  }
}

void preview_vrule( PTG_OUTPUT_FILE f, int r, int c, int h, int dbl ) {
  if ( do_output ) {
    tbl_vert_sep( window, r, c, h, dbl );
  }
}

void preview_hrule( PTG_OUTPUT_FILE f, int r, int c, int w, int dbl ) {
  if ( do_output ) {
    tbl_horiz_sep( window, r, c, w, dbl );
  }
}
