#ifndef CLP_H

#define CLP_H
#include "clplib.h"
#include "pdl_gen.h"
#include "DefTableKeyList.h"

extern DefTableKey CLP_InputFile;
#ifdef PROTO_OK
extern void clp_usage (char *);
#else
extern void clp_usage ();
#endif

extern DefTableKey DepFile;
extern DefTableKey OutputFile;
extern int PreviewDisplay;
extern DefTableKeyList IncludeDirs;
extern DefTableKey Source;

#endif
