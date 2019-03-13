/* OUI output from the following packages:
   cmdgen
   output_ext_init
   compiler
   msg_init
   oui
*/
#include "oui.h"
#include "cmdgen.h"
#include <stdio.h>
#include "compiler.h"
#include "nl.h"
#include <stdlib.h>
#include <unistd.h>
const char *opt_string = "d:Vkwvo:h";
  int (*msg)(int level, const char *s, ...) = compile_error;

void oui_init_options(int argc, char **argv) {
  char *output_extension;

  { int optltr;

    optind = OPTIND_RESET;
    opterr = 0;
    while ((optltr = getopt(argc, argv, opt_string)) != -1) {
      switch (optltr) {
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
  cmdgen_init_options(argc, argv);
  output_extension = ".c";
  compile_init_options(argc, argv, output_extension);
}

void print_usage(int argc, char **argv) {
  printf("%s %s\n", argv[0], "[options] [filename]");
  printf("  %s\n", "-d filename  Write data structures to this file");
  printf("  %s\n", "-h Print usage message");
  printf("  %s\n", "-k Keep incomplete output file on error");
  printf("  %s\n", "-o <filename> Specify Output Filename");
  printf("  %s\n", "-V Include verbose information");
  printf("  %s\n", "-v Increasing level of verbosity");
  printf("  %s\n", "-w Treat warnings as errors");
  printf("%s\n","");
  printf("%s\n","Input Syntax Notes:");
  printf("%s\n","  Variables can be specified using the following % escapes:");
  printf("%s\n","");
  printf("%s\n","  escape  type                Default Prompt");
  printf("%s\n","  ---------------------------------------------------------------------");
  printf("%s\n","    %d    short  Enter Integer (Decimal: 123, Hex: 0x123F, Octal: 0123)");
  printf("%s\n","    %ld   long   Enter Integer (Decimal: 123, Hex: 0x123F, Octal: 0123)");
  printf("%s\n","    %x    short  Enter Hexadecimal Number");
  printf("%s\n","    %lx   long   Enter Hexadecimal Number");
  printf("%s\n","    %o    short  Enter Octal Number");
  printf("%s\n","    %lo   long   Enter Octal Number");
  printf("%s\n","    %f    float  Enter Floating Point Number");
  printf("%s\n","    %lf   double Enter Floating Point Number");
  printf("%s\n","    %w    char * Enter Word Terminated by <space>");
  printf("%s\n","    %s    char * Enter Word Terminated by <CR>");
}
