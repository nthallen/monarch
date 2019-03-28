
#include "HEAD.h"
#include "err.h"
#include "node.h"
#include "visitprocs.h"
#include "attrpredef.h"

#include "visitmap.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#include "liga_dapto.h"
#endif

#ifndef _VisitVarDecl
#define _VisitVarDecl()
#endif

#ifndef _VisitEntry
#define _VisitEntry()
#endif

#ifndef _VisitExit
#define _VisitExit()
#endif


#if defined(__STDC__) || defined(__cplusplus)
#define _CALL_VS_(args) (void (*)args)
#else
#define _CALL_VS_(args) 
#endif
dim_t* _IG_incl24;
int* _IG_incl23;
dim_t* _IG_incl22;
dim_t* _IG_incl21;
dim_t* _IG_incl20;
dim_t* _IG_incl19;
int* _IG_incl18;
int* _IG_incl17;
dim_t* _IG_incl15;
int* _IG_incl14;
int* _IG_incl16;
int* _IG_incl13;
int* _IG_incl12;
dim_t* _IG_incl11;
dim_t* _IG_incl10;
dim_t* _IG_incl9;
int* _IG_incl8;
int* _IG_incl7;
int* _IG_incl6;
dim_t* _IG_incl5;
dim_t* _IG_incl4;
int* _IG_incl3;
int* _IG_incl2;
Environment* _IG_incl1;
Environment* _IG_incl0;
dim_t _AVTDunterminated__const8;
dim_t _AVTDunterminated__const9;
dim_t _AVTDunterminated__const10;
PTGNode _AVNamedTableStringPrint_post;
PTGNode _AVNamedTableFieldPrint_post;
int _AVTDunterminatedCRow_pre;
glue_t _AVTDunterminatedGlue_pre;
int _AVTableDefs__const6;
dim_t _AVTableDefs__const9;
dim_t _AVTableDefs__const10;
int _AVG1Attr_pre;
int _AVHBunterminatedCCol_pre;
dim_t _AVHBFields__const13;
dim_t _AVHBFields__const14;
int _AVG3__const11;
int _AVG2__const12;
dim_t _AVG1__const19;
dim_t _AVG1__const20;
int _AVG1ColNumber_pre;
Binding _AVTableNameUse_Bind;
int _AVTableNameUse_Sym;
DefTableKey _AVTableNameUse_Key;
Binding _AVTableNameDef_Bind;
int _AVTableNameDef_Sym;
dim_t _AVUnnamedTable_MinHeight;
dim_t _AVUnnamedTable_MinWidth;
PTGNode _AVNamedTablesStringPrint_pre;
PTGNode _AVNamedTablesFieldPrint_pre;
int _AVNamedTablesAttr_post;
int _AVTableRef_Col;
int _AVTableRef_Row;
dim_t _AVTableRef_Height;
dim_t _AVTableRef_Width;
int _AVTableRef_ForReal;
dims_t _AVTableRef_MinDims;
Binding _AVCField_Bind;
dim_t _AVCField_MinWidth;
int _AVCField_Sym;
dim_t _AVColumns_MinWidth;
dim_t _AVColumns_MinHeight;
dim_t _AVGFIELD_MinWidth;
dim_t _AVGFIELD_MinHeight;
dim_t _AVRightAlign_MinWidth;
glue_t _AVLeftAlignGlue_pre;
dim_t _AVLeftAlign_Width;
int _AVRightAlignChar_present;
int _AVLeftAlignChar_present;
dim_t _AVDatum__const1;
dim_t _AVDatum__const2;
dim_t _AVDatum_Height;
int _AVDatum_Row;
dim_t _AVDatum_Width;
int _AVDatum_Col;
int _AVDatum_PrintCol;
dim_t _AVDatum_FullWidth;
dim_t _AVDatum_MinHeight;
dim_t _AVDatum_MinWidth;
int _AVDatum_String;
dims_t _AVHWord_WordDims_RuleAttr_91;
dim_t _AVHWord_Height;
dim_t _AVHWord_Width;
int _AVHWord_Col;
int _AVHWord_Row;
int _AVHWord_IsEmpty;
int _AVVField__const6;
dim_t _AVVField__const8;
dim_t _AVHBOX_Width;
int _AVTable_N_Cols;
dim_t _AVTable_Height;
instance_t _AVNamedTable_Instance;
int _AVAttr_NewAttr;
dim_t _AVRule_Height;
dim_t _AVRule_Width;
int _AVRule_Col;
int _AVRule_Row;
int _AVRule_ForReal;
int _AVRule_Vertical;
dim_t _AVGlue_MinHeight;
dim_t _AVGlue_MinWidth;
dim_t _AVVGlue_MinHeight;
dim_t _AVHGlue_MinWidth;
dim_t _AVVDimension_Dimension;
dim_t _AVHDimension_Dimension;
int _AVGlueSpec_Space;
int _AVSpace_Space;
dim_t _AVDimension_Dimension;
PTGNode _AVProgram_RuleDef;
PTGNode _AVProgram_RulePrint;
PTGNode _AVProgram_FullOutput;

#if defined(__STDC__) || defined(__cplusplus)
void LIGA_ATTREVAL (NODEPTR _currn)
#else
void LIGA_ATTREVAL (_currn) NODEPTR _currn;
#endif
{}
/*SPC(0)*/

