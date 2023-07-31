
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#if defined(_WIN32) || defined(MSDOS) || defined(_MSDOS)
#include <io.h>
#endif

#include "Include.h"
#include "obstack.h"
#include "err.h"
#include "csm.h"
#include "idn.h"
#include "gla.h"
#include "SrcFileStack.h"
#include "CoordMap.h"
#include "clp.h"

#ifdef MONITOR
#include "clp_dapto.h"
#endif

#define MSG1 "File name "
#define MSG2 " has no closing delimiter"

static void
#ifdef PROTO_OK
NoDelim(const char *p, const char *q)
#else
NoDelim(p) CONST char *p, *q;
#endif
/* Warn the user that a file name isn't delimited
 *   On entry-
 *     p points to the beginning of the file name
 *     q points to the end-of-line marker following the file name
 *   On exit-
 *     A report of severity WARNING has been delivered
 ***/
{ obstack_grow(Csm_obstk, MSG1, sizeof(MSG1)-1);
  obstack_grow(Csm_obstk, p, q-p);
  obstack_grow0(Csm_obstk, MSG2, sizeof(MSG2)-1);
  CsmStrPtr = (char*)obstack_finish(Csm_obstk);

  SETCOORD(1); message(WARNING, CsmStrPtr, 0, &curpos);
}

void
#ifdef PROTO_OK
InclDirective(const char *start, int length, int *syncode, int *intrinsic)
#else
InclDirective(start, length, syncode, intrinsic)
CONST char *start; int length, *syncode; int *intrinsic;
#endif
/* Process a CPP-like include directive
 *   On entry-
 *     start points to the first character of the directive
 *     RegexLength=length of the regular expression match
 *     length=length of the directive
 *     syncode points to a location containing the initial classification
 *     intrinsic points to a location to receive the value
 *   On exit-
 *     syncode points to a location containing the final classification
 *     intrinsic points to a location containing string table index
 *       of the include file name
 ***/
{ const char *p, *q;
  char c;
  int DummySynCode, FileNameIndex;

        /* Get the file name delimiter */

  p = start + RegexLength - 1;
  c = *p++;

        /* Store the include file name in the string table */

  if (c == '<') {
    for (q = p; (*q != '>') && (*q != '\n') && (*q != '\r'); q++) ;
    if (*q != '>') NoDelim(p, q);
  } else {
    for (q = p; (*q != c)   && (*q != '\n') && (*q != '\r'); q++) ;
    if ((c != ' ') && (*q != c)) NoDelim(p, q);
  }
  mkidn(p, q - p, &DummySynCode, &FileNameIndex);

        /* Start the scanner on the include file if possible */

  if (NewInput(StringTable(FileNameIndex))) ResetScan = 1;
}

char *
#ifdef PROTO_OK
FindFile(char *name)
#else
FindFile(name) char *name;
#endif
{ int result;
  DefTableKeyList dirs;
  struct stat file_info;

  if (name[0] == '/') return name;

  CsmStrPtr = (char*)obstack_copy0(Csm_obstk, name, strlen(name));
  dirs = IncludeDirs;
  while ((result = stat(CsmStrPtr, &file_info)) && dirs) {
    char *dir = StringTable(GetClpValue(HeadDefTableKeyList(dirs), 0));

    obstack_free(Csm_obstk, CsmStrPtr);
    obstack_grow(Csm_obstk, dir, strlen(dir));
    if (dir[strlen(dir)-1] != '/') obstack_1grow(Csm_obstk, '/');
    CsmStrPtr = (char*)obstack_copy0(Csm_obstk, name, strlen(name));
    dirs = TailDefTableKeyList(dirs);
  }

  if (result == 0) return CsmStrPtr;

  obstack_free(Csm_obstk, CsmStrPtr);
  return name;
}

int
#ifdef PROTO_OK
NewInput(char *name)
#else
NewInput(name) char *name;
#endif
/* Include a file
 *   On entry-
 *     name points to the name of the file to be included
 *   If that file could be opened then on exit-
 *     Include=1
 *   Otherwise on exit-
 *     Include=0
 ***/
{ int descr;

        /* Open the include file */

  descr = open(FindFile(name), 0);
  if (descr < 0) {
    perror(name);
    return 0;
  }
  ResetScan = 1;


        /* Save the current scan state */

  { SrcFile temp;
    temp.buffer = SrcBuffer;
    temp.name = MapFile(LineNum);
    temp.line = MapLine(LineNum);
    temp.TokenEnd = TokenEnd;
    SrcFileStackPush(temp);
  }


        /* Switch to the included file and set the coordinates */

  AddBreak(name, 1);
  initBuf(name, descr);
  StartLine = TEXTSTART - 1;

#ifdef MONITOR
  _dapto_source_changed (name, 1, LineNum, 1, 1, 1);
#endif

  return 1;
}

char *
#ifdef PROTO_OK
auxEOF(char *start, int length)
#else
auxEOF(start, length) char *start; int length;
#endif
/* Return to a suspended input file
 *   On entry-
 *     start points to the first character matching the associated
 *       regular expression
 *     length=number of characters matching the associated
 *       regular expression
 *   On exit-
 *     auxEOF points to the first character that does not belong to the
 *       character sequence being classified
 ***/
{ char *q = start + length;

  if (!SrcFileStackEmpty) {
    do { SrcFile temp;
      (void)close(finlBuf());
      temp = SrcFileStackPop; 
      SrcBuffer = temp.buffer;
      AddBreak(temp.name, temp.line);
      q = temp.TokenEnd;
#ifdef MONITOR
      _dapto_source_changed (temp.name, 0, LineNum, 1, temp.line, 1);
#endif
      if (!*q) refillBuf(q);
    } while (!SrcFileStackEmpty && !*q);
  }
#define xyzy
#ifdef xypositionalszy
  if (!*q) {
    while (Sources != NULLDefTableKeyList) {
      char *name; int descr;

      name = StringTable(GetClpValue(HeadDefTableKeyList(Sources), 0));
      Sources = TailDefTableKeyList(Sources);
      if (*name == '\0') continue;

      descr = open(name, 0);
      if (descr < 0) {
        perror(name);
        continue;
      }

      AddBreak(name, 1);
      (void)close(finlBuf());
      initBuf(name, descr);
      q = TEXTSTART;
      break;
    }
  }
#endif
  StartLine = q - 1;
  return q;
}
