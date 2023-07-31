#include <stdio.h>
#include <stdlib.h>

#include "ptg_gen.h"
#include "obstack.h"

/* -------------------------------------------------------- */
/*                      Memory Management                   */
/* -------------------------------------------------------- */

static Obstack _PTGObstack;
static void *_PTGFirstObj = NULL;

static void _PTGInit(void)
{
       if (_PTGFirstObj)
               return;
       obstack_init(&_PTGObstack);
       _PTGFirstObj = obstack_alloc(&_PTGObstack, 0);
}

void PTGFree(void)
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
	PTGNode p4;
	long p5;
} * _PPTGFile;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGFile(_PPTGFile n)
#else
static void _PrPTGFile(n)
	_PPTGFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "\nCompiled Output:\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ": Index: \n");
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " Fill at end of index\n");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, ": Total Length: ");
	PTG_OUTPUT_LONG(f, n->p5);
	PTG_OUTPUT_STRING(f, "\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGFile(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, long p5)
#else
PTGNode PTGFile(p1, p2, p3, p4, p5)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
long p5;
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
	return (PTGNode)n;
}


/* Implementation of Pattern Header */

typedef struct _SPTGHeader{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGHeader;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGHeader(_PPTGHeader n)
#else
static void _PrPTGHeader(n)
	_PPTGHeader n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " Program Length\n");
	ptg_output_time(f);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " Padding\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGHeader(PTGNode p1, PTGNode p2)
