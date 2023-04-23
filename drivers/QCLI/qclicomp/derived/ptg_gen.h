#ifndef _PTGGEN_H
#define _PTGGEN_H

#include <stdio.h>
#include "eliproto.h"

/* Include-files specified in .ptg.phi-files */

#include "ptg.h"
/* Definition of Output-Macros */

#if !defined(PTG_OUTPUT_FILE)
#    define PTG_OUTPUT_FILE FILE *
#    define PTG_OUTPUT_DEFAULT 1
#else
#    define PTG_OUTPUT_DEFAULT 0
#endif
#if !defined(PTG_OUTPUT_STRING)
#    define PTG_OUTPUT_STRING(file,param) fputs(param, file)
#    if !defined(PTG_OUTPUT_INT)
#            define PTG_OUTPUT_INT(file,param)    fprintf(file,"%d",param)
#    endif
#    if !defined(PTG_OUTPUT_LONG)
#            define PTG_OUTPUT_LONG(file,param)   fprintf(file,"%ld",param)
#    endif
#    if !defined(PTG_OUTPUT_SHORT)
#            define PTG_OUTPUT_SHORT(file,param)  fprintf(file,"%d",(int) param)
#    endif
#    if !defined(PTG_OUTPUT_CHAR)
#            define PTG_OUTPUT_CHAR(file,param)   fputc(param, file)
#    endif
#    if !defined(PTG_OUTPUT_FLOAT)
#            define PTG_OUTPUT_FLOAT(file,param)  fprintf(file,"%g",(double)param)
#    endif
#    if !defined(PTG_OUTPUT_DOUBLE)
#            define PTG_OUTPUT_DOUBLE(file,param) fprintf(file,"%g",param)
#    endif

#else
     /* PTG_OUTPUT_STRING defined */
     extern void _PTGPrintInt ELI_ARG((PTG_OUTPUT_FILE,int));
     extern void _PTGPrintLong ELI_ARG((PTG_OUTPUT_FILE,long));
     extern void _PTGPrintChar ELI_ARG((PTG_OUTPUT_FILE,char));
     extern void _PTGPrintDouble ELI_ARG((PTG_OUTPUT_FILE,double));
#    if !defined(PTG_OUTPUT_INT)
#            define PTG_OUTPUT_INT(file,param)    _PTGPrintInt(file,param)
#    endif
#    if !defined(PTG_OUTPUT_LONG)
#            define PTG_OUTPUT_LONG(file,param)   _PTGPrintLong(file,param)
#    endif
#    if !defined(PTG_OUTPUT_SHORT)
#            define PTG_OUTPUT_SHORT(file,param)  _PTGPrintInt(file,(int)param)
#    endif
#    if !defined(PTG_OUTPUT_CHAR)
#            define PTG_OUTPUT_CHAR(file,param)   _PTGPrintChar(file,param)
#    endif
#    if !defined(PTG_OUTPUT_FLOAT)
#            define PTG_OUTPUT_FLOAT(file,param)  _PTGPrintDouble(file,(double)param)
#    endif
#    if !defined(PTG_OUTPUT_DOUBLE)
#            define PTG_OUTPUT_DOUBLE(file,param) _PTGPrintDouble(file,param)
#    endif
#endif

/* Define PTGNode Type */
#if defined(__cplusplus)
struct _SPTG0;
typedef void (* _PTGProc)(struct _SPTG0 *);
#else
typedef void (* _PTGProc)();
#endif

typedef struct _SPTG0
{
  _PTGProc _print;
} * _PPTG0;
typedef _PPTG0 PTGNode;                      /* the only exported type */

/* predefined static PTGNULL-Node */

extern struct _SPTG0 _PTGNULL;
#define PTGNULL (& _PTGNULL)
#define PTGNull() (& _PTGNULL)

/* output functions */

#if PTG_OUTPUT_DEFAULT
extern PTGNode PTGOut ELI_ARG((PTGNode root));
extern PTGNode PTGOutFile ELI_ARG((const char *filename, PTGNode root));
extern PTGNode PTGOutFPtr ELI_ARG((FILE *output, PTGNode root));
#endif
extern PTGNode PTGProcess ELI_ARG((PTG_OUTPUT_FILE file, PTGNode root));

/* Memory Management functions. */

extern void PTGFree ELI_ARG((void));

