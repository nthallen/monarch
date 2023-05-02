
/* definition of tree node structure */

#ifndef NODE_H
#define NODE_H
#include "err.h"
#include "nodeptr.h" /* defines NODEPTR */
#include "HEAD.h"

#ifdef MONITOR
#define _NODECOMMON int _prod; POSITION _coord; int _uid;
#else
#define _NODECOMMON int _prod;
#endif
struct NODEPTR_struct {
        _NODECOMMON
#ifdef __cplusplus
        void* operator new(size_t size);
#endif
};

typedef struct _TSTableDefs* _TSPTableDefs;
typedef struct _TSTDunterminated* _TSPTDunterminated;
typedef struct _TSHBunterminated* _TSPHBunterminated;
typedef struct _TSHBFields* _TSPHBFields;
typedef struct _TSG3* _TSPG3;
typedef struct _TSG2* _TSPG2;
typedef struct _TSG1* _TSPG1;
typedef struct _TSGAField* _TSPGAField;
typedef struct _TSTableNameUse* _TSPTableNameUse;
typedef struct _TSTableNameDef* _TSPTableNameDef;
typedef struct _TSUnnamedTable* _TSPUnnamedTable;
typedef struct _TSNamedTables* _TSPNamedTables;
typedef struct _TSTableRef* _TSPTableRef;
typedef struct _TSHFIELD* _TSPHFIELD;
typedef struct _TSCField* _TSPCField;
typedef struct _TSColumns* _TSPColumns;
typedef struct _TSGFIELD* _TSPGFIELD;
typedef struct _TSRightAlign* _TSPRightAlign;
typedef struct _TSLeftAlign* _TSPLeftAlign;
typedef struct _TSRightAlignChar* _TSPRightAlignChar;
typedef struct _TSLeftAlignChar* _TSPLeftAlignChar;
typedef struct _TSDatumDimensions* _TSPDatumDimensions;
typedef struct _TSDatum* _TSPDatum;
typedef struct _TSHWord* _TSPHWord;
typedef struct _TSVField* _TSPVField;
typedef struct _TSHBOX* _TSPHBOX;
typedef struct _TSTable* _TSPTable;
typedef struct _TSNamedTable* _TSPNamedTable;
typedef struct _TSAttr* _TSPAttr;
typedef struct _TSInput* _TSPInput;
typedef struct _TSRule* _TSPRule;
typedef struct _TSGlue* _TSPGlue;
typedef struct _TSVGlue* _TSPVGlue;
typedef struct _TSHGlue* _TSPHGlue;
typedef struct _TSVDimension* _TSPVDimension;
typedef struct _TSHDimension* _TSPHDimension;
typedef struct _TSGlueSpec* _TSPGlueSpec;
typedef struct _TSSpace* _TSPSpace;
typedef struct _TSDimension* _TSPDimension;
typedef struct _TSWord* _TSPWord;
typedef struct _TSProgram* _TSPProgram;
typedef struct _TPrule_1* _TPPrule_1;
typedef struct _TPrule_2* _TPPrule_2;
typedef struct _TPrule_3* _TPPrule_3;
typedef struct _TPrule_4* _TPPrule_4;
typedef struct _TPrule_5* _TPPrule_5;
typedef struct _TPrule_6* _TPPrule_6;
typedef struct _TPrule_7* _TPPrule_7;
typedef struct _TPrule_8* _TPPrule_8;
typedef struct _TPrule_9* _TPPrule_9;
typedef struct _TPrule_10* _TPPrule_10;
typedef struct _TPrule_11* _TPPrule_11;
typedef struct _TPrule_12* _TPPrule_12;
typedef struct _TPrule_13* _TPPrule_13;
typedef struct _TPrule_14* _TPPrule_14;
typedef struct _TPrule_15* _TPPrule_15;
typedef struct _TPrule_16* _TPPrule_16;
typedef struct _TPrule_17* _TPPrule_17;
typedef struct _TPrule_18* _TPPrule_18;
typedef struct _TPrule_19* _TPPrule_19;
typedef struct _TPrule_20* _TPPrule_20;
typedef struct _TPrule_21* _TPPrule_21;
typedef struct _TPrule_22* _TPPrule_22;
typedef struct _TPrule_23* _TPPrule_23;
typedef struct _TPrule_24* _TPPrule_24;
typedef struct _TPrule_25* _TPPrule_25;
typedef struct _TPrule_26* _TPPrule_26;
typedef struct _TPrule_27* _TPPrule_27;
typedef struct _TPrule_28* _TPPrule_28;
typedef struct _TPrule_29* _TPPrule_29;
typedef struct _TPrule_30* _TPPrule_30;
typedef struct _TPrule_31* _TPPrule_31;
typedef struct _TPrule_32* _TPPrule_32;
typedef struct _TPrule_33* _TPPrule_33;
typedef struct _TPrule_34* _TPPrule_34;
typedef struct _TPrule_036* _TPPrule_036;
typedef struct _TPrule_035* _TPPrule_035;
typedef struct _TPrule_034* _TPPrule_034;
typedef struct _TPrule_033* _TPPrule_033;
typedef struct _TPrule_032* _TPPrule_032;
typedef struct _TPrule_031* _TPPrule_031;
typedef struct _TPrule_030* _TPPrule_030;
typedef struct _TPrule_029* _TPPrule_029;
typedef struct _TPrule_028* _TPPrule_028;
typedef struct _TPrule_027* _TPPrule_027;
typedef struct _TPrule_026* _TPPrule_026;
typedef struct _TPrule_025* _TPPrule_025;
typedef struct _TPrule_024* _TPPrule_024;
typedef struct _TPrule_023* _TPPrule_023;
typedef struct _TPrule_022* _TPPrule_022;
typedef struct _TPrule_021* _TPPrule_021;
typedef struct _TPrule_020* _TPPrule_020;
typedef struct _TPrule_019* _TPPrule_019;
typedef struct _TPrule_018* _TPPrule_018;
typedef struct _TPrule_017* _TPPrule_017;
typedef struct _TPrule_016* _TPPrule_016;
typedef struct _TPrule_015* _TPPrule_015;
typedef struct _TPrule_014* _TPPrule_014;
typedef struct _TPrule_013* _TPPrule_013;
typedef struct _TPrule_012* _TPPrule_012;
typedef struct _TPrule_011* _TPPrule_011;
typedef struct _TPrule_010* _TPPrule_010;
typedef struct _TPrule_09* _TPPrule_09;
typedef struct _TPrule_08* _TPPrule_08;
typedef struct _TPrule_07* _TPPrule_07;
typedef struct _TPrule_06* _TPPrule_06;
typedef struct _TPrule_05* _TPPrule_05;
typedef struct _TPrule_04* _TPPrule_04;
typedef struct _TPrule_03* _TPPrule_03;
typedef struct _TPrule_02* _TPPrule_02;
typedef struct _TPrule_01* _TPPrule_01;