#if defined(__STDC__) || defined(__cplusplus)
void _VS0Empty(NODEPTR _currn)
#else
void _VS0Empty(_currn) NODEPTR _currn;
#endif
{ _VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_1(_TPPrule_1 _currn)
#else
void _VS2rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVNamedTablesAttr_post=_AVG1Attr_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_1(_TPPrule_1 _currn)
#else
void _VS3rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVNamedTableStringPrint_post=_AVNamedTablesStringPrint_pre;
/*SPC(0)*/
_AVNamedTableFieldPrint_post=_AVNamedTablesFieldPrint_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_2(_TPPrule_2 _currn)
#else
void _VS2rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_2(_TPPrule_2 _currn)
#else
void _VS3rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_3(_TPPrule_3 _currn)
#else
void _VS3rule_3(_currn )
_TPPrule_3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_4(_TPPrule_4 _currn)
#else
void _VS2rule_4(_currn )
_TPPrule_4 _currn;

#endif
{
PTGNode _AS1FieldPrint_pre;
int _AS1Row;

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATAttr_pre=_AVG1Attr_pre;
/*SPC(0)*/
_currn->_desc1->_ATColEnv=NewScope((* _IG_incl0));
/*SPC(675)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVUnnamedTable_MinHeight=_currn->_desc1->_ATMinHeight;
/*SPC(538)*/
_AVUnnamedTable_MinWidth=_currn->_desc1->_ATMinWidth;
/*SPC(539)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_4(_TPPrule_4 _currn)
#else
void _VS3rule_4(_currn )
_TPPrule_4 _currn;

#endif
{
PTGNode _AS1FieldPrint_pre;
int _AS1Row;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Row)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_4(_TPPrule_4 _currn)
#else
void _VS4rule_4(_currn )
_TPPrule_4 _currn;

#endif
{
PTGNode _AS1FieldPrint_pre;
int _AS1Row;

_VisitVarDecl()
_VisitEntry();
_AS1FieldPrint_pre=_AVNamedTableFieldPrint_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*,PTGNode*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Row)),(&( _AS1FieldPrint_pre)));
_AVG1Attr_pre=_currn->_desc1->_ATAttr_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_5(_TPPrule_5 _currn)
#else
void _VS1rule_5(_currn )
_TPPrule_5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_5(_TPPrule_5 _currn)
#else
void _VS2rule_5(_currn )
_TPPrule_5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTableNameUse_Sym=_currn->_ATTERM_1;
/*SPC(511)*/
_AVTableNameUse_Bind=BindingInScope((* _IG_incl1), _AVTableNameUse_Sym);
/*SPC(870)*/
_AVTableNameUse_Key=KeyOf(_AVTableNameUse_Bind);
/*SPC(873)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_6(_TPPrule_6 _currn)
#else
void _VS1rule_6(_currn )
_TPPrule_6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_6(_TPPrule_6 _currn)
#else
void _VS2rule_6(_currn )
_TPPrule_6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATKey=_AVTableNameUse_Key;
/*SPC(498)*/

if (NOT(HasMinDims(_currn->_ATKey))) {
message(ERROR, "Undefined Table Ref", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(499)*/
_AVTableRef_MinDims=GetMinDims(_currn->_ATKey, MKDIMS(MKDIM0(), MKDIM0()));
/*SPC(503)*/
_currn->_ATMinWidth=WIDTH(_AVTableRef_MinDims);
/*SPC(506)*/
_currn->_ATMinHeight=HEIGHT(_AVTableRef_MinDims);
/*SPC(507)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_6(_TPPrule_6 _currn)
#else
void _VS3rule_6(_currn )
_TPPrule_6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTableRef_Col=(* _IG_incl2);
/*SPC(381)*/
_AVTableRef_Row=(* _IG_incl3);
/*SPC(380)*/
_AVTableRef_Height=GlueDim(_currn->_ATMinHeight, (* _IG_incl4));
/*SPC(323)*/
_AVTableRef_Width=GlueDim(_currn->_ATMinWidth, (* _IG_incl5));
/*SPC(322)*/
_AVTableRef_ForReal=(* _IG_incl6);
/*SPC(520)*/

if (_AVTableRef_ForReal) {
NewInstance(_currn->_ATKey, _AVTableRef_Width, _AVTableRef_Height, _AVTableRef_Row, _AVTableRef_Col, 1, 0);

} else {
}
;
/*SPC(522)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_7(_TPPrule_7 _currn)
#else
void _VS1rule_7(_currn )
_TPPrule_7 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_7(_TPPrule_7 _currn)
#else
void _VS2rule_7(_currn )
_TPPrule_7 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTableNameDef_Sym=_currn->_ATTERM_1;
/*SPC(494)*/
_AVTableNameDef_Bind=BindIdn((* _IG_incl1), _AVTableNameDef_Sym);
/*SPC(836)*/
_currn->_ATKey=KeyOf(_AVTableNameDef_Bind);
/*SPC(839)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_8(_TPPrule_8 _currn)
#else
void _VS2rule_8(_currn )
_TPPrule_8 _currn;

#endif
{
PTGNode _AS2FieldPrint_pre;
int _AS2Row;

_VisitVarDecl()
_VisitEntry();
_AVG1Attr_pre=4;
/*SPC(103)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_desc2->_ATAttr_pre=_AVG1Attr_pre;
/*SPC(0)*/
_currn->_desc2->_ATColEnv=NewScope((* _IG_incl0));
/*SPC(675)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
ResetMinDims(_currn->_desc1->_ATKey, MKDIMS(_currn->_desc2->_ATMinWidth, _currn->_desc2->_ATMinHeight));
NewInstance(_currn->_desc1->_ATKey, _currn->_desc2->_ATMinWidth, _currn->_desc2->_ATMinHeight, 0, 0, 0, 0);
;
/*SPC(485)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_8(_TPPrule_8 _currn)
#else
void _VS3rule_8(_currn )
_TPPrule_8 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
int* _IL_incl6;
PTGNode _AS2FieldPrint_pre;
int _AS2Row;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATForReal);
_AVNamedTable_Instance=PopInstance(_currn->_desc1->_ATKey);

_CYCLE0Instance:;
;
/*SPC(559)*/
_AVNamedTableStringPrint_post=PTGNULL;
/*SPC(574)*/
_AVNamedTableFieldPrint_post=PTGNULL;
/*SPC(572)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATForReal=INST_EXISTS(_AVNamedTable_Instance);
/*SPC(569)*/
_currn->_ATCol=INST_COL(_AVNamedTable_Instance);
/*SPC(568)*/
_currn->_ATRow=INST_ROW(_AVNamedTable_Instance);
/*SPC(567)*/
_currn->_ATHeight=HEIGHT(INST_SIZE(_AVNamedTable_Instance));
/*SPC(566)*/
_currn->_ATWidth=WIDTH(INST_SIZE(_AVNamedTable_Instance));
/*SPC(565)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Row)));
_AS2FieldPrint_pre=_AVNamedTableFieldPrint_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*,PTGNode*)) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Row)),(&( _AS2FieldPrint_pre)));

if (_currn->_ATForReal) {
SeqFieldPtg(_currn->_desc1->_ATKey, _AVNamedTableFieldPrint_post);
SeqStringPtg(_currn->_desc1->_ATKey, _AVNamedTableStringPrint_post);
;

} else {
}
;
/*SPC(576)*/

if (!(NOT(_currn->_ATForReal))) {
_AVNamedTable_Instance=PopInstance(_currn->_desc1->_ATKey);

goto _CYCLE0Instance;
}
;
/*SPC(561)*/
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl6=_IL_incl6;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_8(_TPPrule_8 _currn)
#else
void _VS4rule_8(_currn )
_TPPrule_8 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
int* _IL_incl6;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATForReal);
_AVNamedTableStringPrint_post=PTGSeq(_AVNamedTableStringPrint_post, GetStringPtg(_currn->_desc1->_ATKey, PTGNULL));
/*SPC(588)*/
_AVNamedTableFieldPrint_post=PTGSeq(_AVNamedTableFieldPrint_post, GetFieldPtg(_currn->_desc1->_ATKey, PTGNULL));
/*SPC(584)*/
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl6=_IL_incl6;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn)
#else
void _VS1rule_9(_currn )
_TPPrule_9 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
int* _IL_incl12;
int* _IL_incl6;
Environment* _IL_incl1;
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl12=_IG_incl12;_IG_incl12= &(_currn->_ATTableName);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATForReal);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATTableEnv);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATColEnv);
_currn->_ATTableEnv=TableRootEnv;
/*SPC(808)*/
_currn->_ATColEnv=ColRootEnv;
/*SPC(664)*/
_AVG1Attr_pre=4;
/*SPC(102)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1Attr_pre=_AVNamedTablesAttr_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATForReal=1;
/*SPC(481)*/
_currn->_ATCol=0;
/*SPC(334)*/
_currn->_ATRow=0;
/*SPC(333)*/
_currn->_ATHeight=GlueDim(_AVUnnamedTable_MinHeight, _AVUnnamedTable_MinHeight);
/*SPC(267)*/
_currn->_ATWidth=GlueDim(_AVUnnamedTable_MinWidth, _AVUnnamedTable_MinWidth);
/*SPC(266)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATTableName=get_table_name(InputFile);
/*SPC(8)*/
_AVNamedTablesStringPrint_pre=PTGNULL;
/*SPC(396)*/
_AVNamedTablesFieldPrint_pre=PTGNULL;
/*SPC(395)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVProgram_RulePrint=print_rules(_currn->_ATTableName);
/*SPC(455)*/
_AVProgram_RuleDef=define_rules(_currn->_ATTableName);
/*SPC(456)*/
_AVProgram_FullOutput=PTGFile(_AVNamedTableStringPrint_post, _AVProgram_RulePrint, _AVNamedTableFieldPrint_post, StringTable(_currn->_ATTableName), ADD(SPACE(_currn->_ATHeight), 1), ADD(SPACE(_currn->_ATWidth), 1), _AVProgram_RuleDef);
/*SPC(397)*/

