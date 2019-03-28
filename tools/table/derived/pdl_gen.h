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

#include "dim.h"
#include "ptg_gen.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE dim_t
extern TYPE Getdim_t ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setdim_t ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetdim_t ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE dims_t
extern TYPE Getdims_t ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setdims_t ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetdims_t ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern int Hasdims_t ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE instance_t
extern TYPE Getinstance_t ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setinstance_t ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetinstance_t ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE
#define TYPE PTGNode
extern TYPE GetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void SetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void ResetPTGNode ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern void SeqPTGNode ELI_ARG((int _Property, DefTableKey key, PTGNode ptg));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define SetMinWidth(key, _add, _replace)   \
		Setdim_t(2, (key), (_add), (_replace))
#define ResetMinWidth(key, _val)   \
		Resetdim_t(2, (key), (_val))
#define GetMinWidth(key, deflt)   \
		Getdim_t(2, (key), (deflt))
#define SetMinHeight(key, _add, _replace)   \
		Setdim_t(3, (key), (_add), (_replace))
#define ResetMinHeight(key, _val)   \
		Resetdim_t(3, (key), (_val))
#define GetMinHeight(key, deflt)   \
		Getdim_t(3, (key), (deflt))
#define HasMinDims(key)   \
		Hasdims_t(4, (key))
#define SetMinDims(key, _add, _replace)   \
		Setdims_t(4, (key), (_add), (_replace))
#define ResetMinDims(key, _val)   \
		Resetdims_t(4, (key), (_val))
#define GetMinDims(key, deflt)   \
		Getdims_t(4, (key), (deflt))
#define SetWidth(key, _add, _replace)   \
		Setdim_t(5, (key), (_add), (_replace))
#define ResetWidth(key, _val)   \
		Resetdim_t(5, (key), (_val))
#define GetWidth(key, deflt)   \
		Getdim_t(5, (key), (deflt))
#define SetInstance(key, _add, _replace)   \
		Setinstance_t(6, (key), (_add), (_replace))
#define ResetInstance(key, _val)   \
		Resetinstance_t(6, (key), (_val))
#define GetInstance(key, deflt)   \
		Getinstance_t(6, (key), (deflt))
#define SeqFieldPtg(key, ptg)   \
		SeqPTGNode(7, (key), (ptg))
#define SetFieldPtg(key, _add, _replace)   \
		SetPTGNode(7, (key), (_add), (_replace))
#define ResetFieldPtg(key, _val)   \
		ResetPTGNode(7, (key), (_val))
#define GetFieldPtg(key, deflt)   \
		GetPTGNode(7, (key), (deflt))
#define SeqStringPtg(key, ptg)   \
		SeqPTGNode(8, (key), (ptg))
#define SetStringPtg(key, _add, _replace)   \
		SetPTGNode(8, (key), (_add), (_replace))
#define ResetStringPtg(key, _val)   \
		ResetPTGNode(8, (key), (_val))
#define GetStringPtg(key, deflt)   \
		GetPTGNode(8, (key), (deflt))

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