struct _TSTableDefs
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _AT_const8;
int _ATCRow_pre;
glue_t _ATGlue_pre;
};

struct _TSTDunterminated
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCRow_post;
glue_t _ATGlue_post;
};

struct _TSHBunterminated
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCCol_post;
glue_t _ATGlue_post;
int _ATAttr_post;
};

struct _TSHBFields
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCCol_pre;
glue_t _ATGlue_pre;
int _ATAttr_pre;
};

struct _TSG3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATColNumber_post;
int _ATAttr_post;
};

struct _TSGAField
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _AT_const3;
dim_t _AT_const4;
};

struct _TSTableNameUse
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTableNameDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSUnnamedTable
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSNamedTables
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTableRef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
};

struct _TSHFIELD
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATWidth;
dim_t _ATHeight;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
};

struct _TSCField
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATColMinWidth;
dim_t _ATWidth;
dim_t _ATMinHeight;
};

struct _TSColumns
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATN_Cols;
};

struct _TSGFIELD
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
};

struct _TSRightAlign
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLeftAlign
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinWidth;
};

struct _TSRightAlignChar
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLeftAlignChar
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDatumDimensions
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinHeight;
dim_t _ATMinWidth;
};

struct _TSDatum
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSHWord
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATAttr_pre;
dim_t _ATMinHeight;
dim_t _ATMinWidth;
int _ATString;
};