if (NE(OutputFile, NoKey)) {
PTGOutFile(StringTable(GetClpValue(OutputFile, 0)), _AVProgram_FullOutput);

} else {
PTGOut(_AVProgram_FullOutput);
}
;
/*SPC(407)*/
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl12=_IL_incl12;
_IG_incl6=_IL_incl6;
_IG_incl1=_IL_incl1;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_10(_TPPrule_10 _currn)
#else
void _VS2rule_10(_currn )
_TPPrule_10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGFIELD_MinWidth=_AVGlue_MinWidth;
/*SPC(218)*/
_AVGFIELD_MinHeight=_AVGlue_MinHeight;
/*SPC(217)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_10(_TPPrule_10 _currn)
#else
void _VS3rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl7);
/*SPC(376)*/
_currn->_ATRow=(* _IG_incl8);
/*SPC(375)*/
_currn->_ATHeight=(* _IG_incl9);
/*SPC(317)*/
_currn->_ATWidth=(* _IG_incl10);
/*SPC(315)*/
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_10(_TPPrule_10 _currn)
#else
void _VS4rule_10(_currn )
_TPPrule_10 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_11(_TPPrule_11 _currn)
#else
void _VS2rule_11(_currn )
_TPPrule_11 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGFIELD_MinWidth=_currn->_desc1->_ATMinWidth;
/*SPC(214)*/
_AVGFIELD_MinHeight=_currn->_desc1->_ATMinHeight;
/*SPC(213)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_11(_TPPrule_11 _currn)
#else
void _VS3rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl7);
/*SPC(376)*/
_currn->_ATRow=(* _IG_incl8);
/*SPC(375)*/
_currn->_ATHeight=(* _IG_incl9);
/*SPC(317)*/
_currn->_ATWidth=(* _IG_incl10);
/*SPC(315)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_11(_TPPrule_11 _currn)
#else
void _VS4rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_12(_TPPrule_12 _currn)
#else
void _VS2rule_12(_currn )
_TPPrule_12 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGFIELD_MinWidth=_AVDatum__const2;
/*SPC(210)*/
_AVGFIELD_MinHeight=_AVDatum__const1;
/*SPC(209)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_12(_TPPrule_12 _currn)
#else
void _VS3rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl7);
/*SPC(376)*/
_currn->_ATRow=(* _IG_incl8);
/*SPC(375)*/
_currn->_ATHeight=(* _IG_incl9);
/*SPC(317)*/
_currn->_ATWidth=(* _IG_incl10);
/*SPC(315)*/
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_12(_TPPrule_12 _currn)
#else
void _VS4rule_12(_currn )
_TPPrule_12 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_13(_TPPrule_13 _currn)
#else
void _VS2rule_13(_currn )
_TPPrule_13 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATAttr_pre=_AVG1Attr_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGFIELD_MinWidth=_currn->_desc1->_ATMinWidth;
/*SPC(206)*/
_AVGFIELD_MinHeight=_currn->_desc1->_ATMinHeight;
/*SPC(205)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_13(_TPPrule_13 _currn)
#else
void _VS3rule_13(_currn )
_TPPrule_13 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl7);
/*SPC(376)*/
_currn->_ATRow=(* _IG_incl8);
/*SPC(375)*/
_currn->_ATHeight=(* _IG_incl9);
/*SPC(317)*/
_currn->_ATWidth=(* _IG_incl10);
/*SPC(315)*/
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_13(_TPPrule_13 _currn)
#else
void _VS4rule_13(_currn )
_TPPrule_13 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_14(_TPPrule_14 _currn)
#else
void _VS2rule_14(_currn )
_TPPrule_14 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGFIELD_MinWidth=_currn->_desc1->_ATMinWidth;
/*SPC(202)*/
_AVGFIELD_MinHeight=_currn->_desc1->_ATMinHeight;
/*SPC(201)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_14(_TPPrule_14 _currn)
#else
void _VS3rule_14(_currn )
_TPPrule_14 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl7);
/*SPC(376)*/
_currn->_ATRow=(* _IG_incl8);
/*SPC(375)*/
_currn->_ATHeight=(* _IG_incl9);
/*SPC(317)*/
_currn->_ATWidth=(* _IG_incl10);
/*SPC(315)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_14(_TPPrule_14 _currn)
#else
void _VS4rule_14(_currn )
_TPPrule_14 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_15(_TPPrule_15 _currn)
#else
void _VS2rule_15(_currn )
_TPPrule_15 _currn;

#endif
{
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_AS1Attr_pre=_AVG1Attr_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Attr_pre)));
_AVGFIELD_MinWidth=_currn->_desc1->_ATMinWidth;
/*SPC(198)*/
_AVGFIELD_MinHeight=_currn->_desc1->_ATMinHeight;
/*SPC(197)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_15(_TPPrule_15 _currn)
#else
void _VS3rule_15(_currn )
_TPPrule_15 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl7);
/*SPC(376)*/
_currn->_ATRow=(* _IG_incl8);
/*SPC(375)*/
_currn->_ATHeight=(* _IG_incl9);
/*SPC(317)*/
_currn->_ATWidth=(* _IG_incl10);
/*SPC(315)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Attr_pre)));
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_15(_TPPrule_15 _currn)
#else
void _VS4rule_15(_currn )
_TPPrule_15 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR ,int*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Attr_pre)));
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_16(_TPPrule_16 _currn)
#else
void _VS2rule_16(_currn )
_TPPrule_16 _currn;

#endif
{
PTGNode _AS1FieldPrint_pre;
int _AS1Row;

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATAttr_pre=_AVG1Attr_pre;
/*SPC(0)*/
_currn->_desc1->_ATColEnv=NewScope((* _IG_incl0));
/*SPC(675)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1Attr_pre=_currn->_desc1->_ATAttr_post;
/*SPC(0)*/
_AVGFIELD_MinWidth=_currn->_desc1->_ATMinWidth;
/*SPC(194)*/
_AVGFIELD_MinHeight=_currn->_desc1->_ATMinHeight;
/*SPC(193)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_16(_TPPrule_16 _currn)
#else
void _VS3rule_16(_currn )
_TPPrule_16 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;
PTGNode _AS1FieldPrint_pre;
int _AS1Row;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl7);
/*SPC(376)*/
_currn->_ATRow=(* _IG_incl8);
/*SPC(375)*/
_currn->_ATHeight=(* _IG_incl9);
/*SPC(317)*/
_currn->_ATWidth=(* _IG_incl10);
/*SPC(315)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Row)));
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_16(_TPPrule_16 _currn)
#else
void _VS4rule_16(_currn )
_TPPrule_16 _currn;

#endif
{
dim_t* _IL_incl20;
dim_t* _IL_incl19;
int* _IL_incl18;
int* _IL_incl17;
dim_t* _IL_incl5;
dim_t* _IL_incl4;
int* _IL_incl3;
int* _IL_incl2;
PTGNode _AS1FieldPrint_pre;
int _AS1Row;

_VisitVarDecl()
_VisitEntry();
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWidth);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATHeight);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATRow);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATCol);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATWidth);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATHeight);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATRow);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATCol);
_AS1FieldPrint_pre=_AVNamedTableFieldPrint_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*,PTGNode*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Row)),(&( _AS1FieldPrint_pre)));
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;
_IG_incl3=_IL_incl3;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_17(_TPPrule_17 _currn)
#else
void _VS2rule_17(_currn )
_TPPrule_17 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATMinHeight=_AVVDimension_Dimension;
/*SPC(155)*/
_currn->_ATMinWidth=_AVHDimension_Dimension;
/*SPC(154)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_18(_TPPrule_18 _currn)
#else
void _VS2rule_18(_currn )
_TPPrule_18 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATMinHeight=MKDIM(DatumHeight(DEF_DATUM_HT), 0);
/*SPC(150)*/
_currn->_ATMinWidth=_AVHDimension_Dimension;
/*SPC(149)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_19(_TPPrule_19 _currn)
#else
void _VS2rule_19(_currn )
_TPPrule_19 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATMinHeight=MKDIM(DatumHeight(DEF_DATUM_HT), 0);
/*SPC(145)*/
_currn->_ATMinWidth=MKDIM(DatumWidth(DEF_DATUM_WID), 0);
/*SPC(144)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_20(_TPPrule_20 _currn)
#else
void _VS2rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVDatum__const1=_currn->_desc2->_ATMinHeight;
/*SPC(137)*/
_AVDatum__const2=_currn->_desc2->_ATMinWidth;
/*SPC(137)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_20(_TPPrule_20 _currn)
#else
void _VS3rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDatum_Row=(* _IG_incl3);
/*SPC(380)*/
_AVDatum_Col=(* _IG_incl2);
/*SPC(381)*/
_AVDatum_FullWidth=(* _IG_incl11);
/*SPC(419)*/
_AVDatum_MinHeight=_currn->_desc2->_ATMinHeight;
/*SPC(140)*/
_AVDatum_MinWidth=_currn->_desc2->_ATMinWidth;
/*SPC(139)*/
_AVDatum_String=_currn->_desc1->_ATString;
/*SPC(138)*/
_AVDatum_Height=GlueDim(_AVDatum_MinHeight, (* _IG_incl4));
/*SPC(323)*/
_AVDatum_Width=GlueDim(_AVDatum_MinWidth, (* _IG_incl5));
/*SPC(322)*/
_AVDatum_PrintCol=SUB(ADD(_AVDatum_Col, SPACE(_AVDatum_FullWidth)), SPACE(_AVDatum_Width));
/*SPC(421)*/
_AVNamedTableStringPrint_post=PTGSeq(_AVNamedTableStringPrint_post, print_field_string((* _IG_incl12), _AVDatum_Row, _AVDatum_PrintCol, SPACE(_AVDatum_Width), SPACE(_AVDatum_Height)));
/*SPC(431)*/
_AVNamedTableFieldPrint_post=PTGSeq(_AVNamedTableFieldPrint_post, PTGField(StringTable((* _IG_incl12)), PTGId(_AVDatum_String), _AVDatum_Row, _AVDatum_PrintCol));
/*SPC(423)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_21(_TPPrule_21 _currn)
#else
void _VS2rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1Attr_pre=_currn->_ATAttr_pre;
/*SPC(120)*/
_currn->_ATString=_currn->_desc1->_ATString;
/*SPC(131)*/
_AVHWord_WordDims_RuleAttr_91=CalcWordDims(StringTable(_currn->_ATString), _currn->_ATAttr_pre);
/*SPC(132)*/
_currn->_ATMinHeight=HEIGHT(_AVHWord_WordDims_RuleAttr_91);
/*SPC(134)*/
_currn->_ATMinWidth=WIDTH(_AVHWord_WordDims_RuleAttr_91);
/*SPC(133)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_21(_TPPrule_21 _currn)
#else
void _VS3rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVHWord_Height=GlueDim(_currn->_ATMinHeight, (* _IG_incl4));
/*SPC(323)*/
_AVHWord_Width=GlueDim(_currn->_ATMinWidth, (* _IG_incl5));
/*SPC(322)*/
_AVHWord_Col=(* _IG_incl2);
/*SPC(381)*/
_AVHWord_Row=(* _IG_incl3);
/*SPC(380)*/
_AVHWord_IsEmpty=EQ(strlen(StringTable(_currn->_ATString)), 0);
/*SPC(440)*/
_AVNamedTableStringPrint_post=
((_AVHWord_IsEmpty
) ? (_AVNamedTableStringPrint_post
) : (PTGSeq(_AVNamedTableStringPrint_post, PTGString(_AVHWord_Row, _AVHWord_Col, _currn->_ATAttr_pre, PTGId(_currn->_ATString), StringTable((* _IG_incl12))))))
;
/*SPC(441)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_22(_TPPrule_22 _currn)
#else
void _VS2rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttr_NewAttr=3;
/*SPC(100)*/
_AVG1Attr_pre=_AVAttr_NewAttr;
/*SPC(117)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_23(_TPPrule_23 _currn)
#else
void _VS2rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttr_NewAttr=5;
/*SPC(99)*/
_AVG1Attr_pre=_AVAttr_NewAttr;
/*SPC(117)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_24(_TPPrule_24 _currn)
#else
void _VS1rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_24(_TPPrule_24 _currn)
#else
void _VS2rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVAttr_NewAttr=_currn->_ATTERM_1;
/*SPC(97)*/
_AVG1Attr_pre=_AVAttr_NewAttr;
/*SPC(117)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_25(_TPPrule_25 _currn)
#else
void _VS1rule_25(_currn )
_TPPrule_25 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATInpFileEx_RuleAttr_95=NewInput(StringTable(_currn->_ATTERM_1));
/*SPC(84)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_25(_TPPrule_25 _currn)
#else
void _VS2rule_25(_currn )
_TPPrule_25 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
WriteDepFile(StringTable(_currn->_ATTERM_1));
/*SPC(88)*/

