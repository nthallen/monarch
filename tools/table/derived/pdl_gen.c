#include "pdl_gen.h"

#ifdef MONITOR
#include "pdl_dapto.h"
#endif

#define PRESENT find(key, _property, (Entry *)&_Item, 0)
#define VALUE (_Item->PropVal)

#define TYPE int

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct intElt))

typedef struct intElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *intProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getint (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getint (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  intProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setint (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setint (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  intProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetint (int _property, DefTableKey key, TYPE _val)
#else
void
Resetint (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  intProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE dim_t

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct dim_tElt))

typedef struct dim_tElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *dim_tProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getdim_t (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getdim_t (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  dim_tProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setdim_t (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setdim_t (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  dim_tProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetdim_t (int _property, DefTableKey key, TYPE _val)
#else
void
Resetdim_t (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  dim_tProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE dims_t

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct dims_tElt))

typedef struct dims_tElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *dims_tProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getdims_t (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getdims_t (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  dims_tProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setdims_t (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setdims_t (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  dims_tProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetdims_t (int _property, DefTableKey key, TYPE _val)
#else
void
Resetdims_t (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  dims_tProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
Hasdims_t (int _property, DefTableKey key)
#else
int
Hasdims_t (_property, key)
int _property;
DefTableKey key;
#endif
{  dims_tProperty _Item;
{
  return(PRESENT);
}
}

#undef ACCESS
#undef TYPE
#define TYPE instance_t

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct instance_tElt))

typedef struct instance_tElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *instance_tProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getinstance_t (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getinstance_t (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  instance_tProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setinstance_t (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setinstance_t (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  instance_tProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetinstance_t (int _property, DefTableKey key, TYPE _val)
#else
void
Resetinstance_t (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  instance_tProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE
#define TYPE PTGNode

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct PTGNodeElt))

typedef struct PTGNodeElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *PTGNodeProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetPTGNode (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetPTGNode (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  PTGNodeProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetPTGNode (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetPTGNode (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  PTGNodeProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetPTGNode (int _property, DefTableKey key, TYPE _val)
#else
void
ResetPTGNode (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  PTGNodeProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SeqPTGNode (int _property, DefTableKey key, PTGNode ptg)
#else
void
SeqPTGNode (_property, key, ptg)
int _property;
DefTableKey key;
PTGNode ptg;
#endif
{  PTGNodeProperty _Item;
{
  PTGNode was;
  
  was = ACCESS ? VALUE : PTGNULL;
  VALUE = PTGSeq(was,ptg);  
}
}

#undef ACCESS
#undef TYPE

static struct PropElt PDLe0 = {(Entry)0, 0};

DefTableKey
#if defined(__STDC__) || defined(__cplusplus)
CloneKey (DefTableKey key)
#else
CloneKey (key)
    DefTableKey key;
#endif
{
  DefTableKey k;
  Entry e;

  if (key == NoKey) return NoKey;
  k = NewKey ();
  for (e = key->List; (e != (Entry)0) && (e->selector != 0);
       e = e->next) {
    switch (e->selector) {
      case 1:
         ResetClpValue (k, ((intProperty)e)->PropVal);
         break;
      case 2:
         ResetMinWidth (k, ((dim_tProperty)e)->PropVal);
         break;
      case 3:
         ResetMinHeight (k, ((dim_tProperty)e)->PropVal);
         break;
      case 4:
         ResetMinDims (k, ((dims_tProperty)e)->PropVal);
         break;
      case 5:
         ResetWidth (k, ((dim_tProperty)e)->PropVal);
         break;
      case 6:
         ResetInstance (k, ((instance_tProperty)e)->PropVal);
         break;
      case 7:
         ResetFieldPtg (k, ((PTGNodeProperty)e)->PropVal);
         break;
      case 8:
         ResetStringPtg (k, ((PTGNodeProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "MinWidth",
    "MinHeight",
    "MinDims",
    "Width",
    "Instance",
    "FieldPtg",
    "StringPtg",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "dim_t",
    "dim_t",
    "dims_t",
    "dim_t",
    "instance_t",
    "PTGNode",
    "PTGNode",
};

void
#if defined(__STDC__) || defined(__cplusplus)
pdl_mon_properties(DefTableKey k)
#else
pdl_mon_properties(k) DefTableKey k;
#endif
{
    Entry e;
    if (k == NoKey) return;
    for (e = k->List; (e != (Entry)0) && (e->selector != 0);
         e = e->next) {
        DAPTO_RESULT_STR (pdl_names[e->selector]);
        DAPTO_RESULT_STR (pdl_types[e->selector]);
        switch (e->selector) {
            case 1:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 2:
#ifdef DAPTO_RESULTdim_t
                DAPTO_RESULTdim_t (((dim_tProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((dim_tProperty)e)->PropVal);
#endif
                break;
            case 3:
#ifdef DAPTO_RESULTdim_t
                DAPTO_RESULTdim_t (((dim_tProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((dim_tProperty)e)->PropVal);
#endif
                break;
            case 4:
#ifdef DAPTO_RESULTdims_t
                DAPTO_RESULTdims_t (((dims_tProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((dims_tProperty)e)->PropVal);
#endif
                break;
            case 5:
#ifdef DAPTO_RESULTdim_t
                DAPTO_RESULTdim_t (((dim_tProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((dim_tProperty)e)->PropVal);
#endif
                break;
            case 6:
#ifdef DAPTO_RESULTinstance_t
                DAPTO_RESULTinstance_t (((instance_tProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((instance_tProperty)e)->PropVal);
#endif
                break;
            case 7:
#ifdef DAPTO_RESULTPTGNode
                DAPTO_RESULTPTGNode (((PTGNodeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PTGNodeProperty)e)->PropVal);
#endif
                break;
            case 8:
#ifdef DAPTO_RESULTPTGNode
                DAPTO_RESULTPTGNode (((PTGNodeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PTGNodeProperty)e)->PropVal);
#endif
                break;
            default: DAPTO_RESULT_STR ("unknown property");
        }
    }
}
#endif
