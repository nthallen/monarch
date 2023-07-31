
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
int* _IG_incl34;
int* _IG_incl33;
long* _IG_incl32;
WaveDtoAP* _IG_incl31;
DefTableKey* _IG_incl27;
int* _IG_incl25;
PTGNode* _IG_incl26;
double* _IG_incl24;
double* _IG_incl23;
double* _IG_incl21;
int* _IG_incl20;
long* _IG_incl19;
WaveDtoAP* _IG_incl18;
double* _IG_incl16;
DefTableKey* _IG_incl17;
Environment* _IG_incl14;
int* _IG_incl8;
long* _IG_incl9;
int* _IG_incl6;
double* _IG_incl5;
int* _IG_incl4;
int* _IG_incl2;
int* _IG_incl1;
double* _IG_incl0;
double _AVRingCmd__const6;
int _AVRingCmd__const7;
int _AVRingCmd__const53;
PTGNode _AVRingCmd__const54;
int _AVRingCmd__const55;
double _AVG4__const6;
int _AVG4__const7;
double _AVICOSCmd__const6;
int _AVICOSCmd__const7;
double _AVICOSCmd__const62;
PTGNode _AVICOSCmd__const63;
PTGNode _AVICOSCmd__const64;
PTGNode _AVICOSCmd__const65;
PTGNode _AVICOSCmd__const66;
PTGNode _AVICOSCmd__const67;
double _AVICOSCmd__const68;
long _AVICOSCmd__const69;
double _AVICOSCmd__const70;
RateDefP _AVICOSCmd__const71;
double _AVICOSCmd__const72;
int _AVICOSCmd_cICOSRampCount_post;
double _AVICOSCmdCrntI_post;
longP _AVTzDefrvals_post;
int _AVTzDefrcnt_post;
double _AVG3__const6;
int _AVG3__const7;
double _AVG3__const62;
PTGNode _AVG3__const63;
PTGNode _AVG3__const64;
PTGNode _AVG3__const65;
PTGNode _AVG3__const66;
PTGNode _AVG3__const67;
double _AVG3__const68;
RateDefP _AVG3__const71;
double _AVG3__const72;
PTGNode _AVG1__const22;
PTGNode _AVG1__const23;
PTGNode _AVG1__const24;
PTGNode _AVG1__const25;
PTGNode _AVG1__const26;
PTGNode _AVG1__const27;
PTGNode _AVG1__const28;
PTGNode _AVG1__const29;
PTGNode _AVG1__const30;
PTGNode _AVG1__const31;
PTGNode _AVG1__const32;
PTGNode _AVG1__const33;
PTGNode _AVG1__const34;
PTGNode _AVG1__const35;
PTGNode _AVG1__const36;
PTGNode _AVG1__const37;
PTGNode _AVG1__const38;
int _AVWaveWaveCnt_post;
long _AVG1WaveAddr_post;
int _AVConfigCmds_cICOSRampCount_post;
long _AVRingStepsize_ProgLen;
double _AVRingStepsize_Istep;
double _AVRingCount_Iramp_RuleAttr_89;
long _AVRingCount_ProgLen;
double _AVRingCount_Istep;
double _AVRingStep_Istep;
long _AVRingStep_ProgLen;
PTGNode _AVCurrentSteps_PTG;
double _AVCurrentSteps_Istep;
double _AVCurrentSteps_Istop;
double _AVCurrentSteps_Istart;
long _AVCurrentSteps_NetSamples;
long _AVCurrentSteps_ProgLen;
PTGNode _AVRingCurrent_PTG;
double _AVRingCurrent_Value;
long _AVRingCurrent_NetSamples;
long _AVRingCurrent_ProgLen;
double _AVTpreVal_RawRate;
DefTableKey _AVTpreVal_Key;
double _AVTpreVal_Value;
double _AVTonVal_TonPct_RuleAttr_93;
double _AVTonVal_ToffD;
DefTableKey _AVTonVal_Key;
double _AVTonVal_Value;
DefTableKey _AVTpreDef_Key;
DefTableKey _AVTonDef_Key;
DefTableKey _AVRingNsampleDef_Key;
DefTableKey _AVToffDef_Key;
RateDefP _AVRingRateDef_RateDef;
DefTableKey _AVRingRateDef_Key;
PTGNode _AVRingData__const54;
long _AVRingData_NetSamples;
long _AVRingData_ProgLen;
int _AVDAC3Value_DAC3Unique;
WaveDtoAP _AVDAC3Value_DtoAs;
long _AVSampleSpec_Nsample;
int _AVSampleSpec_Naverage;
double _AVTzTime__const1;
double _AVTzSpec_RawRate;
RateDefP _AVRateDef_RateDef;
int _AVRateDef_Naverage;
double _AVRateDef_RawRate;
long _AVNsampleDef_Nsample;
int _AVNaverage_Naverage;
int _AVICOSRamp_ICOSRampIncrement;
PTGNode _AVICOSRamp_Summary;
PTGNode _AVICOSRamp_PTG;
int _AVICOSRamp_DtoA;
double _AVICOSRamp_DeltaI;
WaveDtoAP _AVICOSRamp_DtoAs;
long _AVICOSRamp_SSrampi;
long _AVICOSRamp_SSzi;
int _AVICOSRamp_SplitFactor;
int _AVICOSRamp_SplitCycle;
double _AVICOSRamp_Tramp1;
long _AVICOSRamp_Trampi;
double _AVICOSRamp_Iramp;
double _AVICOSRamp_Istop1;
double _AVICOSRamp_Istart1;
double _AVICOSRamp_Istop;
double _AVICOSRamp_Istart;
DefTableKey _AVICOSRamp_Key;
double _AVdIdt_Value;
double _AVPercent_Value;
double _AVRateUnit_Value;
double _AVTimeUnit_Value;
double _AVTime_Value;
double _AVCurrentUnit_Value;
PTGNode _AVICOSRateDef__const63;
RateDefP _AVICOSRateDef__const71;
int _AVICOSRateDef_SampleUnique;
PTGNode _AVICOSNsampleDef__const64;
int _AVICOSNsampleDef_SampleUnique;
RateDefP _AVICOSNsampleDef_RateDef;
long _AVICOSNsampleDef_Nsample;
double _AVICOSNsampleDef_Tramps;
int _AVNcoaddDef_NcoaddUnique;
int _AVIzDef_IzUnique;
PTGNode _AVTzDef__const66;
int _AVTzDef_TzUnique;
int _AVPrefix_Prefix;
int _AVPrefix_PrefixUnique;
int _AVDigitizerType_Digitizer;
int _AVDigitizerType_DigUnique;
int _AVQCLIConfigType_QCLIConfig;
int _AVQCLIConfigType_QCUnique;
int _AVSourceFile_ICOSRampInitCount;
int _AVSourceFile_ICOSRampCountResult;
PTGNode _AVSourceFile_DISPoutput;
PTGNode _AVSourceFile_Moutput;
PTGNode _AVSourceFile_CMDoutput;
PTGNode _AVSourceFile_Summary;
PTGNode _AVSourceFile_PTG;
int _AVSourceFile_NWaves;
long _AVSourceFile_ProgLen;
PTGNode _AVWave__const24;
PTGNode _AVWave__const25;
PTGNode _AVWave__const26;
PTGNode _AVWave__const27;
PTGNode _AVWave__const29;
PTGNode _AVWave__const30;
PTGNode _AVWave__const31;
PTGNode _AVWave__const32;
PTGNode _AVWave__const33;
PTGNode _AVWave__const34;
PTGNode _AVWave__const36;
PTGNode _AVWave__const38;
PTGNode _AVWave_DISPoutput;
PTGNode _AVWave_CMDoutput;
PTGNode _AVWave_WaveIndex;
long _AVWave_ProgLen;
int _AVWave_Ncoadd_specd;
int _AVWave_Sym;
double _AVRingCmds__const6;
int _AVRingCmds__const7;
double _AVRingCmds_Istart1;
double _AVRingCmds_dIdt;
int _AVRingCmds_ISICOS;
PTGNode _AVRingCmds_CMDoutput;
double _AVRingCmds_Iz;
long _AVRingCmds_TzSamples;
long _AVRingCmds_Ftrigger;
long _AVRingCmds_Ttrigger;
long _AVRingCmds_Toff;
long _AVRingCmds_RawSamples;
int _AVRingCmds_Naverage;
long _AVRingCmds_TpreSpec;
long _AVRingCmds_Ton;
long _AVRingCmds_NetSamples;
WaveDtoAP _AVRingCmds_DtoAs;
PTGNode _AVRingCmds_PTG;
long _AVRingCmds_ProgLen;
long _AVRingWave__const5;
DefTableKey _AVRingWave__const9;
PTGNode _AVRingWave__const24;
PTGNode _AVRingWave__const25;
PTGNode _AVRingWave__const26;
PTGNode _AVRingWave__const27;
PTGNode _AVRingWave__const29;
PTGNode _AVRingWave__const30;
PTGNode _AVRingWave__const31;
PTGNode _AVRingWave__const32;
PTGNode _AVRingWave__const33;
PTGNode _AVRingWave__const34;
PTGNode _AVRingWave__const38;
double _AVICOSCmds__const6;
int _AVICOSCmds__const7;
long _AVICOSWaveWaveAddr_post;
long _AVICOSCmdsWaveAddr_pre;
int _AVICOSCmds_ICOSRampInitCount;
double _AVICOSCmds_Istart1;
int _AVICOSCmds_ISICOS;
PTGNode _AVICOSCmds_CMDoutput;
double _AVICOSCmds_TriggerSecs;
PTGNode _AVICOSCmds_Summary;
PTGNode _AVICOSCmds_PTG;
long _AVICOSCmds_LoopAddr;
int _AVICOSCmds_WaveNum;
int _AVICOSCmds_DtoA;
double _AVICOSCmds_Iz;
long _AVICOSCmds_TzRawSamples;
long _AVICOSCmds_TzSamples;
long _AVICOSCmds_RampSamples;
long _AVICOSCmds_RawSamples;
long _AVICOSCmds_NetSamples;
long _AVICOSCmds_SSrcy;
long _AVICOSCmds_SSzif;
long _AVICOSCmds_ProgLen;
long _AVICOSCmds_Ftrigger;
long _AVICOSCmds_Tcycle;
int _AVICOSCmds_Scycle;
long _AVICOSCmds_Ttrigger;
long _AVICOSCmds_Toff;
long _AVICOSCmds_Ton;
long _AVICOSCmds_Trcy;
long _AVICOSCmds_Srcy;
long _AVICOSCmds_Trcypre;
long _AVICOSCmds_Trcymin;
long _AVICOSCmds_EstSamples;
double _AVICOSCmds_Tz1;
double _AVICOSCmds_Tramps1;
long _AVICOSCmds_Tcyc0;
int _AVICOSCmds_Scyc0;
long _AVICOSCmds_Tzi;
int _AVICOSCmds_Szi;
double _AVICOSCmds_Tz;
double _AVICOSCmds_NetRate;
RateDefP _AVICOSCmds_RateDef;
short _AVICOSCmds_dIdt_bits;
double _AVICOSCmds_dIdt;
DefTableKey _AVICOSCmds_Key;
Binding _AVDefIdent_Bind;
int _AVDefIdent_Unique;
long _AVICOSWave__const5;
DefTableKey _AVICOSWave__const9;
PTGNode _AVICOSWave__const24;
PTGNode _AVICOSWave__const25;
PTGNode _AVICOSWave__const26;
PTGNode _AVICOSWave__const27;
PTGNode _AVICOSWave__const29;
PTGNode _AVICOSWave__const30;
PTGNode _AVICOSWave__const31;
PTGNode _AVICOSWave__const32;
PTGNode _AVICOSWave__const33;
PTGNode _AVICOSWave__const34;
PTGNode _AVICOSWave__const36;
PTGNode _AVICOSWave__const38;

#if defined(__STDC__) || defined(__cplusplus)
void LIGA_ATTREVAL (NODEPTR _currn)
#else
void LIGA_ATTREVAL (_currn) NODEPTR _currn;
#endif
{(*(VS1MAP[_currn->_prod])) ((NODEPTR)_currn);}
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
void _VS1rule_1(_TPPrule_1 _currn)
#else
void _VS1rule_1(_currn )
_TPPrule_1 _currn;

