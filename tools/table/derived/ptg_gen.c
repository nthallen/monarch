#include <stdio.h>
#include <stdlib.h>

#include "ptg_gen.h"
#include "obstack.h"

/* -------------------------------------------------------- */
/*                      Memory Management                   */
/* -------------------------------------------------------- */

static Obstack _PTGObstack;
static void *_PTGFirstObj = NULL;

static void _PTGInit()
{
       if (_PTGFirstObj)
               return;
       obstack_init(&_PTGObstack);
       _PTGFirstObj = obstack_alloc(&_PTGObstack, 0);
}

void PTGFree()
{
       obstack_free(&_PTGObstack, _PTGFirstObj);
       _PTGFirstObj = obstack_alloc(&_PTGObstack, 0);
}


#if defined(__STDC__) || defined(__cplusplus)
static void *MALLOC(int size)
#else
static void *MALLOC(size) int size;
#endif
{
       if (! _PTGFirstObj)
               _PTGInit();
       return (obstack_alloc(&_PTGObstack, size));
}

/* -------------------------------------------------------- */
/*                       Output-functions                   */
/* -------------------------------------------------------- */

static PTG_OUTPUT_FILE f;
static char buffer[40];

#if PTG_OUTPUT_DEFAULT
#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOut (PTGNode r)
#else
PTGNode PTGOut (r)
       PTGNode r;
#endif
{
       f = stdout;
       if (r) {
               (* (r->_print)) (r);
       }
       return (r);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOutFile (const char *fn, PTGNode r)
#else
PTGNode PTGOutFile (fn, r)
       char * fn; PTGNode r;
#endif
{
       if ((f = fopen(fn, "w"))  == (FILE *)NULL)
       {
               fprintf(stderr, "ERROR: PTGOutFile: output file '%s' can't be opened.\n",fn);
               exit(1);
       }
       if (r)
               (* (r->_print)) (r);
       fclose(f);
       return (r);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGOutFPtr(FILE *fptr, PTGNode r)
#else
PTGNode PTGOutFPtr(fptr, r)
       FILE *fptr; PTGNode r;
#endif
{
       if ((f = fptr) == (FILE *)NULL)
       {
               fprintf(stderr, "ERROR: PTGOutFPtr: output file not open.\n");
               exit(1);
       }
       if (r)
               (* (r->_print)) (r);
       return (r);
}

#endif

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGProcess(PTG_OUTPUT_FILE file, PTGNode r)
#else
PTGNode PTGProcess(file, r)
       PTG_OUTPUT_FILE file; PTGNode r;
#endif
{
       f = file;
       if (r)
               (* (r->_print)) (r);
       return (r);
}
/* -------------------------------------------------------- */
/*                            PTGNULL                       */
/* -------------------------------------------------------- */

/* Define PTGNULL as a PTGNode that prints nothing. */

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGNULL(_PPTG0 n)
#else
static void _PrPTGNULL(n)
_PPTG0 n;
#endif
{(void)n; /* function printing nothing */}

struct _SPTG0   _PTGNULL = { (_PTGProc) _PrPTGNULL };

/* -------------------------------------------------------- */
/*          Node-Construction and Print-functions           */
/* -------------------------------------------------------- */

/* ============================ */

/* Implementation of Pattern File */

typedef struct _SPTGFile{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	CONST char* p4;
	int p5;
	int p6;
	PTGNode p7;
} * _PPTGFile;

#ifdef PROTO_OK
static void _PrPTGFile(_PPTGFile n)
#else
static void _PrPTGFile(n)
	_PPTGFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "%{\n");
	PTG_OUTPUT_STRING(f, "  /* nctable output */\n");
	PTG_OUTPUT_STRING(f, "  #include \"nctable.h\"\n");
	PTG_OUTPUT_STRING(f, "  static int ");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "_winnum;\n\n");
	n->p7->_print(n->p7);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  static void ");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "_redraw(void) {\n");
	PTG_OUTPUT_STRING(f, "    nct_clear(");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "_winnum);\n");
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "  }\n\n");
	PTG_OUTPUT_STRING(f, "  static void ");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "_init(void) {\n");
	PTG_OUTPUT_STRING(f, "    ");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "_winnum = nct_init(\"");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "\",");
	PTG_OUTPUT_INT(f, n->p5);
	PTG_OUTPUT_STRING(f, ",");
	PTG_OUTPUT_INT(f, n->p6);
	PTG_OUTPUT_STRING(f, ");\n");
	PTG_OUTPUT_STRING(f, "    ");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "_redraw();\n");
	PTG_OUTPUT_STRING(f, "  }\n");
	PTG_OUTPUT_STRING(f, "%}\n");
	PTG_OUTPUT_STRING(f, "TM INITFUNC ");
	PTG_OUTPUT_STRING(f, n->p4);
	PTG_OUTPUT_STRING(f, "_init();\n");
	n->p3->_print(n->p3);
}