if (NOT(_currn->_ATInpFileEx_RuleAttr_95)) {
message(ERROR, CatStrInd("can not open file ", _currn->_ATTERM_1), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(87)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_26(_TPPrule_26 _currn)
#else
void _VS2rule_26(_currn )
_TPPrule_26 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRule_Vertical=IsVertical(_currn->_ATString);
/*SPC(160)*/
_currn->_ATMinHeight=MKDIM(MUL(SUB(1, _AVRule_Vertical), RuleThickness), _AVRule_Vertical);
/*SPC(162)*/
_currn->_ATMinWidth=MKDIM(MUL(_AVRule_Vertical, RuleThickness), SUB(1, _AVRule_Vertical));
/*SPC(161)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_26(_TPPrule_26 _currn)
#else
void _VS3rule_26(_currn )
_TPPrule_26 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRule_Height=GlueDim(_currn->_ATMinHeight, (* _IG_incl4));
/*SPC(323)*/
_AVRule_Width=GlueDim(_currn->_ATMinWidth, (* _IG_incl5));
/*SPC(322)*/
_AVRule_Col=(* _IG_incl2);
/*SPC(381)*/
_AVRule_Row=(* _IG_incl3);
/*SPC(380)*/
_AVRule_ForReal=(* _IG_incl6);
/*SPC(461)*/

if (_AVRule_ForReal) {
NewRule(_AVRule_Row, _AVRule_Col, SPACE(_AVRule_Width), SPACE(_AVRule_Height), 1, _currn->_ATString);

} else {
}
;
/*SPC(463)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_27(_TPPrule_27 _currn)
#else
void _VS2rule_27(_currn )
_TPPrule_27 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVVGlue_MinHeight=_AVVDimension_Dimension;
/*SPC(61)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_28(_TPPrule_28 _currn)
#else
void _VS2rule_28(_currn )
_TPPrule_28 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVHGlue_MinWidth=_AVHDimension_Dimension;
/*SPC(57)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_29(_TPPrule_29 _currn)
#else
void _VS1rule_29(_currn )
_TPPrule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_29(_TPPrule_29 _currn)
#else
void _VS2rule_29(_currn )
_TPPrule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVGlueSpec_Space=_currn->_ATTERM_1;
/*SPC(53)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_30(_TPPrule_30 _currn)
#else
void _VS1rule_30(_currn )
_TPPrule_30 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_30(_TPPrule_30 _currn)
#else
void _VS2rule_30(_currn )
_TPPrule_30 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSpace_Space=MUL(_currn->_ATTERM_1, (* _IG_incl13));
/*SPC(48)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_31(_TPPrule_31 _currn)
#else
void _VS2rule_31(_currn )
_TPPrule_31 _currn;

#endif
{
int* _IL_incl13;

_VisitVarDecl()
_VisitEntry();
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATGlueScale);
_currn->_ATGlueScale=DatumHeight(1);
/*SPC(43)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVVDimension_Dimension=_AVDimension_Dimension;
/*SPC(44)*/
_IG_incl13=_IL_incl13;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_32(_TPPrule_32 _currn)
#else
void _VS2rule_32(_currn )
_TPPrule_32 _currn;

#endif
{
int* _IL_incl13;

_VisitVarDecl()
_VisitEntry();
_IL_incl13=_IG_incl13;_IG_incl13= &(_currn->_ATGlueScale);
_currn->_ATGlueScale=DatumWidth(1);
/*SPC(38)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVHDimension_Dimension=_AVDimension_Dimension;
/*SPC(39)*/
_IG_incl13=_IL_incl13;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_33(_TPPrule_33 _currn)
#else
void _VS2rule_33(_currn )
_TPPrule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_34(_TPPrule_34 _currn)
#else
void _VS2rule_34(_currn )
_TPPrule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_036(_TPPrule_036 _currn)
#else
void _VS2rule_036(_currn )
_TPPrule_036 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG1Attr_pre=(* _IG_incl16);
/*SPC(114)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_036(_TPPrule_036 _currn)
#else
void _VS3rule_036(_currn )
_TPPrule_036 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVVField__const8=MKDIM0();
/*SPC(1081)*/
_currn->_ATMinWidth=_currn->_desc1->_AT_const3;
/*SPC(182)*/
_currn->_ATMinHeight=_currn->_desc1->_AT_const4;
/*SPC(178)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_036(_TPPrule_036 _currn,glue_t* _AS0Glue_pre,int* _AS0CRow_pre)
#else
void _VS4rule_036(_currn ,_AS0Glue_pre,_AS0CRow_pre)
_TPPrule_036 _currn;
int* _AS0CRow_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl24;
int* _IL_incl23;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl24=_IG_incl24;_IG_incl24= &(_currn->_ATHeight);
_IL_incl23=_IG_incl23;_IG_incl23= &(_currn->_ATRow);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
_currn->_ATCol=(* _IG_incl14);
/*SPC(346)*/
_currn->_ATRow=(* _AS0CRow_pre);
/*SPC(345)*/
_currn->_ATHeight=GlueApply(_currn->_ATMinHeight, (* _AS0Glue_pre));
/*SPC(293)*/
_currn->_ATWidth=GlueDim(_currn->_ATMinWidth, (* _IG_incl15));
/*SPC(292)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTDunterminatedCRow_pre=ADD((* _AS0CRow_pre), SPACE(_currn->_ATHeight));
/*SPC(344)*/
_AVTDunterminatedGlue_pre=GlueApplied(_currn->_ATMinHeight, (* _AS0Glue_pre));
/*SPC(294)*/
_IG_incl24=_IL_incl24;
_IG_incl23=_IL_incl23;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_036(_TPPrule_036 _currn,glue_t* _AS0Glue_pre,int* _AS0CRow_pre)
#else
void _VS5rule_036(_currn ,_AS0Glue_pre,_AS0CRow_pre)
_TPPrule_036 _currn;
int* _AS0CRow_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl24;
int* _IL_incl23;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl24=_IG_incl24;_IG_incl24= &(_currn->_ATHeight);
_IL_incl23=_IG_incl23;_IG_incl23= &(_currn->_ATRow);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVVField__const6=ZERO();
/*SPC(1081)*/
_IG_incl24=_IL_incl24;
_IG_incl23=_IL_incl23;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_035(_TPPrule_035 _currn)
#else
void _VS2rule_035(_currn )
_TPPrule_035 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG1Attr_pre=(* _IG_incl16);
/*SPC(114)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_035(_TPPrule_035 _currn)
#else
void _VS3rule_035(_currn )
_TPPrule_035 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVVField__const8=IDENTICAL(_AVColumns_MinWidth);
/*SPC(1077)*/
_currn->_ATMinWidth=IDENTICAL(_AVColumns_MinWidth);
/*SPC(182)*/
_currn->_ATMinHeight=IDENTICAL(_AVColumns_MinHeight);
/*SPC(178)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_035(_TPPrule_035 _currn,glue_t* _AS0Glue_pre,int* _AS0CRow_pre)
#else
void _VS4rule_035(_currn ,_AS0Glue_pre,_AS0CRow_pre)
_TPPrule_035 _currn;
int* _AS0CRow_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl24;
int* _IL_incl23;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl24=_IG_incl24;_IG_incl24= &(_currn->_ATHeight);
_IL_incl23=_IG_incl23;_IG_incl23= &(_currn->_ATRow);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
_currn->_ATRow=(* _AS0CRow_pre);
/*SPC(345)*/
_currn->_ATHeight=GlueApply(_currn->_ATMinHeight, (* _AS0Glue_pre));
/*SPC(293)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTDunterminatedCRow_pre=ADD((* _AS0CRow_pre), SPACE(_currn->_ATHeight));
/*SPC(344)*/
_AVTDunterminatedGlue_pre=GlueApplied(_currn->_ATMinHeight, (* _AS0Glue_pre));
/*SPC(294)*/
_currn->_ATCol=(* _IG_incl14);
/*SPC(346)*/
_currn->_ATWidth=GlueDim(_currn->_ATMinWidth, (* _IG_incl15));
/*SPC(292)*/
_IG_incl24=_IL_incl24;
_IG_incl23=_IL_incl23;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_035(_TPPrule_035 _currn,glue_t* _AS0Glue_pre,int* _AS0CRow_pre)
#else
void _VS5rule_035(_currn ,_AS0Glue_pre,_AS0CRow_pre)
_TPPrule_035 _currn;
int* _AS0CRow_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl24;
int* _IL_incl23;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl24=_IG_incl24;_IG_incl24= &(_currn->_ATHeight);
_IL_incl23=_IG_incl23;_IG_incl23= &(_currn->_ATRow);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVVField__const6=IDENTICAL(_currn->_desc1->_ATN_Cols);
/*SPC(1077)*/
_IG_incl24=_IL_incl24;
_IG_incl23=_IL_incl23;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_034(_TPPrule_034 _currn)
#else
void _VS2rule_034(_currn )
_TPPrule_034 _currn;

#endif
{
int _AS1CRow_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_034(_TPPrule_034 _currn)
#else
void _VS3rule_034(_currn )
_TPPrule_034 _currn;

#endif
{
int _AS1CRow_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTDunterminated__const8=_AVVField__const8;
/*SPC(1073)*/
_AVTDunterminated__const9=IDENTICAL(_currn->_desc1->_ATMinWidth);
/*SPC(1073)*/
_AVTDunterminated__const10=IDENTICAL(_currn->_desc1->_ATMinHeight);
/*SPC(1073)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_034(_TPPrule_034 _currn)
#else
void _VS4rule_034(_currn )
_TPPrule_034 _currn;

#endif
{
int _AS1CRow_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
_AS1CRow_pre=_AVTDunterminatedCRow_pre;
/*SPC(0)*/
_AS1Glue_pre=_AVTDunterminatedGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CRow_pre)));
_currn->_ATCRow_post=_AVTDunterminatedCRow_pre;
/*SPC(0)*/
_currn->_ATGlue_post=_AVTDunterminatedGlue_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_034(_TPPrule_034 _currn,int* _AS0_const6)
#else
void _VS5rule_034(_currn ,_AS0_const6)
_TPPrule_034 _currn;
int* _AS0_const6;

#endif
{
int _AS1CRow_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CRow_pre)));
(* _AS0_const6)=_AVVField__const6;
/*SPC(1073)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_033(_TPPrule_033 _currn)
#else
void _VS2rule_033(_currn )
_TPPrule_033 _currn;

#endif
{
int _AS2CRow_pre;
glue_t _AS2Glue_pre;
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_033(_TPPrule_033 _currn)
#else
void _VS3rule_033(_currn )
_TPPrule_033 _currn;

#endif
{
int _AS2CRow_pre;
glue_t _AS2Glue_pre;
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVTDunterminated__const8=MAXDIM(_AVTDunterminated__const8, _AVVField__const8);
/*SPC(1069)*/
_AVTDunterminated__const9=MAXDIM(_AVTDunterminated__const9, IDENTICAL(_currn->_desc2->_ATMinWidth));
/*SPC(1069)*/
_AVTDunterminated__const10=ADDDIM(_AVTDunterminated__const10, IDENTICAL(_currn->_desc2->_ATMinHeight));
/*SPC(1069)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_033(_TPPrule_033 _currn)
#else
void _VS4rule_033(_currn )
_TPPrule_033 _currn;

#endif
{
int _AS2CRow_pre;
glue_t _AS2Glue_pre;
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AS2CRow_pre=_currn->_desc1->_ATCRow_post;
/*SPC(0)*/
_AS2Glue_pre=_currn->_desc1->_ATGlue_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CRow_pre)));
_currn->_ATCRow_post=_AVTDunterminatedCRow_pre;
/*SPC(0)*/
_currn->_ATGlue_post=_AVTDunterminatedGlue_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_033(_TPPrule_033 _currn,int* _AS0_const6)
#else
void _VS5rule_033(_currn ,_AS0_const6)
_TPPrule_033 _currn;
int* _AS0_const6;