/* ============================ */
/* functions for making PTG nodes */
PTGNode PTGFile ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, long p5));
PTGNode PTGHeader ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGHex ELI_ARG((short p1, int p2));
PTGNode PTGFileSum ELI_ARG((PTGNode p1));
PTGNode PTGICOSHdr ELI_ARG((int p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9));
PTGNode PTGDACs ELI_ARG((short p1, double p2, short p3, double p4, short p5, double p6, short p7, double p8));
PTGNode PTGICOSWave ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9, PTGNode p10, PTGNode p11, PTGNode p12, PTGNode p13, PTGNode p14, int p15, int p16, long p17, PTGNode p18, PTGNode p19, PTGNode p20));
PTGNode PTGICOSProg ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4));
PTGNode PTGRamp ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, int p7));
PTGNode PTGWaveIndex ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGIz ELI_ARG((PTGNode p1));
PTGNode PTGdIdt ELI_ARG((double p1));
PTGNode PTGSampleRate ELI_ARG((double p1, int p2));
PTGNode PTGSpecd ELI_ARG((PTGNode p1));
PTGNode PTGLong ELI_ARG((long p1));
PTGNode PTGTcycle ELI_ARG((double p1));
PTGNode PTGFcycle ELI_ARG((int p1));
PTGNode PTGStepsize ELI_ARG((long p1));
PTGNode PTGCurrent ELI_ARG((double p1));
PTGNode PTGTime ELI_ARG((double p1));
PTGNode PTGTzSample ELI_ARG((int p1, CONST char* p2));
PTGNode PTGPercent ELI_ARG((double p1));
PTGNode PTGTz ELI_ARG((PTGNode p1, long p2, double p3));
PTGNode PTGWaves ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGTonoff ELI_ARG((long p1, long p2, long p3, PTGNode p4));
PTGNode PTGFill ELI_ARG((short p1, int p2));
PTGNode PTGICOSFill ELI_ARG((short p1, int p2));
PTGNode PTGRingHdr ELI_ARG((int p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9));
PTGNode PTGRingData ELI_ARG((short p1, double p2));
PTGNode PTGCommas ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGDouble ELI_ARG((double p1));
PTGNode PTGCmdCode ELI_ARG((PTGNode p1, PTGNode p2, CONST char* p3, int p4));
PTGNode PTGCPCIdef ELI_ARG((int p1, int p2, int p3, int p4, int p5, int p6, CONST char* p7, long p8, CONST char* p9));
PTGNode PTGMFile ELI_ARG((PTGNode p1, PTGNode p2, PTGNode p3, PTGNode p4, PTGNode p5, PTGNode p6, PTGNode p7, PTGNode p8, PTGNode p9, PTGNode p10, PTGNode p11));
PTGNode PTGMCommas ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGMString ELI_ARG((PTGNode p1));
PTGNode PTGWaveCmd ELI_ARG((PTGNode p1, int p2));
PTGNode PTGWaveName ELI_ARG((CONST char* p1));
PTGNode PTGWaveNames ELI_ARG((PTGNode p1, int p2, CONST char* p3));
PTGNode PTGId ELI_ARG((int p1));
PTGNode PTGAsIs ELI_ARG((CONST char* p1));
PTGNode PTGNumb ELI_ARG((int p1));
PTGNode PTGCString ELI_ARG((CONST char* p1));
PTGNode PTGCChar ELI_ARG((int p1));
PTGNode PTGPString ELI_ARG((CONST char* p1));
PTGNode PTGSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGCommaSeq ELI_ARG((PTGNode p1, PTGNode p2));
PTGNode PTGEol ELI_ARG((PTGNode p1));

/* prototypes for used function call insertions */

void ptg_output_time ELI_ARG((PTG_OUTPUT_FILE));
void PTG_OUTPUT_HEX ELI_ARG((PTG_OUTPUT_FILE, short, int));
void PTG_OUTPUT_1HEX ELI_ARG((PTG_OUTPUT_FILE, short));
void PTG_OUTPUT_ICOSHEX ELI_ARG((PTG_OUTPUT_FILE, short, int));
void CondMatNL ELI_ARG((PTG_OUTPUT_FILE));
void ptg_output_name ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
void PtgOutId ELI_ARG((PTG_OUTPUT_FILE, int));
void CPtgOutstr ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
void CPtgOutchar ELI_ARG((PTG_OUTPUT_FILE, int));
void PPtgOutstr ELI_ARG((PTG_OUTPUT_FILE, CONST char*));
/* ============================ */

#ifdef MONITOR
/* Monitoring support for structured values */
#define DAPTO_RESULTPTGNode(n) DAPTO_RESULT_PTR(n)
#define DAPTO_ARGPTGNode(n) DAPTO_ARG_PTR(n, PTGNode)
#endif

#endif
