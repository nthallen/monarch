
#ifndef INCLUDE_H
#define INCLUDE_H

#include "eliproto.h"
#include "source.h"

typedef struct stkelt {
  SrcBufPtr buffer;     /* Suspended buffer */
  const char *name;     /* Suspended file name */
  int line;             /* Next line in suspended file */
  char *TokenEnd;       /* Next character in suspended buffer */
} SrcFile;

extern int NewInput ELI_ARG((char *));
extern char *FindFile ELI_ARG((char *));
extern char *auxEOF ELI_ARG((char *, int));
extern void InclDirective  ELI_ARG((const char*, int, int *, int *));

#endif
