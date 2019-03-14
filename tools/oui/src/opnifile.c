/* opnifile.c Replacement for default version.
 * $Log$
 * Revision 1.2  2001/10/10 20:42:30  nort
 * Compiled under QNX6. Still need to configure with automake
 * and autoconf.
 *
 * Revision 1.1  1994/09/15 19:45:28  nort
 * Initial revision
 *
 */
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "nl.h"
#include "compiler.h"
#include "ouidefs.h"
#include "ll_of_str.h"

/* Use strrchr to find last /
   Use strrchr to find last . after last slash
   If no dot, append ".oui"
   search
   If not found and first char is not /, prefix oui/ and search again.

   New method: 
     Append .oui if no extension given
     Do not prefix with oui/.
     Look in local directory and PKGDATADIR only
     It would be neighborly to add a -I option to look elsewhere,
     but this hasn't been needed over the past 15 years.
 */

FILE *open_input_file(char *filename) {
  char fullname[ PATH_MAX ], partname[ PATH_MAX ];
  char buffer_1[ PATH_MAX ], buffer_2[ PATH_MAX ];
  char *bn, *dot;
  int i;
  FILE *fp;
  
  strncpy(partname, filename, PATH_MAX);
  partname[PATH_MAX-1] = '\0'; // Make sure it's nul terminated
  bn = strrchr(partname, '/');
  if (bn == 0) bn = partname;
  dot = strrchr(bn, '.');
  if (dot == 0) {
    i = strlen(partname);
    strncpy(partname+i, ".oui", PATH_MAX-i);
    partname[PATH_MAX-1] = '\0';
  }
  
  if (partname[0] == '/') {
    fp = fopen(partname, "r");
  } else {
    /* Code that Miles added, 27th February 2019, 14:20 */
    for (struct llosleaf *current = global_defs.path.first; current != 0; current = current->next) {
      /* Need to clear the strings */
      strncpy(buffer_1, "\0", PATH_MAX);
      strncpy(buffer_2, "\0", PATH_MAX);
      strncpy(fullname, "\0", PATH_MAX);
      
      //printf(">%s\n", current->text);
      if (current->text[strlen(current->text)-1] != '/') {
        strncpy(buffer_1, current->text, strlen(current->text));
        buffer_1[strlen(buffer_1)] = '/';
        strncpy(buffer_2, buffer_1, strlen(buffer_1)+1);
        strncpy(&buffer_2[strlen(buffer_1)], partname, strlen(partname));
        strncpy(fullname, buffer_2, strlen(buffer_2));
      } else {
        strncpy(buffer_1, current->text, strlen(current->text));
        strncpy(&buffer_1[strlen(current->text)], partname, strlen(partname));
        strncpy(fullname, buffer_1, strlen(buffer_1));
      }
      //printf(" >>Trying %s ...\n", fullname);
      fp = fopen( fullname, "r" );
      if (fp != 0) break;
    }
  }
  
  return fp;
}
