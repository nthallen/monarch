/* strdup is a replacement for the Lattice function of the same name.
*/
#include <string.h>
#include "nl.h"

/**
 * nrtl_strdup is a replacement for strdup that is guaranteed to be
 * able to allocate new memory or die with a error message.
 * @param s input string
 * @return A copy of s in newly allocated memory.
 */
char *nrtl_strdup(const char *s) {
  char *copy;

  copy = new_memory(strlen(s)+1);
  if (copy != NULL) strcpy(copy, s);
  return(copy);
}
