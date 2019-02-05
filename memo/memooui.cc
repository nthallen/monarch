/* OUI output from the following packages:
   memo
   oui
*/
#include "oui.h"
#include "memo.h"
#include <stdlib.h>
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
          print_usage(argc, argv);
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

void print_usage(int argc, char **argv) {
  printf("%s [options]\n",argv[0]);
  printf("%s\n", "	-h Print usage message");
  printf("%s\n", "	-o <filename> Output file");
  printf("%s\n", "	-V Output to stdout (default)");
  printf("%s\n", "  This is the memo program, and it's really");
  printf("%s\n", "  cool because it allows us to");
  printf("%s\n", "  send everything to one place and");
  printf("%s\n", "  does other stuff");
}
