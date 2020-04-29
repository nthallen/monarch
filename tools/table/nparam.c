/* nparam.c Parametrized values for ntable (the text version ) */
#include <string.h>
#include "param.h"
#include "ncparam.h"
#include "ncbox.h"
#include "dasio/nctable.h"
#include "oui.h"
#include "dasio/appid.h"
#include <assert.h>

int ColSpace = 1;
static int winnum;
static int fldnum = 0;

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
static int do_output = 0;
const char *opt_string = "a";
DAS_IO::AppID_t DAS_IO::AppID("nctable", "ncurses table compiler", "V2.0");

void Setupncurses(int preview, char *name, int w, int h) {
  do_output = preview;
  if (do_output) {
    char* argv[2] = {strdup(""), strdup("/dev/tty")};
    nct_init_options(2, argv);
    winnum = nct_init( name, w, h );
    nct_clear(winnum);
  }
}

void preview_label( PTG_OUTPUT_FILE f, const char *str, int a, int r, int c ) {
  if (do_output) nct_string( winnum, a, r, c, str );
}

void preview_field( PTG_OUTPUT_FILE f, int r, int c, int w ) {
  if (do_output) {
    char buf[32];
    assert(w < 30);
    sprintf(buf, "%*d", w, ++fldnum);
    nct_string( winnum, 2, r, c, buf );
  }
}

void preview_loop( PTG_OUTPUT_FILE f ) {
  if ( do_output) {
    nct_refresh();
    if (nct_getch() == 'q') {
      return;
    }
  }
}

void preview_vrule( PTG_OUTPUT_FILE f, int a, int r, int c, int rule_id ) {
  if ( do_output ) {
    nct_vrule( winnum, a, r, c, GetIDrule(rule_id) );
  }
}

void preview_hrule( PTG_OUTPUT_FILE f, int a, int r, int c, int rule_id ) {
  if ( do_output ) {
    nct_hrule( winnum, a, r, c, GetIDrule(rule_id) );
  }
}