#endif
{
double _AS1Value;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Value)));
_AVRingStepsize_Istep=_AS1Value;
/*SPC(894)*/
_AVRingStepsize_ProgLen=ADD(ceil(SUB(DIV((* _IG_incl0), _AVRingStepsize_Istep), .05)), 1);
/*SPC(895)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_2(_TPPrule_2 _currn)
#else
void _VS1rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCount_Iramp_RuleAttr_89=(* _IG_incl0);
/*SPC(890)*/
_AVRingCount_ProgLen=_currn->_ATTERM_1;
/*SPC(889)*/
_AVRingCount_Istep=DIV(_AVRingCount_Iramp_RuleAttr_89, SUB(_AVRingCount_ProgLen, 1));
/*SPC(891)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_3(_TPPrule_3 _currn)
#else
void _VS1rule_3(_currn )
_TPPrule_3 _currn;

#endif
{
double* _IL_incl0;
double _AS2Value;
double _AS1Value;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATIramp);
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Value)));
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2,(&( _AS2Value)));
_AVCurrentSteps_Istop=_AS2Value;
/*SPC(876)*/
_AVCurrentSteps_Istart=_AS1Value;
/*SPC(875)*/
_currn->_ATIramp=SUB(_AVCurrentSteps_Istop, _AVCurrentSteps_Istart);
/*SPC(877)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
_AVCurrentSteps_Istep=_AVRingStep_Istep;
/*SPC(880)*/
_AVCurrentSteps_NetSamples=_AVRingStep_ProgLen;
/*SPC(879)*/
_AVCurrentSteps_ProgLen=MUL(_AVRingStep_ProgLen, (* _IG_incl1));
/*SPC(878)*/
_AVCurrentSteps_PTG=RingdownPTG(_AVCurrentSteps_Istart, _AVCurrentSteps_Istop, _AVCurrentSteps_Istep, _AVCurrentSteps_ProgLen, (* _IG_incl1), (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(936)*/
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_4(_TPPrule_4 _currn)
#else
void _VS1rule_4(_currn )
_TPPrule_4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTpreVal_Value=DIV(_currn->_ATTERM_1, _AVTpreVal_RawRate);
/*SPC(859)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTpreVal_Value=_AVTime_Value;
/*SPC(857)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTonVal_TonPct_RuleAttr_93=
((OR(LE(_currn->_desc1->_ATValue, 0), GE(_currn->_desc1->_ATValue, 100))
) ? (
(message(ERROR, "Ton percentage out of range", 0, (&( _currn->_AT_pos))), 50)

) : (_currn->_desc1->_ATValue))
;
/*SPC(834)*/
_AVTonVal_Value=MUL(_AVTonVal_ToffD, DIV(_AVTonVal_TonPct_RuleAttr_93, SUB(100, _AVTonVal_TonPct_RuleAttr_93)));
/*SPC(841)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTonVal_Value=_AVTime_Value;
/*SPC(831)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_8(_TPPrule_8 _currn)
#else
void _VS1rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetDAC3Unique(_currn->_ATKey, 1, 0);
/*SPC(1412)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_8(_TPPrule_8 _currn)
#else
void _VS2rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
set_dac3_value(_AVDAC3Value_DtoAs, _currn->_desc1->_ATValue, (&( _currn->_AT_pos)));
/*SPC(549)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_8(_TPPrule_8 _currn)
#else
void _VS3rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDAC3Value_DAC3Unique=GetDAC3Unique(_currn->_ATKey, 0);
/*SPC(1415)*/

if (NOT(_AVDAC3Value_DAC3Unique)) {
message(ERROR, "DAC3 is multiply defined in this waveform", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(540)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn)
#else
void _VS1rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetDAC3Unique(_currn->_ATKey, 1, 0);
/*SPC(1412)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_9(_TPPrule_9 _currn)
#else
void _VS2rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
set_dac3_bits(_AVDAC3Value_DtoAs, _currn->_ATTERM_1, (&( _currn->_AT_pos)));
/*SPC(545)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_9(_TPPrule_9 _currn)
#else
void _VS3rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDAC3Value_DAC3Unique=GetDAC3Unique(_currn->_ATKey, 0);
/*SPC(1415)*/

if (NOT(_AVDAC3Value_DAC3Unique)) {
message(ERROR, "DAC3 is multiply defined in this waveform", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(540)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_10(_TPPrule_10 _currn)
#else
void _VS1rule_10(_currn )
_TPPrule_10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVSampleSpec_Naverage=(* _IG_incl4);
/*SPC(335)*/

if (EQ(_AVTzSpec_RawRate, 0.)) {
message(ERROR, "Tz specified in samples, but rate is zero", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(347)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATTz=
((GT(_AVTzSpec_RawRate, 0.)
) ? (DIV(_AVSampleSpec_Nsample, _AVTzSpec_RawRate)
) : (0.))
;
/*SPC(349)*/
_AVTzDefrcnt_post=ADD(_currn->_ATrcnt_pre, 
((GT(_currn->_ATTz, 0.)
) ? (2
) : (0))
);
/*SPC(369)*/

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
_currn->_AT_const66=IDENTICAL(_currn->_desc1->_ATSummary);
/*SPC(346)*/
_AVTzDefrvals_post=
((GT(_currn->_ATTz, 0.)
) ? (
(Set_rval(_AVTzDefrvals_post, _currn->_ATrcnt_pre, _currn->_ATTz), Set_rval(_AVTzDefrvals_post, ADD(_currn->_ATrcnt_pre, 1), _currn->_ATTz))

) : (_AVTzDefrvals_post))
;
/*SPC(370)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_11(_TPPrule_11 _currn)
#else
void _VS1rule_11(_currn )
_TPPrule_11 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATSummary=PTGSpecd(PTGTzSample(_currn->_ATTERM_1, ""));
/*SPC(730)*/
_AVSampleSpec_Nsample=MUL(_currn->_ATTERM_1, (* _IG_incl4));
/*SPC(343)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_12(_TPPrule_12 _currn)
#else
void _VS1rule_12(_currn )
_TPPrule_12 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATSummary=PTGSpecd(PTGTzSample(_currn->_ATTERM_1, "Raw "));
/*SPC(727)*/
_AVSampleSpec_Nsample=MUL(DIV_UP(_currn->_ATTERM_1, _AVSampleSpec_Naverage), _AVSampleSpec_Naverage);
/*SPC(338)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_13(_TPPrule_13 _currn)
#else
void _VS1rule_13(_currn )
_TPPrule_13 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (GE(_AVPercent_Value, 1.)) {
message(ERROR, "Tz percent must be less than 100", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(327)*/
_currn->_ATTz=
((GT(_AVPercent_Value, 0)
) ? (MUL((* _IG_incl5), MUL(0.5, DIV(_AVPercent_Value, SUB(1., _AVPercent_Value))))
) : (0))
;
/*SPC(329)*/
_AVTzDefrcnt_post=ADD(_currn->_ATrcnt_pre, 
((GT(_currn->_ATTz, 0.)
) ? (2
) : (0))
);
/*SPC(369)*/

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
_currn->_AT_const66=IDENTICAL(_currn->_desc1->_ATSummary);
/*SPC(326)*/
_AVTzDefrvals_post=
((GT(_currn->_ATTz, 0.)
) ? (
(Set_rval(_AVTzDefrvals_post, _currn->_ATrcnt_pre, _currn->_ATTz), Set_rval(_AVTzDefrvals_post, ADD(_currn->_ATrcnt_pre, 1), _currn->_ATTz))

) : (_AVTzDefrvals_post))
;
/*SPC(370)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_14(_TPPrule_14 _currn)
#else
void _VS1rule_14(_currn )
_TPPrule_14 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTzTime__const1=_AVTime_Value;
/*SPC(325)*/
_currn->_ATSummary=PTGSpecd(PTGTime(MUL(_AVTime_Value, 1000.)));
/*SPC(723)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_15(_TPPrule_15 _currn)
#else
void _VS1rule_15(_currn )
_TPPrule_15 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATTz=_AVTzTime__const1;
/*SPC(323)*/
_AVTzDefrcnt_post=ADD(_currn->_ATrcnt_pre, 
((GT(_currn->_ATTz, 0.)
) ? (2
) : (0))
);
/*SPC(369)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_15(_TPPrule_15 _currn)
#else
void _VS2rule_15(_currn )
_TPPrule_15 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_AT_const66=IDENTICAL(_currn->_desc1->_ATSummary);
/*SPC(322)*/
_AVTzDefrvals_post=
((GT(_currn->_ATTz, 0.)
) ? (
(Set_rval(_AVTzDefrvals_post, _currn->_ATrcnt_pre, _currn->_ATTz), Set_rval(_AVTzDefrvals_post, ADD(_currn->_ATrcnt_pre, 1), _currn->_ATTz))

) : (_AVTzDefrvals_post))
;
/*SPC(370)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_16(_TPPrule_16 _currn)
#else
void _VS1rule_16(_currn )
_TPPrule_16 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVRateDef_Naverage=_AVNaverage_Naverage;
/*SPC(300)*/
_AVRateDef_RawRate=MUL(_currn->_ATTERM_1, _AVRateUnit_Value);
/*SPC(299)*/
_currn->_ATSummary=PTGSpecd(PTGSampleRate(_AVRateDef_RawRate, _AVRateDef_Naverage));
/*SPC(689)*/
_AVRateDef_RateDef=NewRateDefPtr(_AVRateDef_RawRate, _AVNaverage_Naverage, 1, (* _IG_incl6), (&( _currn->_AT_pos)));
/*SPC(301)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_17(_TPPrule_17 _currn)
#else
void _VS1rule_17(_currn )
_TPPrule_17 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVNsampleDef_Nsample=_currn->_ATTERM_1;
/*SPC(283)*/
_currn->_ATSummary=PTGSpecd(PTGLong(_AVNsampleDef_Nsample));
/*SPC(693)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_18(_TPPrule_18 _currn)
#else
void _VS1rule_18(_currn )
_TPPrule_18 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVNaverage_Naverage=_currn->_ATTERM_1;
/*SPC(275)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_19(_TPPrule_19 _currn)
#else
void _VS1rule_19(_currn )
_TPPrule_19 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVNaverage_Naverage=1;
/*SPC(273)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_20(_TPPrule_20 _currn)
#else
void _VS1rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetNcoaddUnique(_currn->_ATKey, 1, 0);
/*SPC(1360)*/

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
_AVNcoaddDef_NcoaddUnique=GetNcoaddUnique(_currn->_ATKey, 0);
/*SPC(1363)*/

if (NOT(_AVNcoaddDef_NcoaddUnique)) {
message(ERROR, "Ncoadd is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(124)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_21(_TPPrule_21 _currn)
#else
void _VS1rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_currn->_ATTramp=_currn->_desc2->_ATValue;
/*SPC(248)*/

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
_AVTzDefrcnt_post=ADD(_currn->_ATrcnt_pre, 1);
/*SPC(376)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_21(_TPPrule_21 _currn)
#else
void _VS4rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDefrvals_post=Set_rval(_AVTzDefrvals_post, _currn->_ATrcnt_pre, _currn->_ATTramp);
/*SPC(377)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_21(_TPPrule_21 _currn)
#else
void _VS5rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_ICOSRampIncrement=1;
/*SPC(1440)*/
_currn->_ATICOSRampCount=ADD(_AVICOSCmd_cICOSRampCount_post, _AVICOSRamp_ICOSRampIncrement);
/*SPC(1441)*/
_currn->_ATSrampi=DIV_UP(usecs(_currn->_ATTramp), (* _IG_incl9));
/*SPC(390)*/
_AVICOSCmd_cICOSRampCount_post=_currn->_ATICOSRampCount;
/*SPC(1442)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_21(_TPPrule_21 _currn)
#else
void _VS6rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_SSrampi=SUB(MUL(_AVICOSRamp_SplitFactor, _currn->_ATSrampi), 
((AND(AND(_AVICOSRamp_SplitCycle, EQ(_AVICOSRamp_SSzi, 0)), EQ(_currn->_ATICOSRampCount, (* _IG_incl8)))
) ? (1
) : (0))
);
/*SPC(464)*/
_AVICOSRamp_Trampi=MUL(_currn->_ATSrampi, (* _IG_incl9));
/*SPC(392)*/
_AVICOSRamp_Istop=_currn->_desc1->_ATValue;
/*SPC(247)*/
_AVICOSRamp_Istart=SUB(_currn->_desc1->_ATValue, MUL(_currn->_desc2->_ATValue, _currn->_ATdIdt));
/*SPC(246)*/
_AVICOSRamp_Key=NewKey();
/*SPC(208)*/
_AVICOSRamp_Tramp1=DIV(_AVICOSRamp_Trampi, 1000000.);
/*SPC(393)*/
_AVICOSRamp_Iramp=MUL(_AVICOSRamp_Tramp1, _currn->_ATdIdt);
/*SPC(394)*/
_AVICOSRamp_Istop1=_AVICOSRamp_Istop;
/*SPC(250)*/
_AVICOSRamp_Istart1=SUB(_AVICOSRamp_Istop, _AVICOSRamp_Iramp);
/*SPC(251)*/
_AVICOSRamp_Summary=PTGRamp(PTGNull(), PTGCurrent(MUL(_AVICOSRamp_Istart1, 1000.)), IDENTICAL(_currn->_desc1->_ATSummary), PTGCurrent(MUL(_AVICOSRamp_Istop1, 1000.)), IDENTICAL(_currn->_desc2->_ATSummary), PTGTime(MUL(_AVICOSRamp_Tramp1, 1000.)), _currn->_ATSrampi);
/*SPC(697)*/
_AVICOSRamp_DeltaI=SUB(_AVICOSRamp_Istart1, _AVICOSCmdCrntI_post);
/*SPC(532)*/
_AVICOSRamp_DtoA=alloc_dtoa(_AVICOSRamp_DtoAs, _AVICOSRamp_DeltaI, (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(533)*/
_AVICOSCmdCrntI_post=_AVICOSRamp_Istop1;
/*SPC(535)*/
_AVICOSRamp_PTG=PTGICOSFill(ADD(WV_RAMP_ON, _AVICOSRamp_DtoA), _AVICOSRamp_SSrampi);
/*SPC(639)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_22(_TPPrule_22 _currn)
#else
void _VS1rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_currn->_ATTramp=_currn->_desc2->_ATValue;
/*SPC(239)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_22(_TPPrule_22 _currn)
#else
void _VS3rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDefrcnt_post=ADD(_currn->_ATrcnt_pre, 1);
/*SPC(376)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_22(_TPPrule_22 _currn)
#else
void _VS4rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDefrvals_post=Set_rval(_AVTzDefrvals_post, _currn->_ATrcnt_pre, _currn->_ATTramp);
/*SPC(377)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_22(_TPPrule_22 _currn)
#else
void _VS5rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_ICOSRampIncrement=1;
/*SPC(1440)*/
_currn->_ATICOSRampCount=ADD(_AVICOSCmd_cICOSRampCount_post, _AVICOSRamp_ICOSRampIncrement);
/*SPC(1441)*/
_currn->_ATSrampi=DIV_UP(usecs(_currn->_ATTramp), (* _IG_incl9));
/*SPC(390)*/
_AVICOSCmd_cICOSRampCount_post=_currn->_ATICOSRampCount;
/*SPC(1442)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_22(_TPPrule_22 _currn)
#else
void _VS6rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_SSrampi=SUB(MUL(_AVICOSRamp_SplitFactor, _currn->_ATSrampi), 
((AND(AND(_AVICOSRamp_SplitCycle, EQ(_AVICOSRamp_SSzi, 0)), EQ(_currn->_ATICOSRampCount, (* _IG_incl8)))
) ? (1
) : (0))
);
/*SPC(464)*/
_AVICOSRamp_Trampi=MUL(_currn->_ATSrampi, (* _IG_incl9));
/*SPC(392)*/
_AVICOSRamp_Istop=ADD(_currn->_desc1->_ATValue, MUL(_currn->_desc2->_ATValue, _currn->_ATdIdt));
/*SPC(238)*/
_AVICOSRamp_Istart=_currn->_desc1->_ATValue;
/*SPC(237)*/
_AVICOSRamp_Key=NewKey();
/*SPC(208)*/
_AVICOSRamp_Tramp1=DIV(_AVICOSRamp_Trampi, 1000000.);
/*SPC(393)*/
_AVICOSRamp_Iramp=MUL(_AVICOSRamp_Tramp1, _currn->_ATdIdt);
/*SPC(394)*/
_AVICOSRamp_Istop1=ADD(_AVICOSRamp_Istart, _AVICOSRamp_Iramp);
/*SPC(242)*/
_AVICOSRamp_Istart1=_AVICOSRamp_Istart;
/*SPC(241)*/
_AVICOSRamp_Summary=PTGRamp(IDENTICAL(_currn->_desc1->_ATSummary), PTGCurrent(MUL(_AVICOSRamp_Istart1, 1000.)), PTGNull(), PTGCurrent(MUL(_AVICOSRamp_Istop1, 1000.)), IDENTICAL(_currn->_desc2->_ATSummary), PTGTime(MUL(_AVICOSRamp_Tramp1, 1000.)), _currn->_ATSrampi);
/*SPC(697)*/
_AVICOSRamp_DeltaI=SUB(_AVICOSRamp_Istart1, _AVICOSCmdCrntI_post);
/*SPC(532)*/
_AVICOSRamp_DtoA=alloc_dtoa(_AVICOSRamp_DtoAs, _AVICOSRamp_DeltaI, (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(533)*/
_AVICOSCmdCrntI_post=_AVICOSRamp_Istop1;
/*SPC(535)*/
_AVICOSRamp_PTG=PTGICOSFill(ADD(WV_RAMP_ON, _AVICOSRamp_DtoA), _AVICOSRamp_SSrampi);
/*SPC(639)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_23(_TPPrule_23 _currn)
#else
void _VS1rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_currn->_ATTramp=DIV(SUB(_currn->_desc2->_ATValue, _currn->_desc1->_ATValue), _currn->_ATdIdt);
/*SPC(230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_23(_TPPrule_23 _currn)
#else
void _VS3rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDefrcnt_post=ADD(_currn->_ATrcnt_pre, 1);
/*SPC(376)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_23(_TPPrule_23 _currn)
#else
void _VS4rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDefrvals_post=Set_rval(_AVTzDefrvals_post, _currn->_ATrcnt_pre, _currn->_ATTramp);
/*SPC(377)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_23(_TPPrule_23 _currn)
#else
void _VS5rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_ICOSRampIncrement=1;
/*SPC(1440)*/
_currn->_ATICOSRampCount=ADD(_AVICOSCmd_cICOSRampCount_post, _AVICOSRamp_ICOSRampIncrement);
/*SPC(1441)*/
_currn->_ATSrampi=DIV_UP(usecs(_currn->_ATTramp), (* _IG_incl9));
/*SPC(390)*/
_AVICOSCmd_cICOSRampCount_post=_currn->_ATICOSRampCount;
/*SPC(1442)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_23(_TPPrule_23 _currn)
#else
void _VS6rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_SSrampi=SUB(MUL(_AVICOSRamp_SplitFactor, _currn->_ATSrampi), 
((AND(AND(_AVICOSRamp_SplitCycle, EQ(_AVICOSRamp_SSzi, 0)), EQ(_currn->_ATICOSRampCount, (* _IG_incl8)))
) ? (1
) : (0))
);
/*SPC(464)*/
_AVICOSRamp_Trampi=MUL(_currn->_ATSrampi, (* _IG_incl9));
/*SPC(392)*/
_AVICOSRamp_Istop=_currn->_desc2->_ATValue;
/*SPC(229)*/
_AVICOSRamp_Istart=_currn->_desc1->_ATValue;
/*SPC(228)*/
_AVICOSRamp_Key=NewKey();
/*SPC(208)*/
_AVICOSRamp_Tramp1=DIV(_AVICOSRamp_Trampi, 1000000.);
/*SPC(393)*/
_AVICOSRamp_Iramp=MUL(_AVICOSRamp_Tramp1, _currn->_ATdIdt);
/*SPC(394)*/
_AVICOSRamp_Istop1=ADD(_AVICOSRamp_Istart, _AVICOSRamp_Iramp);
/*SPC(233)*/
_AVICOSRamp_Istart1=_AVICOSRamp_Istart;
/*SPC(232)*/
_AVICOSRamp_Summary=PTGRamp(IDENTICAL(_currn->_desc1->_ATSummary), PTGCurrent(MUL(_AVICOSRamp_Istart1, 1000.)), IDENTICAL(_currn->_desc2->_ATSummary), PTGCurrent(MUL(_AVICOSRamp_Istop1, 1000.)), PTGNull(), PTGTime(MUL(_AVICOSRamp_Tramp1, 1000.)), _currn->_ATSrampi);
/*SPC(697)*/
_AVICOSRamp_DeltaI=SUB(_AVICOSRamp_Istart1, _AVICOSCmdCrntI_post);
/*SPC(532)*/
_AVICOSRamp_DtoA=alloc_dtoa(_AVICOSRamp_DtoAs, _AVICOSRamp_DeltaI, (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(533)*/
_AVICOSCmdCrntI_post=_AVICOSRamp_Istop1;
/*SPC(535)*/
_AVICOSRamp_PTG=PTGICOSFill(ADD(WV_RAMP_ON, _AVICOSRamp_DtoA), _AVICOSRamp_SSrampi);
/*SPC(639)*/

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
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
SetdIdtDefined(_currn->_ATWaveKey, 1, 2);
ResetdIdt(_currn->_ATWaveKey, DIV(SUB(_currn->_desc2->_ATValue, _currn->_desc1->_ATValue), _currn->_desc3->_ATValue));
;
/*SPC(213)*/

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
_currn->_ATTramp=_currn->_desc3->_ATValue;
/*SPC(221)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_24(_TPPrule_24 _currn)
#else
void _VS3rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDefrcnt_post=ADD(_currn->_ATrcnt_pre, 1);
/*SPC(376)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_24(_TPPrule_24 _currn)
#else
void _VS4rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDefrvals_post=Set_rval(_AVTzDefrvals_post, _currn->_ATrcnt_pre, _currn->_ATTramp);
/*SPC(377)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_24(_TPPrule_24 _currn)
#else
void _VS5rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_ICOSRampIncrement=1;
/*SPC(1440)*/
_currn->_ATICOSRampCount=ADD(_AVICOSCmd_cICOSRampCount_post, _AVICOSRamp_ICOSRampIncrement);
/*SPC(1441)*/
_currn->_ATSrampi=DIV_UP(usecs(_currn->_ATTramp), (* _IG_incl9));
/*SPC(390)*/
_AVICOSCmd_cICOSRampCount_post=_currn->_ATICOSRampCount;
/*SPC(1442)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_24(_TPPrule_24 _currn)
#else
void _VS6rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (EQ(GetdIdtDefined(_currn->_ATWaveKey, 0), 2)) {
message(ERROR, "dI/dt is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(216)*/
_AVICOSRamp_SSrampi=SUB(MUL(_AVICOSRamp_SplitFactor, _currn->_ATSrampi), 
((AND(AND(_AVICOSRamp_SplitCycle, EQ(_AVICOSRamp_SSzi, 0)), EQ(_currn->_ATICOSRampCount, (* _IG_incl8)))
) ? (1
) : (0))
);
/*SPC(464)*/
_AVICOSRamp_Trampi=MUL(_currn->_ATSrampi, (* _IG_incl9));
/*SPC(392)*/
_AVICOSRamp_Istop=_currn->_desc2->_ATValue;
/*SPC(220)*/
_AVICOSRamp_Istart=_currn->_desc1->_ATValue;
/*SPC(219)*/
_AVICOSRamp_Key=NewKey();
/*SPC(208)*/
_AVICOSRamp_Tramp1=DIV(_AVICOSRamp_Trampi, 1000000.);
/*SPC(393)*/
_AVICOSRamp_Iramp=MUL(_AVICOSRamp_Tramp1, _currn->_ATdIdt);
/*SPC(394)*/
_AVICOSRamp_Istop1=ADD(_AVICOSRamp_Istart, _AVICOSRamp_Iramp);
/*SPC(224)*/
_AVICOSRamp_Istart1=_AVICOSRamp_Istart;
/*SPC(223)*/
_AVICOSRamp_Summary=PTGRamp(IDENTICAL(_currn->_desc1->_ATSummary), PTGCurrent(MUL(_AVICOSRamp_Istart1, 1000.)), IDENTICAL(_currn->_desc2->_ATSummary), PTGCurrent(MUL(_AVICOSRamp_Istop1, 1000.)), IDENTICAL(_currn->_desc3->_ATSummary), PTGTime(MUL(_AVICOSRamp_Tramp1, 1000.)), _currn->_ATSrampi);
/*SPC(697)*/
_AVICOSRamp_DeltaI=SUB(_AVICOSRamp_Istart1, _AVICOSCmdCrntI_post);
/*SPC(532)*/
_AVICOSRamp_DtoA=alloc_dtoa(_AVICOSRamp_DtoAs, _AVICOSRamp_DeltaI, (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(533)*/
_AVICOSCmdCrntI_post=_AVICOSRamp_Istop1;
/*SPC(535)*/
_AVICOSRamp_PTG=PTGICOSFill(ADD(WV_RAMP_ON, _AVICOSRamp_DtoA), _AVICOSRamp_SSrampi);
/*SPC(639)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_25(_TPPrule_25 _currn)
#else
void _VS1rule_25(_currn )
_TPPrule_25 _currn;

#endif
{
double _AS1Value;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Value)));
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVdIdt_Value=DIV(_AS1Value, _AVTimeUnit_Value);
/*SPC(177)*/
SetdIdtDefined(_currn->_ATKey, 1, 2);
ResetdIdt(_currn->_ATKey, _AVdIdt_Value);
;
/*SPC(181)*/

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

if (EQ(GetdIdtDefined(_currn->_ATKey, 0), 2)) {
message(ERROR, "dI/dt is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(184)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_26(_TPPrule_26 _currn)
#else
void _VS1rule_26(_currn )
_TPPrule_26 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATValue=atof(StringTable(_currn->_ATTERM_1));
/*SPC(162)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_27(_TPPrule_27 _currn)
#else
void _VS1rule_27(_currn )
_TPPrule_27 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATValue=CAST(double, _currn->_ATTERM_1);
/*SPC(161)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_28(_TPPrule_28 _currn)
#else
void _VS1rule_28(_currn )
_TPPrule_28 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRateUnit_Value=DIV(1., _AVTimeUnit_Value);
/*SPC(160)*/

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
_AVRateUnit_Value=1000000.;
/*SPC(159)*/

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
_AVRateUnit_Value=1000;
/*SPC(158)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_31(_TPPrule_31 _currn)
#else
void _VS1rule_31(_currn )
_TPPrule_31 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRateUnit_Value=1;
/*SPC(157)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_32(_TPPrule_32 _currn)
#else
void _VS1rule_32(_currn )
_TPPrule_32 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTimeUnit_Value=0.000001;
/*SPC(156)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_33(_TPPrule_33 _currn)
#else
void _VS1rule_33(_currn )
_TPPrule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTimeUnit_Value=0.001;
/*SPC(155)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_34(_TPPrule_34 _currn)
#else
void _VS1rule_34(_currn )
_TPPrule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTimeUnit_Value=1;
/*SPC(154)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_35(_TPPrule_35 _currn)
#else
void _VS1rule_35(_currn )
_TPPrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCurrentUnit_Value=0.000001;
/*SPC(153)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_36(_TPPrule_36 _currn)
#else
void _VS1rule_36(_currn )
_TPPrule_36 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCurrentUnit_Value=0.001;
/*SPC(152)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_37(_TPPrule_37 _currn)
#else
void _VS1rule_37(_currn )
_TPPrule_37 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVCurrentUnit_Value=1;
/*SPC(151)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_38(_TPPrule_38 _currn)
#else
void _VS1rule_38(_currn )
_TPPrule_38 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVTime_Value=MUL(_currn->_desc1->_ATValue, _AVTimeUnit_Value);
/*SPC(149)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_39(_TPPrule_39 _currn,double* _AS0Value)
#else
void _VS1rule_39(_currn ,_AS0Value)
_TPPrule_39 _currn;
double* _AS0Value;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(* _AS0Value)=MUL(_currn->_desc1->_ATValue, _AVCurrentUnit_Value);
/*SPC(146)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_40(_TPPrule_40 _currn)
#else
void _VS1rule_40(_currn )
_TPPrule_40 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetPrefixUnique(_currn->_ATKey, 1, 0);
/*SPC(1282)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_40(_TPPrule_40 _currn)
#else
void _VS2rule_40(_currn )
_TPPrule_40 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPrefix_Prefix=_currn->_ATTERM_1;
/*SPC(98)*/
_AVPrefix_PrefixUnique=GetPrefixUnique(_currn->_ATKey, 0);
/*SPC(1285)*/
ResetPrefix(_currn->_ATKey, _AVPrefix_Prefix);
/*SPC(95)*/

if (NOT(_AVPrefix_PrefixUnique)) {
message(ERROR, "Prefix is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(92)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_41(_TPPrule_41 _currn)
#else
void _VS1rule_41(_currn )
_TPPrule_41 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetDigUnique(_currn->_ATKey, 1, 0);
/*SPC(1256)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_41(_TPPrule_41 _currn)
#else
void _VS2rule_41(_currn )
_TPPrule_41 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDigitizerType_Digitizer=DIG_SSP;
/*SPC(78)*/
_AVDigitizerType_DigUnique=GetDigUnique(_currn->_ATKey, 0);
/*SPC(1259)*/
ResetDigitizer(_currn->_ATKey, _AVDigitizerType_Digitizer);
/*SPC(69)*/

if (NOT(_AVDigitizerType_DigUnique)) {
message(ERROR, "Digitizer is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(66)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_42(_TPPrule_42 _currn)
#else
void _VS1rule_42(_currn )
_TPPrule_42 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetDigUnique(_currn->_ATKey, 1, 0);
/*SPC(1256)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_42(_TPPrule_42 _currn)
#else
void _VS2rule_42(_currn )
_TPPrule_42 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDigitizerType_Digitizer=DIG_CS210;
/*SPC(75)*/
_AVDigitizerType_DigUnique=GetDigUnique(_currn->_ATKey, 0);
/*SPC(1259)*/
ResetDigitizer(_currn->_ATKey, _AVDigitizerType_Digitizer);
/*SPC(69)*/

if (NOT(_AVDigitizerType_DigUnique)) {
message(ERROR, "Digitizer is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(66)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_43(_TPPrule_43 _currn)
#else
void _VS1rule_43(_currn )
_TPPrule_43 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetDigUnique(_currn->_ATKey, 1, 0);
/*SPC(1256)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_43(_TPPrule_43 _currn)
#else
void _VS2rule_43(_currn )
_TPPrule_43 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDigitizerType_Digitizer=DIG_CPCI14;
/*SPC(72)*/
_AVDigitizerType_DigUnique=GetDigUnique(_currn->_ATKey, 0);
/*SPC(1259)*/
ResetDigitizer(_currn->_ATKey, _AVDigitizerType_Digitizer);
/*SPC(69)*/

if (NOT(_AVDigitizerType_DigUnique)) {
message(ERROR, "Digitizer is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(66)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_44(_TPPrule_44 _currn)
#else
void _VS1rule_44(_currn )
_TPPrule_44 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetQCUnique(_currn->_ATKey, 1, 0);
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_44(_TPPrule_44 _currn)
#else
void _VS2rule_44(_currn )
_TPPrule_44 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVQCLIConfigType_QCLIConfig=QCLI_CFG_STANDARDx2P41;
/*SPC(52)*/
_AVQCLIConfigType_QCUnique=GetQCUnique(_currn->_ATKey, 0);
/*SPC(1233)*/
ResetQCLIConfig(_currn->_ATKey, _AVQCLIConfigType_QCLIConfig);
/*SPC(34)*/

if (NOT(_AVQCLIConfigType_QCUnique)) {
message(ERROR, "QCLIConfig is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_45(_TPPrule_45 _currn)
#else
void _VS1rule_45(_currn )
_TPPrule_45 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetQCUnique(_currn->_ATKey, 1, 0);
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_45(_TPPrule_45 _currn)
#else
void _VS2rule_45(_currn )
_TPPrule_45 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVQCLIConfigType_QCLIConfig=QCLI_CFG_FASTRAMPx25;
/*SPC(49)*/
_AVQCLIConfigType_QCUnique=GetQCUnique(_currn->_ATKey, 0);
/*SPC(1233)*/
ResetQCLIConfig(_currn->_ATKey, _AVQCLIConfigType_QCLIConfig);
/*SPC(34)*/

if (NOT(_AVQCLIConfigType_QCUnique)) {
message(ERROR, "QCLIConfig is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_46(_TPPrule_46 _currn)
#else
void _VS1rule_46(_currn )
_TPPrule_46 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetQCUnique(_currn->_ATKey, 1, 0);
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_46(_TPPrule_46 _currn)
#else
void _VS2rule_46(_currn )
_TPPrule_46 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVQCLIConfigType_QCLIConfig=QCLI_CFG_FASTRAMPx10;
/*SPC(46)*/
_AVQCLIConfigType_QCUnique=GetQCUnique(_currn->_ATKey, 0);
/*SPC(1233)*/
ResetQCLIConfig(_currn->_ATKey, _AVQCLIConfigType_QCLIConfig);
/*SPC(34)*/

if (NOT(_AVQCLIConfigType_QCUnique)) {
message(ERROR, "QCLIConfig is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_47(_TPPrule_47 _currn)
#else
void _VS1rule_47(_currn )
_TPPrule_47 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetQCUnique(_currn->_ATKey, 1, 0);
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_47(_TPPrule_47 _currn)
#else
void _VS2rule_47(_currn )
_TPPrule_47 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVQCLIConfigType_QCLIConfig=QCLI_CFG_FASTRAMP;
/*SPC(43)*/
_AVQCLIConfigType_QCUnique=GetQCUnique(_currn->_ATKey, 0);
/*SPC(1233)*/
ResetQCLIConfig(_currn->_ATKey, _AVQCLIConfigType_QCLIConfig);
/*SPC(34)*/

if (NOT(_AVQCLIConfigType_QCUnique)) {
message(ERROR, "QCLIConfig is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_48(_TPPrule_48 _currn)
#else
void _VS1rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetQCUnique(_currn->_ATKey, 1, 0);
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_48(_TPPrule_48 _currn)
#else
void _VS2rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVQCLIConfigType_QCLIConfig=QCLI_CFG_STANDARDxP33;
/*SPC(40)*/
_AVQCLIConfigType_QCUnique=GetQCUnique(_currn->_ATKey, 0);
/*SPC(1233)*/
ResetQCLIConfig(_currn->_ATKey, _AVQCLIConfigType_QCLIConfig);
/*SPC(34)*/

if (NOT(_AVQCLIConfigType_QCUnique)) {
message(ERROR, "QCLIConfig is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_49(_TPPrule_49 _currn)
#else
void _VS1rule_49(_currn )
_TPPrule_49 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetQCUnique(_currn->_ATKey, 1, 0);
/*SPC(1230)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_49(_TPPrule_49 _currn)
#else
void _VS2rule_49(_currn )
_TPPrule_49 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVQCLIConfigType_QCLIConfig=QCLI_CFG_STANDARD;
/*SPC(37)*/
_AVQCLIConfigType_QCUnique=GetQCUnique(_currn->_ATKey, 0);
/*SPC(1233)*/
ResetQCLIConfig(_currn->_ATKey, _AVQCLIConfigType_QCLIConfig);
/*SPC(34)*/

if (NOT(_AVQCLIConfigType_QCUnique)) {
message(ERROR, "QCLIConfig is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(31)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_50(_TPPrule_50 _currn)
#else
void _VS1rule_50(_currn )
_TPPrule_50 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDefIdent_Bind=BindIdn((* _IG_incl14), _currn->_ATSym);
/*SPC(1081)*/
_currn->_ATKey=KeyOf(_AVDefIdent_Bind);
/*SPC(1084)*/
SetUnique(_currn->_ATKey, 1, 0);
/*SPC(1204)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_50(_TPPrule_50 _currn)
#else
void _VS2rule_50(_currn )
_TPPrule_50 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVDefIdent_Unique=GetUnique(_currn->_ATKey, 0);
/*SPC(1207)*/

if (NOT(_AVDefIdent_Unique)) {
message(ERROR, CatStrInd("Waveform is multiply defined: ", _currn->_ATSym), 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(9)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_51(_TPPrule_51 _currn)
#else
void _VS1rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingWave__const9=_currn->_desc1->_ATKey;
/*SPC(6)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_51(_TPPrule_51 _currn)
#else
void _VS2rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_desc2->_ATKey=(* _IG_incl17);
/*SPC(751)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const7=_AVRingCmds__const7;
/*SPC(6)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_51(_TPPrule_51 _currn)
#else
void _VS3rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const6=_AVRingCmds__const6;
/*SPC(6)*/
_currn->_AT_const8=_currn->_desc1->_ATSym;
/*SPC(6)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_51(_TPPrule_51 _currn)
#else
void _VS4rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmds_Iz=(* _IG_incl16);
/*SPC(905)*/
_AVRingCmds_DtoAs=(* _IG_incl18);
/*SPC(743)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVRingWave__const5=_AVRingCmds_ProgLen;
/*SPC(6)*/
_AVRingWave__const24=PTGNumb(_currn->_desc2->_ATRawRate);
/*SPC(6)*/
_AVRingWave__const25=PTGNumb(_AVRingCmds_RawSamples);
/*SPC(6)*/
_AVRingWave__const26=PTGNumb(_AVRingCmds_NetSamples);
/*SPC(6)*/
_AVRingWave__const27=PTGNumb(_AVRingCmds_Naverage);
/*SPC(6)*/
_AVRingWave__const29=PTGNumb(_AVRingCmds_Ftrigger);
/*SPC(6)*/
_AVRingWave__const30=PTGNumb(_AVRingCmds_ISICOS);
/*SPC(6)*/
_AVRingWave__const31=PTGNumb(_AVRingCmds_TzSamples);
/*SPC(6)*/
_AVRingWave__const32=PTGDouble(_AVRingCmds_dIdt);
/*SPC(6)*/
_AVRingWave__const33=PTGDouble(_AVRingCmds_Istart1);
/*SPC(6)*/
_AVRingWave__const34=IDENTICAL(_AVRingCmds_CMDoutput);
/*SPC(6)*/
_AVRingWave__const38=IDENTICAL(_AVRingCmds_PTG);
/*SPC(6)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_52(_TPPrule_52 _currn)
#else
void _VS1rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSWave__const9=_currn->_desc1->_ATKey;
/*SPC(5)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_52(_TPPrule_52 _currn)
#else
void _VS2rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_AT_const6=_AVICOSCmds__const6;
/*SPC(5)*/
_currn->_AT_const7=_AVICOSCmds__const7;
/*SPC(5)*/
_currn->_AT_const8=_currn->_desc1->_ATSym;
/*SPC(5)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_52(_TPPrule_52 _currn)
#else
void _VS3rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmdsWaveAddr_pre=_AVICOSWaveWaveAddr_post;
/*SPC(0)*/
_AVICOSCmds_LoopAddr=(* _IG_incl19);
/*SPC(576)*/
_AVICOSCmds_WaveNum=(* _IG_incl20);
/*SPC(575)*/
_currn->_desc2->_ATDtoAs=(* _IG_incl18);
/*SPC(524)*/
_AVICOSCmds_Iz=(* _IG_incl16);
/*SPC(523)*/
_AVICOSCmds_Key=(* _IG_incl17);
/*SPC(190)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVICOSWave__const5=_AVICOSCmds_ProgLen;
/*SPC(5)*/
_AVICOSWave__const24=PTGNumb(_currn->_desc2->_ATRawRate);
/*SPC(5)*/
_AVICOSWave__const25=PTGNumb(_AVICOSCmds_RawSamples);
/*SPC(5)*/
_AVICOSWave__const26=PTGNumb(_AVICOSCmds_NetSamples);
/*SPC(5)*/
_AVICOSWave__const27=PTGNumb(_currn->_desc2->_ATNaverage);
/*SPC(5)*/
_AVICOSWave__const29=PTGNumb(_AVICOSCmds_Ftrigger);
/*SPC(5)*/
_AVICOSWave__const30=PTGNumb(_AVICOSCmds_ISICOS);
/*SPC(5)*/
_AVICOSWave__const31=PTGNumb(_AVICOSCmds_TzSamples);
/*SPC(5)*/
_AVICOSWave__const32=PTGDouble(_AVICOSCmds_dIdt);
/*SPC(5)*/
_AVICOSWave__const33=PTGDouble(_AVICOSCmds_Istart1);
/*SPC(5)*/
_AVICOSWave__const34=IDENTICAL(_AVICOSCmds_CMDoutput);
/*SPC(5)*/
_AVICOSWave__const36=IDENTICAL(_AVICOSCmds_Summary);
/*SPC(5)*/
_AVICOSWave__const38=IDENTICAL(_AVICOSCmds_PTG);
/*SPC(5)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_062(_TPPrule_062 _currn)
#else
void _VS1rule_062(_currn )
_TPPrule_062 _currn;

#endif
{
WaveDtoAP* _IL_incl18;
DefTableKey* _IL_incl17;

_VisitVarDecl()
_VisitEntry();
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATDtoAs);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATKey=_AVRingWave__const9;
/*SPC(15)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATDtoAs=new_wavedtoa();
/*SPC(518)*/
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_062(_TPPrule_062 _currn)
#else
void _VS2rule_062(_currn )
_TPPrule_062 _currn;

#endif
{
WaveDtoAP* _IL_incl18;
DefTableKey* _IL_incl17;
int* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATDtoAs);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATKey);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATNcoadd);
_AVWave_Ncoadd_specd=_currn->_desc1->_AT_const7;
/*SPC(262)*/
_currn->_ATNcoadd=
((GT(_AVWave_Ncoadd_specd, 1)
) ? (_AVWave_Ncoadd_specd
) : (1))
;
/*SPC(264)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_062(_TPPrule_062 _currn)
#else
void _VS3rule_062(_currn )
_TPPrule_062 _currn;

#endif
{
PTGNode* _IL_incl26;
int* _IL_incl20;
long* _IL_incl19;
WaveDtoAP* _IL_incl18;
double* _IL_incl16;
DefTableKey* _IL_incl17;
int* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl26=_IG_incl26;_IG_incl26= &(_currn->_ATWaveName);
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWaveNum);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATLoopAddr);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATDtoAs);
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATIz);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATKey);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATNcoadd);
_currn->_ATLoopAddr=ADD(_AVG1WaveAddr_post, 10);
/*SPC(569)*/
_currn->_ATWaveNum=_AVWaveWaveCnt_post;
/*SPC(567)*/
_currn->_ATIz=_currn->_desc1->_AT_const6;
/*SPC(519)*/
_AVWave_Sym=_currn->_desc1->_AT_const8;
/*SPC(16)*/
_currn->_ATWaveName=PTGId(_AVWave_Sym);
/*SPC(598)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVWave__const24=_AVRingWave__const24;
/*SPC(1689)*/
_AVWave__const25=_AVRingWave__const25;
/*SPC(1689)*/
_AVWave__const26=_AVRingWave__const26;
/*SPC(1689)*/
_AVWave__const27=_AVRingWave__const27;
/*SPC(1689)*/
_AVWave__const29=_AVRingWave__const29;
/*SPC(1689)*/
_AVWave__const30=_AVRingWave__const30;
/*SPC(1689)*/
_AVWave__const31=_AVRingWave__const31;
/*SPC(1689)*/
_AVWave__const32=_AVRingWave__const32;
/*SPC(1689)*/
_AVWave__const33=_AVRingWave__const33;
/*SPC(1689)*/
_AVWave__const34=_AVRingWave__const34;
/*SPC(1689)*/
_AVWave__const36=PTGNull();
/*SPC(1689)*/
_AVWave__const38=_AVRingWave__const38;
/*SPC(1689)*/
_AVWaveWaveCnt_post=ADD(_AVWaveWaveCnt_post, 1);
/*SPC(568)*/
_AVWave_DISPoutput=PTGWaveName(StringTable(_AVWave_Sym));
/*SPC(1039)*/
_AVWave_CMDoutput=PTGWaveCmd(_currn->_ATWaveName, _currn->_ATWaveNum);
/*SPC(964)*/
_AVWave_WaveIndex=PTGWaveIndex(_currn->_ATWaveName, PTGHex(_AVG1WaveAddr_post, 1));
/*SPC(599)*/
_AVWave_ProgLen=_AVRingWave__const5;
/*SPC(570)*/
_AVG1WaveAddr_post=ADD(_currn->_ATLoopAddr, _AVWave_ProgLen);
/*SPC(572)*/
_IG_incl26=_IL_incl26;
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl16=_IL_incl16;
_IG_incl17=_IL_incl17;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_061(_TPPrule_061 _currn)
#else
void _VS1rule_061(_currn )
_TPPrule_061 _currn;

#endif
{
WaveDtoAP* _IL_incl18;
DefTableKey* _IL_incl17;

_VisitVarDecl()
_VisitEntry();
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATDtoAs);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATDtoAs=new_wavedtoa();
/*SPC(518)*/
_currn->_ATKey=_AVICOSWave__const9;
/*SPC(15)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_061(_TPPrule_061 _currn)
#else
void _VS2rule_061(_currn )
_TPPrule_061 _currn;

#endif
{
WaveDtoAP* _IL_incl18;
DefTableKey* _IL_incl17;
int* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATDtoAs);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATKey);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATNcoadd);
_AVWave_Ncoadd_specd=_currn->_desc1->_AT_const7;
/*SPC(262)*/
_currn->_ATNcoadd=
((GT(_AVWave_Ncoadd_specd, 1)
) ? (_AVWave_Ncoadd_specd
) : (1))
;
/*SPC(264)*/
_IG_incl18=_IL_incl18;
_IG_incl17=_IL_incl17;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_061(_TPPrule_061 _currn)
#else
void _VS3rule_061(_currn )
_TPPrule_061 _currn;

#endif
{
PTGNode* _IL_incl26;
int* _IL_incl20;
long* _IL_incl19;
WaveDtoAP* _IL_incl18;
double* _IL_incl16;
DefTableKey* _IL_incl17;
int* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl26=_IG_incl26;_IG_incl26= &(_currn->_ATWaveName);
_IL_incl20=_IG_incl20;_IG_incl20= &(_currn->_ATWaveNum);
_IL_incl19=_IG_incl19;_IG_incl19= &(_currn->_ATLoopAddr);
_IL_incl18=_IG_incl18;_IG_incl18= &(_currn->_ATDtoAs);
_IL_incl16=_IG_incl16;_IG_incl16= &(_currn->_ATIz);
_IL_incl17=_IG_incl17;_IG_incl17= &(_currn->_ATKey);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATNcoadd);
_currn->_ATLoopAddr=ADD(_AVG1WaveAddr_post, 10);
/*SPC(569)*/
_currn->_ATWaveNum=_AVWaveWaveCnt_post;
/*SPC(567)*/
_currn->_ATIz=_currn->_desc1->_AT_const6;
/*SPC(519)*/
_AVWave_Sym=_currn->_desc1->_AT_const8;
/*SPC(16)*/
_AVICOSWaveWaveAddr_post=_AVG1WaveAddr_post;
/*SPC(0)*/
_currn->_ATWaveName=PTGId(_AVWave_Sym);
/*SPC(598)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVWave__const24=_AVICOSWave__const24;
/*SPC(1685)*/
_AVWave__const25=_AVICOSWave__const25;
/*SPC(1685)*/
_AVWave__const26=_AVICOSWave__const26;
/*SPC(1685)*/
_AVWave__const27=_AVICOSWave__const27;
/*SPC(1685)*/
_AVWave__const29=_AVICOSWave__const29;
/*SPC(1685)*/
_AVWave__const30=_AVICOSWave__const30;
/*SPC(1685)*/
_AVWave__const31=_AVICOSWave__const31;
/*SPC(1685)*/
_AVWave__const32=_AVICOSWave__const32;
/*SPC(1685)*/
_AVWave__const33=_AVICOSWave__const33;
/*SPC(1685)*/
_AVWave__const34=_AVICOSWave__const34;
/*SPC(1685)*/
_AVWave__const36=_AVICOSWave__const36;
/*SPC(1685)*/
_AVWave__const38=_AVICOSWave__const38;
/*SPC(1685)*/
_AVWaveWaveCnt_post=ADD(_AVWaveWaveCnt_post, 1);
/*SPC(568)*/
_AVWave_DISPoutput=PTGWaveName(StringTable(_AVWave_Sym));
/*SPC(1039)*/
_AVWave_CMDoutput=PTGWaveCmd(_currn->_ATWaveName, _currn->_ATWaveNum);
/*SPC(964)*/
_AVWave_WaveIndex=PTGWaveIndex(_currn->_ATWaveName, PTGHex(_AVG1WaveAddr_post, 1));
/*SPC(599)*/
_AVWave_ProgLen=_AVICOSWave__const5;
/*SPC(570)*/
_AVG1WaveAddr_post=ADD(_currn->_ATLoopAddr, _AVWave_ProgLen);
/*SPC(572)*/
_IG_incl26=_IL_incl26;
_IG_incl20=_IL_incl20;
_IG_incl19=_IL_incl19;
_IG_incl18=_IL_incl18;
_IG_incl16=_IL_incl16;
_IG_incl17=_IL_incl17;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_060(_TPPrule_060 _currn)
#else
void _VS1rule_060(_currn )
_TPPrule_060 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATrcnt_pre=_AVTzDefrcnt_post;
/*SPC(0)*/
_AVTzSpec_RawRate=(* _IG_incl21);
/*SPC(320)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_060(_TPPrule_060 _currn)
#else
void _VS2rule_060(_currn )
_TPPrule_060 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_AT_const70=IDENTICAL(_currn->_desc1->_ATTz);
/*SPC(1681)*/
SetTzUnique(_currn->_ATKey, 1, 0);
/*SPC(1334)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_060(_TPPrule_060 _currn)
#else
void _VS3rule_060(_currn )
_TPPrule_060 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTzDef__const66=_currn->_desc1->_AT_const66;
/*SPC(1681)*/
_AVTzDef_TzUnique=GetTzUnique(_currn->_ATKey, 0);
/*SPC(1337)*/

if (NOT(_AVTzDef_TzUnique)) {
message(ERROR, "Tz is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(106)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_059(_TPPrule_059 _currn)
#else
void _VS1rule_059(_currn )
_TPPrule_059 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTpreVal_RawRate=(* _IG_incl23);
/*SPC(855)*/
_AVTpreVal_Key=(* _IG_incl17);
/*SPC(854)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (HasTpre(_AVTpreDef_Key)) {
message(ERROR, "Only one definition of Tpre is allowed per waveform", 0, (&( _currn->_AT_pos)));

} else {
ResetTpre(_AVTpreDef_Key, _AVTpreVal_Value);
}
;
/*SPC(847)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_058(_TPPrule_058 _currn)
#else
void _VS1rule_058(_currn )
_TPPrule_058 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTonVal_ToffD=(* _IG_incl24);
/*SPC(829)*/
_AVTonVal_Key=(* _IG_incl17);
/*SPC(828)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (HasTon(_AVTonDef_Key)) {
message(ERROR, "Only one definition of Ton is allowed per waveform", 0, (&( _currn->_AT_pos)));

} else {
ResetTon(_AVTonDef_Key, _AVTonVal_Value);
}
;
/*SPC(821)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_057(_TPPrule_057 _currn)
#else
void _VS1rule_057(_currn )
_TPPrule_057 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (HasToff(_AVToffDef_Key)) {
message(ERROR, "Only one definition of Toff is allowed per waveform", 0, (&( _currn->_AT_pos)));

} else {
ResetToff(_AVToffDef_Key, _AVTime_Value);
}
;
/*SPC(812)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_056(_TPPrule_056 _currn)
#else
void _VS1rule_056(_currn )
_TPPrule_056 _currn;

#endif
{
DefTableKey* _IL_incl27;
int* _IL_incl25;
Environment* _IL_incl14;
int* _IL_incl6;
int* _IL_incl2;

_VisitVarDecl()
_VisitEntry();
_IL_incl27=_IG_incl27;_IG_incl27= &(_currn->_ATKey);
_IL_incl25=_IG_incl25;_IG_incl25= &(_currn->_ATPrefix);
_IL_incl14=_IG_incl14;_IG_incl14= &(_currn->_ATEnv);
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATDigitizer);
_IL_incl2=_IG_incl2;_IG_incl2= &(_currn->_ATQCLIConfig);
_currn->_ATKey=NewKey();
/*SPC(25)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVSourceFile_ICOSRampInitCount=0;
/*SPC(1434)*/
_currn->_ATEnv=RootEnv;
/*SPC(1053)*/
_AVICOSCmd_cICOSRampCount_post=_AVSourceFile_ICOSRampInitCount;
/*SPC(1435)*/
_AVWaveWaveCnt_post=0;
/*SPC(563)*/
_AVG1WaveAddr_post=128;
/*SPC(561)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATDigitizer=GetDigitizer(_currn->_ATKey, DIG_CPCI14);
/*SPC(61)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATQCLIConfig=GetQCLIConfig(_currn->_ATKey, QCLI_CFG_STANDARD);
/*SPC(26)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATPrefix=GetPrefix(_currn->_ATKey, stostr("QCLI", 4));
/*SPC(87)*/
_AVICOSCmd_cICOSRampCount_post=_AVConfigCmds_cICOSRampCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVSourceFile_ICOSRampCountResult=_AVICOSCmd_cICOSRampCount_post;
/*SPC(1436)*/
_AVSourceFile_Moutput=PTGMFile(_AVG1__const23, _AVG1__const24, _AVG1__const25, _AVG1__const26, _AVG1__const27, _AVG1__const28, _AVG1__const29, _AVG1__const30, _AVG1__const31, _AVG1__const32, _AVG1__const33);
/*SPC(997)*/
_AVSourceFile_Summary=PTGFileSum(_AVG1__const36);
/*SPC(650)*/
_AVSourceFile_NWaves=_AVWaveWaveCnt_post;
/*SPC(564)*/
_AVSourceFile_ProgLen=_AVG1WaveAddr_post;
/*SPC(562)*/
_AVSourceFile_DISPoutput=PTGWaveNames(_AVG1__const22, _AVSourceFile_NWaves, StringTable(_currn->_ATPrefix));
/*SPC(1030)*/
_AVSourceFile_CMDoutput=PTGCmdCode(_AVG1__const34, _AVG1__const35, StringTable(_currn->_ATPrefix), _AVSourceFile_NWaves);
/*SPC(953)*/
_AVSourceFile_PTG=PTGFile(PTGHeader(PTGHex(_AVSourceFile_ProgLen, 1), PTGHex(0, 5)), _AVG1__const37, PTGFill(0, SUB(120, _AVSourceFile_NWaves)), _AVG1__const38, _AVSourceFile_ProgLen);
/*SPC(584)*/

if (NE(OutFile, NoKey)) {
PTGOutFile(StringTable(GetClpValue(OutFile, 0)), _AVSourceFile_PTG);

} else {
PTGOut(_AVSourceFile_PTG);
}
;
/*SPC(593)*/

if (NE(VerbFile, NoKey)) {
PTGOutFile(StringTable(GetClpValue(VerbFile, 0)), _AVSourceFile_Summary);

} else {
}
;
/*SPC(653)*/

if (NE(CmdFile, NoKey)) {
PTGOutFile(StringTable(GetClpValue(CmdFile, 0)), _AVSourceFile_CMDoutput);

} else {
}
;
/*SPC(960)*/

if (NE(MFile, NoKey)) {
PTGOutFile(StringTable(GetClpValue(MFile, 0)), _AVSourceFile_Moutput);

} else {
}
;
/*SPC(1021)*/

if (NE(DispFile, NoKey)) {
PTGOutFile(StringTable(GetClpValue(DispFile, 0)), _AVSourceFile_DISPoutput);

} else {
}
;
/*SPC(1035)*/
_IG_incl27=_IL_incl27;
_IG_incl25=_IL_incl25;
_IG_incl14=_IL_incl14;
_IG_incl6=_IL_incl6;
_IG_incl2=_IL_incl2;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_055(_TPPrule_055 _currn)
#else
void _VS1rule_055(_currn )
_TPPrule_055 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingStep_Istep=_AVRingStepsize_Istep;
/*SPC(883)*/
_AVRingStep_ProgLen=_AVRingStepsize_ProgLen;
/*SPC(885)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_054(_TPPrule_054 _currn)
#else
void _VS1rule_054(_currn )
_TPPrule_054 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingStep_Istep=_AVRingCount_Istep;
/*SPC(883)*/
_AVRingStep_ProgLen=_AVRingCount_ProgLen;
/*SPC(885)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_053(_TPPrule_053 _currn)
#else
void _VS1rule_053(_currn )
_TPPrule_053 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingRateDef_RateDef=_AVRateDef_RateDef;
/*SPC(791)*/

if (HasRateDef(_AVRingRateDef_Key)) {
message(ERROR, "Only one definition of SampleRate is allowed per waveform", 0, (&( _currn->_AT_pos)));

} else {
ResetRateDef(_AVRingRateDef_Key, _AVRingRateDef_RateDef);
}
;
/*SPC(792)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_052(_TPPrule_052 _currn)
#else
void _VS1rule_052(_currn )
_TPPrule_052 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (HasNsample(_AVRingNsampleDef_Key)) {
message(ERROR, "Only one definition of Nsample is allowed per waveform", 0, (&( _currn->_AT_pos)));

} else {
ResetNsample(_AVRingNsampleDef_Key, _AVNsampleDef_Nsample);
}
;
/*SPC(804)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_051(_TPPrule_051 _currn)
#else
void _VS1rule_051(_currn )
_TPPrule_051 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingData__const54=IDENTICAL(_AVRingCurrent_PTG);
/*SPC(1645)*/
_AVRingData_NetSamples=_AVRingCurrent_NetSamples;
/*SPC(864)*/
_AVRingData_ProgLen=_AVRingCurrent_ProgLen;
/*SPC(862)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_050(_TPPrule_050 _currn)
#else
void _VS1rule_050(_currn )
_TPPrule_050 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingData__const54=IDENTICAL(_AVCurrentSteps_PTG);
/*SPC(1641)*/
_AVRingData_NetSamples=_AVCurrentSteps_NetSamples;
/*SPC(864)*/
_AVRingData_ProgLen=_AVCurrentSteps_ProgLen;
/*SPC(862)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_049(_TPPrule_049 _currn)
#else
void _VS1rule_049(_currn )
_TPPrule_049 _currn;

#endif
{
double _AS1Value;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Value)));
_AVRingCurrent_Value=_AS1Value;
/*SPC(870)*/
_AVRingCurrent_NetSamples=1;
/*SPC(869)*/
_AVRingCurrent_ProgLen=1;
/*SPC(868)*/
_AVRingCurrent_PTG=RingdownPTG(_AVRingCurrent_Value, _AVRingCurrent_Value, 0, 1, (* _IG_incl1), (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(929)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_048(_TPPrule_048 _currn)
#else
void _VS1rule_048(_currn )
_TPPrule_048 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_048(_TPPrule_048 _currn)
#else
void _VS2rule_048(_currn )
_TPPrule_048 _currn;

#endif
{
double* _IL_incl23;

_VisitVarDecl()
_VisitEntry();
_IL_incl23=_IG_incl23;_IG_incl23= &(_currn->_ATRawRate);

if (NOT(HasRateDef(_currn->_ATKey))) {
message(ERROR, "SampleRate is required", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(755)*/

if (NOT(OR(HasNsample(_currn->_ATKey), HasToff(_currn->_ATKey)))) {
message(ERROR, "Must specify either Toff or Nsample", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(752)*/
_currn->_ATRawRate=
((HasRateDef(_currn->_ATKey)
) ? (PTRSELECT(GetRateDef(_currn->_ATKey, 0), samples)
) : (10000000.))
;
/*SPC(769)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmds__const7=_AVG4__const7;
/*SPC(1633)*/
_IG_incl23=_IL_incl23;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_048(_TPPrule_048 _currn)
#else
void _VS3rule_048(_currn )
_TPPrule_048 _currn;

#endif
{
double* _IL_incl24;
double* _IL_incl23;

_VisitVarDecl()
_VisitEntry();
_IL_incl24=_IG_incl24;_IG_incl24= &(_currn->_ATToffD);
_IL_incl23=_IG_incl23;_IG_incl23= &(_currn->_ATRawRate);
_AVRingCmds_TpreSpec=usecs(GetTpre(_currn->_ATKey, .000001));
/*SPC(766)*/
_currn->_ATTpre=
((GT(_AVRingCmds_TpreSpec, 1)
) ? (_AVRingCmds_TpreSpec
) : (1))
;
/*SPC(768)*/
_currn->_ATNsample=GetNsample(_currn->_ATKey, MUL(_currn->_ATRawRate, ADD(DIV(_currn->_ATTpre, 1000000.), GetToff(_currn->_ATKey, 0))));
/*SPC(777)*/
_currn->_ATToffD=GetToff(_currn->_ATKey, DIV(_currn->_ATNsample, _currn->_ATRawRate));
/*SPC(783)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

if (NOT(HasTon(_currn->_ATKey))) {
message(ERROR, "Ton is required", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(758)*/
_AVRingCmds__const6=_AVG4__const6;
/*SPC(1633)*/
_IG_incl24=_IL_incl24;
_IG_incl23=_IL_incl23;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_048(_TPPrule_048 _currn)
#else
void _VS4rule_048(_currn )
_TPPrule_048 _currn;

#endif
{
double* _IL_incl24;
double* _IL_incl23;

_VisitVarDecl()
_VisitEntry();
_IL_incl24=_IG_incl24;_IG_incl24= &(_currn->_ATToffD);
_IL_incl23=_IG_incl23;_IG_incl23= &(_currn->_ATRawRate);
_AVRingCmds_Istart1=NEG(1.);
/*SPC(988)*/
_AVRingCmds_dIdt=0.;
/*SPC(987)*/
_AVRingCmds_ISICOS=0;
/*SPC(975)*/
_AVRingCmds_TzSamples=DIV_UP(MUL(_currn->_ATTpre, _currn->_ATRawRate), 1000000);
/*SPC(787)*/
_AVRingCmds_Toff=usecs(_currn->_ATToffD);
/*SPC(784)*/
_AVRingCmds_Naverage=
((HasRateDef(_currn->_ATKey)
) ? (PTRSELECT(GetRateDef(_currn->_ATKey, 0), naverage)
) : (1))
;
/*SPC(773)*/
_AVRingCmds_Ton=usecs(GetTon(_currn->_ATKey, 0.));
/*SPC(761)*/
_AVRingCmds_NetSamples=_currn->_desc1->_AT_const53;
/*SPC(746)*/
_AVRingCmds_ProgLen=_currn->_desc1->_AT_const55;
/*SPC(744)*/
_AVRingCmds_Ttrigger=ADD(_AVRingCmds_Ton, _AVRingCmds_Toff);
/*SPC(785)*/
_AVRingCmds_RawSamples=MUL(_currn->_ATNsample, _AVRingCmds_Naverage);
/*SPC(782)*/
_AVRingCmds_PTG=PTGSeq(PTGRingHdr((* _IG_incl20), (* _IG_incl26), PTGHex(RINGDOWN_WAVEFORM_CODE, 1), PTGHex(SUB(_AVRingCmds_Ton, 1), 1), PTGHex(SUB(_AVRingCmds_Toff, 1), 1), PTGHex(_currn->_ATTpre, 1), PTGHex((* _IG_incl19), 1), PTGHex(_AVRingCmds_ProgLen, 1), PTGDACs(0, 0., 0, 0., amps_to_bits(_AVRingCmds_Iz, (* _IG_incl2), (&( _currn->_AT_pos))), _AVRingCmds_Iz, dtoa_bits(_AVRingCmds_DtoAs, 3), dtoa_value(_AVRingCmds_DtoAs, 3))), _currn->_desc1->_AT_const54);
/*SPC(906)*/
_AVRingCmds_Ftrigger=DIV_UP(1000000, _AVRingCmds_Ttrigger);
/*SPC(786)*/
_AVRingCmds_CMDoutput=PTGCPCIdef(_currn->_ATRawRate, _AVRingCmds_RawSamples, _AVRingCmds_NetSamples, _AVRingCmds_Naverage, (* _IG_incl1), _AVRingCmds_Ftrigger, "RINGDOWN", _AVRingCmds_TzSamples, StringTable((* _IG_incl25)));
/*SPC(976)*/
_IG_incl24=_IL_incl24;
_IG_incl23=_IL_incl23;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_047(_TPPrule_047 _currn)
#else
void _VS2rule_047(_currn )
_TPPrule_047 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTpreDef_Key=(* _IG_incl17);
/*SPC(846)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmd__const7=ZERO();
/*SPC(1629)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_047(_TPPrule_047 _currn)
#else
void _VS3rule_047(_currn )
_TPPrule_047 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const6=ZERO();
/*SPC(1629)*/
_AVRingCmd__const53=ZERO();
/*SPC(1629)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1629)*/
_AVRingCmd__const55=ZERO();
/*SPC(1629)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_046(_TPPrule_046 _currn)
#else
void _VS2rule_046(_currn )
_TPPrule_046 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=ZERO();
/*SPC(1625)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_046(_TPPrule_046 _currn)
#else
void _VS3rule_046(_currn )
_TPPrule_046 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVTonDef_Key=(* _IG_incl17);
/*SPC(820)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmd__const6=ZERO();
/*SPC(1625)*/
_AVRingCmd__const53=ZERO();
/*SPC(1625)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1625)*/
_AVRingCmd__const55=ZERO();
/*SPC(1625)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_045(_TPPrule_045 _currn)
#else
void _VS1rule_045(_currn )
_TPPrule_045 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVToffDef_Key=(* _IG_incl17);
/*SPC(811)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_045(_TPPrule_045 _currn)
#else
void _VS2rule_045(_currn )
_TPPrule_045 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=ZERO();
/*SPC(1621)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_045(_TPPrule_045 _currn)
#else
void _VS3rule_045(_currn )
_TPPrule_045 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const6=ZERO();
/*SPC(1621)*/
_AVRingCmd__const53=ZERO();
/*SPC(1621)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1621)*/
_AVRingCmd__const55=ZERO();
/*SPC(1621)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_044(_TPPrule_044 _currn)
#else
void _VS1rule_044(_currn )
_TPPrule_044 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingRateDef_Key=(* _IG_incl17);
/*SPC(790)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_044(_TPPrule_044 _currn)
#else
void _VS2rule_044(_currn )
_TPPrule_044 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=ZERO();
/*SPC(1617)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_044(_TPPrule_044 _currn)
#else
void _VS3rule_044(_currn )
_TPPrule_044 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const6=ZERO();
/*SPC(1617)*/
_AVRingCmd__const53=ZERO();
/*SPC(1617)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1617)*/
_AVRingCmd__const55=ZERO();
/*SPC(1617)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_043(_TPPrule_043 _currn)
#else
void _VS1rule_043(_currn )
_TPPrule_043 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingNsampleDef_Key=(* _IG_incl17);
/*SPC(803)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_043(_TPPrule_043 _currn)
#else
void _VS2rule_043(_currn )
_TPPrule_043 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=ZERO();
/*SPC(1613)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_043(_TPPrule_043 _currn)
#else
void _VS3rule_043(_currn )
_TPPrule_043 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const6=ZERO();
/*SPC(1613)*/
_AVRingCmd__const53=ZERO();
/*SPC(1613)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1613)*/
_AVRingCmd__const55=ZERO();
/*SPC(1613)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_042(_TPPrule_042 _currn)
#else
void _VS2rule_042(_currn )
_TPPrule_042 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=ZERO();
/*SPC(1609)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_042(_TPPrule_042 _currn)
#else
void _VS3rule_042(_currn )
_TPPrule_042 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmd__const6=ZERO();
/*SPC(1609)*/
_AVRingCmd__const53=IDENTICAL(_AVRingData_NetSamples);
/*SPC(1609)*/
_AVRingCmd__const54=_AVRingData__const54;
/*SPC(1609)*/
_AVRingCmd__const55=IDENTICAL(_AVRingData_ProgLen);
/*SPC(1609)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_041(_TPPrule_041 _currn)
#else
void _VS1rule_041(_currn )
_TPPrule_041 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(123)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_041(_TPPrule_041 _currn)
#else
void _VS2rule_041(_currn )
_TPPrule_041 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=IDENTICAL(_currn->_desc1->_ATNcoadd);
/*SPC(1605)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_041(_TPPrule_041 _currn)
#else
void _VS3rule_041(_currn )
_TPPrule_041 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmd__const6=ZERO();
/*SPC(1605)*/
_AVRingCmd__const53=ZERO();
/*SPC(1605)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1605)*/
_AVRingCmd__const55=ZERO();
/*SPC(1605)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_040(_TPPrule_040 _currn)
#else
void _VS1rule_040(_currn )
_TPPrule_040 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(114)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_040(_TPPrule_040 _currn)
#else
void _VS2rule_040(_currn )
_TPPrule_040 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=ZERO();
/*SPC(1601)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_040(_TPPrule_040 _currn)
#else
void _VS3rule_040(_currn )
_TPPrule_040 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmd__const6=IDENTICAL(_currn->_desc1->_ATIz);
/*SPC(1601)*/
_AVRingCmd__const53=ZERO();
/*SPC(1601)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1601)*/
_AVRingCmd__const55=ZERO();
/*SPC(1601)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_039(_TPPrule_039 _currn)
#else
void _VS1rule_039(_currn )
_TPPrule_039 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_039(_TPPrule_039 _currn)
#else
void _VS2rule_039(_currn )
_TPPrule_039 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVRingCmd__const7=ZERO();
/*SPC(1597)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_039(_TPPrule_039 _currn)
#else
void _VS3rule_039(_currn )
_TPPrule_039 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVRingCmd__const6=ZERO();
/*SPC(1597)*/
_AVRingCmd__const53=ZERO();
/*SPC(1597)*/
_AVRingCmd__const54=PTGNull();
/*SPC(1597)*/
_AVRingCmd__const55=ZERO();
/*SPC(1597)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_038(_TPPrule_038 _currn)
#else
void _VS1rule_038(_currn )
_TPPrule_038 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl27);
/*SPC(30)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_038(_TPPrule_038 _currn)
#else
void _VS2rule_038(_currn )
_TPPrule_038 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_037(_TPPrule_037 _currn)
#else
void _VS1rule_037(_currn )
_TPPrule_037 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATValue=_AVTime_Value;
/*SPC(168)*/
_currn->_ATSummary=PTGSpecd(PTGTime(MUL(_currn->_ATValue, 1000.)));
/*SPC(719)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_036(_TPPrule_036 _currn)
#else
void _VS1rule_036(_currn )
_TPPrule_036 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATValue=_AVTime_Value;
/*SPC(168)*/
_currn->_ATSummary=PTGSpecd(PTGTime(MUL(_currn->_ATValue, 1000.)));
/*SPC(719)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_035(_TPPrule_035 _currn)
#else
void _VS1rule_035(_currn )
_TPPrule_035 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPercent_Value=DIV(_currn->_desc1->_ATValue, 100.);
/*SPC(164)*/
_currn->_ATSummary=PTGSpecd(PTGPercent(MUL(_AVPercent_Value, 100.)));
/*SPC(733)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_028(_TPPrule_028 _currn)
#else
void _VS1rule_028(_currn )
_TPPrule_028 _currn;

#endif
{
double _AS1Value;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Value)));
SetIzUnique(_currn->_ATKey, 1, 0);
/*SPC(1308)*/
_currn->_ATIz=_AS1Value;
/*SPC(515)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_028(_TPPrule_028 _currn)
#else
void _VS2rule_028(_currn )
_TPPrule_028 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVIzDef_IzUnique=GetIzUnique(_currn->_ATKey, 0);
/*SPC(1311)*/

if (NOT(_AVIzDef_IzUnique)) {
message(ERROR, "Iz is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(115)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_027(_TPPrule_027 _currn)
#else
void _VS1rule_027(_currn )
_TPPrule_027 _currn;

#endif
{
double _AS1Value;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Value)));
_currn->_ATValue=_AS1Value;
/*SPC(167)*/
_currn->_ATSummary=PTGSpecd(PTGCurrent(MUL(_currn->_ATValue, 1000.)));
/*SPC(716)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_026(_TPPrule_026 _currn)
#else
void _VS1rule_026(_currn )
_TPPrule_026 _currn;

#endif
{
double _AS1Value;

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR ,double*)) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1,(&( _AS1Value)));
_currn->_ATValue=_AS1Value;
/*SPC(166)*/
_currn->_ATSummary=PTGSpecd(PTGCurrent(MUL(_currn->_ATValue, 1000.)));
/*SPC(713)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_025(_TPPrule_025 _currn)
#else
void _VS1rule_025(_currn )
_TPPrule_025 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSRateDef__const71=IDENTICAL(_AVRateDef_RateDef);
/*SPC(1541)*/
SetSampleUnique(_currn->_ATKey, 1, 0);
/*SPC(1386)*/

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
_AVICOSRateDef__const63=IDENTICAL(_currn->_desc1->_ATSummary);
/*SPC(1541)*/
_AVICOSRateDef_SampleUnique=GetSampleUnique(_currn->_ATKey, 0);
/*SPC(1389)*/

if (NOT(_AVICOSRateDef_SampleUnique)) {
message(ERROR, "Only one definition of Nsample or SampleRate is allowed", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(135)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_024(_TPPrule_024 _currn)
#else
void _VS1rule_024(_currn )
_TPPrule_024 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetSampleUnique(_currn->_ATKey, 1, 0);
/*SPC(1386)*/
_AVICOSNsampleDef_Nsample=_AVNsampleDef_Nsample;
/*SPC(289)*/
_AVICOSNsampleDef_RateDef=NewRateDefPtr(
((GT(_AVICOSNsampleDef_Tramps, 0)
) ? (DIV(_AVICOSNsampleDef_Nsample, _AVICOSNsampleDef_Tramps)
) : (_AVICOSNsampleDef_Nsample))
, 1, 0, (* _IG_incl6), (&( _currn->_AT_pos)));
/*SPC(292)*/

if (AND(EQ(_AVICOSNsampleDef_Tramps, 0), GT(_AVICOSNsampleDef_Nsample, 0))) {
message(ERROR, "Cannot specify Nsample on waveform with no ramp", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(290)*/

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
_AVICOSNsampleDef__const64=IDENTICAL(_currn->_desc1->_ATSummary);
/*SPC(1537)*/
_AVICOSNsampleDef_SampleUnique=GetSampleUnique(_currn->_ATKey, 0);
/*SPC(1389)*/

if (NOT(_AVICOSNsampleDef_SampleUnique)) {
message(ERROR, "Only one definition of Nsample or SampleRate is allowed", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(135)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_023(_TPPrule_023 _currn)
#else
void _VS1rule_023(_currn )
_TPPrule_023 _currn;

#endif
{
double* _IL_incl21;
long* _IL_incl9;
double* _IL_incl5;
int* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATRawRate);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATStepsize);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATTramps);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATNaverage);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATTramps=_AVG3__const72;
/*SPC(268)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmds_RateDef=_AVG3__const71;
/*SPC(307)*/
_AVTzDefrcnt_post=0;
/*SPC(364)*/
_currn->_ATNaverage=PTRSELECT(_AVICOSCmds_RateDef, naverage);
/*SPC(311)*/
_currn->_ATRawRate=PTRSELECT(_AVICOSCmds_RateDef, samples);
/*SPC(310)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTzDefrvals_post=malloc(MUL(sizeof(long), _currn->_desc1->_ATrcnt_post));
/*SPC(365)*/
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmds_ICOSRampInitCount=0;
/*SPC(1434)*/
_currn->_ATStepsize=PickRes(_currn->_desc1->_ATrcnt_post, _AVTzDefrvals_post);
/*SPC(366)*/
_AVICOSCmd_cICOSRampCount_post=_AVICOSCmds_ICOSRampInitCount;
/*SPC(1435)*/
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmds__const6=_AVG3__const6;
/*SPC(1533)*/
_AVICOSCmds__const7=_AVG3__const7;
/*SPC(1533)*/
_IG_incl21=_IL_incl21;
_IG_incl9=_IL_incl9;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_023(_TPPrule_023 _currn)
#else
void _VS2rule_023(_currn )
_TPPrule_023 _currn;

#endif
{
int* _IL_incl34;
int* _IL_incl33;
long* _IL_incl32;
WaveDtoAP* _IL_incl31;
double* _IL_incl21;
int* _IL_incl8;
long* _IL_incl9;
double* _IL_incl5;
int* _IL_incl4;

_VisitVarDecl()
_VisitEntry();
_IL_incl34=_IG_incl34;_IG_incl34= &(_currn->_ATSplitCycle);
_IL_incl33=_IG_incl33;_IG_incl33= &(_currn->_ATSplitFactor);
_IL_incl32=_IG_incl32;_IG_incl32= &(_currn->_ATSSzi);
_IL_incl31=_IG_incl31;_IG_incl31= &(_currn->_ATDtoAs);
_IL_incl21=_IG_incl21;_IG_incl21= &(_currn->_ATRawRate);
_IL_incl8=_IG_incl8;_IG_incl8= &(_currn->_ATICOSRampCountResult);
_IL_incl9=_IG_incl9;_IG_incl9= &(_currn->_ATStepsize);
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATTramps);
_IL_incl4=_IG_incl4;_IG_incl4= &(_currn->_ATNaverage);

if (EQ(GetdIdtDefined(_AVICOSCmds_Key, 0), 0)) {
message(ERROR, "dI/dt undefined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(192)*/
_AVICOSCmds_DtoA=alloc_dtoa(_currn->_ATDtoAs, _AVICOSCmds_Iz, (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(525)*/
_currn->_ATICOSRampCountResult=_currn->_desc1->_AT_cICOSRampCount_post;
/*SPC(1436)*/
_AVICOSCmds_Tz=_currn->_desc1->_AT_const70;
/*SPC(353)*/
_AVICOSCmdCrntI_post=_AVICOSCmds_Iz;
/*SPC(528)*/
_AVICOSCmds_Szi=DIV_UP(usecs(_AVICOSCmds_Tz), _currn->_ATStepsize);
/*SPC(397)*/
_AVICOSCmds_Scyc0=ADD(MUL(2, _AVICOSCmds_Szi), _currn->_desc1->_AT_const69);
/*SPC(399)*/
_AVICOSCmds_Tcyc0=MUL(_AVICOSCmds_Scyc0, _currn->_ATStepsize);
/*SPC(402)*/
_AVICOSCmds_EstSamples=
((GT(_currn->_ATRawRate, 0.)
) ? (CAST(long, floor(DIV(MUL(_AVICOSCmds_Tcyc0, _currn->_ATRawRate), 1000000.)))
) : (0))
;
/*SPC(424)*/
_AVICOSCmds_Trcymin=
((GE(_AVICOSCmds_EstSamples, 16384)
) ? (200
) : (1))
;
/*SPC(430)*/
_currn->_ATSplitCycle=LT(MUL(4, _AVICOSCmds_Trcymin), _currn->_ATStepsize);
/*SPC(432)*/
_currn->_ATSplitFactor=
((_currn->_ATSplitCycle
) ? (2
) : (1))
;
/*SPC(452)*/
_currn->_ATSSzi=MUL(_currn->_ATSplitFactor, _AVICOSCmds_Szi);
/*SPC(454)*/
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSWaveWaveAddr_post=_AVICOSCmdsWaveAddr_pre;
/*SPC(0)*/
_AVICOSCmds_Istart1=_AVG3__const62;
/*SPC(991)*/
_AVICOSCmds_ISICOS=1;
/*SPC(967)*/
_AVICOSCmds_SSzif=SUB(_currn->_ATSSzi, 
((_currn->_ATSSzi
) ? (_currn->_ATSplitCycle
) : (0))
);
/*SPC(455)*/
_AVICOSCmds_Ton=
((_currn->_ATSplitCycle
) ? (_AVICOSCmds_Trcymin
) : (_currn->_ATStepsize))
;
/*SPC(437)*/
_AVICOSCmds_Srcy=
((_currn->_ATSplitCycle
) ? (0
) : (DIV_UP(_AVICOSCmds_Trcymin, _currn->_ATStepsize)))
;
/*SPC(434)*/
_AVICOSCmds_Trcypre=
((_currn->_ATSplitCycle
) ? (_AVICOSCmds_Trcymin
) : (0))
;
/*SPC(433)*/
_AVICOSCmds_Tramps1=_AVG3__const68;
/*SPC(403)*/
_AVICOSCmds_Tzi=MUL(_AVICOSCmds_Szi, _currn->_ATStepsize);
/*SPC(398)*/
_AVICOSCmds_NetRate=DIV(_currn->_ATRawRate, _currn->_ATNaverage);
/*SPC(312)*/
_AVICOSCmds_dIdt=GetdIdt(_AVICOSCmds_Key, 1.);
/*SPC(195)*/
_AVICOSCmds_SSrcy=
((_currn->_ATSplitCycle
) ? (1
) : (_AVICOSCmds_Srcy))
;
/*SPC(456)*/
_AVICOSCmds_Scycle=ADD(_AVICOSCmds_Scyc0, _AVICOSCmds_Srcy);
/*SPC(442)*/
_AVICOSCmds_Ttrigger=SUB(_AVICOSCmds_Tcyc0, _AVICOSCmds_Trcypre);
/*SPC(441)*/
_AVICOSCmds_Toff=
((_currn->_ATSplitCycle
) ? (SUB(_currn->_ATStepsize, _AVICOSCmds_Ton)
) : (_AVICOSCmds_Ton))
;
/*SPC(438)*/
_AVICOSCmds_Trcy=MUL(_currn->_ATStepsize, _AVICOSCmds_Srcy);
/*SPC(436)*/
_AVICOSCmds_Tz1=DIV(_AVICOSCmds_Tzi, 1000000.);
/*SPC(406)*/
_AVICOSCmds_dIdt_bits=aps_to_bits(_AVICOSCmds_dIdt, (* _IG_incl2), (&( _currn->_AT_pos)));
/*SPC(196)*/
_AVICOSCmds_TriggerSecs=DIV(_AVICOSCmds_Ttrigger, 1000000.);
/*SPC(658)*/
_AVICOSCmds_TzSamples=
((GT(_AVICOSCmds_NetRate, 0.)
) ? (CAST(long, floor(MUL(_AVICOSCmds_Tz1, _AVICOSCmds_NetRate)))
) : (0))
;
/*SPC(493)*/
_AVICOSCmds_RampSamples=
((GT(_AVICOSCmds_NetRate, 0.)
) ? (CAST(long, SUB(floor(MUL(ADD(_AVICOSCmds_Tz1, _AVICOSCmds_Tramps1), _AVICOSCmds_NetRate)), _AVICOSCmds_TzSamples))
) : (0))
;
/*SPC(485)*/
_AVICOSCmds_NetSamples=
((GT(_AVICOSCmds_NetRate, 0.)
) ? (CAST(long, floor(DIV(MUL(_AVICOSCmds_Ttrigger, _AVICOSCmds_NetRate), 1000000.)))
) : (0))
;
/*SPC(478)*/
_AVICOSCmds_ProgLen=MUL(_currn->_ATSplitFactor, _AVICOSCmds_Scycle);
/*SPC(453)*/
_AVICOSCmds_Tcycle=ADD(_AVICOSCmds_Tcyc0, _AVICOSCmds_Trcy);
/*SPC(443)*/
_AVICOSCmds_PTG=PTGSeq(PTGICOSHdr(_AVICOSCmds_WaveNum, (* _IG_incl26), PTGHex(ICOS_WAVEFORM_CODE, 1), PTGHex(SUB(_AVICOSCmds_Ton, 1), 1), PTGHex(SUB(_AVICOSCmds_Toff, 1), 1), PTGHex(1, 1), PTGHex(_AVICOSCmds_LoopAddr, 1), PTGHex(_AVICOSCmds_ProgLen, 1), PTGDACs(_AVICOSCmds_dIdt_bits, _AVICOSCmds_dIdt, dtoa_bits(_currn->_ATDtoAs, 1), dtoa_value(_currn->_ATDtoAs, 1), dtoa_bits(_currn->_ATDtoAs, 2), dtoa_value(_currn->_ATDtoAs, 2), dtoa_bits(_currn->_ATDtoAs, 3), dtoa_value(_currn->_ATDtoAs, 3))), PTGICOSProg(
((_currn->_ATSSzi
) ? (PTGICOSFill(ADD(WV_RAMP_OFF, _AVICOSCmds_DtoA), _currn->_ATSSzi)
) : (PTGNULL))
, _AVG3__const67, 
((_AVICOSCmds_SSzif
) ? (PTGICOSFill(ADD(WV_RAMP_RESET, _AVICOSCmds_DtoA), _AVICOSCmds_SSzif)
) : (PTGNULL))
, PTGICOSFill(ADD(WV_RAMP_OFF_T, _AVICOSCmds_DtoA), _AVICOSCmds_SSrcy)));
/*SPC(604)*/
_AVICOSCmds_TzRawSamples=MUL(_AVICOSCmds_TzSamples, _currn->_ATNaverage);
/*SPC(498)*/
_AVICOSCmds_RawSamples=MUL(_AVICOSCmds_NetSamples, _currn->_ATNaverage);
/*SPC(484)*/
_AVICOSCmds_Ftrigger=DIV_UP(1000000, _AVICOSCmds_Tcycle);
/*SPC(444)*/
_AVICOSCmds_CMDoutput=PTGCPCIdef(_currn->_ATRawRate, _AVICOSCmds_RawSamples, _AVICOSCmds_NetSamples, _currn->_ATNaverage, (* _IG_incl1), _AVICOSCmds_Ftrigger, "ICOS", _AVICOSCmds_TzSamples, StringTable((* _IG_incl25)));
/*SPC(968)*/
_AVICOSCmds_Summary=PTGICOSWave((* _IG_incl26), _AVG3__const63, PTGSampleRate(_currn->_ATRawRate, _currn->_ATNaverage), _AVG3__const64, PTGLong(_AVICOSCmds_RampSamples), PTGIz(PTGCurrent(MUL(_AVICOSCmds_Iz, 1000.))), PTGdIdt(_AVICOSCmds_dIdt), PTGTcycle(DIV(_AVICOSCmds_Tcycle, 1000.)), PTGStepsize(_currn->_ATStepsize), _AVG3__const65, _AVG3__const66, PTGFcycle(_AVICOSCmds_Ftrigger), PTGTz(PTGTime(MUL(_AVICOSCmds_Tz1, 1000.)), _AVICOSCmds_TzSamples, MUL(DIV(SUB(_AVICOSCmds_TriggerSecs, _AVICOSCmds_Tramps1), _AVICOSCmds_TriggerSecs), 100.)), PTGTonoff(_AVICOSCmds_Ton, _AVICOSCmds_Toff, ADD(_AVICOSCmds_Trcy, _AVICOSCmds_Trcypre), PTGTime(MUL(_AVICOSCmds_TriggerSecs, 1000.))), _AVICOSCmds_Scycle, _AVICOSCmds_ProgLen, _AVICOSCmdsWaveAddr_pre, PTGLong(_AVICOSCmds_RawSamples), PTGLong(_AVICOSCmds_NetSamples), PTGLong(_AVICOSCmds_TzSamples));
/*SPC(659)*/
_IG_incl34=_IL_incl34;
_IG_incl33=_IL_incl33;
_IG_incl32=_IL_incl32;
_IG_incl31=_IL_incl31;
_IG_incl21=_IL_incl21;
_IG_incl8=_IL_incl8;
_IG_incl9=_IL_incl9;
_IG_incl5=_IL_incl5;
_IG_incl4=_IL_incl4;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_022(_TPPrule_022 _currn)
#else
void _VS1rule_022(_currn )
_TPPrule_022 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(180)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_022(_TPPrule_022 _currn)
#else
void _VS2rule_022(_currn )
_TPPrule_022 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const72=ZERO();
/*SPC(1529)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_022(_TPPrule_022 _currn)
#else
void _VS3rule_022(_currn )
_TPPrule_022 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const71=NULLRATE();
/*SPC(1529)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_022(_TPPrule_022 _currn)
#else
void _VS6rule_022(_currn )
_TPPrule_022 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const6=ZERO();
/*SPC(1529)*/
_AVICOSCmd__const7=ZERO();
/*SPC(1529)*/
_AVICOSCmd__const69=ZERO();
/*SPC(1529)*/
_AVICOSCmd__const70=ZERO();
/*SPC(1529)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_022(_TPPrule_022 _currn)
#else
void _VS7rule_022(_currn )
_TPPrule_022 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const62=NEGONE();
/*SPC(1529)*/
_AVICOSCmd__const63=PTGNull();
/*SPC(1529)*/
_AVICOSCmd__const64=PTGNull();
/*SPC(1529)*/
_AVICOSCmd__const65=PTGNull();
/*SPC(1529)*/
_AVICOSCmd__const66=PTGNull();
/*SPC(1529)*/
_AVICOSCmd__const67=PTGNull();
/*SPC(1529)*/
_AVICOSCmd__const68=ZERO();
/*SPC(1529)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_021(_TPPrule_021 _currn)
#else
void _VS2rule_021(_currn )
_TPPrule_021 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const72=ZERO();
/*SPC(1525)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_021(_TPPrule_021 _currn)
#else
void _VS3rule_021(_currn )
_TPPrule_021 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const71=NULLRATE();
/*SPC(1525)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_021(_TPPrule_021 _currn)
#else
void _VS5rule_021(_currn )
_TPPrule_021 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(105)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_021(_TPPrule_021 _currn)
#else
void _VS6rule_021(_currn )
_TPPrule_021 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const6=ZERO();
/*SPC(1525)*/
_AVICOSCmd__const7=ZERO();
/*SPC(1525)*/
_AVICOSCmd__const69=ZERO();
/*SPC(1525)*/
_AVICOSCmd__const70=_currn->_desc1->_AT_const70;
/*SPC(1525)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_021(_TPPrule_021 _currn)
#else
void _VS7rule_021(_currn )
_TPPrule_021 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const62=NEGONE();
/*SPC(1525)*/
_AVICOSCmd__const63=PTGNull();
/*SPC(1525)*/
_AVICOSCmd__const64=PTGNull();
/*SPC(1525)*/
_AVICOSCmd__const65=PTGNull();
/*SPC(1525)*/
_AVICOSCmd__const66=_AVTzDef__const66;
/*SPC(1525)*/
_AVICOSCmd__const67=PTGNull();
/*SPC(1525)*/
_AVICOSCmd__const68=ZERO();
/*SPC(1525)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_020(_TPPrule_020 _currn)
#else
void _VS1rule_020(_currn )
_TPPrule_020 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(123)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_020(_TPPrule_020 _currn)
#else
void _VS2rule_020(_currn )
_TPPrule_020 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const72=ZERO();
/*SPC(1521)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_020(_TPPrule_020 _currn)
#else
void _VS3rule_020(_currn )
_TPPrule_020 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const71=NULLRATE();
/*SPC(1521)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_020(_TPPrule_020 _currn)
#else
void _VS6rule_020(_currn )
_TPPrule_020 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const6=ZERO();
/*SPC(1521)*/
_AVICOSCmd__const7=IDENTICAL(_currn->_desc1->_ATNcoadd);
/*SPC(1521)*/
_AVICOSCmd__const69=ZERO();
/*SPC(1521)*/
_AVICOSCmd__const70=ZERO();
/*SPC(1521)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_020(_TPPrule_020 _currn)
#else
void _VS7rule_020(_currn )
_TPPrule_020 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const62=NEGONE();
/*SPC(1521)*/
_AVICOSCmd__const63=PTGNull();
/*SPC(1521)*/
_AVICOSCmd__const64=PTGNull();
/*SPC(1521)*/
_AVICOSCmd__const65=PTGNull();
/*SPC(1521)*/
_AVICOSCmd__const66=PTGNull();
/*SPC(1521)*/
_AVICOSCmd__const67=PTGNull();
/*SPC(1521)*/
_AVICOSCmd__const68=ZERO();
/*SPC(1521)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_019(_TPPrule_019 _currn)
#else
void _VS1rule_019(_currn )
_TPPrule_019 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(114)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_019(_TPPrule_019 _currn)
#else
void _VS2rule_019(_currn )
_TPPrule_019 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const72=ZERO();
/*SPC(1517)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_019(_TPPrule_019 _currn)
#else
void _VS3rule_019(_currn )
_TPPrule_019 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const71=NULLRATE();
/*SPC(1517)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_019(_TPPrule_019 _currn)
#else
void _VS6rule_019(_currn )
_TPPrule_019 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const6=IDENTICAL(_currn->_desc1->_ATIz);
/*SPC(1517)*/
_AVICOSCmd__const7=ZERO();
/*SPC(1517)*/
_AVICOSCmd__const69=ZERO();
/*SPC(1517)*/
_AVICOSCmd__const70=ZERO();
/*SPC(1517)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_019(_TPPrule_019 _currn)
#else
void _VS7rule_019(_currn )
_TPPrule_019 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const62=NEGONE();
/*SPC(1517)*/
_AVICOSCmd__const63=PTGNull();
/*SPC(1517)*/
_AVICOSCmd__const64=PTGNull();
/*SPC(1517)*/
_AVICOSCmd__const65=PTGNull();
/*SPC(1517)*/
_AVICOSCmd__const66=PTGNull();
/*SPC(1517)*/
_AVICOSCmd__const67=PTGNull();
/*SPC(1517)*/
_AVICOSCmd__const68=ZERO();
/*SPC(1517)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_018(_TPPrule_018 _currn)
#else
void _VS2rule_018(_currn )
_TPPrule_018 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const72=ZERO();
/*SPC(1513)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_018(_TPPrule_018 _currn)
#else
void _VS3rule_018(_currn )
_TPPrule_018 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(134)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const71=_AVICOSRateDef__const71;
/*SPC(1513)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_018(_TPPrule_018 _currn)
#else
void _VS6rule_018(_currn )
_TPPrule_018 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const6=ZERO();
/*SPC(1513)*/
_AVICOSCmd__const7=ZERO();
/*SPC(1513)*/
_AVICOSCmd__const69=ZERO();
/*SPC(1513)*/
_AVICOSCmd__const70=ZERO();
/*SPC(1513)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_018(_TPPrule_018 _currn)
#else
void _VS7rule_018(_currn )
_TPPrule_018 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const62=NEGONE();
/*SPC(1513)*/
_AVICOSCmd__const63=_AVICOSRateDef__const63;
/*SPC(1513)*/
_AVICOSCmd__const64=PTGNull();
/*SPC(1513)*/
_AVICOSCmd__const65=PTGNull();
/*SPC(1513)*/
_AVICOSCmd__const66=PTGNull();
/*SPC(1513)*/
_AVICOSCmd__const67=PTGNull();
/*SPC(1513)*/
_AVICOSCmd__const68=ZERO();
/*SPC(1513)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_017(_TPPrule_017 _currn)
#else
void _VS1rule_017(_currn )
_TPPrule_017 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATWaveKey=(* _IG_incl17);
/*SPC(209)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_currn->_desc1->_ATdIdt=GetdIdt(_currn->_desc1->_ATWaveKey, 1.);
/*SPC(210)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const72=IDENTICAL(_currn->_desc1->_ATTramp);
/*SPC(1509)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_017(_TPPrule_017 _currn)
#else
void _VS3rule_017(_currn )
_TPPrule_017 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const71=NULLRATE();
/*SPC(1509)*/

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
_currn->_desc1->_ATrcnt_pre=_AVTzDefrcnt_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_017(_TPPrule_017 _currn)
#else
void _VS5rule_017(_currn )
_TPPrule_017 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_017(_TPPrule_017 _currn)
#else
void _VS6rule_017(_currn )
_TPPrule_017 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const6=ZERO();
/*SPC(1509)*/
_AVICOSCmd__const7=ZERO();
/*SPC(1509)*/
_AVICOSCmd__const69=IDENTICAL(_currn->_desc1->_ATSrampi);
/*SPC(1509)*/
_AVICOSCmd__const70=ZERO();
/*SPC(1509)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_017(_TPPrule_017 _currn)
#else
void _VS7rule_017(_currn )
_TPPrule_017 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSRamp_DtoAs=(* _IG_incl31);
/*SPC(531)*/
_AVICOSRamp_SSzi=(* _IG_incl32);
/*SPC(463)*/
_AVICOSRamp_SplitFactor=(* _IG_incl33);
/*SPC(462)*/
_AVICOSRamp_SplitCycle=(* _IG_incl34);
/*SPC(461)*/
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const62=IDENTICAL(_AVICOSRamp_Istart1);
/*SPC(1509)*/
_AVICOSCmd__const63=PTGNull();
/*SPC(1509)*/
_AVICOSCmd__const64=PTGNull();
/*SPC(1509)*/
_AVICOSCmd__const65=IDENTICAL(_AVICOSRamp_Summary);
/*SPC(1509)*/
_AVICOSCmd__const66=PTGNull();
/*SPC(1509)*/
_AVICOSCmd__const67=IDENTICAL(_AVICOSRamp_PTG);
/*SPC(1509)*/
_AVICOSCmd__const68=IDENTICAL(_AVICOSRamp_Tramp1);
/*SPC(1509)*/

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
_AVICOSCmd__const72=ZERO();
/*SPC(1505)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_016(_TPPrule_016 _currn)
#else
void _VS3rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(134)*/
_AVICOSNsampleDef_Tramps=(* _IG_incl5);
/*SPC(288)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const71=IDENTICAL(_AVICOSNsampleDef_RateDef);
/*SPC(1505)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_016(_TPPrule_016 _currn)
#else
void _VS6rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const6=ZERO();
/*SPC(1505)*/
_AVICOSCmd__const7=ZERO();
/*SPC(1505)*/
_AVICOSCmd__const69=ZERO();
/*SPC(1505)*/
_AVICOSCmd__const70=ZERO();
/*SPC(1505)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_016(_TPPrule_016 _currn)
#else
void _VS7rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const62=NEGONE();
/*SPC(1505)*/
_AVICOSCmd__const63=PTGNull();
/*SPC(1505)*/
_AVICOSCmd__const64=_AVICOSNsampleDef__const64;
/*SPC(1505)*/
_AVICOSCmd__const65=PTGNull();
/*SPC(1505)*/
_AVICOSCmd__const66=PTGNull();
/*SPC(1505)*/
_AVICOSCmd__const67=PTGNull();
/*SPC(1505)*/
_AVICOSCmd__const68=ZERO();
/*SPC(1505)*/

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
_AVICOSCmd__const72=ZERO();
/*SPC(1501)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_015(_TPPrule_015 _currn)
#else
void _VS3rule_015(_currn )
_TPPrule_015 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVICOSCmd__const71=NULLRATE();
/*SPC(1501)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_015(_TPPrule_015 _currn)
#else
void _VS6rule_015(_currn )
_TPPrule_015 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const6=ZERO();
/*SPC(1501)*/
_AVICOSCmd__const7=ZERO();
/*SPC(1501)*/
_AVICOSCmd__const69=ZERO();
/*SPC(1501)*/
_AVICOSCmd__const70=ZERO();
/*SPC(1501)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_015(_TPPrule_015 _currn)
#else
void _VS7rule_015(_currn )
_TPPrule_015 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd__const62=NEGONE();
/*SPC(1501)*/
_AVICOSCmd__const63=PTGNull();
/*SPC(1501)*/
_AVICOSCmd__const64=PTGNull();
/*SPC(1501)*/
_AVICOSCmd__const65=PTGNull();
/*SPC(1501)*/
_AVICOSCmd__const66=PTGNull();
/*SPC(1501)*/
_AVICOSCmd__const67=PTGNull();
/*SPC(1501)*/
_AVICOSCmd__const68=ZERO();
/*SPC(1501)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_014(_TPPrule_014 _currn)
#else
void _VS1rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_AVG4__const7=_AVRingCmd__const7;
/*SPC(1497)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_014(_TPPrule_014 _currn)
#else
void _VS3rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG4__const6=_AVRingCmd__const6;
/*SPC(1497)*/
_currn->_AT_const53=_AVRingCmd__const53;
/*SPC(1497)*/
_currn->_AT_const54=_AVRingCmd__const54;
/*SPC(1497)*/
_currn->_AT_const55=_AVRingCmd__const55;
/*SPC(1497)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_013(_TPPrule_013 _currn)
#else
void _VS1rule_013(_currn )
_TPPrule_013 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG4__const7=ADD(_AVG4__const7, _AVRingCmd__const7);
/*SPC(1493)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG4__const6=ADD(_AVG4__const6, _AVRingCmd__const6);
/*SPC(1493)*/
_currn->_AT_const53=ADD(_currn->_desc1->_AT_const53, _AVRingCmd__const53);
/*SPC(1493)*/
_currn->_AT_const54=PTGSeq(_currn->_desc1->_AT_const54, _AVRingCmd__const54);
/*SPC(1493)*/
_currn->_AT_const55=ADD(_currn->_desc1->_AT_const55, _AVRingCmd__const55);
/*SPC(1493)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_012(_TPPrule_012 _currn)
#else
void _VS1rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_AVG3__const72=_AVICOSCmd__const72;
/*SPC(1489)*/

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
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG3__const71=_AVICOSCmd__const71;
/*SPC(1489)*/

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
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATrcnt_post=_AVTzDefrcnt_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_012(_TPPrule_012 _currn)
#else
void _VS5rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_012(_TPPrule_012 _currn)
#else
void _VS6rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG3__const6=_AVICOSCmd__const6;
/*SPC(1489)*/
_AVG3__const7=_AVICOSCmd__const7;
/*SPC(1489)*/
_currn->_AT_const69=_AVICOSCmd__const69;
/*SPC(1489)*/
_currn->_AT_const70=_AVICOSCmd__const70;
/*SPC(1489)*/
_currn->_AT_cICOSRampCount_post=_AVICOSCmd_cICOSRampCount_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_012(_TPPrule_012 _currn)
#else
void _VS7rule_012(_currn )
_TPPrule_012 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG3__const62=_AVICOSCmd__const62;
/*SPC(1489)*/
_AVG3__const63=_AVICOSCmd__const63;
/*SPC(1489)*/
_AVG3__const64=_AVICOSCmd__const64;
/*SPC(1489)*/
_AVG3__const65=_AVICOSCmd__const65;
/*SPC(1489)*/
_AVG3__const66=_AVICOSCmd__const66;
/*SPC(1489)*/
_AVG3__const67=_AVICOSCmd__const67;
/*SPC(1489)*/
_AVG3__const68=_AVICOSCmd__const68;
/*SPC(1489)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_011(_TPPrule_011 _currn)
#else
void _VS1rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
_AVG3__const72=ADD(_AVG3__const72, _AVICOSCmd__const72);
/*SPC(1485)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_011(_TPPrule_011 _currn)
#else
void _VS3rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG3__const71=PICKRATE(_AVG3__const71, _AVICOSCmd__const71);
/*SPC(1485)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_011(_TPPrule_011 _currn)
#else
void _VS4rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVTzDefrcnt_post=_currn->_desc1->_ATrcnt_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_currn->_ATrcnt_post=_AVTzDefrcnt_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS5rule_011(_TPPrule_011 _currn)
#else
void _VS5rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS5MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS6rule_011(_TPPrule_011 _currn)
#else
void _VS6rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVICOSCmd_cICOSRampCount_post=_currn->_desc1->_AT_cICOSRampCount_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS6MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG3__const6=ADD(_AVG3__const6, _AVICOSCmd__const6);
/*SPC(1485)*/
_AVG3__const7=ADD(_AVG3__const7, _AVICOSCmd__const7);
/*SPC(1485)*/
_currn->_AT_const69=ADD(_currn->_desc1->_AT_const69, _AVICOSCmd__const69);
/*SPC(1485)*/
_currn->_AT_const70=ADD(_currn->_desc1->_AT_const70, _AVICOSCmd__const70);
/*SPC(1485)*/
_currn->_AT_cICOSRampCount_post=_AVICOSCmd_cICOSRampCount_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS7rule_011(_TPPrule_011 _currn)
#else
void _VS7rule_011(_currn )
_TPPrule_011 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS7MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG3__const62=FIRSTNONNEG(_AVG3__const62, _AVICOSCmd__const62);
/*SPC(1485)*/
_AVG3__const63=PTGSeq(_AVG3__const63, _AVICOSCmd__const63);
/*SPC(1485)*/
_AVG3__const64=PTGSeq(_AVG3__const64, _AVICOSCmd__const64);
/*SPC(1485)*/
_AVG3__const65=PTGSeq(_AVG3__const65, _AVICOSCmd__const65);
/*SPC(1485)*/
_AVG3__const66=PTGSeq(_AVG3__const66, _AVICOSCmd__const66);
/*SPC(1485)*/
_AVG3__const67=PTGSeq(_AVG3__const67, _AVICOSCmd__const67);
/*SPC(1485)*/
_AVG3__const68=ADD(_AVG3__const68, _AVICOSCmd__const68);
/*SPC(1485)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_010(_TPPrule_010 _currn)
#else
void _VS1rule_010(_currn )
_TPPrule_010 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

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
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_08(_TPPrule_08 _currn)
#else
void _VS3rule_08(_currn )
_TPPrule_08 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVG1__const22=IDENTICAL(_AVWave_DISPoutput);
/*SPC(1473)*/
_AVG1__const23=PTGMString(_currn->_desc1->_ATWaveName);
/*SPC(1473)*/
_AVG1__const24=_AVWave__const24;
/*SPC(1473)*/
_AVG1__const25=_AVWave__const25;
/*SPC(1473)*/
_AVG1__const26=_AVWave__const26;
/*SPC(1473)*/
_AVG1__const27=_AVWave__const27;
/*SPC(1473)*/
_AVG1__const28=PTGNumb(_currn->_desc1->_ATNcoadd);
/*SPC(1473)*/
_AVG1__const29=_AVWave__const29;
/*SPC(1473)*/
_AVG1__const30=_AVWave__const30;
/*SPC(1473)*/
_AVG1__const31=_AVWave__const31;
/*SPC(1473)*/
_AVG1__const32=_AVWave__const32;
/*SPC(1473)*/
_AVG1__const33=_AVWave__const33;
/*SPC(1473)*/
_AVG1__const34=_AVWave__const34;
/*SPC(1473)*/
_AVG1__const35=IDENTICAL(_AVWave_CMDoutput);
/*SPC(1473)*/
_AVG1__const36=_AVWave__const36;
/*SPC(1473)*/
_AVG1__const37=IDENTICAL(_AVWave_WaveIndex);
/*SPC(1473)*/
_AVG1__const38=_AVWave__const38;
/*SPC(1473)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_07(_TPPrule_07 _currn)
#else
void _VS3rule_07(_currn )
_TPPrule_07 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_AVG1__const22=PTGCommas(_AVG1__const22, IDENTICAL(_AVWave_DISPoutput));
/*SPC(1469)*/
_AVG1__const23=PTGMCommas(_AVG1__const23, PTGMString(_currn->_desc2->_ATWaveName));
/*SPC(1469)*/
_AVG1__const24=PTGMCommas(_AVG1__const24, _AVWave__const24);
/*SPC(1469)*/
_AVG1__const25=PTGMCommas(_AVG1__const25, _AVWave__const25);
/*SPC(1469)*/
_AVG1__const26=PTGMCommas(_AVG1__const26, _AVWave__const26);
/*SPC(1469)*/
_AVG1__const27=PTGMCommas(_AVG1__const27, _AVWave__const27);
/*SPC(1469)*/
_AVG1__const28=PTGMCommas(_AVG1__const28, PTGNumb(_currn->_desc2->_ATNcoadd));
/*SPC(1469)*/
_AVG1__const29=PTGMCommas(_AVG1__const29, _AVWave__const29);
/*SPC(1469)*/
_AVG1__const30=PTGMCommas(_AVG1__const30, _AVWave__const30);
/*SPC(1469)*/
_AVG1__const31=PTGMCommas(_AVG1__const31, _AVWave__const31);
/*SPC(1469)*/
_AVG1__const32=PTGMCommas(_AVG1__const32, _AVWave__const32);
/*SPC(1469)*/
_AVG1__const33=PTGMCommas(_AVG1__const33, _AVWave__const33);
/*SPC(1469)*/
_AVG1__const34=PTGCommas(_AVG1__const34, _AVWave__const34);
/*SPC(1469)*/
_AVG1__const35=PTGSeq(_AVG1__const35, IDENTICAL(_AVWave_CMDoutput));
/*SPC(1469)*/
_AVG1__const36=PTGWaves(_AVG1__const36, _AVWave__const36);
/*SPC(1469)*/
_AVG1__const37=PTGSeq(_AVG1__const37, IDENTICAL(_AVWave_WaveIndex));
/*SPC(1469)*/
_AVG1__const38=PTGSeq(_AVG1__const38, _AVWave__const38);
/*SPC(1469)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_06(_TPPrule_06 _currn)
#else
void _VS1rule_06(_currn )
_TPPrule_06 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl27);
/*SPC(65)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_05(_TPPrule_05 _currn)
#else
void _VS1rule_05(_currn )
_TPPrule_05 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl17);
/*SPC(539)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_AVDAC3Value_DtoAs=(* _IG_incl18);
/*SPC(538)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_05(_TPPrule_05 _currn)
#else
void _VS3rule_05(_currn )
_TPPrule_05 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

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
_AVConfigCmds_cICOSRampCount_post=_AVICOSCmd_cICOSRampCount_post;
/*SPC(0)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_02(_TPPrule_02 _currn)
#else
void _VS1rule_02(_currn )
_TPPrule_02 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATKey=(* _IG_incl27);
/*SPC(91)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