#endif
{
int _AS2CRow_pre;
glue_t _AS2Glue_pre;
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const6)));
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CRow_pre)));
(* _AS0_const6)=max(_AS1_const6, _AVVField__const6);
/*SPC(1069)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_032(_TPPrule_032 _currn)
#else
void _VS2rule_032(_currn )
_TPPrule_032 _currn;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_032(_TPPrule_032 _currn)
#else
void _VS3rule_032(_currn )
_TPPrule_032 _currn;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const8=_AVTDunterminated__const8;
/*SPC(1065)*/
_AVTableDefs__const9=_AVTDunterminated__const9;
/*SPC(1065)*/
_AVTableDefs__const10=_AVTDunterminated__const10;
/*SPC(1065)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_032(_TPPrule_032 _currn)
#else
void _VS4rule_032(_currn )
_TPPrule_032 _currn;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
_AVTDunterminatedCRow_pre=_currn->_ATCRow_pre;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_ATGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_032(_TPPrule_032 _currn,int* _AS0Attr_pre)
#else
void _VS5rule_032(_currn ,_AS0Attr_pre)
_TPPrule_032 _currn;
int* _AS0Attr_pre;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const6)));
_AVTableDefs__const6=_AS1_const6;
/*SPC(1065)*/
_AVTDunterminatedCRow_pre=_currn->_desc1->_ATCRow_post;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_desc1->_ATGlue_post;
/*SPC(0)*/
_AVG1Attr_pre=(* _AS0Attr_pre);
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_031(_TPPrule_031 _currn)
#else
void _VS2rule_031(_currn )
_TPPrule_031 _currn;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_031(_TPPrule_031 _currn)
#else
void _VS3rule_031(_currn )
_TPPrule_031 _currn;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const8=_AVTDunterminated__const8;
/*SPC(1061)*/
_AVTableDefs__const9=_AVTDunterminated__const9;
/*SPC(1061)*/
_AVTableDefs__const10=_AVTDunterminated__const10;
/*SPC(1061)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_031(_TPPrule_031 _currn)
#else
void _VS4rule_031(_currn )
_TPPrule_031 _currn;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
_AVTDunterminatedCRow_pre=_currn->_ATCRow_pre;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_ATGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_031(_TPPrule_031 _currn,int* _AS0Attr_pre)
#else
void _VS5rule_031(_currn ,_AS0Attr_pre)
_TPPrule_031 _currn;
int* _AS0Attr_pre;

#endif
{
int _AS1_const6;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const6)));
_AVTableDefs__const6=_AS1_const6;
/*SPC(1061)*/
_AVTDunterminatedCRow_pre=_currn->_desc1->_ATCRow_post;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_desc1->_ATGlue_post;
/*SPC(0)*/
_AVG1Attr_pre=(* _AS0Attr_pre);
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_030(_TPPrule_030 _currn)
#else
void _VS3rule_030(_currn )
_TPPrule_030 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_AT_const8=MKDIM0();
/*SPC(1057)*/
_AVTableDefs__const9=MKDIM0();
/*SPC(1057)*/
_AVTableDefs__const10=MKDIM0();
/*SPC(1057)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_030(_TPPrule_030 _currn,int* _AS0Attr_pre)
#else
void _VS5rule_030(_currn ,_AS0Attr_pre)
_TPPrule_030 _currn;
int* _AS0Attr_pre;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTableDefs__const6=ZERO();
/*SPC(1057)*/
_AVTDunterminatedCRow_pre=_currn->_ATCRow_pre;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_ATGlue_pre;
/*SPC(0)*/
_AVG1Attr_pre=(* _AS0Attr_pre);
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_029(_TPPrule_029 _currn)
#else
void _VS2rule_029(_currn )
_TPPrule_029 _currn;

#endif
{
int* _IL_incl16;
Environment* _IL_incl0;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATTableAttr);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATColEnv);
_currn->_ATTableAttr=_currn->_ATAttr_pre;
/*SPC(106)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATAttr_post=_currn->_ATAttr_pre;
/*SPC(105)*/
_currn->_ATMinWidth=_AVTableDefs__const9;
/*SPC(252)*/
_currn->_ATMinHeight=_AVTableDefs__const10;
/*SPC(245)*/
_IG_incl16=_IL_incl16;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_029(_TPPrule_029 _currn,int* _AS0Row)
#else
void _VS3rule_029(_currn ,_AS0Row)
_TPPrule_029 _currn;
int* _AS0Row;

#endif
{
dim_t* _IL_incl22;
dim_t* _IL_incl15;
int* _IL_incl14;
int* _IL_incl16;
dim_t* _IL_incl11;
Environment* _IL_incl0;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl22=_IG_incl22;_IG_incl22= &(_currn->_ATColumnsMinWidth);
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATWidth);
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATCol);
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATTableAttr);
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATColEnv);
_currn->_ATCol=(* _IG_incl17);
/*SPC(339)*/
(* _AS0Row)=(* _IG_incl18);
/*SPC(338)*/
_currn->_ATInhHeight=(* _IG_incl19);
/*SPC(273)*/
_currn->_ATWidth=GlueDim(_currn->_ATMinWidth, (* _IG_incl20));
/*SPC(271)*/
_currn->_ATColumnsMinWidth=_currn->_desc1->_AT_const8;
/*SPC(249)*/
_currn->_desc1->_ATCRow_pre=(* _AS0Row);
/*SPC(340)*/
_currn->_desc1->_ATGlue_pre=GlueSet(_currn->_ATMinHeight, _currn->_ATInhHeight);
/*SPC(276)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl22=_IL_incl22;
_IG_incl15=_IL_incl15;
_IG_incl14=_IL_incl14;
_IG_incl16=_IL_incl16;
_IG_incl11=_IL_incl11;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_029(_TPPrule_029 _currn,int* _AS0Row,PTGNode* _AS0FieldPrint_pre)
#else
void _VS4rule_029(_currn ,_AS0Row,_AS0FieldPrint_pre)
_TPPrule_029 _currn;
PTGNode* _AS0FieldPrint_pre;
int* _AS0Row;

#endif
{
dim_t* _IL_incl22;
dim_t* _IL_incl15;
int* _IL_incl14;
int* _IL_incl16;
dim_t* _IL_incl11;
Environment* _IL_incl0;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl22=_IG_incl22;_IG_incl22= &(_currn->_ATColumnsMinWidth);
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATWidth);
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATCol);
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATTableAttr);
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATColEnv);
_AVNamedTableFieldPrint_post=PTGNULL;
/*SPC(412)*/
_AS1Attr_pre=_currn->_ATAttr_pre;
/*SPC(107)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Attr_pre)));
_AVNamedTableFieldPrint_post=PTGSeq((* _AS0FieldPrint_pre), _AVNamedTableFieldPrint_post);
/*SPC(411)*/
_AVTable_N_Cols=_AVTableDefs__const6;
/*SPC(600)*/
_AVTable_Height=GlueDim(_currn->_ATMinHeight, _currn->_ATInhHeight);
/*SPC(275)*/
_IG_incl22=_IL_incl22;
_IG_incl15=_IL_incl15;
_IG_incl14=_IL_incl14;
_IG_incl16=_IL_incl16;
_IG_incl11=_IL_incl11;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_028(_TPPrule_028 _currn)
#else
void _VS2rule_028(_currn )
_TPPrule_028 _currn;

#endif
{
int* _IL_incl16;
Environment* _IL_incl0;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATTableAttr);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATColEnv);
_currn->_ATTableAttr=_currn->_ATAttr_pre;
/*SPC(106)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATAttr_post=_currn->_ATAttr_pre;
/*SPC(105)*/
_currn->_ATMinWidth=_AVTableDefs__const9;
/*SPC(252)*/
_currn->_ATMinHeight=_AVTableDefs__const10;
/*SPC(245)*/
_IG_incl16=_IL_incl16;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_028(_TPPrule_028 _currn,int* _AS0Row)
#else
void _VS3rule_028(_currn ,_AS0Row)
_TPPrule_028 _currn;
int* _AS0Row;

