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
#define TYPE double

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct doubleElt))

typedef struct doubleElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *doubleProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getdouble (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getdouble (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  doubleProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setdouble (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setdouble (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  doubleProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetdouble (int _property, DefTableKey key, TYPE _val)
#else
void
Resetdouble (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  doubleProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
Hasdouble (int _property, DefTableKey key)
#else
int
Hasdouble (_property, key)
int _property;
DefTableKey key;
#endif
{  doubleProperty _Item;
{
  return(PRESENT);
}
}

#undef ACCESS
#undef TYPE
#define TYPE RateDefP

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct RateDefPElt))

typedef struct RateDefPElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *RateDefPProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
GetRateDefP (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
GetRateDefP (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  RateDefPProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
SetRateDefP (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
SetRateDefP (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  RateDefPProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
ResetRateDefP (int _property, DefTableKey key, TYPE _val)
#else
void
ResetRateDefP (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  RateDefPProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
HasRateDefP (int _property, DefTableKey key)
#else
int
HasRateDefP (_property, key)
int _property;
DefTableKey key;
#endif
{  RateDefPProperty _Item;
{
  return(PRESENT);
}
}

#undef ACCESS
#undef TYPE
#define TYPE long

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct longElt))

typedef struct longElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *longProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getlong (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getlong (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  longProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setlong (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setlong (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  longProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetlong (int _property, DefTableKey key, TYPE _val)
#else
void
Resetlong (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  longProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
Haslong (int _property, DefTableKey key)
#else
int
Haslong (_property, key)
int _property;
DefTableKey key;
#endif
{  longProperty _Item;
{
  return(PRESENT);
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
         ResetQCLIConfig (k, ((intProperty)e)->PropVal);
         break;
      case 3:
         ResetDigitizer (k, ((intProperty)e)->PropVal);
         break;
      case 4:
         ResetPrefix (k, ((intProperty)e)->PropVal);
         break;
      case 5:
         ResetdIdt (k, ((doubleProperty)e)->PropVal);
         break;
      case 6:
         ResetdIdtDefined (k, ((intProperty)e)->PropVal);
         break;
      case 7:
         ResetRateDef (k, ((RateDefPProperty)e)->PropVal);
         break;
      case 8:
         ResetToff (k, ((doubleProperty)e)->PropVal);
         break;
      case 9:
         ResetTon (k, ((doubleProperty)e)->PropVal);
         break;
      case 10:
         ResetTpre (k, ((doubleProperty)e)->PropVal);
         break;
      case 11:
         ResetNsample (k, ((longProperty)e)->PropVal);
         break;
      case 12:
         ResetPTG (k, ((PTGNodeProperty)e)->PropVal);
         break;
      case 13:
         ResetUnique (k, ((intProperty)e)->PropVal);
         break;
      case 14:
         ResetQCUnique (k, ((intProperty)e)->PropVal);
         break;
      case 15:
         ResetDigUnique (k, ((intProperty)e)->PropVal);
         break;
      case 16:
         ResetPrefixUnique (k, ((intProperty)e)->PropVal);
         break;
      case 17:
         ResetIzUnique (k, ((intProperty)e)->PropVal);
         break;
      case 18:
         ResetTzUnique (k, ((intProperty)e)->PropVal);
         break;
      case 19:
         ResetNcoaddUnique (k, ((intProperty)e)->PropVal);
         break;
      case 20:
         ResetSampleUnique (k, ((intProperty)e)->PropVal);
         break;
      case 21:
         ResetDAC3Unique (k, ((intProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "QCLIConfig",
    "Digitizer",
    "Prefix",
    "dIdt",
    "dIdtDefined",
    "RateDef",
    "Toff",
    "Ton",
    "Tpre",
    "Nsample",
    "PTG",
    "Unique",
    "QCUnique",
    "DigUnique",
    "PrefixUnique",
    "IzUnique",
    "TzUnique",
    "NcoaddUnique",
    "SampleUnique",
    "DAC3Unique",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "int",
    "int",
    "int",
    "double",
    "int",
    "RateDefP",
    "double",
    "double",
    "double",
    "long",
    "PTGNode",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
    "int",
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
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 3:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 4:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 5:
#ifdef DAPTO_RESULTdouble
                DAPTO_RESULTdouble (((doubleProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((doubleProperty)e)->PropVal);
#endif
                break;
            case 6:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 7:
#ifdef DAPTO_RESULTRateDefP
                DAPTO_RESULTRateDefP (((RateDefPProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((RateDefPProperty)e)->PropVal);
#endif
                break;
            case 8:
#ifdef DAPTO_RESULTdouble
                DAPTO_RESULTdouble (((doubleProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((doubleProperty)e)->PropVal);
#endif
                break;
            case 9:
#ifdef DAPTO_RESULTdouble
                DAPTO_RESULTdouble (((doubleProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((doubleProperty)e)->PropVal);
#endif
                break;
            case 10:
#ifdef DAPTO_RESULTdouble
                DAPTO_RESULTdouble (((doubleProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((doubleProperty)e)->PropVal);
#endif
                break;
            case 11:
#ifdef DAPTO_RESULTlong
                DAPTO_RESULTlong (((longProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((longProperty)e)->PropVal);
#endif
                break;
            case 12:
#ifdef DAPTO_RESULTPTGNode
                DAPTO_RESULTPTGNode (((PTGNodeProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((PTGNodeProperty)e)->PropVal);
#endif
                break;
            case 13:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 14:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 15:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 16:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 17:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 18:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 19:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 20:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 21:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            default: DAPTO_RESULT_STR ("unknown property");
        }
    }
}
#endif