struct _TSVField
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
};

struct _TSHBOX
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATHeight;
dim_t _ATInhWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
};

struct _TSTable
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATAttr_post;
int _ATAttr_pre;
Environment _ATColEnv;
int _ATCol;
dim_t _ATInhHeight;
dim_t _ATWidth;
dim_t _ATColumnsMinWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
int _ATTableAttr;
};

struct _TSNamedTable
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATForReal;
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
};

struct _TSAttr
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSInput
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRule
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinHeight;
dim_t _ATMinWidth;
int _ATString;
};

struct _TSGlue
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSVGlue
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSHGlue
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSVDimension
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATGlueScale;
};

struct _TSHDimension
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATGlueScale;
};

struct _TSGlueSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSSpace
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDimension
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSWord
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATString;
};

struct _TSProgram
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATTableEnv;
Environment _ATColEnv;
int _ATForReal;
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
int _ATTableName;
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPNamedTables _desc1;
_TSPInput _desc2;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPNamedTables _desc1;
_TSPNamedTable _desc2;
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTable _desc1;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
_TSPTableNameUse _desc1;
POSITION _AT_pos;
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATTERM_1;
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATForReal;
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPTableNameDef _desc1;
_TSPTable _desc2;
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATTableEnv;
Environment _ATColEnv;
int _ATForReal;
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
int _ATTableName;
_TSPNamedTables _desc1;
_TSPUnnamedTable _desc2;
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPGlue _desc1;
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPRule _desc1;
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPDatum _desc1;
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPHWord _desc1;
};

struct _TPrule_14
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPTableRef _desc1;
};

struct _TPrule_15
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPHBOX _desc1;
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
_TSPTable _desc1;
};

struct _TPrule_17
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinHeight;
dim_t _ATMinWidth;
_TSPHDimension _desc1;
_TSPVDimension _desc2;
};

struct _TPrule_18
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinHeight;
dim_t _ATMinWidth;
_TSPHDimension _desc1;
};

struct _TPrule_19
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinHeight;
dim_t _ATMinWidth;
};

struct _TPrule_20
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPWord _desc1;
_TSPDatumDimensions _desc2;
};

struct _TPrule_21
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATAttr_pre;
dim_t _ATMinHeight;
dim_t _ATMinWidth;
int _ATString;
_TSPWord _desc1;
};

struct _TPrule_22
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_23
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_24
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_25
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
int _ATInpFileEx_RuleAttr_95;
};

struct _TPrule_26
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinHeight;
dim_t _ATMinWidth;
int _ATString;
};

struct _TPrule_27
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPVDimension _desc1;
};

struct _TPrule_28
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPHDimension _desc1;
};

struct _TPrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATGlueScale;
_TSPDimension _desc1;
};

struct _TPrule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATGlueScale;
_TSPDimension _desc1;
};

struct _TPrule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATString;
};

struct _TPrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATString;
};

struct _TPrule_036
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
_TSPGAField _desc1;
};

struct _TPrule_035
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
_TSPColumns _desc1;
};

struct _TPrule_034
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _AT_const8;
int _ATCRow_pre;
glue_t _ATGlue_pre;
_TSPTDunterminated _desc1;
};

struct _TPrule_033
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _AT_const8;
int _ATCRow_pre;
glue_t _ATGlue_pre;
_TSPTDunterminated _desc1;
};

struct _TPrule_032
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _AT_const8;
int _ATCRow_pre;
glue_t _ATGlue_pre;
};