#endif
{
dim_t* _IL_incl22;
dim_t* _IL_incl15;
int* _IL_incl14;
int* _IL_incl16;
dim_t* _IL_incl11;
Environment* _IL_incl0;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl22=_IG_incl22;_IG_incl22= &(_currn->_ATColumnsMinWidth);
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATWidth);
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATCol);
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATTableAttr);
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATColEnv);
_currn->_ATCol=(* _IG_incl17);
/*SPC(339)*/
(* _AS0Row)=(* _IG_incl18);
/*SPC(338)*/
_currn->_ATInhHeight=(* _IG_incl19);
/*SPC(273)*/
_currn->_ATWidth=GlueDim(_currn->_ATMinWidth, (* _IG_incl20));
/*SPC(271)*/
_currn->_ATColumnsMinWidth=_currn->_desc1->_AT_const8;
/*SPC(249)*/
_currn->_desc1->_ATCRow_pre=(* _AS0Row);
/*SPC(340)*/
_currn->_desc1->_ATGlue_pre=GlueSet(_currn->_ATMinHeight, _currn->_ATInhHeight);
/*SPC(276)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl22=_IL_incl22;
_IG_incl15=_IL_incl15;
_IG_incl14=_IL_incl14;
_IG_incl16=_IL_incl16;
_IG_incl11=_IL_incl11;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_028(_TPPrule_028 _currn,int* _AS0Row,PTGNode* _AS0FieldPrint_pre)
#else
void _VS4rule_028(_currn ,_AS0Row,_AS0FieldPrint_pre)
_TPPrule_028 _currn;
PTGNode* _AS0FieldPrint_pre;
int* _AS0Row;

#endif
{
dim_t* _IL_incl22;
dim_t* _IL_incl15;
int* _IL_incl14;
int* _IL_incl16;
dim_t* _IL_incl11;
Environment* _IL_incl0;
int _AS1Attr_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl22=_IG_incl22;_IG_incl22= &(_currn->_ATColumnsMinWidth);
_IL_incl15=_IG_incl15;_IG_incl15= &(_currn->_ATWidth);
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATCol);
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATTableAttr);
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATColEnv);
_AVNamedTableFieldPrint_post=PTGNULL;
/*SPC(412)*/
_AS1Attr_pre=_currn->_ATAttr_pre;
/*SPC(107)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Attr_pre)));
_AVNamedTableFieldPrint_post=PTGSeq((* _AS0FieldPrint_pre), _AVNamedTableFieldPrint_post);
/*SPC(411)*/
_AVTable_N_Cols=_AVTableDefs__const6;
/*SPC(600)*/
_AVTable_Height=GlueDim(_currn->_ATMinHeight, _currn->_ATInhHeight);
/*SPC(275)*/
_IG_incl22=_IL_incl22;
_IG_incl15=_IL_incl15;
_IG_incl14=_IL_incl14;
_IG_incl16=_IL_incl16;
_IG_incl11=_IL_incl11;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_027(_TPPrule_027 _currn)
#else
void _VS2rule_027(_currn )
_TPPrule_027 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRightAlignChar_present=1;
/*SPC(167)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_026(_TPPrule_026 _currn)
#else
void _VS2rule_026(_currn )
_TPPrule_026 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRightAlign_MinWidth=MKDIM(0, _AVG3__const11);
/*SPC(173)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_025(_TPPrule_025 _currn)
#else
void _VS2rule_025(_currn )
_TPPrule_025 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLeftAlignChar_present=1;
/*SPC(166)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_024(_TPPrule_024 _currn)
#else
void _VS2rule_024(_currn )
_TPPrule_024 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATMinWidth=MKDIM(0, _AVG2__const12);
/*SPC(169)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_024(_TPPrule_024 _currn)
#else
void _VS3rule_024(_currn )
_TPPrule_024 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTDunterminatedGlue_pre=GlueApplied(_currn->_ATMinWidth, _AVLeftAlignGlue_pre);
/*SPC(288)*/
_AVLeftAlign_Width=GlueApply(_currn->_ATMinWidth, _AVLeftAlignGlue_pre);
/*SPC(287)*/
_AVHBunterminatedCCol_pre=ADD(_AVHBunterminatedCCol_pre, SPACE(_AVLeftAlign_Width));
/*SPC(365)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_023(_TPPrule_023 _currn)
#else
void _VS2rule_023(_currn )
_TPPrule_023 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATMinWidth=_currn->_desc1->_AT_const3;
/*SPC(182)*/
_currn->_ATMinHeight=_currn->_desc1->_AT_const4;
/*SPC(178)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_023(_TPPrule_023 _currn,glue_t* _AS0Glue_pre,int* _AS0CCol_pre)
#else
void _VS3rule_023(_currn ,_AS0Glue_pre,_AS0CCol_pre)
_TPPrule_023 _currn;
int* _AS0CCol_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl11;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
_currn->_ATCol=(* _AS0CCol_pre);
/*SPC(370)*/
_currn->_ATRow=(* _IG_incl3);
/*SPC(369)*/
_currn->_ATWidth=GlueApply(_currn->_ATMinWidth, (* _AS0Glue_pre));
/*SPC(299)*/
_currn->_ATHeight=GlueDim(_currn->_ATMinHeight, (* _IG_incl21));
/*SPC(298)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVHBunterminatedCCol_pre=ADD((* _AS0CCol_pre), SPACE(_currn->_ATWidth));
/*SPC(371)*/
_AVTDunterminatedGlue_pre=GlueApplied(_currn->_ATMinWidth, (* _AS0Glue_pre));
/*SPC(300)*/
_IG_incl11=_IL_incl11;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_023(_TPPrule_023 _currn,glue_t* _AS0Glue_pre,int* _AS0CCol_pre)
#else
void _VS4rule_023(_currn ,_AS0Glue_pre,_AS0CCol_pre)
_TPPrule_023 _currn;
int* _AS0CCol_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl11;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl11=_IL_incl11;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_022(_TPPrule_022 _currn,dim_t* _AS0_const14,dim_t* _AS0_const13)
#else
void _VS2rule_022(_currn ,_AS0_const14,_AS0_const13)
_TPPrule_022 _currn;
dim_t* _AS0_const13;
dim_t* _AS0_const14;

#endif
{
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(* _AS0_const13)=IDENTICAL(_currn->_desc1->_ATMinWidth);
/*SPC(1025)*/
(* _AS0_const14)=IDENTICAL(_currn->_desc1->_ATMinHeight);
/*SPC(1025)*/
_currn->_ATAttr_post=_AVG1Attr_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_022(_TPPrule_022 _currn,dim_t* _AS0_const14,dim_t* _AS0_const13)
#else
void _VS3rule_022(_currn ,_AS0_const14,_AS0_const13)
_TPPrule_022 _currn;
dim_t* _AS0_const13;
dim_t* _AS0_const14;

#endif
{
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
_AS1CCol_pre=_AVHBunterminatedCCol_pre;
/*SPC(0)*/
_AS1Glue_pre=_AVTDunterminatedGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CCol_pre)));
_currn->_ATCCol_post=_AVHBunterminatedCCol_pre;
/*SPC(0)*/
_currn->_ATGlue_post=_AVTDunterminatedGlue_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_022(_TPPrule_022 _currn,dim_t* _AS0_const14,dim_t* _AS0_const13)
#else
void _VS4rule_022(_currn ,_AS0_const14,_AS0_const13)
_TPPrule_022 _currn;
dim_t* _AS0_const13;
dim_t* _AS0_const14;

#endif
{
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CCol_pre)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_021(_TPPrule_021 _currn,dim_t* _AS0_const14,dim_t* _AS0_const13)
#else
void _VS2rule_021(_currn ,_AS0_const14,_AS0_const13)
_TPPrule_021 _currn;
dim_t* _AS0_const13;
dim_t* _AS0_const14;

#endif
{
int _AS2CCol_pre;
glue_t _AS2Glue_pre;
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));
_AVG1Attr_pre=_currn->_desc1->_ATAttr_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0_const13)=ADDDIM(_AS1_const13, IDENTICAL(_currn->_desc2->_ATMinWidth));
/*SPC(1021)*/
(* _AS0_const14)=MAXDIM(_AS1_const14, IDENTICAL(_currn->_desc2->_ATMinHeight));
/*SPC(1021)*/
_currn->_ATAttr_post=_AVG1Attr_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_021(_TPPrule_021 _currn,dim_t* _AS0_const14,dim_t* _AS0_const13)
#else
void _VS3rule_021(_currn ,_AS0_const14,_AS0_const13)
_TPPrule_021 _currn;
dim_t* _AS0_const13;
dim_t* _AS0_const14;

#endif
{
int _AS2CCol_pre;
glue_t _AS2Glue_pre;
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));
_AS2CCol_pre=_currn->_desc1->_ATCCol_post;
/*SPC(0)*/
_AS2Glue_pre=_currn->_desc1->_ATGlue_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CCol_pre)));
_currn->_ATCCol_post=_AVHBunterminatedCCol_pre;
/*SPC(0)*/
_currn->_ATGlue_post=_AVTDunterminatedGlue_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_021(_TPPrule_021 _currn,dim_t* _AS0_const14,dim_t* _AS0_const13)
#else
void _VS4rule_021(_currn ,_AS0_const14,_AS0_const13)
_TPPrule_021 _currn;
dim_t* _AS0_const13;
dim_t* _AS0_const14;