#else
PTGNode PTGHeader(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGHeader n;
	n = (_PPTGHeader)MALLOC(sizeof(struct _SPTGHeader));
	n->_print = (_PTGProc)_PrPTGHeader;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Hex */

typedef struct _SPTGHex{
	_PTGProc _print;
	short p1;
	int p2;
} * _PPTGHex;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGHex(_PPTGHex n)
#else
static void _PrPTGHex(n)
	_PPTGHex n;
#endif
{
	PTG_OUTPUT_HEX(f, n->p1, n->p2);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGHex(short p1, int p2)
#else
PTGNode PTGHex(p1, p2)

short p1;
int p2;
#endif
{
	_PPTGHex n;
	n = (_PPTGHex)MALLOC(sizeof(struct _SPTGHex));
	n->_print = (_PTGProc)_PrPTGHex;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern FileSum */

typedef struct _SPTGFileSum{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGFileSum;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGFileSum(_PPTGFileSum n)
#else
static void _PrPTGFileSum(n)
	_PPTGFileSum n;
#endif
{
	PTG_OUTPUT_STRING(f, "Waveform Summaries:\n\n");
	n->p1->_print(n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGFileSum(PTGNode p1)
#else
PTGNode PTGFileSum(p1)

PTGNode p1;
#endif
{
	_PPTGFileSum n;
	n = (_PPTGFileSum)MALLOC(sizeof(struct _SPTGFileSum));
	n->_print = (_PTGProc)_PrPTGFileSum;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern ICOSHdr */

typedef struct _SPTGICOSHdr{
	_PTGProc _print;
	int p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
	PTGNode p8;
	PTGNode p9;
} * _PPTGICOSHdr;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGICOSHdr(_PPTGICOSHdr n)
#else
static void _PrPTGICOSHdr(n)
	_PPTGICOSHdr n;
#endif
{
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " ICOS Waveform ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	n->p9->_print(n->p9);
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, " Ton-1\n");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, " Toff-1\n");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, " Tpre (1)\n");
	n->p7->_print(n->p7);
	PTG_OUTPUT_STRING(f, " Loop Address\n");
	n->p8->_print(n->p8);
	PTG_OUTPUT_STRING(f, " Loop Length\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGICOSHdr(int p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9)
#else
PTGNode PTGICOSHdr(p1, p2, p3, p4, p5, p6, p7, p8, p9)

int p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
PTGNode p8;
PTGNode p9;
#endif
{
	_PPTGICOSHdr n;
	n = (_PPTGICOSHdr)MALLOC(sizeof(struct _SPTGICOSHdr));
	n->_print = (_PTGProc)_PrPTGICOSHdr;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	n->p8 = p8;
	n->p9 = p9;
	return (PTGNode)n;
}


/* Implementation of Pattern DACs */

typedef struct _SPTGDACs{
	_PTGProc _print;
	short p1;
	double p2;
	short p3;
	double p4;
	short p5;
	double p6;
	short p7;
	double p8;
} * _PPTGDACs;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGDACs(_PPTGDACs n)
#else
static void _PrPTGDACs(n)
	_PPTGDACs n;
#endif
{
	PTG_OUTPUT_1HEX(f, n->p3);
	PTG_OUTPUT_STRING(f, " DAC0 - ");
	PTG_OUTPUT_DOUBLE(f, n->p4);
	PTG_OUTPUT_STRING(f, " Amps\n");
	PTG_OUTPUT_1HEX(f, n->p1);
	PTG_OUTPUT_STRING(f, " DAC1 - ");
	PTG_OUTPUT_DOUBLE(f, n->p2);
	PTG_OUTPUT_STRING(f, " Amps/Sec\n");
	PTG_OUTPUT_1HEX(f, n->p5);
	PTG_OUTPUT_STRING(f, " DAC2 - ");
	PTG_OUTPUT_DOUBLE(f, n->p6);
	PTG_OUTPUT_STRING(f, " Amps\n");
	PTG_OUTPUT_1HEX(f, n->p7);
	PTG_OUTPUT_STRING(f, " DAC3 - ");
	PTG_OUTPUT_DOUBLE(f, n->p8);
	PTG_OUTPUT_STRING(f, " Amps\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGDACs(short p1, double p2, short p3, double p4, short p5, double p6, short p7, double p8)
#else
PTGNode PTGDACs(p1, p2, p3, p4, p5, p6, p7, p8)

short p1;
double p2;
short p3;
double p4;
short p5;
double p6;
short p7;
double p8;
#endif
{
	_PPTGDACs n;
	n = (_PPTGDACs)MALLOC(sizeof(struct _SPTGDACs));
	n->_print = (_PTGProc)_PrPTGDACs;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	n->p8 = p8;
	return (PTGNode)n;
}


/* Implementation of Pattern ICOSWave */

typedef struct _SPTGICOSWave{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
	PTGNode p8;
	PTGNode p9;
	PTGNode p10;
	PTGNode p11;
	PTGNode p12;
	PTGNode p13;
	PTGNode p14;
	int p15;
	int p16;
	long p17;
	PTGNode p18;
	PTGNode p19;
	PTGNode p20;
} * _PPTGICOSWave;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGICOSWave(_PPTGICOSWave n)
#else
static void _PrPTGICOSWave(n)
	_PPTGICOSWave n;
#endif
{
	PTG_OUTPUT_STRING(f, "ICOS Waveform ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " @ ");
	PTG_OUTPUT_LONG(f, n->p17);
	PTG_OUTPUT_STRING(f, " {");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  Sampling:    ");
	n->p18->_print(n->p18);
	PTG_OUTPUT_STRING(f, " @ ");
	n->p3->_print(n->p3);
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  Net Samples: ");
	n->p19->_print(n->p19);
	PTG_OUTPUT_STRING(f, " Z:");
	n->p20->_print(n->p20);
	PTG_OUTPUT_STRING(f, " ramp:");
	n->p5->_print(n->p5);
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n");
	n->p6->_print(n->p6);
	n->p7->_print(n->p7);
	n->p8->_print(n->p8);
	n->p12->_print(n->p12);
	n->p9->_print(n->p9);
	PTG_OUTPUT_STRING(f, "  Scycle:      ");
	PTG_OUTPUT_INT(f, n->p15);
	PTG_OUTPUT_STRING(f, " ");
	PTG_OUTPUT_INT(f, n->p16);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  Tz:          ");
	n->p13->_print(n->p13);
	n->p11->_print(n->p11);
	PTG_OUTPUT_STRING(f, "\n");
	n->p14->_print(n->p14);
	n->p10->_print(n->p10);
	PTG_OUTPUT_STRING(f, "}\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGICOSWave(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9, PTGNode p10, PTGNode p11, PTGNode p12, PTGNode p13, PTGNode p14, int p15, int p16, long p17, PTGNode p18, PTGNode p19, PTGNode p20)
#else
PTGNode PTGICOSWave(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
PTGNode p8;
PTGNode p9;
PTGNode p10;
PTGNode p11;
PTGNode p12;
PTGNode p13;
PTGNode p14;
int p15;
int p16;
long p17;
PTGNode p18;
PTGNode p19;
PTGNode p20;
#endif
{
	_PPTGICOSWave n;
	n = (_PPTGICOSWave)MALLOC(sizeof(struct _SPTGICOSWave));
	n->_print = (_PTGProc)_PrPTGICOSWave;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	n->p8 = p8;
	n->p9 = p9;
	n->p10 = p10;
	n->p11 = p11;
	n->p12 = p12;
	n->p13 = p13;
	n->p14 = p14;
	n->p15 = p15;
	n->p16 = p16;
	n->p17 = p17;
	n->p18 = p18;
	n->p19 = p19;
	n->p20 = p20;
	return (PTGNode)n;
}


/* Implementation of Pattern ICOSProg */

typedef struct _SPTGICOSProg{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
} * _PPTGICOSProg;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGICOSProg(_PPTGICOSProg n)
#else
static void _PrPTGICOSProg(n)
	_PPTGICOSProg n;
#endif
{
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
	n->p3->_print(n->p3);
	n->p4->_print(n->p4);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGICOSProg(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4)
#else
PTGNode PTGICOSProg(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
#endif
{
	_PPTGICOSProg n;
	if(p1 == PTGNULL && p2 == PTGNULL && p3 == PTGNULL && p4 == PTGNULL)
		return PTGNULL;
	n = (_PPTGICOSProg)MALLOC(sizeof(struct _SPTGICOSProg));
	n->_print = (_PTGProc)_PrPTGICOSProg;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern Ramp */

typedef struct _SPTGRamp{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	int p7;
} * _PPTGRamp;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGRamp(_PPTGRamp n)
#else
static void _PrPTGRamp(n)
	_PPTGRamp n;
#endif
{
	PTG_OUTPUT_STRING(f, "  Ramp {\n");
	PTG_OUTPUT_STRING(f, "    Istart:    ");
	n->p2->_print(n->p2);
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "    Istop:     ");
	n->p4->_print(n->p4);
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "    Tramp:     ");
	n->p6->_print(n->p6);
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "    Sramp:     ");
	PTG_OUTPUT_INT(f, n->p7);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  }\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGRamp(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, int p7)
#else
PTGNode PTGRamp(p1, p2, p3, p4, p5, p6, p7)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
int p7;
#endif
{
	_PPTGRamp n;
	n = (_PPTGRamp)MALLOC(sizeof(struct _SPTGRamp));
	n->_print = (_PTGProc)_PrPTGRamp;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	return (PTGNode)n;
}


/* Implementation of Pattern WaveIndex */

typedef struct _SPTGWaveIndex{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGWaveIndex;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGWaveIndex(_PPTGWaveIndex n)
#else
static void _PrPTGWaveIndex(n)
	_PPTGWaveIndex n;
#endif
{
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGWaveIndex(PTGNode p1, PTGNode p2)
#else
PTGNode PTGWaveIndex(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGWaveIndex n;
	n = (_PPTGWaveIndex)MALLOC(sizeof(struct _SPTGWaveIndex));
	n->_print = (_PTGProc)_PrPTGWaveIndex;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Iz */

typedef struct _SPTGIz{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGIz;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGIz(_PPTGIz n)
#else
static void _PrPTGIz(n)
	_PPTGIz n;
#endif
{
	PTG_OUTPUT_STRING(f, "  Iz:          ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGIz(PTGNode p1)
#else
PTGNode PTGIz(p1)

PTGNode p1;
#endif
{
	_PPTGIz n;
	n = (_PPTGIz)MALLOC(sizeof(struct _SPTGIz));
	n->_print = (_PTGProc)_PrPTGIz;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern dIdt */

typedef struct _SPTGdIdt{
	_PTGProc _print;
	double p1;
} * _PPTGdIdt;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGdIdt(_PPTGdIdt n)
#else
static void _PrPTGdIdt(n)
	_PPTGdIdt n;
#endif
{
	PTG_OUTPUT_STRING(f, "  dI/dt:       ");
	PTG_OUTPUT_DOUBLE(f, n->p1);
	PTG_OUTPUT_STRING(f, " A/sec\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGdIdt(double p1)
#else
PTGNode PTGdIdt(p1)

double p1;
#endif
{
	_PPTGdIdt n;
	n = (_PPTGdIdt)MALLOC(sizeof(struct _SPTGdIdt));
	n->_print = (_PTGProc)_PrPTGdIdt;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern SampleRate */

typedef struct _SPTGSampleRate{
	_PTGProc _print;
	double p1;
	int p2;
} * _PPTGSampleRate;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGSampleRate(_PPTGSampleRate n)
#else
static void _PrPTGSampleRate(n)
	_PPTGSampleRate n;
#endif
{
	PTG_OUTPUT_DOUBLE(f, n->p1);
	PTG_OUTPUT_STRING(f, "/Sec/");
	PTG_OUTPUT_INT(f, n->p2);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGSampleRate(double p1, int p2)
#else
PTGNode PTGSampleRate(p1, p2)

double p1;
int p2;
#endif
{
	_PPTGSampleRate n;
	n = (_PPTGSampleRate)MALLOC(sizeof(struct _SPTGSampleRate));
	n->_print = (_PTGProc)_PrPTGSampleRate;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Specd */

typedef struct _SPTGSpecd{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGSpecd;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGSpecd(_PPTGSpecd n)
#else
static void _PrPTGSpecd(n)
	_PPTGSpecd n;
#endif
{
	PTG_OUTPUT_STRING(f, " (");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ")");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGSpecd(PTGNode p1)
#else
PTGNode PTGSpecd(p1)

PTGNode p1;
#endif
{
	_PPTGSpecd n;
	n = (_PPTGSpecd)MALLOC(sizeof(struct _SPTGSpecd));
	n->_print = (_PTGProc)_PrPTGSpecd;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Long */

typedef struct _SPTGLong{
	_PTGProc _print;
	long p1;
} * _PPTGLong;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGLong(_PPTGLong n)
#else
static void _PrPTGLong(n)
	_PPTGLong n;
#endif
{
	PTG_OUTPUT_LONG(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGLong(long p1)
#else
PTGNode PTGLong(p1)

long p1;
#endif
{
	_PPTGLong n;
	n = (_PPTGLong)MALLOC(sizeof(struct _SPTGLong));
	n->_print = (_PTGProc)_PrPTGLong;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Tcycle */

typedef struct _SPTGTcycle{
	_PTGProc _print;
	double p1;
} * _PPTGTcycle;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGTcycle(_PPTGTcycle n)
#else
static void _PrPTGTcycle(n)
	_PPTGTcycle n;
#endif
{
	PTG_OUTPUT_STRING(f, "  Tcycle:      ");
	PTG_OUTPUT_DOUBLE(f, n->p1);
	PTG_OUTPUT_STRING(f, " msec\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGTcycle(double p1)
#else
PTGNode PTGTcycle(p1)

double p1;
#endif
{
	_PPTGTcycle n;
	n = (_PPTGTcycle)MALLOC(sizeof(struct _SPTGTcycle));
	n->_print = (_PTGProc)_PrPTGTcycle;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Fcycle */

typedef struct _SPTGFcycle{
	_PTGProc _print;
	int p1;
} * _PPTGFcycle;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGFcycle(_PPTGFcycle n)
#else
static void _PrPTGFcycle(n)
	_PPTGFcycle n;
#endif
{
	PTG_OUTPUT_STRING(f, "  Fcycle:      ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " Hz\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGFcycle(int p1)
#else
PTGNode PTGFcycle(p1)

int p1;
#endif
{
	_PPTGFcycle n;
	n = (_PPTGFcycle)MALLOC(sizeof(struct _SPTGFcycle));
	n->_print = (_PTGProc)_PrPTGFcycle;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Stepsize */

typedef struct _SPTGStepsize{
	_PTGProc _print;
	long p1;
} * _PPTGStepsize;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGStepsize(_PPTGStepsize n)
#else
static void _PrPTGStepsize(n)
	_PPTGStepsize n;
#endif
{
	PTG_OUTPUT_STRING(f, "  Stepsize:    ");
	PTG_OUTPUT_LONG(f, n->p1);
	PTG_OUTPUT_STRING(f, " usec\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGStepsize(long p1)
#else
PTGNode PTGStepsize(p1)

long p1;
#endif
{
	_PPTGStepsize n;
	n = (_PPTGStepsize)MALLOC(sizeof(struct _SPTGStepsize));
	n->_print = (_PTGProc)_PrPTGStepsize;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Current */

typedef struct _SPTGCurrent{
	_PTGProc _print;
	double p1;
} * _PPTGCurrent;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGCurrent(_PPTGCurrent n)
#else
static void _PrPTGCurrent(n)
	_PPTGCurrent n;
#endif
{
	PTG_OUTPUT_DOUBLE(f, n->p1);
	PTG_OUTPUT_STRING(f, " mA");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGCurrent(double p1)
#else
PTGNode PTGCurrent(p1)

double p1;
#endif
{
	_PPTGCurrent n;
	n = (_PPTGCurrent)MALLOC(sizeof(struct _SPTGCurrent));
	n->_print = (_PTGProc)_PrPTGCurrent;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Time */

typedef struct _SPTGTime{
	_PTGProc _print;
	double p1;
} * _PPTGTime;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGTime(_PPTGTime n)
#else
static void _PrPTGTime(n)
	_PPTGTime n;
#endif
{
	PTG_OUTPUT_DOUBLE(f, n->p1);
	PTG_OUTPUT_STRING(f, " msec");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGTime(double p1)
#else
PTGNode PTGTime(p1)

double p1;
#endif
{
	_PPTGTime n;
	n = (_PPTGTime)MALLOC(sizeof(struct _SPTGTime));
	n->_print = (_PTGProc)_PrPTGTime;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern TzSample */

typedef struct _SPTGTzSample{
	_PTGProc _print;
	int p1;
	CONST char* p2;
} * _PPTGTzSample;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGTzSample(_PPTGTzSample n)
#else
static void _PrPTGTzSample(n)
	_PPTGTzSample n;
#endif
{
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " ");
	PTG_OUTPUT_STRING(f, n->p2);
	PTG_OUTPUT_STRING(f, "Samples");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGTzSample(int p1, CONST char* p2)
#else
PTGNode PTGTzSample(p1, p2)

int p1;
CONST char* p2;
#endif
{
	_PPTGTzSample n;
	n = (_PPTGTzSample)MALLOC(sizeof(struct _SPTGTzSample));
	n->_print = (_PTGProc)_PrPTGTzSample;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Percent */

typedef struct _SPTGPercent{
	_PTGProc _print;
	double p1;
} * _PPTGPercent;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGPercent(_PPTGPercent n)
#else
static void _PrPTGPercent(n)
	_PPTGPercent n;
#endif
{
	PTG_OUTPUT_DOUBLE(f, n->p1);
	PTG_OUTPUT_STRING(f, "%");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGPercent(double p1)
#else
PTGNode PTGPercent(p1)

double p1;
#endif
{
	_PPTGPercent n;
	n = (_PPTGPercent)MALLOC(sizeof(struct _SPTGPercent));
	n->_print = (_PTGProc)_PrPTGPercent;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern Tz */

typedef struct _SPTGTz{
	_PTGProc _print;
	PTGNode p1;
	long p2;
	double p3;
} * _PPTGTz;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGTz(_PPTGTz n)
#else
static void _PrPTGTz(n)
	_PPTGTz n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_LONG(f, n->p2);
	PTG_OUTPUT_STRING(f, " Samples, ");
	PTG_OUTPUT_DOUBLE(f, n->p3);
	PTG_OUTPUT_STRING(f, "%");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGTz(PTGNode p1, long p2, double p3)
#else
PTGNode PTGTz(p1, p2, p3)

PTGNode p1;
long p2;
double p3;
#endif
{
	_PPTGTz n;
	n = (_PPTGTz)MALLOC(sizeof(struct _SPTGTz));
	n->_print = (_PTGProc)_PrPTGTz;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Waves */

typedef struct _SPTGWaves{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGWaves;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGWaves(_PPTGWaves n)
#else
static void _PrPTGWaves(n)
	_PPTGWaves n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, "\n");
	}
	n->p2->_print(n->p2);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGWaves(PTGNode p1, PTGNode p2)
#else
PTGNode PTGWaves(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGWaves n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGWaves)MALLOC(sizeof(struct _SPTGWaves));
	n->_print = (_PTGProc)_PrPTGWaves;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Tonoff */

typedef struct _SPTGTonoff{
	_PTGProc _print;
	long p1;
	long p2;
	long p3;
	PTGNode p4;
} * _PPTGTonoff;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGTonoff(_PPTGTonoff n)
#else
static void _PrPTGTonoff(n)
	_PPTGTonoff n;
#endif
{
	PTG_OUTPUT_STRING(f, "  Ton/Toff:    ");
	PTG_OUTPUT_LONG(f, n->p1);
	PTG_OUTPUT_STRING(f, "/");
	PTG_OUTPUT_LONG(f, n->p2);
	PTG_OUTPUT_STRING(f, " usec\n");
	PTG_OUTPUT_STRING(f, "  Ttrigger:    ");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  Trecycle:    ");
	PTG_OUTPUT_LONG(f, n->p3);
	PTG_OUTPUT_STRING(f, " usec\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGTonoff(long p1, long p2, long p3, PTGNode p4)
#else
PTGNode PTGTonoff(p1, p2, p3, p4)

long p1;
long p2;
long p3;
PTGNode p4;
#endif
{
	_PPTGTonoff n;
	n = (_PPTGTonoff)MALLOC(sizeof(struct _SPTGTonoff));
	n->_print = (_PTGProc)_PrPTGTonoff;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern Fill */

typedef struct _SPTGFill{
	_PTGProc _print;
	short p1;
	int p2;
} * _PPTGFill;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGFill(_PPTGFill n)
#else
static void _PrPTGFill(n)
	_PPTGFill n;
#endif
{
	PTG_OUTPUT_HEX(f, n->p1, n->p2);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGFill(short p1, int p2)
#else
PTGNode PTGFill(p1, p2)

short p1;
int p2;
#endif
{
	_PPTGFill n;
	n = (_PPTGFill)MALLOC(sizeof(struct _SPTGFill));
	n->_print = (_PTGProc)_PrPTGFill;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern ICOSFill */

typedef struct _SPTGICOSFill{
	_PTGProc _print;
	short p1;
	int p2;
} * _PPTGICOSFill;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGICOSFill(_PPTGICOSFill n)
#else
static void _PrPTGICOSFill(n)
	_PPTGICOSFill n;
#endif
{
	PTG_OUTPUT_ICOSHEX(f, n->p1, n->p2);
	PTG_OUTPUT_STRING(f, "\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGICOSFill(short p1, int p2)
#else
PTGNode PTGICOSFill(p1, p2)

short p1;
int p2;
#endif
{
	_PPTGICOSFill n;
	n = (_PPTGICOSFill)MALLOC(sizeof(struct _SPTGICOSFill));
	n->_print = (_PTGProc)_PrPTGICOSFill;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern RingHdr */

typedef struct _SPTGRingHdr{
	_PTGProc _print;
	int p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
	PTGNode p8;
	PTGNode p9;
} * _PPTGRingHdr;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGRingHdr(_PPTGRingHdr n)
#else
static void _PrPTGRingHdr(n)
	_PPTGRingHdr n;
#endif
{
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " Ringdown Waveform ");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, " ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	n->p9->_print(n->p9);
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, " Ton-1\n");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, " Toff-1\n");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, " Tpre\n");
	n->p7->_print(n->p7);
	PTG_OUTPUT_STRING(f, " Loop Address\n");
	n->p8->_print(n->p8);
	PTG_OUTPUT_STRING(f, " Loop Length\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGRingHdr(int p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9)
#else
PTGNode PTGRingHdr(p1, p2, p3, p4, p5, p6, p7, p8, p9)

int p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
PTGNode p8;
PTGNode p9;
#endif
{
	_PPTGRingHdr n;
	n = (_PPTGRingHdr)MALLOC(sizeof(struct _SPTGRingHdr));
	n->_print = (_PTGProc)_PrPTGRingHdr;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	n->p8 = p8;
	n->p9 = p9;
	return (PTGNode)n;
}


/* Implementation of Pattern RingData */

typedef struct _SPTGRingData{
	_PTGProc _print;
	short p1;
	double p2;
} * _PPTGRingData;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGRingData(_PPTGRingData n)
#else
static void _PrPTGRingData(n)
	_PPTGRingData n;
#endif
{
	PTG_OUTPUT_1HEX(f, n->p1);
	PTG_OUTPUT_STRING(f, " ");
	PTG_OUTPUT_DOUBLE(f, n->p2);
	PTG_OUTPUT_STRING(f, " Amps\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGRingData(short p1, double p2)
#else
PTGNode PTGRingData(p1, p2)

short p1;
double p2;
#endif
{
	_PPTGRingData n;
	n = (_PPTGRingData)MALLOC(sizeof(struct _SPTGRingData));
	n->_print = (_PTGProc)_PrPTGRingData;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Commas */

typedef struct _SPTGCommas{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGCommas;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGCommas(_PPTGCommas n)
#else
static void _PrPTGCommas(n)
	_PPTGCommas n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, ",\n");
	}
	n->p2->_print(n->p2);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGCommas(PTGNode p1, PTGNode p2)
#else
PTGNode PTGCommas(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGCommas n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGCommas)MALLOC(sizeof(struct _SPTGCommas));
	n->_print = (_PTGProc)_PrPTGCommas;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern Double */

typedef struct _SPTGDouble{
	_PTGProc _print;
	double p1;
} * _PPTGDouble;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGDouble(_PPTGDouble n)
#else
static void _PrPTGDouble(n)
	_PPTGDouble n;
#endif
{
	PTG_OUTPUT_DOUBLE(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGDouble(double p1)
#else
PTGNode PTGDouble(p1)

double p1;
#endif
{
	_PPTGDouble n;
	n = (_PPTGDouble)MALLOC(sizeof(struct _SPTGDouble));
	n->_print = (_PTGProc)_PrPTGDouble;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern CmdCode */

typedef struct _SPTGCmdCode{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	CONST char* p3;
	int p4;
} * _PPTGCmdCode;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGCmdCode(_PPTGCmdCode n)
#else
static void _PrPTGCmdCode(n)
	_PPTGCmdCode n;
#endif
{
	PTG_OUTPUT_STRING(f, "%{\n");
	PTG_OUTPUT_STRING(f, "  #ifdef SERVER\n");
	PTG_OUTPUT_STRING(f, "    hsatod_setup_t ");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "_Waves[] = {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "    };\n");
	PTG_OUTPUT_STRING(f, "  #endif\n");
	PTG_OUTPUT_STRING(f, "%}\n");
	PTG_OUTPUT_STRING(f, "&");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "_Wave <int>\n");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, "\t: Number %d {\n");
	PTG_OUTPUT_STRING(f, "\t    if ( $2 < 0 || $2 >= ");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, " ) {\n");
	PTG_OUTPUT_STRING(f, "\t      msg(2, \"Specified waveform number %d out of range\", $2 );\n");
	PTG_OUTPUT_STRING(f, "\t      CANCEL_LINE;\n");
	PTG_OUTPUT_STRING(f, "\t    } else $0 = $2;\n");
	PTG_OUTPUT_STRING(f, "\t  }\n");
	PTG_OUTPUT_STRING(f, "\t;\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGCmdCode(PTGNode p1, PTGNode p2, CONST char* p3, int p4)
#else
PTGNode PTGCmdCode(p1, p2, p3, p4)

PTGNode p1;
PTGNode p2;
CONST char* p3;
int p4;
#endif
{
	_PPTGCmdCode n;
	n = (_PPTGCmdCode)MALLOC(sizeof(struct _SPTGCmdCode));
	n->_print = (_PTGProc)_PrPTGCmdCode;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	return (PTGNode)n;
}


/* Implementation of Pattern CPCIdef */

typedef struct _SPTGCPCIdef{
	_PTGProc _print;
	int p1;
	int p2;
	int p3;
	int p4;
	int p5;
	int p6;
	CONST char* p7;
	long p8;
	CONST char* p9;
} * _PPTGCPCIdef;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGCPCIdef(_PPTGCPCIdef n)
#else
static void _PrPTGCPCIdef(n)
	_PPTGCPCIdef n;
#endif
{
	PTG_OUTPUT_STRING(f, "      {");
	PTG_OUTPUT_INT(f, n->p1);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p3);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p4);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p5);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_INT(f, n->p6);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_STRING(f, n->p9);
	PTG_OUTPUT_STRING(f, "_");
	PTG_OUTPUT_STRING(f, n->p7);
	PTG_OUTPUT_STRING(f, ", ");
	PTG_OUTPUT_LONG(f, n->p8);
	PTG_OUTPUT_STRING(f, "}");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGCPCIdef(int p1, int p2, int p3, int p4, int p5, int p6, CONST char* p7, long p8, CONST char* p9)
#else
PTGNode PTGCPCIdef(p1, p2, p3, p4, p5, p6, p7, p8, p9)

int p1;
int p2;
int p3;
int p4;
int p5;
int p6;
CONST char* p7;
long p8;
CONST char* p9;
#endif
{
	_PPTGCPCIdef n;
	n = (_PPTGCPCIdef)MALLOC(sizeof(struct _SPTGCPCIdef));
	n->_print = (_PTGProc)_PrPTGCPCIdef;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	n->p8 = p8;
	n->p9 = p9;
	return (PTGNode)n;
}


/* Implementation of Pattern MFile */

typedef struct _SPTGMFile{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
	PTGNode p3;
	PTGNode p4;
	PTGNode p5;
	PTGNode p6;
	PTGNode p7;
	PTGNode p8;
	PTGNode p9;
	PTGNode p10;
	PTGNode p11;
} * _PPTGMFile;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGMFile(_PPTGMFile n)
#else
static void _PrPTGMFile(n)
	_PPTGMFile n;
#endif
{
	PTG_OUTPUT_STRING(f, "WaveSpecs = struct( ...\n");
	PTG_OUTPUT_STRING(f, "  'Name', { ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'RawRate', { ");
	n->p2->_print(n->p2);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'RawSamples', { ");
	n->p3->_print(n->p3);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'NetSamples', { ");
	n->p4->_print(n->p4);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'NAverage', { ");
	n->p5->_print(n->p5);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'NCoadd', { ");
	n->p6->_print(n->p6);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'FTrigger', { ");
	n->p7->_print(n->p7);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'ISICOS', { ");
	n->p8->_print(n->p8);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'TzSamples', { ");
	n->p9->_print(n->p9);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'dIdt', { ");
	n->p10->_print(n->p10);
	PTG_OUTPUT_STRING(f, " }, ...\n");
	PTG_OUTPUT_STRING(f, "  'I0', { ");
	n->p11->_print(n->p11);
	PTG_OUTPUT_STRING(f, " } ...\n");
	PTG_OUTPUT_STRING(f, ");\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGMFile(PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9, PTGNode p10, PTGNode p11)
#else
PTGNode PTGMFile(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)

PTGNode p1;
PTGNode p2;
PTGNode p3;
PTGNode p4;
PTGNode p5;
PTGNode p6;
PTGNode p7;
PTGNode p8;
PTGNode p9;
PTGNode p10;
PTGNode p11;
#endif
{
	_PPTGMFile n;
	n = (_PPTGMFile)MALLOC(sizeof(struct _SPTGMFile));
	n->_print = (_PTGProc)_PrPTGMFile;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	n->p4 = p4;
	n->p5 = p5;
	n->p6 = p6;
	n->p7 = p7;
	n->p8 = p8;
	n->p9 = p9;
	n->p10 = p10;
	n->p11 = p11;
	return (PTGNode)n;
}


/* Implementation of Pattern MCommas */

typedef struct _SPTGMCommas{
	_PTGProc _print;
	PTGNode p1;
	PTGNode p2;
} * _PPTGMCommas;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGMCommas(_PPTGMCommas n)
#else
static void _PrPTGMCommas(n)
	_PPTGMCommas n;
#endif
{
	n->p1->_print(n->p1);
	if (n->p1 != PTGNULL && n->p2 != PTGNULL)
	{
		PTG_OUTPUT_STRING(f, ",");
		CondMatNL(f);
	}
	n->p2->_print(n->p2);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGMCommas(PTGNode p1, PTGNode p2)
#else
PTGNode PTGMCommas(p1, p2)

PTGNode p1;
PTGNode p2;
#endif
{
	_PPTGMCommas n;
	if(p1 == PTGNULL && p2 == PTGNULL)
		return PTGNULL;
	n = (_PPTGMCommas)MALLOC(sizeof(struct _SPTGMCommas));
	n->_print = (_PTGProc)_PrPTGMCommas;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern MString */

typedef struct _SPTGMString{
	_PTGProc _print;
	PTGNode p1;
} * _PPTGMString;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGMString(_PPTGMString n)
#else
static void _PrPTGMString(n)
	_PPTGMString n;
#endif
{
	PTG_OUTPUT_STRING(f, "'");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "'");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGMString(PTGNode p1)
#else
PTGNode PTGMString(p1)

PTGNode p1;
#endif
{
	_PPTGMString n;
	n = (_PPTGMString)MALLOC(sizeof(struct _SPTGMString));
	n->_print = (_PTGProc)_PrPTGMString;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern WaveCmd */

typedef struct _SPTGWaveCmd{
	_PTGProc _print;
	PTGNode p1;
	int p2;
} * _PPTGWaveCmd;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGWaveCmd(_PPTGWaveCmd n)
#else
static void _PrPTGWaveCmd(n)
	_PPTGWaveCmd n;
#endif
{
	PTG_OUTPUT_STRING(f, "\t: ");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, " { $0 = ");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "; }\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGWaveCmd(PTGNode p1, int p2)
#else
PTGNode PTGWaveCmd(p1, p2)

PTGNode p1;
int p2;
#endif
{
	_PPTGWaveCmd n;
	n = (_PPTGWaveCmd)MALLOC(sizeof(struct _SPTGWaveCmd));
	n->_print = (_PTGProc)_PrPTGWaveCmd;
	n->p1 = p1;
	n->p2 = p2;
	return (PTGNode)n;
}


/* Implementation of Pattern WaveName */

typedef struct _SPTGWaveName{
	_PTGProc _print;
	CONST char* p1;
} * _PPTGWaveName;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGWaveName(_PPTGWaveName n)
#else
static void _PrPTGWaveName(n)
	_PPTGWaveName n;
#endif
{
	PTG_OUTPUT_STRING(f, "  ");
	ptg_output_name(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGWaveName(CONST char* p1)
#else
PTGNode PTGWaveName(p1)

CONST char* p1;
#endif
{
	_PPTGWaveName n;
	n = (_PPTGWaveName)MALLOC(sizeof(struct _SPTGWaveName));
	n->_print = (_PTGProc)_PrPTGWaveName;
	n->p1 = p1;
	return (PTGNode)n;
}


/* Implementation of Pattern WaveNames */

typedef struct _SPTGWaveNames{
	_PTGProc _print;
	PTGNode p1;
	int p2;
	CONST char* p3;
} * _PPTGWaveNames;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGWaveNames(_PPTGWaveNames n)
#else
static void _PrPTGWaveNames(n)
	_PPTGWaveNames n;
#endif
{
	PTG_OUTPUT_STRING(f, "%{\n");
	PTG_OUTPUT_STRING(f, "  static const char *");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "_Wt[] = {\n");
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  };\n");
	PTG_OUTPUT_STRING(f, "  #define N_");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "_WAVES ");
	PTG_OUTPUT_INT(f, n->p2);
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "\n");
	PTG_OUTPUT_STRING(f, "  const char *");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "_Wave_text( int n ) {\n");
	PTG_OUTPUT_STRING(f, "    if ( n < 0 || n >= N_");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "_WAVES )\n");
	PTG_OUTPUT_STRING(f, "      return \"----------\";\n");
	PTG_OUTPUT_STRING(f, "    else return ");
	PTG_OUTPUT_STRING(f, n->p3);
	PTG_OUTPUT_STRING(f, "_Wt[n];\n");
	PTG_OUTPUT_STRING(f, "  }\n");
	PTG_OUTPUT_STRING(f, "%}\n");
}

#if defined(__STDC__) || defined(__cplusplus)
PTGNode PTGWaveNames(PTGNode p1, int p2, CONST char* p3)
#else
PTGNode PTGWaveNames(p1, p2, p3)

PTGNode p1;
int p2;
CONST char* p3;
#endif
{
	_PPTGWaveNames n;
	n = (_PPTGWaveNames)MALLOC(sizeof(struct _SPTGWaveNames));
	n->_print = (_PTGProc)_PrPTGWaveNames;
	n->p1 = p1;
	n->p2 = p2;
	n->p3 = p3;
	return (PTGNode)n;
}


/* Implementation of Pattern Id */

typedef struct _SPTGId{
	_PTGProc _print;
	int p1;
} * _PPTGId;

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGId(_PPTGId n)
#else
static void _PrPTGId(n)
	_PPTGId n;
#endif
{
	PtgOutId(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGAsIs(_PPTGAsIs n)
#else
static void _PrPTGAsIs(n)
	_PPTGAsIs n;
#endif
{
	PTG_OUTPUT_STRING(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGNumb(_PPTGNumb n)
#else
static void _PrPTGNumb(n)
	_PPTGNumb n;
#endif
{
	PTG_OUTPUT_INT(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGCString(_PPTGCString n)
#else
static void _PrPTGCString(n)
	_PPTGCString n;
#endif
{
	CPtgOutstr(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGCChar(_PPTGCChar n)
#else
static void _PrPTGCChar(n)
	_PPTGCChar n;
#endif
{
	CPtgOutchar(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGPString(_PPTGPString n)
#else
static void _PrPTGPString(n)
	_PPTGPString n;
#endif
{
	PPtgOutstr(f, n->p1);
}

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGSeq(_PPTGSeq n)
#else
static void _PrPTGSeq(n)
	_PPTGSeq n;
#endif
{
	n->p1->_print(n->p1);
	n->p2->_print(n->p2);
}

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
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

#if defined(__STDC__) || defined(__cplusplus)
static void _PrPTGEol(_PPTGEol n)
#else
static void _PrPTGEol(n)
	_PPTGEol n;
#endif
{
	n->p1->_print(n->p1);
	PTG_OUTPUT_STRING(f, "\n");
}

#if defined(__STDC__) || defined(__cplusplus)
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


#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintInt(PTG_OUTPUT_FILE file, int param)
#else
void _PTGPrintInt(file, param)
       PTG_OUTPUT_FILE file; int param;
#endif
{    /* used for short and int */
       sprintf(buffer,"%d",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintLong(PTG_OUTPUT_FILE file, long param)
#else
void _PTGPrintLong(file, param)
       PTG_OUTPUT_FILE file; long param;
#endif
{
       sprintf(buffer,"%ld",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#if defined(__STDC__) || defined(__cplusplus)
void _PTGPrintDouble(PTG_OUTPUT_FILE file, double param)
#else
void _PTGPrintDouble(file, param)
       PTG_OUTPUT_FILE file; double param;
#endif
{    /* used for float and double */
       sprintf(buffer,"%g",param);
       PTG_OUTPUT_STRING(file,buffer);
}

#if defined(__STDC__) || defined(__cplusplus)
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

