
/* implementation of tree construction functions */

#include "node.h"

#include "nodecode.h"

#include "attrpredef.h"

#include "visitmap.h"

#include "treeact.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#include "MONTblStack.h"
#endif

#include <stdlib.h>

#define _USE_OBSTACK 1

/* use of obstack: */

#if _USE_OBSTACK

#include "obstack.h"
static struct obstack TreeSpace;
static void *_TreeBase;

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	return obstack_alloc(&TreeSpace, size);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	return (char *)(obstack_alloc(&TreeSpace, size));
}
#endif

void InitTree()
{
	obstack_init(&TreeSpace);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

void FreeTree()
{
	obstack_free(&TreeSpace, _TreeBase);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

#else

#include <stdio.h>

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	void *retval = malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	char *retval = (char *) malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#endif

void InitTree() { }

void FreeTree() { }

#endif

#ifdef MONITOR
#define _SETCOORD(node) \
        node->_coord = _coordref ? *_coordref : NoCoord;
#define _COPYCOORD(node) \
        node->_coord = _currn->_desc1->_coord;
#else
#define _SETCOORD(node)
#define _COPYCOORD(node)
#endif
#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingCmd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingCmd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingCmd)) return (_currn);
if (IsSymb (_currn, SYMBDAC3def)) return (Mkrule_039(_coordref, _currn));
if (IsSymb (_currn, SYMBIzDef)) return (Mkrule_040(_coordref, _currn));
if (IsSymb (_currn, SYMBNcoaddDef)) return (Mkrule_041(_coordref, _currn));
if (IsSymb (_currn, SYMBRingData)) return (Mkrule_042(_coordref, _currn));
if (IsSymb (_currn, SYMBToffDef)) return (Mkrule_045(_coordref, _currn));
if (IsSymb (_currn, SYMBTonDef)) return (Mkrule_046(_coordref, _currn));
if (IsSymb (_currn, SYMBTpreDef)) return (Mkrule_047(_coordref, _currn));
if (IsSymb (_currn, SYMBNsampleDef)) return (Mkrule_043(_coordref, _currn));
if (IsSymb (_currn, SYMBRingNsampleDef)) return (Mkrule_043(_coordref, _currn));
if (IsSymb (_currn, SYMBRateDef)) return (Mkrule_044(_coordref, _currn));
if (IsSymb (_currn, SYMBRingRateDef)) return (Mkrule_044(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRingCmd */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG4 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG4 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG4)) return (_currn);
return(NULLNODEPTR);
}/* MkG4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkICOSCmd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkICOSCmd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBICOSCmd)) return (_currn);
if (IsSymb (_currn, SYMBICOSRamp)) return (Mkrule_017(_coordref, _currn));
if (IsSymb (_currn, SYMBTzDef)) return (Mkrule_021(_coordref, _currn));
if (IsSymb (_currn, SYMBdIdt)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBICOSNsampleDef)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBICOSRateDef)) return (Mkrule_018(_coordref, _currn));
if (IsSymb (_currn, SYMBDAC3def)) return (Mkrule_015(_coordref, _currn));
if (IsSymb (_currn, SYMBIzDef)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBNcoaddDef)) return (Mkrule_020(_coordref, _currn));
if (IsSymb (_currn, SYMBNsampleDef)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBRateDef)) return (Mkrule_018(_coordref, _currn));
return(NULLNODEPTR);
}/* MkICOSCmd */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG3 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG3 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG3)) return (_currn);
return(NULLNODEPTR);
}/* MkG3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG1 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG1 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG1)) return (_currn);
if (IsSymb (_currn, SYMBICOSWave)) return (Mkrule_08(_coordref, _currn));
if (IsSymb (_currn, SYMBRingWave)) return (Mkrule_08(_coordref, _currn));
if (IsSymb (_currn, SYMBWave)) return (Mkrule_08(_coordref, _currn));
return(NULLNODEPTR);
}/* MkG1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDAC3def (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDAC3def (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDAC3def)) return (_currn);
return(NULLNODEPTR);
}/* MkDAC3def */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG2 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG2 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG2)) return (_currn);
return(NULLNODEPTR);
}/* MkG2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConfigCmds (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConfigCmds (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConfigCmds)) return (_currn);
if (IsSymb (_currn, SYMBG2)) return (Mkrule_04(_coordref, _currn));
return(NULLNODEPTR);
}/* MkConfigCmds */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkQCLIConfig (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkQCLIConfig (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBQCLIConfig)) return (_currn);
return(NULLNODEPTR);
}/* MkQCLIConfig */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDigitizer (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDigitizer (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDigitizer)) return (_currn);
return(NULLNODEPTR);
}/* MkDigitizer */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConfigCmd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConfigCmd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConfigCmd)) return (_currn);
if (IsSymb (_currn, SYMBDigitizer)) return (Mkrule_01(_coordref, _currn));
if (IsSymb (_currn, SYMBPrefix)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBQCLIConfig)) return (Mkrule_03(_coordref, _currn));
return(NULLNODEPTR);
}/* MkConfigCmd */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingStepsize (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingStepsize (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingStepsize)) return (_currn);
if (IsSymb (_currn, SYMBCurrent)) return (Mkrule_1(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRingStepsize */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingCount (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingCount (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingCount)) return (_currn);
return(NULLNODEPTR);
}/* MkRingCount */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingStep (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingStep (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingStep)) return (_currn);
if (IsSymb (_currn, SYMBRingCount)) return (Mkrule_054(_coordref, _currn));
if (IsSymb (_currn, SYMBCurrent)) return (Mkrule_055(_coordref, _currn));
if (IsSymb (_currn, SYMBRingStepsize)) return (Mkrule_055(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRingStep */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCurrentSteps (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCurrentSteps (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCurrentSteps)) return (_currn);
return(NULLNODEPTR);
}/* MkCurrentSteps */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingCurrent (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingCurrent (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingCurrent)) return (_currn);
if (IsSymb (_currn, SYMBCurrent)) return (Mkrule_049(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRingCurrent */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTpreVal (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTpreVal (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTpreVal)) return (_currn);
if (IsSymb (_currn, SYMBTime)) return (Mkrule_5(_coordref, _currn));
return(NULLNODEPTR);
}/* MkTpreVal */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTonVal (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTonVal (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTonVal)) return (_currn);
if (IsSymb (_currn, SYMBTime)) return (Mkrule_7(_coordref, _currn));
return(NULLNODEPTR);
}/* MkTonVal */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTpreDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTpreDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTpreDef)) return (_currn);
return(NULLNODEPTR);
}/* MkTpreDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTonDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTonDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTonDef)) return (_currn);
return(NULLNODEPTR);
}/* MkTonDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingNsampleDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingNsampleDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingNsampleDef)) return (_currn);
if (IsSymb (_currn, SYMBNsampleDef)) return (Mkrule_052(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRingNsampleDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkToffDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkToffDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBToffDef)) return (_currn);
return(NULLNODEPTR);
}/* MkToffDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingRateDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingRateDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingRateDef)) return (_currn);
if (IsSymb (_currn, SYMBRateDef)) return (Mkrule_053(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRingRateDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingData (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingData (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingData)) return (_currn);
return(NULLNODEPTR);
}/* MkRingData */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDAC3Value (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDAC3Value (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDAC3Value)) return (_currn);
return(NULLNODEPTR);
}/* MkDAC3Value */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSampleSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSampleSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSampleSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkSampleSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTzTime (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTzTime (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTzTime)) return (_currn);
if (IsSymb (_currn, SYMBTime)) return (Mkrule_14(_coordref, _currn));
return(NULLNODEPTR);
}/* MkTzTime */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTzSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTzSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTzSpec)) return (_currn);
if (IsSymb (_currn, SYMBTzTime)) return (Mkrule_15(_coordref, _currn));
if (IsSymb (_currn, SYMBPercent)) return (Mkrule_13(_coordref, _currn));
if (IsSymb (_currn, SYMBSampleSpec)) return (Mkrule_10(_coordref, _currn));
if (IsSymb (_currn, SYMBTime)) return (Mkrule_15(_coordref, _currn));
return(NULLNODEPTR);
}/* MkTzSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRateDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRateDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRateDef)) return (_currn);
return(NULLNODEPTR);
}/* MkRateDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNsample (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNsample (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNsample)) return (_currn);
return(NULLNODEPTR);
}/* MkNsample */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNsampleDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNsampleDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNsampleDef)) return (_currn);
return(NULLNODEPTR);
}/* MkNsampleDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNaverage (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNaverage (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNaverage)) return (_currn);
return(NULLNODEPTR);
}/* MkNaverage */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNcoadd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNcoadd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNcoadd)) return (_currn);
return(NULLNODEPTR);
}/* MkNcoadd */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkICOSRamp (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkICOSRamp (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBICOSRamp)) return (_currn);
return(NULLNODEPTR);
}/* MkICOSRamp */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkdIdt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkdIdt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBdIdt)) return (_currn);
return(NULLNODEPTR);
}/* MkdIdt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPrepTime (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPrepTime (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPrepTime)) return (_currn);
return(NULLNODEPTR);
}/* MkPrepTime */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIstop (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkIstop (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBIstop)) return (_currn);
return(NULLNODEPTR);
}/* MkIstop */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIstart (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkIstart (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBIstart)) return (_currn);
return(NULLNODEPTR);
}/* MkIstart */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPercent (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPercent (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPercent)) return (_currn);
return(NULLNODEPTR);
}/* MkPercent */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRateUnit (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRateUnit (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRateUnit)) return (_currn);
return(NULLNODEPTR);
}/* MkRateUnit */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTimeUnit (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTimeUnit (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTimeUnit)) return (_currn);
return(NULLNODEPTR);
}/* MkTimeUnit */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTime (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTime (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTime)) return (_currn);
return(NULLNODEPTR);
}/* MkTime */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCurrentUnit (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCurrentUnit (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCurrentUnit)) return (_currn);
return(NULLNODEPTR);
}/* MkCurrentUnit */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFloatVal (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFloatVal (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFloatVal)) return (_currn);
return(NULLNODEPTR);
}/* MkFloatVal */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCurrent (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCurrent (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCurrent)) return (_currn);
return(NULLNODEPTR);
}/* MkCurrent */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkICOSRateDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkICOSRateDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBICOSRateDef)) return (_currn);
if (IsSymb (_currn, SYMBRateDef)) return (Mkrule_025(_coordref, _currn));
return(NULLNODEPTR);
}/* MkICOSRateDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkICOSNsampleDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkICOSNsampleDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBICOSNsampleDef)) return (_currn);
if (IsSymb (_currn, SYMBNsampleDef)) return (Mkrule_024(_coordref, _currn));
return(NULLNODEPTR);
}/* MkICOSNsampleDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNcoaddDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNcoaddDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNcoaddDef)) return (_currn);
return(NULLNODEPTR);
}/* MkNcoaddDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIzDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkIzDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBIzDef)) return (_currn);
return(NULLNODEPTR);
}/* MkIzDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTzDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTzDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTzDef)) return (_currn);
return(NULLNODEPTR);
}/* MkTzDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPrefix (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPrefix (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPrefix)) return (_currn);
return(NULLNODEPTR);
}/* MkPrefix */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDigitizerType (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDigitizerType (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDigitizerType)) return (_currn);
return(NULLNODEPTR);
}/* MkDigitizerType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkQCLIConfigType (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkQCLIConfigType (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBQCLIConfigType)) return (_currn);
return(NULLNODEPTR);
}/* MkQCLIConfigType */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSourceFile (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSourceFile (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSourceFile)) return (_currn);
return(NULLNODEPTR);
}/* MkSourceFile */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkWave (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkWave (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBWave)) return (_currn);
if (IsSymb (_currn, SYMBICOSWave)) return (Mkrule_061(_coordref, _currn));
if (IsSymb (_currn, SYMBRingWave)) return (Mkrule_062(_coordref, _currn));
return(NULLNODEPTR);
}/* MkWave */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingCmds (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingCmds (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingCmds)) return (_currn);
if (IsSymb (_currn, SYMBG4)) return (Mkrule_048(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRingCmds */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRingWave (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRingWave (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRingWave)) return (_currn);
return(NULLNODEPTR);
}/* MkRingWave */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkICOSCmds (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkICOSCmds (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBICOSCmds)) return (_currn);
if (IsSymb (_currn, SYMBG3)) return (Mkrule_023(_coordref, _currn));
return(NULLNODEPTR);
}/* MkICOSCmds */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDefIdent (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDefIdent (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDefIdent)) return (_currn);
return(NULLNODEPTR);
}/* MkDefIdent */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkICOSWave (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkICOSWave (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBICOSWave)) return (_currn);
return(NULLNODEPTR);
}/* MkICOSWave */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_1 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_1 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_1 _currn;
#ifdef __cplusplus
_currn = new _TPrule_1;
#else
_currn = (_TPPrule_1) TreeNodeAlloc (sizeof (struct _TPrule_1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_1;
_currn->_desc1 = (_TSPCurrent) MkCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_1: root of subtree no. 1 can not be made a Current node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_1;
return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_2 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_2 _currn;
#ifdef __cplusplus
_currn = new _TPrule_2;
#else
_currn = (_TPPrule_2) TreeNodeAlloc (sizeof (struct _TPrule_2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_2;
_SETCOORD(_currn)
_TERMACT_rule_2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_3 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_3 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_3 _currn;
#ifdef __cplusplus
_currn = new _TPrule_3;
#else
_currn = (_TPPrule_3) TreeNodeAlloc (sizeof (struct _TPrule_3));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_3;
_currn->_desc1 = (_TSPCurrent) MkCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 1 can not be made a Current node ", 0, _coordref);
_currn->_desc2 = (_TSPCurrent) MkCurrent (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 2 can not be made a Current node ", 0, _coordref);
_currn->_desc3 = (_TSPRingStep) MkRingStep (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 3 can not be made a RingStep node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_3;
return ( (NODEPTR) _currn);
}/* Mkrule_3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_4 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_4 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_4 _currn;
#ifdef __cplusplus
_currn = new _TPrule_4;
#else
_currn = (_TPPrule_4) TreeNodeAlloc (sizeof (struct _TPrule_4));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_4;
_SETCOORD(_currn)
_TERMACT_rule_4;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_5 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_5 _currn;
#ifdef __cplusplus
_currn = new _TPrule_5;
#else
_currn = (_TPPrule_5) TreeNodeAlloc (sizeof (struct _TPrule_5));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_5;
_currn->_desc1 = (_TSPTime) MkTime (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_5: root of subtree no. 1 can not be made a Time node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_5;
return ( (NODEPTR) _currn);
}/* Mkrule_5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_6 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_6 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_6 _currn;
#ifdef __cplusplus
_currn = new _TPrule_6;
#else
_currn = (_TPPrule_6) TreeNodeAlloc (sizeof (struct _TPrule_6));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_6;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_6: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_6;
return ( (NODEPTR) _currn);
}/* Mkrule_6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_7 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_7 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_7 _currn;
#ifdef __cplusplus
_currn = new _TPrule_7;
#else
_currn = (_TPPrule_7) TreeNodeAlloc (sizeof (struct _TPrule_7));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_7;
_currn->_desc1 = (_TSPTime) MkTime (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_7: root of subtree no. 1 can not be made a Time node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_7;
return ( (NODEPTR) _currn);
}/* Mkrule_7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_8 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_8 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_8 _currn;
#ifdef __cplusplus
_currn = new _TPrule_8;
#else
_currn = (_TPPrule_8) TreeNodeAlloc (sizeof (struct _TPrule_8));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_8;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_8;
return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_9 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_9 _currn;
#ifdef __cplusplus
_currn = new _TPrule_9;
#else
_currn = (_TPPrule_9) TreeNodeAlloc (sizeof (struct _TPrule_9));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_9;
_SETCOORD(_currn)
_TERMACT_rule_9;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_9 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_10 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_10 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_10 _currn;
#ifdef __cplusplus
_currn = new _TPrule_10;
#else
_currn = (_TPPrule_10) TreeNodeAlloc (sizeof (struct _TPrule_10));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_10;
_currn->_desc1 = (_TSPSampleSpec) MkSampleSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 1 can not be made a SampleSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_10;
return ( (NODEPTR) _currn);
}/* Mkrule_10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_11 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_11 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_11 _currn;
#ifdef __cplusplus
_currn = new _TPrule_11;
#else
_currn = (_TPPrule_11) TreeNodeAlloc (sizeof (struct _TPrule_11));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_11;
_SETCOORD(_currn)
_TERMACT_rule_11;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_11 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_12 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_12 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_12 _currn;
#ifdef __cplusplus
_currn = new _TPrule_12;
#else
_currn = (_TPPrule_12) TreeNodeAlloc (sizeof (struct _TPrule_12));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_12;
_SETCOORD(_currn)
_TERMACT_rule_12;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_12 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_13 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_13 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_13 _currn;
#ifdef __cplusplus
_currn = new _TPrule_13;
#else
_currn = (_TPPrule_13) TreeNodeAlloc (sizeof (struct _TPrule_13));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_13;
_currn->_desc1 = (_TSPPercent) MkPercent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_13: root of subtree no. 1 can not be made a Percent node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_13;
return ( (NODEPTR) _currn);
}/* Mkrule_13 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_14 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_14 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_14 _currn;
#ifdef __cplusplus
_currn = new _TPrule_14;
#else
_currn = (_TPPrule_14) TreeNodeAlloc (sizeof (struct _TPrule_14));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_14;
_currn->_desc1 = (_TSPTime) MkTime (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_14: root of subtree no. 1 can not be made a Time node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_14;
return ( (NODEPTR) _currn);
}/* Mkrule_14 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_15 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_15 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_15 _currn;
#ifdef __cplusplus
_currn = new _TPrule_15;
#else
_currn = (_TPPrule_15) TreeNodeAlloc (sizeof (struct _TPrule_15));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_15;
_currn->_desc1 = (_TSPTzTime) MkTzTime (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_15: root of subtree no. 1 can not be made a TzTime node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_15;
return ( (NODEPTR) _currn);
}/* Mkrule_15 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_16 (POSITION *_coordref, int _TERM1, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_16 (_coordref, _TERM1,_desc1,_desc2)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_16 _currn;
#ifdef __cplusplus
_currn = new _TPrule_16;
#else
_currn = (_TPPrule_16) TreeNodeAlloc (sizeof (struct _TPrule_16));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_16;
_currn->_desc1 = (_TSPRateUnit) MkRateUnit (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_16: root of subtree no. 1 can not be made a RateUnit node ", 0, _coordref);
_currn->_desc2 = (_TSPNaverage) MkNaverage (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_16: root of subtree no. 2 can not be made a Naverage node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_16;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_16 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_17 (POSITION *_coordref, NODEPTR _desc1, int _TERM1)
#else
NODEPTR Mkrule_17 (_coordref,_desc1, _TERM1)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
#endif
{	_TPPrule_17 _currn;
#ifdef __cplusplus
_currn = new _TPrule_17;
#else
_currn = (_TPPrule_17) TreeNodeAlloc (sizeof (struct _TPrule_17));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_17;
_currn->_desc1 = (_TSPNsample) MkNsample (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 1 can not be made a Nsample node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_17;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_17 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_18 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_18 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_18 _currn;
#ifdef __cplusplus
_currn = new _TPrule_18;
#else
_currn = (_TPPrule_18) TreeNodeAlloc (sizeof (struct _TPrule_18));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_18;
_SETCOORD(_currn)
_TERMACT_rule_18;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_18 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_19 (POSITION *_coordref)
#else
NODEPTR Mkrule_19 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_19 _currn;
#ifdef __cplusplus
_currn = new _TPrule_19;
#else
_currn = (_TPPrule_19) TreeNodeAlloc (sizeof (struct _TPrule_19));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_19;
_SETCOORD(_currn)
_TERMACT_rule_19;
return ( (NODEPTR) _currn);
}/* Mkrule_19 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_20 (POSITION *_coordref, NODEPTR _desc1, int _TERM1)
#else
NODEPTR Mkrule_20 (_coordref,_desc1, _TERM1)
	POSITION *_coordref;
	NODEPTR _desc1;
	int _TERM1;
#endif
{	_TPPrule_20 _currn;
#ifdef __cplusplus
_currn = new _TPrule_20;
#else
_currn = (_TPPrule_20) TreeNodeAlloc (sizeof (struct _TPrule_20));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_20;
_currn->_desc1 = (_TSPNcoadd) MkNcoadd (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_20: root of subtree no. 1 can not be made a Ncoadd node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_20;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_20 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_21 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_21 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_21 _currn;
#ifdef __cplusplus
_currn = new _TPrule_21;
#else
_currn = (_TPPrule_21) TreeNodeAlloc (sizeof (struct _TPrule_21));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_21;
_currn->_desc1 = (_TSPIstop) MkIstop (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_21: root of subtree no. 1 can not be made a Istop node ", 0, _coordref);
_currn->_desc2 = (_TSPPrepTime) MkPrepTime (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_21: root of subtree no. 2 can not be made a PrepTime node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_21;
return ( (NODEPTR) _currn);
}/* Mkrule_21 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_22 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_22 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_22 _currn;
#ifdef __cplusplus
_currn = new _TPrule_22;
#else
_currn = (_TPPrule_22) TreeNodeAlloc (sizeof (struct _TPrule_22));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_22;
_currn->_desc1 = (_TSPIstart) MkIstart (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_22: root of subtree no. 1 can not be made a Istart node ", 0, _coordref);
_currn->_desc2 = (_TSPPrepTime) MkPrepTime (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_22: root of subtree no. 2 can not be made a PrepTime node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_22;
return ( (NODEPTR) _currn);
}/* Mkrule_22 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_23 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_23 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_23 _currn;
#ifdef __cplusplus
_currn = new _TPrule_23;
#else
_currn = (_TPPrule_23) TreeNodeAlloc (sizeof (struct _TPrule_23));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_23;
_currn->_desc1 = (_TSPIstart) MkIstart (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 1 can not be made a Istart node ", 0, _coordref);
_currn->_desc2 = (_TSPIstop) MkIstop (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 2 can not be made a Istop node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_23;
return ( (NODEPTR) _currn);
}/* Mkrule_23 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_24 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_24 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
#endif
{	_TPPrule_24 _currn;
#ifdef __cplusplus
_currn = new _TPrule_24;
#else
_currn = (_TPPrule_24) TreeNodeAlloc (sizeof (struct _TPrule_24));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_24;
_currn->_desc1 = (_TSPIstart) MkIstart (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 1 can not be made a Istart node ", 0, _coordref);
_currn->_desc2 = (_TSPIstop) MkIstop (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 2 can not be made a Istop node ", 0, _coordref);
_currn->_desc3 = (_TSPPrepTime) MkPrepTime (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 3 can not be made a PrepTime node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_24;
return ( (NODEPTR) _currn);
}/* Mkrule_24 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_25 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_25 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_25 _currn;
#ifdef __cplusplus
_currn = new _TPrule_25;
#else
_currn = (_TPPrule_25) TreeNodeAlloc (sizeof (struct _TPrule_25));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_25;
_currn->_desc1 = (_TSPCurrent) MkCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 1 can not be made a Current node ", 0, _coordref);
_currn->_desc2 = (_TSPTimeUnit) MkTimeUnit (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 2 can not be made a TimeUnit node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_25;
return ( (NODEPTR) _currn);
}/* Mkrule_25 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_26 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_26 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_26 _currn;
#ifdef __cplusplus
_currn = new _TPrule_26;
#else
_currn = (_TPPrule_26) TreeNodeAlloc (sizeof (struct _TPrule_26));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_26;
_SETCOORD(_currn)
_TERMACT_rule_26;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Float", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_26 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_27 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_27 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_27 _currn;
#ifdef __cplusplus
_currn = new _TPrule_27;
#else
_currn = (_TPPrule_27) TreeNodeAlloc (sizeof (struct _TPrule_27));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_27;
_SETCOORD(_currn)
_TERMACT_rule_27;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_27 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_28 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_28 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_28 _currn;
#ifdef __cplusplus
_currn = new _TPrule_28;
#else
_currn = (_TPPrule_28) TreeNodeAlloc (sizeof (struct _TPrule_28));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_28;
_currn->_desc1 = (_TSPTimeUnit) MkTimeUnit (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 1 can not be made a TimeUnit node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_28;
return ( (NODEPTR) _currn);
}/* Mkrule_28 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_29 (POSITION *_coordref)
#else
NODEPTR Mkrule_29 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_29 _currn;
#ifdef __cplusplus
_currn = new _TPrule_29;
#else
_currn = (_TPPrule_29) TreeNodeAlloc (sizeof (struct _TPrule_29));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_29;
_SETCOORD(_currn)
_TERMACT_rule_29;
return ( (NODEPTR) _currn);
}/* Mkrule_29 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_30 (POSITION *_coordref)
#else
NODEPTR Mkrule_30 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_30 _currn;
#ifdef __cplusplus
_currn = new _TPrule_30;
#else
_currn = (_TPPrule_30) TreeNodeAlloc (sizeof (struct _TPrule_30));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_30;
_SETCOORD(_currn)
_TERMACT_rule_30;
return ( (NODEPTR) _currn);
}/* Mkrule_30 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_31 (POSITION *_coordref)
#else
NODEPTR Mkrule_31 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_31 _currn;
#ifdef __cplusplus
_currn = new _TPrule_31;
#else
_currn = (_TPPrule_31) TreeNodeAlloc (sizeof (struct _TPrule_31));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_31;
_SETCOORD(_currn)
_TERMACT_rule_31;
return ( (NODEPTR) _currn);
}/* Mkrule_31 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_32 (POSITION *_coordref)
#else
NODEPTR Mkrule_32 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_32 _currn;
#ifdef __cplusplus
_currn = new _TPrule_32;
#else
_currn = (_TPPrule_32) TreeNodeAlloc (sizeof (struct _TPrule_32));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_32;
_SETCOORD(_currn)
_TERMACT_rule_32;
return ( (NODEPTR) _currn);
}/* Mkrule_32 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_33 (POSITION *_coordref)
#else
NODEPTR Mkrule_33 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_33 _currn;
#ifdef __cplusplus
_currn = new _TPrule_33;
#else
_currn = (_TPPrule_33) TreeNodeAlloc (sizeof (struct _TPrule_33));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_33;
_SETCOORD(_currn)
_TERMACT_rule_33;
return ( (NODEPTR) _currn);
}/* Mkrule_33 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_34 (POSITION *_coordref)
#else
NODEPTR Mkrule_34 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_34 _currn;
#ifdef __cplusplus
_currn = new _TPrule_34;
#else
_currn = (_TPPrule_34) TreeNodeAlloc (sizeof (struct _TPrule_34));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_34;
_SETCOORD(_currn)
_TERMACT_rule_34;
return ( (NODEPTR) _currn);
}/* Mkrule_34 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_35 (POSITION *_coordref)
#else
NODEPTR Mkrule_35 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_35 _currn;
#ifdef __cplusplus
_currn = new _TPrule_35;
#else
_currn = (_TPPrule_35) TreeNodeAlloc (sizeof (struct _TPrule_35));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_35;
_SETCOORD(_currn)
_TERMACT_rule_35;
return ( (NODEPTR) _currn);
}/* Mkrule_35 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_36 (POSITION *_coordref)
#else
NODEPTR Mkrule_36 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_36 _currn;
#ifdef __cplusplus
_currn = new _TPrule_36;
#else
_currn = (_TPPrule_36) TreeNodeAlloc (sizeof (struct _TPrule_36));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_36;
_SETCOORD(_currn)
_TERMACT_rule_36;
return ( (NODEPTR) _currn);
}/* Mkrule_36 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_37 (POSITION *_coordref)
#else
NODEPTR Mkrule_37 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_37 _currn;
#ifdef __cplusplus
_currn = new _TPrule_37;
#else
_currn = (_TPPrule_37) TreeNodeAlloc (sizeof (struct _TPrule_37));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_37;
_SETCOORD(_currn)
_TERMACT_rule_37;
return ( (NODEPTR) _currn);
}/* Mkrule_37 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_38 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_38 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_38 _currn;
#ifdef __cplusplus
_currn = new _TPrule_38;
#else
_currn = (_TPPrule_38) TreeNodeAlloc (sizeof (struct _TPrule_38));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_38;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_38: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPTimeUnit) MkTimeUnit (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_38: root of subtree no. 2 can not be made a TimeUnit node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_38;
return ( (NODEPTR) _currn);
}/* Mkrule_38 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_39 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_39 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_39 _currn;
#ifdef __cplusplus
_currn = new _TPrule_39;
#else
_currn = (_TPPrule_39) TreeNodeAlloc (sizeof (struct _TPrule_39));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_39;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_39: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPCurrentUnit) MkCurrentUnit (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_39: root of subtree no. 2 can not be made a CurrentUnit node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_39;
return ( (NODEPTR) _currn);
}/* Mkrule_39 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_40 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_40 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_40 _currn;
#ifdef __cplusplus
_currn = new _TPrule_40;
#else
_currn = (_TPPrule_40) TreeNodeAlloc (sizeof (struct _TPrule_40));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_40;
_SETCOORD(_currn)
_TERMACT_rule_40;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Ident", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_40 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_41 (POSITION *_coordref)
#else
NODEPTR Mkrule_41 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_41 _currn;
#ifdef __cplusplus
_currn = new _TPrule_41;
#else
_currn = (_TPPrule_41) TreeNodeAlloc (sizeof (struct _TPrule_41));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_41;
_SETCOORD(_currn)
_TERMACT_rule_41;
return ( (NODEPTR) _currn);
}/* Mkrule_41 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_42 (POSITION *_coordref)
#else
NODEPTR Mkrule_42 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_42 _currn;
#ifdef __cplusplus
_currn = new _TPrule_42;
#else
_currn = (_TPPrule_42) TreeNodeAlloc (sizeof (struct _TPrule_42));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_42;
_SETCOORD(_currn)
_TERMACT_rule_42;
return ( (NODEPTR) _currn);
}/* Mkrule_42 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_43 (POSITION *_coordref)
#else
NODEPTR Mkrule_43 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_43 _currn;
#ifdef __cplusplus
_currn = new _TPrule_43;
#else
_currn = (_TPPrule_43) TreeNodeAlloc (sizeof (struct _TPrule_43));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_43;
_SETCOORD(_currn)
_TERMACT_rule_43;
return ( (NODEPTR) _currn);
}/* Mkrule_43 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_44 (POSITION *_coordref)
#else
NODEPTR Mkrule_44 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_44 _currn;
#ifdef __cplusplus
_currn = new _TPrule_44;
#else
_currn = (_TPPrule_44) TreeNodeAlloc (sizeof (struct _TPrule_44));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_44;
_SETCOORD(_currn)
_TERMACT_rule_44;
return ( (NODEPTR) _currn);
}/* Mkrule_44 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_45 (POSITION *_coordref)
#else
NODEPTR Mkrule_45 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_45 _currn;
#ifdef __cplusplus
_currn = new _TPrule_45;
#else
_currn = (_TPPrule_45) TreeNodeAlloc (sizeof (struct _TPrule_45));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_45;
_SETCOORD(_currn)
_TERMACT_rule_45;
return ( (NODEPTR) _currn);
}/* Mkrule_45 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_46 (POSITION *_coordref)
#else
NODEPTR Mkrule_46 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_46 _currn;
#ifdef __cplusplus
_currn = new _TPrule_46;
#else
_currn = (_TPPrule_46) TreeNodeAlloc (sizeof (struct _TPrule_46));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_46;
_SETCOORD(_currn)
_TERMACT_rule_46;
return ( (NODEPTR) _currn);
}/* Mkrule_46 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_47 (POSITION *_coordref)
#else
NODEPTR Mkrule_47 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_47 _currn;
#ifdef __cplusplus
_currn = new _TPrule_47;
#else
_currn = (_TPPrule_47) TreeNodeAlloc (sizeof (struct _TPrule_47));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_47;
_SETCOORD(_currn)
_TERMACT_rule_47;
return ( (NODEPTR) _currn);
}/* Mkrule_47 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_48 (POSITION *_coordref)
#else
NODEPTR Mkrule_48 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_48 _currn;
#ifdef __cplusplus
_currn = new _TPrule_48;
#else
_currn = (_TPPrule_48) TreeNodeAlloc (sizeof (struct _TPrule_48));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_48;
_SETCOORD(_currn)
_TERMACT_rule_48;
return ( (NODEPTR) _currn);
}/* Mkrule_48 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_49 (POSITION *_coordref)
#else
NODEPTR Mkrule_49 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_49 _currn;
#ifdef __cplusplus
_currn = new _TPrule_49;
#else
_currn = (_TPPrule_49) TreeNodeAlloc (sizeof (struct _TPrule_49));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_49;
_SETCOORD(_currn)
_TERMACT_rule_49;
return ( (NODEPTR) _currn);
}/* Mkrule_49 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_50 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_50 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_50 _currn;
#ifdef __cplusplus
_currn = new _TPrule_50;
#else
_currn = (_TPPrule_50) TreeNodeAlloc (sizeof (struct _TPrule_50));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_50;
_SETCOORD(_currn)
_TERMACT_rule_50;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Ident", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_50 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_51 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_51 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_51 _currn;
#ifdef __cplusplus
_currn = new _TPrule_51;
#else
_currn = (_TPPrule_51) TreeNodeAlloc (sizeof (struct _TPrule_51));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_51;
_currn->_desc1 = (_TSPDefIdent) MkDefIdent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 1 can not be made a DefIdent node ", 0, _coordref);
_currn->_desc2 = (_TSPRingCmds) MkRingCmds (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 2 can not be made a RingCmds node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_51;
return ( (NODEPTR) _currn);
}/* Mkrule_51 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_52 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_52 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_52 _currn;
#ifdef __cplusplus
_currn = new _TPrule_52;
#else
_currn = (_TPPrule_52) TreeNodeAlloc (sizeof (struct _TPrule_52));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_52;
_currn->_desc1 = (_TSPDefIdent) MkDefIdent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_52: root of subtree no. 1 can not be made a DefIdent node ", 0, _coordref);
_currn->_desc2 = (_TSPICOSCmds) MkICOSCmds (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_52: root of subtree no. 2 can not be made a ICOSCmds node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_52;
return ( (NODEPTR) _currn);
}/* Mkrule_52 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_062 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_062 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_062 _currn;
#ifdef __cplusplus
_currn = new _TPrule_062;
#else
_currn = (_TPPrule_062) TreeNodeAlloc (sizeof (struct _TPrule_062));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_062;
_currn->_desc1 = (_TSPRingWave) MkRingWave (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_062: root of subtree no. 1 can not be made a RingWave node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_062;
return ( (NODEPTR) _currn);
}/* Mkrule_062 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_061 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_061 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_061 _currn;
#ifdef __cplusplus
_currn = new _TPrule_061;
#else
_currn = (_TPPrule_061) TreeNodeAlloc (sizeof (struct _TPrule_061));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_061;
_currn->_desc1 = (_TSPICOSWave) MkICOSWave (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_061: root of subtree no. 1 can not be made a ICOSWave node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_061;
return ( (NODEPTR) _currn);
}/* Mkrule_061 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_060 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_060 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_060 _currn;
#ifdef __cplusplus
_currn = new _TPrule_060;
#else
_currn = (_TPPrule_060) TreeNodeAlloc (sizeof (struct _TPrule_060));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_060;
_currn->_desc1 = (_TSPTzSpec) MkTzSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_060: root of subtree no. 1 can not be made a TzSpec node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_060;
return ( (NODEPTR) _currn);
}/* Mkrule_060 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_059 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_059 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_059 _currn;
#ifdef __cplusplus
_currn = new _TPrule_059;
#else
_currn = (_TPPrule_059) TreeNodeAlloc (sizeof (struct _TPrule_059));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_059;
_currn->_desc1 = (_TSPTpreVal) MkTpreVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_059: root of subtree no. 1 can not be made a TpreVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_059;
return ( (NODEPTR) _currn);
}/* Mkrule_059 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_058 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_058 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_058 _currn;
#ifdef __cplusplus
_currn = new _TPrule_058;
#else
_currn = (_TPPrule_058) TreeNodeAlloc (sizeof (struct _TPrule_058));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_058;
_currn->_desc1 = (_TSPTonVal) MkTonVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_058: root of subtree no. 1 can not be made a TonVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_058;
return ( (NODEPTR) _currn);
}/* Mkrule_058 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_057 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_057 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_057 _currn;
#ifdef __cplusplus
_currn = new _TPrule_057;
#else
_currn = (_TPPrule_057) TreeNodeAlloc (sizeof (struct _TPrule_057));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_057;
_currn->_desc1 = (_TSPTime) MkTime (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_057: root of subtree no. 1 can not be made a Time node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_057;
return ( (NODEPTR) _currn);
}/* Mkrule_057 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_056 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_056 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_056 _currn;
#ifdef __cplusplus
_currn = new _TPrule_056;
#else
_currn = (_TPPrule_056) TreeNodeAlloc (sizeof (struct _TPrule_056));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_056;
_currn->_desc1 = (_TSPConfigCmds) MkConfigCmds (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_056: root of subtree no. 1 can not be made a ConfigCmds node ", 0, _coordref);
_currn->_desc2 = (_TSPG1) MkG1 (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_056: root of subtree no. 2 can not be made a G1 node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_056;
return ( (NODEPTR) _currn);
}/* Mkrule_056 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_055 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_055 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_055 _currn;
#ifdef __cplusplus
_currn = new _TPrule_055;
#else
_currn = (_TPPrule_055) TreeNodeAlloc (sizeof (struct _TPrule_055));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_055;
_currn->_desc1 = (_TSPRingStepsize) MkRingStepsize (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_055: root of subtree no. 1 can not be made a RingStepsize node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_055;
return ( (NODEPTR) _currn);
}/* Mkrule_055 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_054 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_054 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_054 _currn;
#ifdef __cplusplus
_currn = new _TPrule_054;
#else
_currn = (_TPPrule_054) TreeNodeAlloc (sizeof (struct _TPrule_054));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_054;
_currn->_desc1 = (_TSPRingCount) MkRingCount (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_054: root of subtree no. 1 can not be made a RingCount node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_054;
return ( (NODEPTR) _currn);
}/* Mkrule_054 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_053 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_053 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_053 _currn;
#ifdef __cplusplus
_currn = new _TPrule_053;
#else
_currn = (_TPPrule_053) TreeNodeAlloc (sizeof (struct _TPrule_053));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_053;
_currn->_desc1 = (_TSPRateDef) MkRateDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_053: root of subtree no. 1 can not be made a RateDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_053;
return ( (NODEPTR) _currn);
}/* Mkrule_053 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_052 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_052 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_052 _currn;
#ifdef __cplusplus
_currn = new _TPrule_052;
#else
_currn = (_TPPrule_052) TreeNodeAlloc (sizeof (struct _TPrule_052));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_052;
_currn->_desc1 = (_TSPNsampleDef) MkNsampleDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_052: root of subtree no. 1 can not be made a NsampleDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_052;
return ( (NODEPTR) _currn);
}/* Mkrule_052 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_051 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_051 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_051 _currn;
#ifdef __cplusplus
_currn = new _TPrule_051;
#else
_currn = (_TPPrule_051) TreeNodeAlloc (sizeof (struct _TPrule_051));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_051;
_currn->_desc1 = (_TSPRingCurrent) MkRingCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_051: root of subtree no. 1 can not be made a RingCurrent node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_051;
return ( (NODEPTR) _currn);
}/* Mkrule_051 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_050 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_050 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_050 _currn;
#ifdef __cplusplus
_currn = new _TPrule_050;
#else
_currn = (_TPPrule_050) TreeNodeAlloc (sizeof (struct _TPrule_050));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_050;
_currn->_desc1 = (_TSPCurrentSteps) MkCurrentSteps (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_050: root of subtree no. 1 can not be made a CurrentSteps node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_050;
return ( (NODEPTR) _currn);
}/* Mkrule_050 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_049 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_049 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_049 _currn;
#ifdef __cplusplus
_currn = new _TPrule_049;
#else
_currn = (_TPPrule_049) TreeNodeAlloc (sizeof (struct _TPrule_049));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_049;
_currn->_desc1 = (_TSPCurrent) MkCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_049: root of subtree no. 1 can not be made a Current node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_049;
return ( (NODEPTR) _currn);
}/* Mkrule_049 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_048 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_048 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_048 _currn;
#ifdef __cplusplus
_currn = new _TPrule_048;
#else
_currn = (_TPPrule_048) TreeNodeAlloc (sizeof (struct _TPrule_048));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_048;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_048: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_048;
return ( (NODEPTR) _currn);
}/* Mkrule_048 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_047 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_047 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_047 _currn;
#ifdef __cplusplus
_currn = new _TPrule_047;
#else
_currn = (_TPPrule_047) TreeNodeAlloc (sizeof (struct _TPrule_047));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_047;
_currn->_desc1 = (_TSPTpreDef) MkTpreDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_047: root of subtree no. 1 can not be made a TpreDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_047;
return ( (NODEPTR) _currn);
}/* Mkrule_047 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_046 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_046 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_046 _currn;
#ifdef __cplusplus
_currn = new _TPrule_046;
#else
_currn = (_TPPrule_046) TreeNodeAlloc (sizeof (struct _TPrule_046));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_046;
_currn->_desc1 = (_TSPTonDef) MkTonDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_046: root of subtree no. 1 can not be made a TonDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_046;
return ( (NODEPTR) _currn);
}/* Mkrule_046 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_045 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_045 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_045 _currn;
#ifdef __cplusplus
_currn = new _TPrule_045;
#else
_currn = (_TPPrule_045) TreeNodeAlloc (sizeof (struct _TPrule_045));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_045;
_currn->_desc1 = (_TSPToffDef) MkToffDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_045: root of subtree no. 1 can not be made a ToffDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_045;
return ( (NODEPTR) _currn);
}/* Mkrule_045 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_044 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_044 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_044 _currn;
#ifdef __cplusplus
_currn = new _TPrule_044;
#else
_currn = (_TPPrule_044) TreeNodeAlloc (sizeof (struct _TPrule_044));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_044;
_currn->_desc1 = (_TSPRingRateDef) MkRingRateDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_044: root of subtree no. 1 can not be made a RingRateDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_044;
return ( (NODEPTR) _currn);
}/* Mkrule_044 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_043 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_043 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_043 _currn;
#ifdef __cplusplus
_currn = new _TPrule_043;
#else
_currn = (_TPPrule_043) TreeNodeAlloc (sizeof (struct _TPrule_043));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_043;
_currn->_desc1 = (_TSPRingNsampleDef) MkRingNsampleDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_043: root of subtree no. 1 can not be made a RingNsampleDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_043;
return ( (NODEPTR) _currn);
}/* Mkrule_043 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_042 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_042 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_042 _currn;
#ifdef __cplusplus
_currn = new _TPrule_042;
#else
_currn = (_TPPrule_042) TreeNodeAlloc (sizeof (struct _TPrule_042));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_042;
_currn->_desc1 = (_TSPRingData) MkRingData (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_042: root of subtree no. 1 can not be made a RingData node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_042;
return ( (NODEPTR) _currn);
}/* Mkrule_042 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_041 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_041 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_041 _currn;
#ifdef __cplusplus
_currn = new _TPrule_041;
#else
_currn = (_TPPrule_041) TreeNodeAlloc (sizeof (struct _TPrule_041));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_041;
_currn->_desc1 = (_TSPNcoaddDef) MkNcoaddDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_041: root of subtree no. 1 can not be made a NcoaddDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_041;
return ( (NODEPTR) _currn);
}/* Mkrule_041 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_040 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_040 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_040 _currn;
#ifdef __cplusplus
_currn = new _TPrule_040;
#else
_currn = (_TPPrule_040) TreeNodeAlloc (sizeof (struct _TPrule_040));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_040;
_currn->_desc1 = (_TSPIzDef) MkIzDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_040: root of subtree no. 1 can not be made a IzDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_040;
return ( (NODEPTR) _currn);
}/* Mkrule_040 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_039 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_039 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_039 _currn;
#ifdef __cplusplus
_currn = new _TPrule_039;
#else
_currn = (_TPPrule_039) TreeNodeAlloc (sizeof (struct _TPrule_039));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_039;
_currn->_desc1 = (_TSPDAC3def) MkDAC3def (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_039: root of subtree no. 1 can not be made a DAC3def node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_039;
return ( (NODEPTR) _currn);
}/* Mkrule_039 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_038 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_038 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_038 _currn;
#ifdef __cplusplus
_currn = new _TPrule_038;
#else
_currn = (_TPPrule_038) TreeNodeAlloc (sizeof (struct _TPrule_038));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_038;
_currn->_desc1 = (_TSPQCLIConfigType) MkQCLIConfigType (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_038: root of subtree no. 1 can not be made a QCLIConfigType node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_038;
return ( (NODEPTR) _currn);
}/* Mkrule_038 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_037 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_037 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_037 _currn;
#ifdef __cplusplus
_currn = new _TPrule_037;
#else
_currn = (_TPPrule_037) TreeNodeAlloc (sizeof (struct _TPrule_037));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_037;
_currn->_desc1 = (_TSPTime) MkTime (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_037: root of subtree no. 1 can not be made a Time node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_037;
return ( (NODEPTR) _currn);
}/* Mkrule_037 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_036 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_036 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_036 _currn;
#ifdef __cplusplus
_currn = new _TPrule_036;
#else
_currn = (_TPPrule_036) TreeNodeAlloc (sizeof (struct _TPrule_036));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_036;
_currn->_desc1 = (_TSPTime) MkTime (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_036: root of subtree no. 1 can not be made a Time node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_036;
return ( (NODEPTR) _currn);
}/* Mkrule_036 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_035 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_035 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_035 _currn;
#ifdef __cplusplus
_currn = new _TPrule_035;
#else
_currn = (_TPPrule_035) TreeNodeAlloc (sizeof (struct _TPrule_035));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_035;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_035: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_035;
return ( (NODEPTR) _currn);
}/* Mkrule_035 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_034 (POSITION *_coordref)
#else
NODEPTR Mkrule_034 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_034 _currn;
#ifdef __cplusplus
_currn = new _TPrule_034;
#else
_currn = (_TPPrule_034) TreeNodeAlloc (sizeof (struct _TPrule_034));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_034;
_SETCOORD(_currn)
_TERMACT_rule_034;
return ( (NODEPTR) _currn);
}/* Mkrule_034 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_033 (POSITION *_coordref)
#else
NODEPTR Mkrule_033 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_033 _currn;
#ifdef __cplusplus
_currn = new _TPrule_033;
#else
_currn = (_TPPrule_033) TreeNodeAlloc (sizeof (struct _TPrule_033));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_033;
_SETCOORD(_currn)
_TERMACT_rule_033;
return ( (NODEPTR) _currn);
}/* Mkrule_033 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_032 (POSITION *_coordref)
#else
NODEPTR Mkrule_032 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_032 _currn;
#ifdef __cplusplus
_currn = new _TPrule_032;
#else
_currn = (_TPPrule_032) TreeNodeAlloc (sizeof (struct _TPrule_032));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_032;
_SETCOORD(_currn)
_TERMACT_rule_032;
return ( (NODEPTR) _currn);
}/* Mkrule_032 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_031 (POSITION *_coordref)
#else
NODEPTR Mkrule_031 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_031 _currn;
#ifdef __cplusplus
_currn = new _TPrule_031;
#else
_currn = (_TPPrule_031) TreeNodeAlloc (sizeof (struct _TPrule_031));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_031;
_SETCOORD(_currn)
_TERMACT_rule_031;
return ( (NODEPTR) _currn);
}/* Mkrule_031 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_030 (POSITION *_coordref)
#else
NODEPTR Mkrule_030 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_030 _currn;
#ifdef __cplusplus
_currn = new _TPrule_030;
#else
_currn = (_TPPrule_030) TreeNodeAlloc (sizeof (struct _TPrule_030));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_030;
_SETCOORD(_currn)
_TERMACT_rule_030;
return ( (NODEPTR) _currn);
}/* Mkrule_030 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_029 (POSITION *_coordref)
#else
NODEPTR Mkrule_029 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_029 _currn;
#ifdef __cplusplus
_currn = new _TPrule_029;
#else
_currn = (_TPPrule_029) TreeNodeAlloc (sizeof (struct _TPrule_029));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_029;
_SETCOORD(_currn)
_TERMACT_rule_029;
return ( (NODEPTR) _currn);
}/* Mkrule_029 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_028 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_028 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_028 _currn;
#ifdef __cplusplus
_currn = new _TPrule_028;
#else
_currn = (_TPPrule_028) TreeNodeAlloc (sizeof (struct _TPrule_028));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_028;
_currn->_desc1 = (_TSPCurrent) MkCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_028: root of subtree no. 1 can not be made a Current node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_028;
return ( (NODEPTR) _currn);
}/* Mkrule_028 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_027 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_027 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_027 _currn;
#ifdef __cplusplus
_currn = new _TPrule_027;
#else
_currn = (_TPPrule_027) TreeNodeAlloc (sizeof (struct _TPrule_027));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_027;
_currn->_desc1 = (_TSPCurrent) MkCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_027: root of subtree no. 1 can not be made a Current node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_027;
return ( (NODEPTR) _currn);
}/* Mkrule_027 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_026 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_026 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_026 _currn;
#ifdef __cplusplus
_currn = new _TPrule_026;
#else
_currn = (_TPPrule_026) TreeNodeAlloc (sizeof (struct _TPrule_026));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_026;
_currn->_desc1 = (_TSPCurrent) MkCurrent (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_026: root of subtree no. 1 can not be made a Current node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_026;
return ( (NODEPTR) _currn);
}/* Mkrule_026 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_025 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_025 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_025 _currn;
#ifdef __cplusplus
_currn = new _TPrule_025;
#else
_currn = (_TPPrule_025) TreeNodeAlloc (sizeof (struct _TPrule_025));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_025;
_currn->_desc1 = (_TSPRateDef) MkRateDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_025: root of subtree no. 1 can not be made a RateDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_025;
return ( (NODEPTR) _currn);
}/* Mkrule_025 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_024 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_024 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_024 _currn;
#ifdef __cplusplus
_currn = new _TPrule_024;
#else
_currn = (_TPPrule_024) TreeNodeAlloc (sizeof (struct _TPrule_024));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_024;
_currn->_desc1 = (_TSPNsampleDef) MkNsampleDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_024: root of subtree no. 1 can not be made a NsampleDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_024;
return ( (NODEPTR) _currn);
}/* Mkrule_024 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_023 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_023 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_023 _currn;
#ifdef __cplusplus
_currn = new _TPrule_023;
#else
_currn = (_TPPrule_023) TreeNodeAlloc (sizeof (struct _TPrule_023));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_023;
_currn->_desc1 = (_TSPG3) MkG3 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_023: root of subtree no. 1 can not be made a G3 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_023;
return ( (NODEPTR) _currn);
}/* Mkrule_023 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_022 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_022 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_022 _currn;
#ifdef __cplusplus
_currn = new _TPrule_022;
#else
_currn = (_TPPrule_022) TreeNodeAlloc (sizeof (struct _TPrule_022));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_022;
_currn->_desc1 = (_TSPdIdt) MkdIdt (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_022: root of subtree no. 1 can not be made a dIdt node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_022;
return ( (NODEPTR) _currn);
}/* Mkrule_022 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_021 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_021 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_021 _currn;
#ifdef __cplusplus
_currn = new _TPrule_021;
#else
_currn = (_TPPrule_021) TreeNodeAlloc (sizeof (struct _TPrule_021));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_021;
_currn->_desc1 = (_TSPTzDef) MkTzDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_021: root of subtree no. 1 can not be made a TzDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_021;
return ( (NODEPTR) _currn);
}/* Mkrule_021 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_020 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_020 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_020 _currn;
#ifdef __cplusplus
_currn = new _TPrule_020;
#else
_currn = (_TPPrule_020) TreeNodeAlloc (sizeof (struct _TPrule_020));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_020;
_currn->_desc1 = (_TSPNcoaddDef) MkNcoaddDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_020: root of subtree no. 1 can not be made a NcoaddDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_020;
return ( (NODEPTR) _currn);
}/* Mkrule_020 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_019 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_019 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_019 _currn;
#ifdef __cplusplus
_currn = new _TPrule_019;
#else
_currn = (_TPPrule_019) TreeNodeAlloc (sizeof (struct _TPrule_019));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_019;
_currn->_desc1 = (_TSPIzDef) MkIzDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_019: root of subtree no. 1 can not be made a IzDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_019;
return ( (NODEPTR) _currn);
}/* Mkrule_019 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_018 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_018 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_018 _currn;
#ifdef __cplusplus
_currn = new _TPrule_018;
#else
_currn = (_TPPrule_018) TreeNodeAlloc (sizeof (struct _TPrule_018));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_018;
_currn->_desc1 = (_TSPICOSRateDef) MkICOSRateDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_018: root of subtree no. 1 can not be made a ICOSRateDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_018;
return ( (NODEPTR) _currn);
}/* Mkrule_018 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_017 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_017 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_017 _currn;
#ifdef __cplusplus
_currn = new _TPrule_017;
#else
_currn = (_TPPrule_017) TreeNodeAlloc (sizeof (struct _TPrule_017));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_017;
_currn->_desc1 = (_TSPICOSRamp) MkICOSRamp (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_017: root of subtree no. 1 can not be made a ICOSRamp node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_017;
return ( (NODEPTR) _currn);
}/* Mkrule_017 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_016 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_016 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_016 _currn;
#ifdef __cplusplus
_currn = new _TPrule_016;
#else
_currn = (_TPPrule_016) TreeNodeAlloc (sizeof (struct _TPrule_016));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_016;
_currn->_desc1 = (_TSPICOSNsampleDef) MkICOSNsampleDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_016: root of subtree no. 1 can not be made a ICOSNsampleDef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_016;
return ( (NODEPTR) _currn);
}/* Mkrule_016 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_015 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_015 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_015 _currn;
#ifdef __cplusplus
_currn = new _TPrule_015;
#else
_currn = (_TPPrule_015) TreeNodeAlloc (sizeof (struct _TPrule_015));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_015;
_currn->_desc1 = (_TSPDAC3def) MkDAC3def (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_015: root of subtree no. 1 can not be made a DAC3def node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_015;
return ( (NODEPTR) _currn);
}/* Mkrule_015 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_014 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_014 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_014 _currn;
#ifdef __cplusplus
_currn = new _TPrule_014;
#else
_currn = (_TPPrule_014) TreeNodeAlloc (sizeof (struct _TPrule_014));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_014;
_currn->_desc1 = (_TSPRingCmd) MkRingCmd (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_014: root of subtree no. 1 can not be made a RingCmd node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_014;
return ( (NODEPTR) _currn);
}/* Mkrule_014 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_013 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_013 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_013 _currn;
#ifdef __cplusplus
_currn = new _TPrule_013;
#else
_currn = (_TPPrule_013) TreeNodeAlloc (sizeof (struct _TPrule_013));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_013;
_currn->_desc1 = (_TSPG4) MkG4 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_013: root of subtree no. 1 can not be made a G4 node ", 0, _coordref);
_currn->_desc2 = (_TSPRingCmd) MkRingCmd (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_013: root of subtree no. 2 can not be made a RingCmd node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_013;
return ( (NODEPTR) _currn);
}/* Mkrule_013 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_012 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_012 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_012 _currn;
#ifdef __cplusplus
_currn = new _TPrule_012;
#else
_currn = (_TPPrule_012) TreeNodeAlloc (sizeof (struct _TPrule_012));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_012;
_currn->_desc1 = (_TSPICOSCmd) MkICOSCmd (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_012: root of subtree no. 1 can not be made a ICOSCmd node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_012;
return ( (NODEPTR) _currn);
}/* Mkrule_012 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_011 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_011 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_011 _currn;
#ifdef __cplusplus
_currn = new _TPrule_011;
#else
_currn = (_TPPrule_011) TreeNodeAlloc (sizeof (struct _TPrule_011));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_011;
_currn->_desc1 = (_TSPG3) MkG3 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_011: root of subtree no. 1 can not be made a G3 node ", 0, _coordref);
_currn->_desc2 = (_TSPICOSCmd) MkICOSCmd (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_011: root of subtree no. 2 can not be made a ICOSCmd node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_011;
return ( (NODEPTR) _currn);
}/* Mkrule_011 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_010 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_010 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_010 _currn;
#ifdef __cplusplus
_currn = new _TPrule_010;
#else
_currn = (_TPPrule_010) TreeNodeAlloc (sizeof (struct _TPrule_010));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_010;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_010: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_currn->_desc2 = (_TSPConfigCmd) MkConfigCmd (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_010: root of subtree no. 2 can not be made a ConfigCmd node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_010;
return ( (NODEPTR) _currn);
}/* Mkrule_010 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_09 (POSITION *_coordref)
#else
NODEPTR Mkrule_09 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_09 _currn;
#ifdef __cplusplus
_currn = new _TPrule_09;
#else
_currn = (_TPPrule_09) TreeNodeAlloc (sizeof (struct _TPrule_09));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_09;
_SETCOORD(_currn)
_TERMACT_rule_09;
return ( (NODEPTR) _currn);
}/* Mkrule_09 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_08 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_08 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_08 _currn;
#ifdef __cplusplus
_currn = new _TPrule_08;
#else
_currn = (_TPPrule_08) TreeNodeAlloc (sizeof (struct _TPrule_08));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_08;
_currn->_desc1 = (_TSPWave) MkWave (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_08: root of subtree no. 1 can not be made a Wave node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_08;
return ( (NODEPTR) _currn);
}/* Mkrule_08 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_07 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_07 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_07 _currn;
#ifdef __cplusplus
_currn = new _TPrule_07;
#else
_currn = (_TPPrule_07) TreeNodeAlloc (sizeof (struct _TPrule_07));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_07;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_07: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPWave) MkWave (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_07: root of subtree no. 2 can not be made a Wave node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_07;
return ( (NODEPTR) _currn);
}/* Mkrule_07 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_06 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_06 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_06 _currn;
#ifdef __cplusplus
_currn = new _TPrule_06;
#else
_currn = (_TPPrule_06) TreeNodeAlloc (sizeof (struct _TPrule_06));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_06;
_currn->_desc1 = (_TSPDigitizerType) MkDigitizerType (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_06: root of subtree no. 1 can not be made a DigitizerType node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_06;
return ( (NODEPTR) _currn);
}/* Mkrule_06 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_05 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_05 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_05 _currn;
#ifdef __cplusplus
_currn = new _TPrule_05;
#else
_currn = (_TPPrule_05) TreeNodeAlloc (sizeof (struct _TPrule_05));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_05;
_currn->_desc1 = (_TSPDAC3Value) MkDAC3Value (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_05: root of subtree no. 1 can not be made a DAC3Value node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_05;
return ( (NODEPTR) _currn);
}/* Mkrule_05 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_04 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_04 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_04 _currn;
#ifdef __cplusplus
_currn = new _TPrule_04;
#else
_currn = (_TPPrule_04) TreeNodeAlloc (sizeof (struct _TPrule_04));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_04;
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_04: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_04;
return ( (NODEPTR) _currn);
}/* Mkrule_04 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_03 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_03 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_03 _currn;
#ifdef __cplusplus
_currn = new _TPrule_03;
#else
_currn = (_TPPrule_03) TreeNodeAlloc (sizeof (struct _TPrule_03));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_03;
_currn->_desc1 = (_TSPQCLIConfig) MkQCLIConfig (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_03: root of subtree no. 1 can not be made a QCLIConfig node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_03;
return ( (NODEPTR) _currn);
}/* Mkrule_03 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_02 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_02 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_02 _currn;
#ifdef __cplusplus
_currn = new _TPrule_02;
#else
_currn = (_TPPrule_02) TreeNodeAlloc (sizeof (struct _TPrule_02));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_02;
_currn->_desc1 = (_TSPPrefix) MkPrefix (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_02: root of subtree no. 1 can not be made a Prefix node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_02;
return ( (NODEPTR) _currn);
}/* Mkrule_02 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_01 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_01 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_01 _currn;
#ifdef __cplusplus
_currn = new _TPrule_01;
#else
_currn = (_TPPrule_01) TreeNodeAlloc (sizeof (struct _TPrule_01));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_01;
_currn->_desc1 = (_TSPDigitizer) MkDigitizer (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_01: root of subtree no. 1 can not be made a Digitizer node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_01;
return ( (NODEPTR) _currn);
}/* Mkrule_01 */