#endif
{
int _AS2CCol_pre;
glue_t _AS2Glue_pre;
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CCol_pre)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_020(_TPPrule_020 _currn,int* _AS0Attr_pre)
#else
void _VS2rule_020(_currn ,_AS0Attr_pre)
_TPPrule_020 _currn;
int* _AS0Attr_pre;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATAttr_pre=(* _AS0Attr_pre);
/*SPC(111)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1Attr_pre=(* _AS0Attr_pre);
/*SPC(110)*/
_currn->_ATMinWidth=_AVHBFields__const13;
/*SPC(236)*/
_currn->_ATMinHeight=_AVHBFields__const14;
/*SPC(232)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_020(_TPPrule_020 _currn,int* _AS0Attr_pre)
#else
void _VS3rule_020(_currn ,_AS0Attr_pre)
_TPPrule_020 _currn;
int* _AS0Attr_pre;

#endif
{
dim_t* _IL_incl21;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATHeight);
_currn->_ATHeight=GlueDim(_currn->_ATMinHeight, (* _IG_incl4));
/*SPC(282)*/
_currn->_ATInhWidth=(* _IG_incl5);
/*SPC(280)*/
_currn->_desc1->_ATCCol_pre=(* _IG_incl2);
/*SPC(361)*/
_currn->_desc1->_ATGlue_pre=GlueSet(_currn->_ATMinWidth, _currn->_ATInhWidth);
/*SPC(283)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_020(_TPPrule_020 _currn,int* _AS0Attr_pre)
#else
void _VS4rule_020(_currn ,_AS0Attr_pre)
_TPPrule_020 _currn;
int* _AS0Attr_pre;

#endif
{
dim_t* _IL_incl21;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATHeight);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVHBOX_Width=GlueDim(_currn->_ATMinWidth, _currn->_ATInhWidth);
/*SPC(281)*/
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_019(_TPPrule_019 _currn)
#else
void _VS2rule_019(_currn )
_TPPrule_019 _currn;

#endif
{
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
_AVG1Attr_pre=_currn->_ATAttr_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));
_AVHBFields__const13=_AS1_const13;
/*SPC(1013)*/
_AVHBFields__const14=_AS1_const14;
/*SPC(1013)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_019(_TPPrule_019 _currn)
#else
void _VS3rule_019(_currn )
_TPPrule_019 _currn;

#endif
{
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
_AVHBunterminatedCCol_pre=_currn->_ATCCol_pre;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_ATGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_019(_TPPrule_019 _currn)
#else
void _VS4rule_019(_currn )
_TPPrule_019 _currn;

#endif
{
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));
_AVHBunterminatedCCol_pre=_currn->_desc1->_ATCCol_post;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_desc1->_ATGlue_post;
/*SPC(0)*/
_AVG1Attr_pre=_currn->_desc1->_ATAttr_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_018(_TPPrule_018 _currn)
#else
void _VS2rule_018(_currn )
_TPPrule_018 _currn;

#endif
{
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
_AVG1Attr_pre=_currn->_ATAttr_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));
_AVHBFields__const13=_AS1_const13;
/*SPC(1009)*/
_AVHBFields__const14=_AS1_const14;
/*SPC(1009)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_018(_TPPrule_018 _currn)
#else
void _VS3rule_018(_currn )
_TPPrule_018 _currn;

#endif
{
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
_AVHBunterminatedCCol_pre=_currn->_ATCCol_pre;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_ATGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_018(_TPPrule_018 _currn)
#else
void _VS4rule_018(_currn )
_TPPrule_018 _currn;

#endif
{
dim_t _AS1_const13;
dim_t _AS1_const14;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,dim_t*,dim_t*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1_const14)),(&( _AS1_const13)));
_AVHBunterminatedCCol_pre=_currn->_desc1->_ATCCol_post;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_desc1->_ATGlue_post;
/*SPC(0)*/
_AVG1Attr_pre=_currn->_desc1->_ATAttr_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_017(_TPPrule_017 _currn)
#else
void _VS2rule_017(_currn )
_TPPrule_017 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVHBFields__const13=MKDIM0();
/*SPC(1005)*/
_AVHBFields__const14=MKDIM0();
/*SPC(1005)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_017(_TPPrule_017 _currn)
#else
void _VS4rule_017(_currn )
_TPPrule_017 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVHBunterminatedCCol_pre=_currn->_ATCCol_pre;
/*SPC(0)*/
_AVTDunterminatedGlue_pre=_currn->_ATGlue_pre;
/*SPC(0)*/
_AVG1Attr_pre=_currn->_ATAttr_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_016(_TPPrule_016 _currn)
#else
void _VS2rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATMinWidth=IDENTICAL(_AVGFIELD_MinWidth);
/*SPC(182)*/
_currn->_ATMinHeight=IDENTICAL(_AVGFIELD_MinHeight);
/*SPC(178)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_016(_TPPrule_016 _currn,glue_t* _AS0Glue_pre,int* _AS0CCol_pre)
#else
void _VS3rule_016(_currn ,_AS0Glue_pre,_AS0CCol_pre)
_TPPrule_016 _currn;
int* _AS0CCol_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl11;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
_currn->_ATCol=(* _AS0CCol_pre);
/*SPC(370)*/
_currn->_ATRow=(* _IG_incl3);
/*SPC(369)*/
_currn->_ATWidth=GlueApply(_currn->_ATMinWidth, (* _AS0Glue_pre));
/*SPC(299)*/
_currn->_ATHeight=GlueDim(_currn->_ATMinHeight, (* _IG_incl21));
/*SPC(298)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVHBunterminatedCCol_pre=ADD((* _AS0CCol_pre), SPACE(_currn->_ATWidth));
/*SPC(371)*/
_AVTDunterminatedGlue_pre=GlueApplied(_currn->_ATMinWidth, (* _AS0Glue_pre));
/*SPC(300)*/
_IG_incl11=_IL_incl11;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_016(_TPPrule_016 _currn,glue_t* _AS0Glue_pre,int* _AS0CCol_pre)
#else
void _VS4rule_016(_currn ,_AS0Glue_pre,_AS0CCol_pre)
_TPPrule_016 _currn;
int* _AS0CCol_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl11;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl11=_IL_incl11;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_015(_TPPrule_015 _currn)
#else
void _VS2rule_015(_currn )
_TPPrule_015 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGlue_MinHeight=IDENTICAL(_AVVGlue_MinHeight);
/*SPC(67)*/
_AVGlue_MinWidth=MKDIM0();
/*SPC(65)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_014(_TPPrule_014 _currn)
#else
void _VS2rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGlue_MinHeight=MKDIM0();
/*SPC(67)*/
_AVGlue_MinWidth=IDENTICAL(_AVHGlue_MinWidth);
/*SPC(65)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_013(_TPPrule_013 _currn)
#else
void _VS2rule_013(_currn )
_TPPrule_013 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const3=IDENTICAL(_AVGFIELD_MinWidth);
/*SPC(989)*/
_currn->_AT_const4=IDENTICAL(_AVGFIELD_MinHeight);
/*SPC(989)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_013(_TPPrule_013 _currn)
#else
void _VS3rule_013(_currn )
_TPPrule_013 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_013(_TPPrule_013 _currn)
#else
void _VS4rule_013(_currn )
_TPPrule_013 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_012(_TPPrule_012 _currn)
#else
void _VS2rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const3=IDENTICAL(_AVGFIELD_MinWidth);
/*SPC(985)*/
_currn->_AT_const4=IDENTICAL(_AVGFIELD_MinHeight);
/*SPC(985)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_012(_TPPrule_012 _currn)
#else
void _VS3rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_012(_TPPrule_012 _currn)
#else
void _VS4rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_011(_TPPrule_011 _currn)
#else
void _VS2rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG3__const11=ADD(_AVG3__const11, IDENTICAL(_AVRightAlignChar_present));
/*SPC(981)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_010(_TPPrule_010 _currn)
#else
void _VS2rule_010(_currn )
_TPPrule_010 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVG3__const11=ZERO();
/*SPC(977)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_09(_TPPrule_09 _currn)
#else
void _VS2rule_09(_currn )
_TPPrule_09 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG2__const12=IDENTICAL(_AVLeftAlignChar_present);
/*SPC(973)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_08(_TPPrule_08 _currn)
#else
void _VS2rule_08(_currn )
_TPPrule_08 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG2__const12=ADD(_AVG2__const12, IDENTICAL(_AVLeftAlignChar_present));
/*SPC(969)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_07(_TPPrule_07 _currn)
#else
void _VS2rule_07(_currn )
_TPPrule_07 _currn;

#endif
{
int _AS2ColNumber_pre;
int _AS2CCol_pre;
glue_t _AS2Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AS2ColNumber_pre=_currn->_desc1->_ATColNumber_post;
/*SPC(0)*/
_AVG1Attr_pre=_currn->_desc1->_ATAttr_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2ColNumber_pre)));
_currn->_ATColNumber_post=_AVG1ColNumber_pre;
/*SPC(0)*/
_currn->_ATAttr_post=_AVG1Attr_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_07(_TPPrule_07 _currn)
#else
void _VS3rule_07(_currn )
_TPPrule_07 _currn;

