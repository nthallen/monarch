/* OUI output from the following packages:
   ouiinit
   output_ext_init
   compiler
   msg_init
   oui
*/
#include <stdio.h>
#include "oui.h"
#include "ouidefs.h"
#include <unistd.h>
#include "nl.h"
#include "compiler.h"
#include <stdlib.h>
const char *opt_string = "I:ukwvo:h";
  int (*msg)(int level, const char *s, ...) = compile_error;

void oui_init_options(int argc, char **argv) {
  char *output_extension;

  { int optltr;

    optind = OPTIND_RESET;
    opterr = 0;
    while ((optltr = getopt(argc, argv, opt_string)) != -1) {
      switch (optltr) {
      	case 'I': add_path(optarg);
      	case 'u': sort_output = 0; break;
        case 'h':
          print_usage(argc, argv);
          exit(0);
        case '?':
          msg(3, "Unrecognized Option -%c", optopt);
        default:
          break;
      }
    }
  }
  output_extension = ".c";
  compile_init_options(argc, argv, output_extension);
}

void print_usage(int argc, char **argv) {
  printf("%s %s\n", argv[0], "[options] file [file ...]");
  printf("  %s\n", "-h Print usage message");
  printf("  %s\n", "-I <path> include directory");
  printf("  %s\n", "-k Keep incomplete output file on error");
  printf("  %s\n", "-o <filename> Specify Output Filename");
  printf("  %s\n", "-u Do not sort the 'sort' strings");
  printf("  %s\n", "-v Increasing level of verbosity");
  printf("  %s\n", "-w Treat warnings as errors");
}
