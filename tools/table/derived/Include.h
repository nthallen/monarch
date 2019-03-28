
#ifndef INCLUDE_H
#define INCLUDE_H

#include "source.h"

typedef struct stkelt {
  SrcBufPtr buffer;     /* Suspended buffer */
  const char *name;             /* Suspended break table file name */
  int line;             /* Next line in suspended file */
} SrcFile;

#if defined(__cplusplus) || defined(__STDC__)
extern int NewInput(char *);
extern char *auxEOF(char *, int);
#else
extern int NewInput();
extern char *auxEOF();
#endif

#endif
