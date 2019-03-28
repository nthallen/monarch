
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MkTDunterminated ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTableDefs ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkHBunterminated ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkHBFields ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG3 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG2 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG1 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkGAField ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTableNameUse ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTableNameDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkUnnamedTable ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNamedTables ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTableRef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkHFIELD ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkCField ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkColumns ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkGFIELD ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRightAlign ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLeftAlign ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRightAlignChar ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLeftAlignChar ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDatumDimensions ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDatum ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkHWord ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkVField ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkHBOX ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTable ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNamedTable ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkAttr ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkInput ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRule ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkGlue ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkVGlue ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkHGlue ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkVDimension ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkHDimension ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkGlueSpec ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkSpace ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDimension ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkWord ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkProgram ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_4 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_5 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_6 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_7 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_8 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_9 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_10 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_11 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_12 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_13 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_14 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_15 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_16 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_17 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_18 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_19 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_20 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_21 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_22 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_23 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_24 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_25 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_26 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_27 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_28 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_29 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_30 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_31 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_32 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_33 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_34 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_036 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_035 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_034 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_033 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_032 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_031 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_030 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_029 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_028 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_027 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_026 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_025 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_024 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_023 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_022 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_021 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_020 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_019 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_018 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_017 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_016 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_015 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_014 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_013 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_012 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_011 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_010 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_09 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_08 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_07 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_06 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_05 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_04 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_03 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_02 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_01 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
#define MkRuleString(pos,val) (val)
#define MkCString(pos,val) (val)
#define MkInteger(pos,val) (val)
#define MkBareWord(pos,val) (val)
#endif
