
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

void InitTree(void)
{
	obstack_init(&TreeSpace);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

void FreeTree(void)
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

void InitTree(void) { }

void FreeTree(void) { }

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
NODEPTR MkTableDefs (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTableDefs (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTableDefs)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBTDunterminated)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBColumns)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBVField)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_034(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_034(_coordref, _currn));
return(NULLNODEPTR);
}/* MkTableDefs */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTDunterminated (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTDunterminated (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTDunterminated)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBColumns)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBVField)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_029(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_029(_coordref, _currn));
return(NULLNODEPTR);
}/* MkTDunterminated */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkHBunterminated (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkHBunterminated (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBHBunterminated)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBHFIELD)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_022(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_022(_coordref, _currn));
return(NULLNODEPTR);
}/* MkHBunterminated */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkHBFields (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkHBFields (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBHBFields)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBHBunterminated)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBHFIELD)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_019(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_019(_coordref, _currn));
return(NULLNODEPTR);
}/* MkHBFields */

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
NODEPTR MkG2 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG2 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG2)) return (_currn);
if (IsSymb (_currn, SYMBLeftAlignChar)) return (Mkrule_09(_coordref, _currn));
return(NULLNODEPTR);
}/* MkG2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG1 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG1 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG1)) return (_currn);
if (IsSymb (_currn, SYMBCField)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_06(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_06(_coordref, _currn));
return(NULLNODEPTR);
}/* MkG1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkGAField (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkGAField (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBGAField)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_013(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_013(_coordref, _currn));
return(NULLNODEPTR);
}/* MkGAField */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTableNameUse (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTableNameUse (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTableNameUse)) return (_currn);
return(NULLNODEPTR);
}/* MkTableNameUse */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTableNameDef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTableNameDef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTableNameDef)) return (_currn);
return(NULLNODEPTR);
}/* MkTableNameDef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkUnnamedTable (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkUnnamedTable (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBUnnamedTable)) return (_currn);
if (IsSymb (_currn, SYMBTable)) return (Mkrule_4(_coordref, _currn));
return(NULLNODEPTR);
}/* MkUnnamedTable */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNamedTables (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNamedTables (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNamedTables)) return (_currn);
return(NULLNODEPTR);
}/* MkNamedTables */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTableRef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTableRef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTableRef)) return (_currn);
return(NULLNODEPTR);
}/* MkTableRef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkHFIELD (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkHFIELD (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBHFIELD)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_023(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_016(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_016(_coordref, _currn));
return(NULLNODEPTR);
}/* MkHFIELD */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkCField (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkCField (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBCField)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_02(_coordref, _currn));
return(NULLNODEPTR);
}/* MkCField */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkColumns (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkColumns (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBColumns)) return (_currn);
return(NULLNODEPTR);
}/* MkColumns */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkGFIELD (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkGFIELD (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBGFIELD)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_10(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_10(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_13(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_15(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_14(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_13(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_12(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_11(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_10(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_16(_coordref, _currn));
return(NULLNODEPTR);
}/* MkGFIELD */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRightAlign (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRightAlign (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRightAlign)) return (_currn);
if (IsSymb (_currn, SYMBG3)) return (Mkrule_026(_coordref, _currn));
return(NULLNODEPTR);
}/* MkRightAlign */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLeftAlign (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLeftAlign (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLeftAlign)) return (_currn);
if (IsSymb (_currn, SYMBLeftAlignChar)) return (Mkrule_024(_coordref, _currn));
if (IsSymb (_currn, SYMBG2)) return (Mkrule_024(_coordref, _currn));
return(NULLNODEPTR);
}/* MkLeftAlign */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRightAlignChar (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRightAlignChar (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRightAlignChar)) return (_currn);
return(NULLNODEPTR);
}/* MkRightAlignChar */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLeftAlignChar (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLeftAlignChar (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLeftAlignChar)) return (_currn);
return(NULLNODEPTR);
}/* MkLeftAlignChar */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDatumDimensions (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDatumDimensions (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDatumDimensions)) return (_currn);
return(NULLNODEPTR);
}/* MkDatumDimensions */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDatum (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDatum (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDatum)) return (_currn);
return(NULLNODEPTR);
}/* MkDatum */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkHWord (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkHWord (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBHWord)) return (_currn);
if (IsSymb (_currn, SYMBWord)) return (Mkrule_21(_coordref, _currn));
return(NULLNODEPTR);
}/* MkHWord */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkVField (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkVField (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBVField)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBColumns)) return (Mkrule_035(_coordref, _currn));
if (IsSymb (_currn, SYMBGAField)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBWord)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBHBOX)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBTableRef)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBHWord)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBDatum)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBRule)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBGlue)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBGFIELD)) return (Mkrule_036(_coordref, _currn));
if (IsSymb (_currn, SYMBTable)) return (Mkrule_036(_coordref, _currn));
return(NULLNODEPTR);
}/* MkVField */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkHBOX (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkHBOX (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBHBOX)) return (_currn);
return(NULLNODEPTR);
}/* MkHBOX */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkTable (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkTable (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBTable)) return (_currn);
return(NULLNODEPTR);
}/* MkTable */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkNamedTable (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkNamedTable (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBNamedTable)) return (_currn);
return(NULLNODEPTR);
}/* MkNamedTable */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkAttr (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkAttr (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBAttr)) return (_currn);
return(NULLNODEPTR);
}/* MkAttr */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkInput (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkInput (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBInput)) return (_currn);
return(NULLNODEPTR);
}/* MkInput */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkRule (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkRule (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBRule)) return (_currn);
return(NULLNODEPTR);
}/* MkRule */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkGlue (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkGlue (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBGlue)) return (_currn);
if (IsSymb (_currn, SYMBHGlue)) return (Mkrule_014(_coordref, _currn));
if (IsSymb (_currn, SYMBVGlue)) return (Mkrule_015(_coordref, _currn));
return(NULLNODEPTR);
}/* MkGlue */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkVGlue (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkVGlue (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBVGlue)) return (_currn);
return(NULLNODEPTR);
}/* MkVGlue */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkHGlue (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkHGlue (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBHGlue)) return (_currn);
return(NULLNODEPTR);
}/* MkHGlue */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkVDimension (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkVDimension (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBVDimension)) return (_currn);
if (IsSymb (_currn, SYMBSpace)) return (Mkrule_31(_coordref, _currn));
if (IsSymb (_currn, SYMBDimension)) return (Mkrule_31(_coordref, _currn));
return(NULLNODEPTR);
}/* MkVDimension */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkHDimension (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkHDimension (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBHDimension)) return (_currn);
if (IsSymb (_currn, SYMBSpace)) return (Mkrule_32(_coordref, _currn));
if (IsSymb (_currn, SYMBDimension)) return (Mkrule_32(_coordref, _currn));
return(NULLNODEPTR);
}/* MkHDimension */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkGlueSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkGlueSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBGlueSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkGlueSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkSpace (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkSpace (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBSpace)) return (_currn);
return(NULLNODEPTR);
}/* MkSpace */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkDimension (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkDimension (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBDimension)) return (_currn);
if (IsSymb (_currn, SYMBSpace)) return (Mkrule_05(_coordref, _currn));
return(NULLNODEPTR);
}/* MkDimension */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkWord (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkWord (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBWord)) return (_currn);
return(NULLNODEPTR);
}/* MkWord */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkProgram (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkProgram (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBProgram)) return (_currn);
return(NULLNODEPTR);
}/* MkProgram */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_1 (POSITION *_coordref)
#else
NODEPTR Mkrule_1 (_coordref)
	POSITION *_coordref;
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
_SETCOORD(_currn)
_TERMACT_rule_1;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_2 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPNamedTables) MkNamedTables (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_2: root of subtree no. 1 can not be made a NamedTables node ", 0, _coordref);
_currn->_desc2 = (_TSPInput) MkInput (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_2: root of subtree no. 2 can not be made a Input node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_2;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_3 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_3 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPNamedTables) MkNamedTables (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 1 can not be made a NamedTables node ", 0, _coordref);
_currn->_desc2 = (_TSPNamedTable) MkNamedTable (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_3: root of subtree no. 2 can not be made a NamedTable node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_3;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_4 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_4 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPTable) MkTable (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_4: root of subtree no. 1 can not be made a Table node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_4;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_5 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
_SETCOORD(_currn)
_TERMACT_rule_5;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "BareWord", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPTableNameUse) MkTableNameUse (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_6: root of subtree no. 1 can not be made a TableNameUse node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_6;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_7 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_7 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
_SETCOORD(_currn)
_TERMACT_rule_7;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "BareWord", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_8 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_8 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPTableNameDef) MkTableNameDef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 1 can not be made a TableNameDef node ", 0, _coordref);
_currn->_desc2 = (_TSPTable) MkTable (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_8: root of subtree no. 2 can not be made a Table node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_8;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_9 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPNamedTables) MkNamedTables (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 1 can not be made a NamedTables node ", 0, _coordref);
_currn->_desc2 = (_TSPUnnamedTable) MkUnnamedTable (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_9: root of subtree no. 2 can not be made a UnnamedTable node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_9;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPGlue) MkGlue (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_10: root of subtree no. 1 can not be made a Glue node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_10;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_11 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_11 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPRule) MkRule (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 1 can not be made a Rule node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_11;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_11 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_12 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_12 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPDatum) MkDatum (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_12: root of subtree no. 1 can not be made a Datum node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_12;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHWord) MkHWord (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_13: root of subtree no. 1 can not be made a HWord node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_13;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPTableRef) MkTableRef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_14: root of subtree no. 1 can not be made a TableRef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_14;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHBOX) MkHBOX (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_15: root of subtree no. 1 can not be made a HBOX node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_15;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_15 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_16 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_16 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPTable) MkTable (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_16: root of subtree no. 1 can not be made a Table node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_16;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_16 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_17 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_17 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPHDimension) MkHDimension (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 1 can not be made a HDimension node ", 0, _coordref);
_currn->_desc2 = (_TSPVDimension) MkVDimension (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 2 can not be made a VDimension node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_17;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_17 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_18 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_18 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPHDimension) MkHDimension (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_18: root of subtree no. 1 can not be made a HDimension node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_18;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_19 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_20 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_20 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPWord) MkWord (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_20: root of subtree no. 1 can not be made a Word node ", 0, _coordref);
_currn->_desc2 = (_TSPDatumDimensions) MkDatumDimensions (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_20: root of subtree no. 2 can not be made a DatumDimensions node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_20;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_20 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_21 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_21 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPWord) MkWord (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_21: root of subtree no. 1 can not be made a Word node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_21;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_21 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_22 (POSITION *_coordref)
#else
NODEPTR Mkrule_22 (_coordref)
	POSITION *_coordref;
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
_SETCOORD(_currn)
_TERMACT_rule_22;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_22 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_23 (POSITION *_coordref)
#else
NODEPTR Mkrule_23 (_coordref)
	POSITION *_coordref;
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
_SETCOORD(_currn)
_TERMACT_rule_23;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_23 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_24 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_24 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
_SETCOORD(_currn)
_TERMACT_rule_24;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_24 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_25 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_25 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
_SETCOORD(_currn)
_TERMACT_rule_25;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "CString", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_dapto_term_int((_currn)->_uid, "RuleString", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_26 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_27 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_27 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPVDimension) MkVDimension (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_27: root of subtree no. 1 can not be made a VDimension node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_27;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHDimension) MkHDimension (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 1 can not be made a HDimension node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_28;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_28 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_29 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_29 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_29 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_30 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_30 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_30 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_31 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_31 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPDimension) MkDimension (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_31: root of subtree no. 1 can not be made a Dimension node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_31;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_31 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_32 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_32 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPDimension) MkDimension (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_32: root of subtree no. 1 can not be made a Dimension node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_32;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_32 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_33 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_33 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "CString", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_33 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_34 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_34 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
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
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "BareWord", _TERM1);
#endif

(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_34 */

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
_currn->_desc1 = (_TSPGAField) MkGAField (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_036: root of subtree no. 1 can not be made a GAField node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_036;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPColumns) MkColumns (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_035: root of subtree no. 1 can not be made a Columns node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_035;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_035 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_034 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_034 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPTDunterminated) MkTDunterminated (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_034: root of subtree no. 1 can not be made a TDunterminated node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_034;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_034 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_033 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_033 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPTDunterminated) MkTDunterminated (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_033: root of subtree no. 1 can not be made a TDunterminated node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_033;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_032 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_031 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_031 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPTableDefs) MkTableDefs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_031: root of subtree no. 1 can not be made a TableDefs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_031;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_031 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_030 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_030 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPTableDefs) MkTableDefs (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_030: root of subtree no. 1 can not be made a TableDefs node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_030;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_030 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_029 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_029 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPVField) MkVField (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_029: root of subtree no. 1 can not be made a VField node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_029;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_029 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_028 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_028 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPTDunterminated) MkTDunterminated (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_028: root of subtree no. 1 can not be made a TDunterminated node ", 0, _coordref);
_currn->_desc2 = (_TSPVField) MkVField (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_028: root of subtree no. 2 can not be made a VField node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_028;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_028 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_027 (POSITION *_coordref)
#else
NODEPTR Mkrule_027 (_coordref)
	POSITION *_coordref;
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
_SETCOORD(_currn)
_TERMACT_rule_027;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPG3) MkG3 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_026: root of subtree no. 1 can not be made a G3 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_026;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_026 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_025 (POSITION *_coordref)
#else
NODEPTR Mkrule_025 (_coordref)
	POSITION *_coordref;
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
_SETCOORD(_currn)
_TERMACT_rule_025;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_024: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_024;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPGAField) MkGAField (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_023: root of subtree no. 1 can not be made a GAField node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_023;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHFIELD) MkHFIELD (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_022: root of subtree no. 1 can not be made a HFIELD node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_022;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_022 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_021 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_021 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPHBunterminated) MkHBunterminated (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_021: root of subtree no. 1 can not be made a HBunterminated node ", 0, _coordref);
_currn->_desc2 = (_TSPHFIELD) MkHFIELD (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_021: root of subtree no. 2 can not be made a HFIELD node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_021;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHBFields) MkHBFields (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_020: root of subtree no. 1 can not be made a HBFields node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_020;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHBunterminated) MkHBunterminated (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_019: root of subtree no. 1 can not be made a HBunterminated node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_019;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHBunterminated) MkHBunterminated (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_018: root of subtree no. 1 can not be made a HBunterminated node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_018;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_018 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_017 (POSITION *_coordref)
#else
NODEPTR Mkrule_017 (_coordref)
	POSITION *_coordref;
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
_SETCOORD(_currn)
_TERMACT_rule_017;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPGFIELD) MkGFIELD (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_016: root of subtree no. 1 can not be made a GFIELD node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_016;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPVGlue) MkVGlue (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_015: root of subtree no. 1 can not be made a VGlue node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_015;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPHGlue) MkHGlue (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_014: root of subtree no. 1 can not be made a HGlue node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_014;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_014 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_013 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_013 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPGFIELD) MkGFIELD (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_013: root of subtree no. 1 can not be made a GFIELD node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_013;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_013 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_012 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_012 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPAttr) MkAttr (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_012: root of subtree no. 1 can not be made a Attr node ", 0, _coordref);
_currn->_desc2 = (_TSPGFIELD) MkGFIELD (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_012: root of subtree no. 2 can not be made a GFIELD node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_012;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc2 = (_TSPRightAlignChar) MkRightAlignChar (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_011: root of subtree no. 2 can not be made a RightAlignChar node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_011;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_011 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_010 (POSITION *_coordref)
#else
NODEPTR Mkrule_010 (_coordref)
	POSITION *_coordref;
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
_SETCOORD(_currn)
_TERMACT_rule_010;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_010 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_09 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_09 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
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
_currn->_desc1 = (_TSPLeftAlignChar) MkLeftAlignChar (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_09: root of subtree no. 1 can not be made a LeftAlignChar node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_09;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_09 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_08 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_08 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPG2) MkG2 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_08: root of subtree no. 1 can not be made a G2 node ", 0, _coordref);
_currn->_desc2 = (_TSPLeftAlignChar) MkLeftAlignChar (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_08: root of subtree no. 2 can not be made a LeftAlignChar node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_08;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc2 = (_TSPCField) MkCField (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_07: root of subtree no. 2 can not be made a CField node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_07;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPCField) MkCField (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_06: root of subtree no. 1 can not be made a CField node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_06;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPSpace) MkSpace (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_05: root of subtree no. 1 can not be made a Space node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_05;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_05 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_04 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_04 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPSpace) MkSpace (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_04: root of subtree no. 1 can not be made a Space node ", 0, _coordref);
_currn->_desc2 = (_TSPGlueSpec) MkGlueSpec (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_04: root of subtree no. 2 can not be made a GlueSpec node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_04;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_04 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_03 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_03 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
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
_currn->_desc1 = (_TSPCField) MkCField (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_03: root of subtree no. 1 can not be made a CField node ", 0, _coordref);
_currn->_desc2 = (_TSPG1) MkG1 (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_03: root of subtree no. 2 can not be made a G1 node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_03;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
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
_currn->_desc1 = (_TSPGAField) MkGAField (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_02: root of subtree no. 1 can not be made a GAField node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_02;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_02 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_01 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3)
#else
NODEPTR Mkrule_01 (_coordref,_desc1,_desc2,_desc3)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
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
_currn->_desc1 = (_TSPLeftAlign) MkLeftAlign (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_01: root of subtree no. 1 can not be made a LeftAlign node ", 0, _coordref);
_currn->_desc2 = (_TSPHFIELD) MkHFIELD (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_01: root of subtree no. 2 can not be made a HFIELD node ", 0, _coordref);
_currn->_desc3 = (_TSPRightAlign) MkRightAlign (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_01: root of subtree no. 3 can not be made a RightAlign node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_01;
(*(VS1MAP[_currn->_prod]))((NODEPTR)_currn);/* bottom up visit */
return ( (NODEPTR) _currn);
}/* Mkrule_01 */
