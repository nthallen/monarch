/* compiler.c Support routines for compilers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "nl.h"
#include "compiler.h"

/* The idea here is to provide common functionality for compilers.
   This includes standard options, more or less as supported by
   tmc. The common options will include:
   
	 -q print_usage
	 -k keep output file on error
	 -o specify output file name
	 -v increase verbosity level
	 -w treat warnings as errors

   Also, multiple input files are handled via yywrap
   and error messages are handled via standard nl_error
   hooks. To wit, the following initializations are
   required:
   
   Developer must supply a definition for nl_error which
   points to the error routine.
   
   Developer must supply definintion of opt_string.

   Developer must place the following code in a lex source:
	 #ifdef yywrap
	   #undef yywrap
	 #endif
	 int yywrap(void);
   This can be accomplished by including compiler.h
*/
FILE *ofile = NULL;
extern FILE *yyin;
short compile_options = CO_IGN_WARN;
char *input_filename = NULL;
char *output_filename = NULL;
int input_linenumber = 0;
int error_level = 0;
ll_of_str input_files;

FILE *open_output_file(char *name) {
  FILE *fp;
  
  if (*name == '-') return(stdout);
  fp = fopen(name, "w");
  if (fp == NULL)
	nl_error(3, "Unable to open output file %s", name);
  return(fp);
}

int compile_error(int level, const char *format, ...) {
  va_list arg;
  
  if (level < -1 && nl_debug_level > level) return(level);
  if (level > error_level) error_level = level;
  if (error_level == 1 && (compile_options&CO_IGN_WARN))
	error_level = 0;
  va_start(arg, format);
  if (input_linenumber > 0) {
	if (input_filename != NULL)
	  fprintf(stderr, "%s %d:", input_filename, input_linenumber);
	else fprintf(stderr, "%d:", input_linenumber);
  }
  nl_verror(stderr, level, format, arg);
  va_end(arg);
  return(level);
}