#endif
{
int _AS2ColNumber_pre;
int _AS2CCol_pre;
glue_t _AS2Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR ,int*)) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2ColNumber_pre)));
_AVG1__const19=ADDDIM(_AVG1__const19, IDENTICAL(_currn->_desc2->_ATColMinWidth));
/*SPC(965)*/
_AVG1__const20=MAXDIM(_AVG1__const20, IDENTICAL(_currn->_desc2->_ATMinHeight));
/*SPC(965)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_07(_TPPrule_07 _currn)
#else
void _VS4rule_07(_currn )
_TPPrule_07 _currn;

#endif
{
int _AS2ColNumber_pre;
int _AS2CCol_pre;
glue_t _AS2Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AS2CCol_pre=_AVHBunterminatedCCol_pre;
/*SPC(0)*/
_AS2Glue_pre=_AVTDunterminatedGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*,int*)) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CCol_pre)),(&( _AS2ColNumber_pre)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_07(_TPPrule_07 _currn)
#else
void _VS5rule_07(_currn )
_TPPrule_07 _currn;

#endif
{
int _AS2ColNumber_pre;
int _AS2CCol_pre;
glue_t _AS2Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR ,glue_t*,int*,int*)) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CCol_pre)),(&( _AS2ColNumber_pre)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_06(_TPPrule_06 _currn)
#else
void _VS2rule_06(_currn )
_TPPrule_06 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
_AS1ColNumber_pre=_AVG1ColNumber_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ColNumber_pre)));
_currn->_ATColNumber_post=_AVG1ColNumber_pre;
/*SPC(0)*/
_currn->_ATAttr_post=_AVG1Attr_pre;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_06(_TPPrule_06 _currn)
#else
void _VS3rule_06(_currn )
_TPPrule_06 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ColNumber_pre)));
_AVG1__const19=IDENTICAL(_currn->_desc1->_ATColMinWidth);
/*SPC(961)*/
_AVG1__const20=IDENTICAL(_currn->_desc1->_ATMinHeight);
/*SPC(961)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_06(_TPPrule_06 _currn)
#else
void _VS4rule_06(_currn )
_TPPrule_06 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
_AS1CCol_pre=_AVHBunterminatedCCol_pre;
/*SPC(0)*/
_AS1Glue_pre=_AVTDunterminatedGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*,int*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CCol_pre)),(&( _AS1ColNumber_pre)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_06(_TPPrule_06 _currn)
#else
void _VS5rule_06(_currn )
_TPPrule_06 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,glue_t*,int*,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CCol_pre)),(&( _AS1ColNumber_pre)));

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_05(_TPPrule_05 _currn)
#else
void _VS2rule_05(_currn )
_TPPrule_05 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVDimension_Dimension=MKDIM(IDENTICAL(_AVSpace_Space), ZERO());
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_04(_TPPrule_04 _currn)
#else
void _VS2rule_04(_currn )
_TPPrule_04 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVDimension_Dimension=MKDIM(IDENTICAL(_AVSpace_Space), IDENTICAL(_AVGlueSpec_Space));
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_03(_TPPrule_03 _currn)
#else
void _VS2rule_03(_currn )
_TPPrule_03 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
_AS1ColNumber_pre=0;
/*SPC(608)*/
(*(_CALL_VS_((NODEPTR ,int*)) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ColNumber_pre)));
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_03(_TPPrule_03 _currn)
#else
void _VS3rule_03(_currn )
_TPPrule_03 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,int*)) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1ColNumber_pre)));
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATN_Cols=_currn->_desc2->_ATColNumber_post;
/*SPC(609)*/
_AVColumns_MinWidth=ADDDIM(ADDDIM(IDENTICAL(_currn->_desc1->_ATColMinWidth), _AVG1__const19), MKDIM(MUL(SUB(_currn->_ATN_Cols, 1), ColSpace), 0));
/*SPC(646)*/
_AVColumns_MinHeight=MAXDIM(IDENTICAL(_currn->_desc1->_ATMinHeight), _AVG1__const20);
/*SPC(225)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_03(_TPPrule_03 _currn)
#else
void _VS4rule_03(_currn )
_TPPrule_03 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
_AS1CCol_pre=(* _IG_incl14);
/*SPC(351)*/
_AS1Glue_pre=GlueSet((* _IG_incl22), (* _IG_incl15));
/*SPC(304)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*,int*)) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CCol_pre)),(&( _AS1ColNumber_pre)));
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_03(_TPPrule_03 _currn)
#else
void _VS5rule_03(_currn )
_TPPrule_03 _currn;

#endif
{
int _AS1ColNumber_pre;
int _AS1CCol_pre;
glue_t _AS1Glue_pre;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,glue_t*,int*,int*)) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Glue_pre)),(&( _AS1CCol_pre)),(&( _AS1ColNumber_pre)));
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1Attr_pre=_currn->_desc2->_ATAttr_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_02(_TPPrule_02 _currn,int* _AS0ColNumber_pre)
#else
void _VS2rule_02(_currn ,_AS0ColNumber_pre)
_TPPrule_02 _currn;
int* _AS0ColNumber_pre;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1ColNumber_pre=ADD((* _AS0ColNumber_pre), 1);
/*SPC(613)*/
_AVCField_MinWidth=_currn->_desc1->_AT_const3;
/*SPC(182)*/
_AVCField_Sym=(* _AS0ColNumber_pre);
/*SPC(614)*/
_AVCField_Bind=BindIdn((* _IG_incl0), _AVCField_Sym);
/*SPC(692)*/
_currn->_ATKey=KeyOf(_AVCField_Bind);
/*SPC(695)*/
ResetMinWidth(_currn->_ATKey, MAXDIM(GetMinWidth(_currn->_ATKey, MKDIM0()), _AVCField_MinWidth));
/*SPC(637)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_02(_TPPrule_02 _currn,int* _AS0ColNumber_pre)
#else
void _VS3rule_02(_currn ,_AS0ColNumber_pre)
_TPPrule_02 _currn;
int* _AS0ColNumber_pre;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATColMinWidth=GetMinWidth(_currn->_ATKey, MKDIM0());
/*SPC(641)*/
_currn->_ATMinHeight=_currn->_desc1->_AT_const4;
/*SPC(178)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_02(_TPPrule_02 _currn,glue_t* _AS0Glue_pre,int* _AS0CCol_pre,int* _AS0ColNumber_pre)
#else
void _VS4rule_02(_currn ,_AS0Glue_pre,_AS0CCol_pre,_AS0ColNumber_pre)
_TPPrule_02 _currn;
int* _AS0ColNumber_pre;
int* _AS0CCol_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl11;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
_currn->_ATCol=(* _AS0CCol_pre);
/*SPC(356)*/
_currn->_ATRow=(* _IG_incl23);
/*SPC(355)*/
_currn->_ATHeight=GlueDim(_currn->_ATMinHeight, (* _IG_incl24));
/*SPC(311)*/
_currn->_ATWidth=GlueApply(_currn->_ATColMinWidth, (* _AS0Glue_pre));
/*SPC(309)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVHBunterminatedCCol_pre=ADD(ADD((* _AS0CCol_pre), SPACE(_currn->_ATWidth)), 1);
/*SPC(357)*/
_AVTDunterminatedGlue_pre=GlueApplied(_currn->_ATColMinWidth, (* _AS0Glue_pre));
/*SPC(310)*/
_IG_incl11=_IL_incl11;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_02(_TPPrule_02 _currn,glue_t* _AS0Glue_pre,int* _AS0CCol_pre,int* _AS0ColNumber_pre)
#else
void _VS5rule_02(_currn ,_AS0Glue_pre,_AS0CCol_pre,_AS0ColNumber_pre)
_TPPrule_02 _currn;
int* _AS0ColNumber_pre;
int* _AS0CCol_pre;
glue_t* _AS0Glue_pre;

#endif
{
dim_t* _IL_incl11;
dim_t* _IL_incl10;
dim_t* _IL_incl9;
int* _IL_incl8;
int* _IL_incl7;

_VisitVarDecl()
_VisitEntry();
_IL_incl11=_IG_incl11;_IG_incl11= &(_currn->_ATWidth);
_IL_incl10=_IG_incl10;_IG_incl10= &(_currn->_ATWidth);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATHeight);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATRow);
_IL_incl7=_IG_incl7;_IG_incl7= &(_currn->_ATCol);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl11=_IL_incl11;
_IG_incl10=_IL_incl10;
_IG_incl9=_IL_incl9;
_IG_incl8=_IL_incl8;
_IG_incl7=_IL_incl7;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_01(_TPPrule_01 _currn,int* _AS0Attr_pre)
#else
void _VS2rule_01(_currn ,_AS0Attr_pre)
_TPPrule_01 _currn;
int* _AS0Attr_pre;

#endif
{
int _AS2CCol_pre;
glue_t _AS2Glue_pre;

_VisitVarDecl()
_VisitEntry();
_AVG1Attr_pre=(* _AS0Attr_pre);
/*SPC(111)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_AVG1Attr_pre=(* _AS0Attr_pre);
/*SPC(110)*/
_currn->_ATMinWidth=ADDDIM(ADDDIM(IDENTICAL(_currn->_desc1->_ATMinWidth), IDENTICAL(_currn->_desc2->_ATMinWidth)), IDENTICAL(_AVRightAlign_MinWidth));
/*SPC(236)*/
_currn->_ATMinHeight=IDENTICAL(_currn->_desc2->_ATMinHeight);
/*SPC(232)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_01(_TPPrule_01 _currn,int* _AS0Attr_pre)
#else
void _VS3rule_01(_currn ,_AS0Attr_pre)
_TPPrule_01 _currn;
int* _AS0Attr_pre;

#endif
{
dim_t* _IL_incl21;
int _AS2CCol_pre;
glue_t _AS2Glue_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATHeight);
_currn->_ATInhWidth=(* _IG_incl5);
/*SPC(280)*/
_AVHBunterminatedCCol_pre=(* _IG_incl2);
/*SPC(361)*/
_AVLeftAlignGlue_pre=GlueSet(_currn->_ATMinWidth, _currn->_ATInhWidth);
/*SPC(283)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATHeight=GlueDim(_currn->_ATMinHeight, (* _IG_incl4));
/*SPC(282)*/
_AS2CCol_pre=_AVHBunterminatedCCol_pre;
/*SPC(0)*/
_AS2Glue_pre=_AVTDunterminatedGlue_pre;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CCol_pre)));
_IG_incl21=_IL_incl21;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_01(_TPPrule_01 _currn,int* _AS0Attr_pre)
#else
void _VS4rule_01(_currn ,_AS0Attr_pre)
_TPPrule_01 _currn;
int* _AS0Attr_pre;

#endif
{
dim_t* _IL_incl21;
int _AS2CCol_pre;
glue_t _AS2Glue_pre;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATHeight);
(*(_CALL_VS_((NODEPTR ,glue_t*,int*)) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Glue_pre)),(&( _AS2CCol_pre)));
_AVHBOX_Width=GlueDim(_currn->_ATMinWidth, _currn->_ATInhWidth);
/*SPC(281)*/
_IG_incl21=_IL_incl21;

_VisitExit();
}

