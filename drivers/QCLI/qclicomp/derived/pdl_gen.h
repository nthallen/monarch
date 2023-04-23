#ifndef PDL_GEN_H
#define PDL_GEN_H

#include "deftbl.h"

#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif

#include "qclicomp.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE double
extern TYPE Getdouble ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setdouble ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetdouble ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern int Hasdouble ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE RateDefP
extern TYPE GetRateDefP ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetRateDefP ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetRateDefP ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern int HasRateDefP ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE long
extern TYPE Getlong ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setlong ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetlong ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern int Haslong ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE PTGNode
extern TYPE GetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define SetQCLIConfig(key, _add, _replace)   \
		Setint(2, (key), (_add), (_replace))
#define ResetQCLIConfig(key, _val)   \
		Resetint(2, (key), (_val))
#define GetQCLIConfig(key, deflt)   \
		Getint(2, (key), (deflt))
#define SetDigitizer(key, _add, _replace)   \
		Setint(3, (key), (_add), (_replace))
#define ResetDigitizer(key, _val)   \
		Resetint(3, (key), (_val))
#define GetDigitizer(key, deflt)   \
		Getint(3, (key), (deflt))
#define SetPrefix(key, _add, _replace)   \
		Setint(4, (key), (_add), (_replace))
#define ResetPrefix(key, _val)   \
		Resetint(4, (key), (_val))
#define GetPrefix(key, deflt)   \
		Getint(4, (key), (deflt))
#define SetdIdt(key, _add, _replace)   \
		Setdouble(5, (key), (_add), (_replace))
#define ResetdIdt(key, _val)   \
		Resetdouble(5, (key), (_val))
#define GetdIdt(key, deflt)   \
		Getdouble(5, (key), (deflt))
#define SetdIdtDefined(key, _add, _replace)   \
		Setint(6, (key), (_add), (_replace))
#define ResetdIdtDefined(key, _val)   \
		Resetint(6, (key), (_val))
#define GetdIdtDefined(key, deflt)   \
		Getint(6, (key), (deflt))
#define HasRateDef(key)   \
		HasRateDefP(7, (key))
#define SetRateDef(key, _add, _replace)   \
		SetRateDefP(7, (key), (_add), (_replace))
#define ResetRateDef(key, _val)   \
		ResetRateDefP(7, (key), (_val))
#define GetRateDef(key, deflt)   \
		GetRateDefP(7, (key), (deflt))
#define HasToff(key)   \
		Hasdouble(8, (key))
#define SetToff(key, _add, _replace)   \
		Setdouble(8, (key), (_add), (_replace))
#define ResetToff(key, _val)   \
		Resetdouble(8, (key), (_val))
#define GetToff(key, deflt)   \
		Getdouble(8, (key), (deflt))
#define HasTon(key)   \
		Hasdouble(9, (key))
#define SetTon(key, _add, _replace)   \
		Setdouble(9, (key), (_add), (_replace))
#define ResetTon(key, _val)   \
		Resetdouble(9, (key), (_val))
#define GetTon(key, deflt)   \
		Getdouble(9, (key), (deflt))
#define HasTpre(key)   \
		Hasdouble(10, (key))
#define SetTpre(key, _add, _replace)   \
		Setdouble(10, (key), (_add), (_replace))
#define ResetTpre(key, _val)   \
		Resetdouble(10, (key), (_val))
#define GetTpre(key, deflt)   \
		Getdouble(10, (key), (deflt))
#define HasNsample(key)   \
		Haslong(11, (key))
#define SetNsample(key, _add, _replace)   \
		Setlong(11, (key), (_add), (_replace))
#define ResetNsample(key, _val)   \
		Resetlong(11, (key), (_val))
#define GetNsample(key, deflt)   \
		Getlong(11, (key), (deflt))
#define SetPTG(key, _add, _replace)   \
		SetPTGNode(12, (key), (_add), (_replace))
#define ResetPTG(key, _val)   \
		ResetPTGNode(12, (key), (_val))
#define GetPTG(key, deflt)   \
		GetPTGNode(12, (key), (deflt))
#define SetUnique(key, _add, _replace)   \
		Setint(13, (key), (_add), (_replace))
#define ResetUnique(key, _val)   \
		Resetint(13, (key), (_val))
#define GetUnique(key, deflt)   \
		Getint(13, (key), (deflt))
#define SetQCUnique(key, _add, _replace)   \
		Setint(14, (key), (_add), (_replace))
#define ResetQCUnique(key, _val)   \
		Resetint(14, (key), (_val))
#define GetQCUnique(key, deflt)   \
		Getint(14, (key), (deflt))
#define SetDigUnique(key, _add, _replace)   \
		Setint(15, (key), (_add), (_replace))
#define ResetDigUnique(key, _val)   \
		Resetint(15, (key), (_val))
#define GetDigUnique(key, deflt)   \
		Getint(15, (key), (deflt))
#define SetPrefixUnique(key, _add, _replace)   \
		Setint(16, (key), (_add), (_replace))
#define ResetPrefixUnique(key, _val)   \
		Resetint(16, (key), (_val))
#define GetPrefixUnique(key, deflt)   \
		Getint(16, (key), (deflt))
#define SetIzUnique(key, _add, _replace)   \
		Setint(17, (key), (_add), (_replace))
#define ResetIzUnique(key, _val)   \
		Resetint(17, (key), (_val))
#define GetIzUnique(key, deflt)   \
		Getint(17, (key), (deflt))
#define SetTzUnique(key, _add, _replace)   \
		Setint(18, (key), (_add), (_replace))
#define ResetTzUnique(key, _val)   \
		Resetint(18, (key), (_val))
#define GetTzUnique(key, deflt)   \
		Getint(18, (key), (deflt))
#define SetNcoaddUnique(key, _add, _replace)   \
		Setint(19, (key), (_add), (_replace))
#define ResetNcoaddUnique(key, _val)   \
		Resetint(19, (key), (_val))
#define GetNcoaddUnique(key, deflt)   \
		Getint(19, (key), (deflt))
#define SetSampleUnique(key, _add, _replace)   \
		Setint(20, (key), (_add), (_replace))
#define ResetSampleUnique(key, _val)   \
		Resetint(20, (key), (_val))
#define GetSampleUnique(key, deflt)   \
		Getint(20, (key), (deflt))
#define SetDAC3Unique(key, _add, _replace)   \
		Setint(21, (key), (_add), (_replace))
#define ResetDAC3Unique(key, _val)   \
		Resetint(21, (key), (_val))
#define GetDAC3Unique(key, deflt)   \
		Getint(21, (key), (deflt))

extern struct PropList PDLk[];


extern DefTableKey CloneKey ELI_ARG((DefTableKey key));
/* Clone a definition
 *    On entry-
 *       key=a valid definition
 *    On exit-
 *       CloneKey=Unique definition with the same properties
 *                and property values as key
 ***/

#ifdef MONITOR
extern void pdl_mon_properties ELI_ARG((DefTableKey));
#endif

#endif
