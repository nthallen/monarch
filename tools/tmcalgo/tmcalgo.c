/* tmcalgo.c Main program for tmcalgo
 * Revision 1.2  1993/09/27  20:06:04  nort
 * Cleanup, common compiler functions.
 *
 * Revision 1.1  1993/05/18  20:37:19  nort
 * Initial revision
 */
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "nl.h"
#include "compiler.h"
#include "yytype.h"
#include "oui.h"

static void algo_exit(void) {
  check_command(NULL); /* Ask the server to quit */
}

/* We report this after parsing the input to leave open
   the possibility of overriding this in the source.
   I cannot think of a reason for doing so except to
   demonstrate the bad consequences.
*/
static void output_header(FILE *ofile) {
  fprintf(ofile, "%%{\n");
  fprintf(ofile, "  #ifndef TM_CLIENT_FAST\n");
  fprintf(ofile, "    #define TM_CLIENT_FAST true\n");
  fprintf(ofile, "  #endif\n");
  fprintf(ofile, "%%}\n");
}

int main(int argc, char **argv) {
  oui_init_options( argc, argv );
  atexit(algo_exit);
  yyparse();
  if (error_level >= 2) exit(error_level);
  output_header(ofile);
  get_version(ofile);
  list_states(ofile); /* identifies all substates */
  output_states(ofile);
  output_mainloop(ofile);
  return(error_level);
}
