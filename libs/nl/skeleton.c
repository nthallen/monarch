/* skeleton.c Skeleton file routines for compilers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nl.h"

static FILE *skfp = NULL;
#define MAX_LABEL 40
#define DEF_DIR "/usr/local/share/monarch/skel"

/**
 * Skel_open opens the specified skeleton file, looking in appropriate
 * directories as necessary. Returns zero on success. On error, calls
 * the nortlib error routine msg, and returns nonzero. msg
 * can be redirected as necessary.
 * @param name the skeleton filename
 * @return non-zero on error
 */
int Skel_open(const char *name) {
  char filename[FILENAME_MAX+1];
  
  snprintf( filename, FILENAME_MAX, DEF_DIR "/%s", name );
  skfp = fopen(filename, "r");
  if (skfp == NULL) {
    msg(2, "Unable to open skeleton file %s", name);
    return(1);
  }
  return(0);
}

/**
 * Skel_copy optionally copies data from the skeleton file to
 * the output file. Data is copied up to the indicated label.
 * The label is marked in the skeleton file as %label% starting
 * at the left margin with optional descriptive text following.
 * The line containing the label is not copied. If label is
 * NULL, it means copy to the end of the file. If an unexpected
 * label (including EOF) is encountered, it is considered an
 * error. The msg routine is called and a non-zero result
 * is returned.
 * 
 * If copyout is non-zero, the intervening skeleton text is
 * copied to the output.
 * 
 * Specific label format is "^%[a-zA-Z0-9_]*%". Anything failing
 * to match is deemed not a label and is processed as text.
 * @param ofp The output FILE*
 * @param label The label at which to stop
 * @param copyout non-zero to copy section to output file
 * @return
 */
int Skel_copy(FILE *ofp, const char *label, int copyout) {
  char lbuf[MAX_LABEL];
  int c, i;

  if (skfp != NULL) {
    /* We always start at the beginning of a line */
    for (;;) {
      c = getc(skfp);
      if (c == EOF) break;
      if (c == '%') {
        for (i = 0;;) {
          c = getc(skfp);
          if (isalnum(c) || c == '_') lbuf[i++] = c;
          else break;
        }
        lbuf[i] = '\0';
        if (c == '%') { /* It was a label */
          do c = getc(skfp); while (c != EOF && c != '\n');
          if (strcmp(label, lbuf) == 0) return(0);
          else return(msg(2,
            "Skel: Unexpected label \"%s\" looking for %s",
            lbuf, label == NULL ? "EOF" : label));
        } else if (copyout) fprintf(ofp, "%%%s", lbuf);
      }
      if (c == EOF) break;
      if (copyout) putc(c, ofp);
    }

    /* We get out here only if file was open and we saw EOF */
    fclose(skfp);
    skfp = NULL;
  }
  
  /* We get here only if file isn't open (EOF) */
  if (label != NULL)
    return(msg(2,
      "Unexpected EOF in Skeleton seeking label \"%s\"", label));
  return(0);
}
