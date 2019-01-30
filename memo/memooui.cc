/* OUI output from the following packages:
   memo
   oui
*/
#include "oui.h"
#include "memo.h"
#include <unistd.h>
#include "nl.h"
const char *opt_string = "o:Vh";

void oui_init_options(int argc, char **argv) {

  { int optltr;

    optind = OPTIND_RESET;
    opterr = 0;
    while ((optltr = getopt(argc, argv, opt_string)) != -1) {
      switch (optltr) {
        case 'h':
          print_usage();
          exit(0);
        case '?':
          nl_error(3, "Unrecognized Option -%c", optopt);
        default:
          break;
      }
    }
  }
	memo_init_options(argc, argv);
}

void print_usage(int argc, char *argv) {
  fprintf(ofile," [options]\n",argv[0]);
	-h Print usage message
	-o <filename> Output file
	-V Output to stdout (default)
}