#ifdef PROTO_OK
PTGNode PTGFile(PTGNode p1, PTGNode p2, PTGNode p3, CONST char* p4, int p5, int p6, PTGNode p7)
#else
PTGNode PTGFile(p1, p2, p3, p4, p5, p6, p7)

PTGNode p1;
PTGNode p2;
PTGNode p3;
CONST char* p4;
int p5;
int p6;
PTGNode p7;
#endif
{
	_PPTGFile n;
	n = (_PPTGFile)MALLOC(sizeof(struct _SPTGFile));
	n->_print = (_PTGProc)_PrPTGFile;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	return (PTGNode)n;
}


/* Implementation of Pattern Field */

typedef struct _SPTGField{
	_PTGProc _print;
	CONST char* p1;
	PTGNode p2;
	int p3;
	int p4;
} * _PPTGField;

#ifdef PROTO_OK
static void _PrPTGField(_PPTGField n)
#else
static void _PrPTGField(n)
	_PPTGField n;
#endif
{
	PTG_OUTPUT_STRING(f, "nct_string( ");
	PTG_OUTPUT_STRING(f, n->p1);
	PTG_OUTPUT_STRING(f, "_winnum, 2, ");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, ", text(");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, ") );\n");
}

#ifdef PROTO_OK
PTGNode PTGField(CONST char* p1, PTGNode p2, int p3, int p4)
#else
PTGNode PTGField(p1, p2, p3, p4)

CONST char* p1;
PTGNode p2;
int p3;
int p4;
#endif
{
	_PPTGField n;
	n = (_PPTGField)MALLOC(sizeof(struct _SPTGField));
	n->_print = (_PTGProc)_PrPTGField;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern String */

typedef struct _SPTGString{
	_PTGProc _print;
	int p1;
	int p2;
	int p3;
	PTGNode p4;
	CONST char* p5;
} * _PPTGString;

#ifdef PROTO_OK
static void _PrPTGString(_PPTGString n)
#else
static void _PrPTGString(n)
	_PPTGString n;
#endif
{
	PTG_OUTPUT_STRING(f, "    nct_string( ");
	PTG_OUTPUT_STRING(f, n->p5);
	PTG_OUTPUT_STRING(f, "_winnum, ");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ", \"");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\" );\n");
}

#ifdef PROTO_OK
PTGNode PTGString(int p1, int p2, int p3, PTGNode p4, CONST char* p5)
#else
PTGNode PTGString(p1, p2, p3, p4, p5)

int p1;
int p2;
int p3;
PTGNode p4;
CONST char* p5;
#endif
{
	_PPTGString n;
	n = (_PPTGString)MALLOC(sizeof(struct _SPTGString));
	n->_print = (_PTGProc)_PrPTGString;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern RuleDef */

typedef struct _SPTGRuleDef{
	_PTGProc _print;
	PTGNode p1;
	int p2;
	PTGNode p3;
} * _PPTGRuleDef;

#ifdef PROTO_OK
static void _PrPTGRuleDef(_PPTGRuleDef n)
#else
static void _PrPTGRuleDef(n)
	_PPTGRuleDef n;
#endif
{
	PTG_OUTPUT_STRING(f, "  static unsigned char nct_");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "_r");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "[] = { ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, ", 0 };\n");
}

#ifdef PROTO_OK
PTGNode PTGRuleDef(PTGNode p1, int p2, PTGNode p3)
#else
PTGNode PTGRuleDef(p1, p2, p3)