struct _TPrule_031
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATAttr_post;
int _ATAttr_pre;
Environment _ATColEnv;
int _ATCol;
dim_t _ATInhHeight;
dim_t _ATWidth;
dim_t _ATColumnsMinWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
int _ATTableAttr;
_TSPTableDefs _desc1;
};

struct _TPrule_030
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATAttr_post;
int _ATAttr_pre;
Environment _ATColEnv;
int _ATCol;
dim_t _ATInhHeight;
dim_t _ATWidth;
dim_t _ATColumnsMinWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
int _ATTableAttr;
_TSPTableDefs _desc1;
};

struct _TPrule_029
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCRow_post;
glue_t _ATGlue_post;
_TSPVField _desc1;
};

struct _TPrule_028
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCRow_post;
glue_t _ATGlue_post;
_TSPTDunterminated _desc1;
_TSPVField _desc2;
};

struct _TPrule_027
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_026
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG3 _desc1;
};

struct _TPrule_025
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_024
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATMinWidth;
_TSPG2 _desc1;
};

struct _TPrule_023
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATWidth;
dim_t _ATHeight;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
_TSPGAField _desc1;
};

struct _TPrule_022
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCCol_post;
glue_t _ATGlue_post;
int _ATAttr_post;
_TSPHFIELD _desc1;
};

struct _TPrule_021
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCCol_post;
glue_t _ATGlue_post;
int _ATAttr_post;
_TSPHBunterminated _desc1;
_TSPHFIELD _desc2;
};

struct _TPrule_020
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATHeight;
dim_t _ATInhWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
_TSPHBFields _desc1;
};

struct _TPrule_019
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCCol_pre;
glue_t _ATGlue_pre;
int _ATAttr_pre;
_TSPHBunterminated _desc1;
};

struct _TPrule_018
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCCol_pre;
glue_t _ATGlue_pre;
int _ATAttr_pre;
_TSPHBunterminated _desc1;
};

struct _TPrule_017
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCCol_pre;
glue_t _ATGlue_pre;
int _ATAttr_pre;
};

struct _TPrule_016
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATCol;
int _ATRow;
dim_t _ATWidth;
dim_t _ATHeight;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
_TSPGFIELD _desc1;
};

struct _TPrule_015
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPVGlue _desc1;
};

struct _TPrule_014
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPHGlue _desc1;
};

struct _TPrule_013
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _AT_const3;
dim_t _AT_const4;
_TSPGFIELD _desc1;
};

struct _TPrule_012
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _AT_const3;
dim_t _AT_const4;
_TSPAttr _desc1;
_TSPGFIELD _desc2;
};

struct _TPrule_011
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG3 _desc1;
_TSPRightAlignChar _desc2;
};

struct _TPrule_010
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_09
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLeftAlignChar _desc1;
};

struct _TPrule_08
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG2 _desc1;
_TSPLeftAlignChar _desc2;
};

struct _TPrule_07
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATColNumber_post;
int _ATAttr_post;
_TSPG1 _desc1;
_TSPCField _desc2;
};

struct _TPrule_06
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATColNumber_post;
int _ATAttr_post;
_TSPCField _desc1;
};

struct _TPrule_05
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSpace _desc1;
};

struct _TPrule_04
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPSpace _desc1;
_TSPGlueSpec _desc2;
};

struct _TPrule_03
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATN_Cols;
_TSPCField _desc1;
_TSPG1 _desc2;
};

struct _TPrule_02
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATCol;
int _ATRow;
dim_t _ATHeight;
dim_t _ATColMinWidth;
dim_t _ATWidth;
dim_t _ATMinHeight;
_TSPGAField _desc1;
};

struct _TPrule_01
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
dim_t _ATHeight;
dim_t _ATInhWidth;
dim_t _ATMinWidth;
dim_t _ATMinHeight;
_TSPLeftAlign _desc1;
_TSPHFIELD _desc2;
_TSPRightAlign _desc3;
};

#undef _NODECOMMON
#endif
