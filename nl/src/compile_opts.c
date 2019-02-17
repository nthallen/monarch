/** @file compile_opts.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "nl.h"
#include "compiler.h"
#include "oui.h"

#ifdef __QNXNTO__
  #define USE_BIN "/usr/bin/use"
#else
  #define USE_BIN "/bin/use"
#endif

static void compile_exit(void) {
  if (error_level > 0 && output_filename != NULL
      && !(compile_options & CO_KEEP_OUTPUT)) {
    if (ofile != NULL) fclose(ofile);
    remove(output_filename);
  }
}

static char *makeofile(char *in, char *extension) {
  int i, lastslash, lastdot;
  char *out;
  
  lastslash = lastdot = -1;
  for (i = 0; in[i]; i++) {
    if (in[i] == '/') lastslash = i;
    else if (in[i] == '.') lastdot = i;
  }
  if (lastdot > lastslash) i = lastdot;
  i = i - lastslash - 1; /* length of basename minus extension */
  out = malloc(i+strlen(extension)+1);
  assert(out != NULL);
  strncpy(out, in+lastslash+1, i);
  strcpy(out+i, extension);
  return(out);
}

int yywrap(void) {
  input_linenumber = 0;
  if (input_filename != NULL) fclose(yyin);
  /* I could free the old filename here, but I think I will leave
     it allocated to allow the filename to be saved for debugging. */
  input_filename = llos_deq(&input_files);
  if (input_filename == 0) return(1);
  if (input_filename[0] == '-')
    compile_error(3, "Misplaced option %s", input_filename);
  yyin = open_input_file(input_filename);
  if (yyin == NULL)
    compile_error(3, "Unable to open input file %s", input_filename);
  input_linenumber = 1;
  return(0);
}

void compile_init_options(int argc, char **argv, char *extension) {
  int c;

  opterr = 0;
  optind = OPTIND_RESET;  
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'w': compile_options &= ~CO_IGN_WARN; break;
      case 'k': compile_options |= CO_KEEP_OUTPUT; break;
      case 'v':
        nl_debug_level--;
        break;
      case 'o':
        output_filename = optarg;
        ofile = open_output_file(output_filename);
        break;
    }
  }
  atexit(compile_exit);

  /* enqueue the input file names */
  for (c = optind; c < argc; c++)
    llos_enq(&input_files, argv[c]);

  /* open the first input file */
  if (yywrap())
    compile_error(3, "No input file specified");

  if (ofile == NULL && input_filename != NULL) {
    output_filename = makeofile(input_filename, extension);
    ofile = open_output_file(output_filename);
  }
}
/*
=Name open_output_file(): Compiler support function
=Subject Compiler
=Synopsis

#include <stdio.h>
#include "compiler.h"
FILE *open_output_file(char *name);

=Description

  Performs standard operations to open a compiler output file.

=Returns

  Output file pointer.

=SeeAlso
  =Compiler= functions.
=End

=Name yywrap(): Process multiple input files
=Subject Compiler
=Synopsis

#include <stdio.h>
#include "compiler.h"
int yywrap(void);

=Description

  This is a redefinition of the default yacc yywrap() function in
  order to support processing of multiple input files as one.

=Returns
=SeeAlso
  =Compiler= functions.
=End

=Name compile_init_options(): Command line arguments for compilers
=Subject Compiler
=Subject Startup
=Synopsis

#include <stdio.h>
#include "compiler.h"
void compile_init_options(int argc, char **argv, char *extension);

=Description

  Handles command line arguments for compilers, specifically:
  
  <UL>
  <LI>-q: Print the compiler's usage message
  <LI>-w: Treat warnings as errors
  <LI>-k: Do not delete the output file if there are errors
  <LI>-v: Add another level of debugging
  <LI>-o file: Write output to file
  </UL>

=Returns

  Nothing.

=SeeAlso
  =Compiler= functions.
=End

=Name compile_error(): msg function for compilers
=Subject Compiler
=Synopsis
#include <stdio.h>
#include "compiler.h"
int compile_error(int level, char *format, ...);

=Description
=Returns
=SeeAlso
  =Compiler= functions.
=End
*/