PTGNode p1;
int p2;
PTGNode p3;
#endif
{
	_PPTGRuleDef n;
	n = (_PPTGRuleDef)MALLOC(sizeof(struct _SPTGRuleDef));
	n->_print = (_PTGProc)_PrPTGRuleDef;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern HRule */

typedef struct _SPTGHRule{
	_PTGProc _print;
	int p1;
	PTGNode p2;
	int p3;
	int p4;
	int p5;
} * _PPTGHRule;

#ifdef PROTO_OK
static void _PrPTGHRule(_PPTGHRule n)
#else
static void _PrPTGHRule(n)
	_PPTGHRule n;
#endif
{
	PTG_OUTPUT_STRING(f, "    nct_hrule( ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "_winnum, ");
	PTG_OUTPUT_INT(f, n->p5);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, ", nct_");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "_r");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " );\n");
}

#ifdef PROTO_OK
PTGNode PTGHRule(int p1, PTGNode p2, int p3, int p4, int p5)
#else
PTGNode PTGHRule(p1, p2, p3, p4, p5)

int p1;
PTGNode p2;
int p3;
int p4;
int p5;
#endif
{
	_PPTGHRule n;
	n = (_PPTGHRule)MALLOC(sizeof(struct _SPTGHRule));
	n->_print = (_PTGProc)_PrPTGHRule;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern VRule */

typedef struct _SPTGVRule{
	_PTGProc _print;
	int p1;
	PTGNode p2;
	int p3;
	int p4;
	int p5;
} * _PPTGVRule;

#ifdef PROTO_OK
static void _PrPTGVRule(_PPTGVRule n)
#else
static void _PrPTGVRule(n)
	_PPTGVRule n;
#endif
{
	PTG_OUTPUT_STRING(f, "    nct_vrule( ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "_winnum, ");
	PTG_OUTPUT_INT(f, n->p5);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, ", nct_");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "_r");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " );\n");
}

#ifdef PROTO_OK
PTGNode PTGVRule(int p1, PTGNode p2, int p3, int p4, int p5)
#else
PTGNode PTGVRule(p1, p2, p3, p4, p5)

int p1;
PTGNode p2;
int p3;
int p4;
int p5;
#endif
{
	_PPTGVRule n;
	n = (_PPTGVRule)MALLOC(sizeof(struct _SPTGVRule));
	n->_print = (_PTGProc)_PrPTGVRule;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	return (PTGNode)n;
}


/* Implementation of Pattern Id */

typedef struct _SPTGId{
	_PTGProc _print;
	int p1;
} * _PPTGId;

#ifdef PROTO_OK
static void _PrPTGId(_PPTGId n)
#else
static void _PrPTGId(n)
	_PPTGId n;
#endif
{
	PtgOutId(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGId(int p1)
#else
PTGNode PTGId(p1)

int p1;
#endif
{
	_PPTGId n;
	n = (_PPTGId)MALLOC(sizeof(struct _SPTGId));
	n->_print = (_PTGProc)_PrPTGId;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern AsIs */

typedef struct _SPTGAsIs{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGAsIs;

#ifdef PROTO_OK
static void _PrPTGAsIs(_PPTGAsIs n)
#else
static void _PrPTGAsIs(n)
	_PPTGAsIs n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGAsIs(CONST char* p1)
#else
PTGNode PTGAsIs(p1)

CONST char* p1;
#endif
{
	_PPTGAsIs n;
	n = (_PPTGAsIs)MALLOC(sizeof(struct _SPTGAsIs));
	n->_print = (_PTGProc)_PrPTGAsIs;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Numb */

typedef struct _SPTGNumb{
	_PTGProc _print;
	int p1;
} * _PPTGNumb;

#ifdef PROTO_OK
static void _PrPTGNumb(_PPTGNumb n)
#else
static void _PrPTGNumb(n)
	_PPTGNumb n;
#endif
{
	PTG_OUTPUT_INT(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGNumb(int p1)
#else
PTGNode PTGNumb(p1)

int p1;
#endif
{
	_PPTGNumb n;
	n = (_PPTGNumb)MALLOC(sizeof(struct _SPTGNumb));
	n->_print = (_PTGProc)_PrPTGNumb;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CString */

typedef struct _SPTGCString{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGCString;

#ifdef PROTO_OK
static void _PrPTGCString(_PPTGCString n)
#else
static void _PrPTGCString(n)
	_PPTGCString n;
#endif
{
	CPtgOutstr(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGCString(CONST char* p1)
#else
PTGNode PTGCString(p1)

CONST char* p1;
#endif
{
	_PPTGCString n;
	n = (_PPTGCString)MALLOC(sizeof(struct _SPTGCString));
	n->_print = (_PTGProc)_PrPTGCString;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CChar */

typedef struct _SPTGCChar{
	_PTGProc _print;
	int p1;
} * _PPTGCChar;

#ifdef PROTO_OK
static void _PrPTGCChar(_PPTGCChar n)
#else
static void _PrPTGCChar(n)
	_PPTGCChar n;
#endif
{
	CPtgOutchar(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGCChar(int p1)
#else
PTGNode PTGCChar(p1)

int p1;
#endif
{
	_PPTGCChar n;
	n = (_PPTGCChar)MALLOC(sizeof(struct _SPTGCChar));
	n->_print = (_PTGProc)_PrPTGCChar;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern PString */

typedef struct _SPTGPString{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGPString;

#ifdef PROTO_OK
static void _PrPTGPString(_PPTGPString n)
#else
static void _PrPTGPString(n)
	_PPTGPString n;
#endif
{
	PPtgOutstr(f, n->p1);
}

#ifdef PROTO_OK
PTGNode PTGPString(CONST char* p1)
#else
PTGNode PTGPString(p1)

CONST char* p1;
#endif
{
	_PPTGPString n;
	n = (_PPTGPString)MALLOC(sizeof(struct _SPTGPString));
	n->_print = (_PTGProc)_PrPTGPString;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Seq */

typedef struct _SPTGSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGSeq;

#ifdef PROTO_OK
static void _PrPTGSeq(_PPTGSeq n)
#else
static void _PrPTGSeq(n)
	_PPTGSeq n;
#endif
{
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGSeq)MALLOC(sizeof(struct _SPTGSeq));
	n->_print = (_PTGProc)_PrPTGSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern CommaSeq */

typedef struct _SPTGCommaSeq{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGCommaSeq;

#ifdef PROTO_OK
static void _PrPTGCommaSeq(_PPTGCommaSeq n)
#else
static void _PrPTGCommaSeq(n)
	_PPTGCommaSeq n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, ", ");
	}
	n->p2->_print(n->p2);
}

#ifdef PROTO_OK
PTGNode PTGCommaSeq(PTGNode p1, PTGNode p2)
#else
PTGNode PTGCommaSeq(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGCommaSeq n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGCommaSeq)MALLOC(sizeof(struct _SPTGCommaSeq));
	n->_print = (_PTGProc)_PrPTGCommaSeq;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Eol */

typedef struct _SPTGEol{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGEol;

#ifdef PROTO_OK
static void _PrPTGEol(_PPTGEol n)
#else
static void _PrPTGEol(n)
	_PPTGEol n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#ifdef PROTO_OK
PTGNode PTGEol(PTGNode p1)
#else
PTGNode PTGEol(p1)

PTGNode p1;
#endif
{
	_PPTGEol n;
	n = (_PPTGEol)MALLOC(sizeof(struct _SPTGEol));
	n->_print = (_PTGProc)_PrPTGEol;
	n->p1 = p1;
	return (PTGNode)n;
}

/* ============================ */

/* -------------------------------------------------------- */
/*                  Default Output Functions                */
/* -------------------------------------------------------- */


#ifdef PROTO_OK
void _PTGPrintInt(PTG_OUTPUT_FILE file, int param)
#else
void _PTGPrintInt(file, param)
       PTG_OUTPUT_FILE file; int param;
#endif
{    /* used for short and int */
       sprintf(buffer,"%d",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintLong(PTG_OUTPUT_FILE file, long param)
#else
void _PTGPrintLong(file, param)
       PTG_OUTPUT_FILE file; long param;
#endif
{
       sprintf(buffer,"%ld",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintDouble(PTG_OUTPUT_FILE file, double param)
#else
void _PTGPrintDouble(file, param)
       PTG_OUTPUT_FILE file; double param;
#endif
{    /* used for float and double */
       sprintf(buffer,"%g",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#ifdef PROTO_OK
void _PTGPrintChar(PTG_OUTPUT_FILE file, char param)
#else
void _PTGPrintChar(file, param)
       PTG_OUTPUT_FILE file; char param;
#endif
{
       buffer[0] = param;
       buffer[1] = 0;
       PTG_OUTPUT_STRING(file,buffer);
}

