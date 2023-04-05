
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

typedef struct _TSRingCmd* _TSPRingCmd;
typedef struct _TSG4* _TSPG4;
typedef struct _TSICOSCmd* _TSPICOSCmd;
typedef struct _TSG3* _TSPG3;
typedef struct _TSG1* _TSPG1;
typedef struct _TSDAC3def* _TSPDAC3def;
typedef struct _TSG2* _TSPG2;
typedef struct _TSConfigCmds* _TSPConfigCmds;
typedef struct _TSQCLIConfig* _TSPQCLIConfig;
typedef struct _TSDigitizer* _TSPDigitizer;
typedef struct _TSConfigCmd* _TSPConfigCmd;
typedef struct _TSRingStepsize* _TSPRingStepsize;
typedef struct _TSRingCount* _TSPRingCount;
typedef struct _TSRingStep* _TSPRingStep;
typedef struct _TSCurrentSteps* _TSPCurrentSteps;
typedef struct _TSRingCurrent* _TSPRingCurrent;
typedef struct _TSTpreVal* _TSPTpreVal;
typedef struct _TSTonVal* _TSPTonVal;
typedef struct _TSTpreDef* _TSPTpreDef;
typedef struct _TSTonDef* _TSPTonDef;
typedef struct _TSRingNsampleDef* _TSPRingNsampleDef;
typedef struct _TSToffDef* _TSPToffDef;
typedef struct _TSRingRateDef* _TSPRingRateDef;
typedef struct _TSRingData* _TSPRingData;
typedef struct _TSDAC3Value* _TSPDAC3Value;
typedef struct _TSSampleSpec* _TSPSampleSpec;
typedef struct _TSTzTime* _TSPTzTime;
typedef struct _TSTzSpec* _TSPTzSpec;
typedef struct _TSRateDef* _TSPRateDef;
typedef struct _TSNsample* _TSPNsample;
typedef struct _TSNsampleDef* _TSPNsampleDef;
typedef struct _TSNaverage* _TSPNaverage;
typedef struct _TSNcoadd* _TSPNcoadd;
typedef struct _TSICOSRamp* _TSPICOSRamp;
typedef struct _TSdIdt* _TSPdIdt;
typedef struct _TSPrepTime* _TSPPrepTime;
typedef struct _TSIstop* _TSPIstop;
typedef struct _TSIstart* _TSPIstart;
typedef struct _TSPercent* _TSPPercent;
typedef struct _TSRateUnit* _TSPRateUnit;
typedef struct _TSTimeUnit* _TSPTimeUnit;
typedef struct _TSTime* _TSPTime;
typedef struct _TSCurrentUnit* _TSPCurrentUnit;
typedef struct _TSFloatVal* _TSPFloatVal;
typedef struct _TSCurrent* _TSPCurrent;
typedef struct _TSICOSRateDef* _TSPICOSRateDef;
typedef struct _TSICOSNsampleDef* _TSPICOSNsampleDef;
typedef struct _TSNcoaddDef* _TSPNcoaddDef;
typedef struct _TSIzDef* _TSPIzDef;
typedef struct _TSTzDef* _TSPTzDef;
typedef struct _TSPrefix* _TSPPrefix;
typedef struct _TSDigitizerType* _TSPDigitizerType;
typedef struct _TSQCLIConfigType* _TSPQCLIConfigType;
typedef struct _TSSourceFile* _TSPSourceFile;
typedef struct _TSWave* _TSPWave;
typedef struct _TSRingCmds* _TSPRingCmds;
typedef struct _TSRingWave* _TSPRingWave;
typedef struct _TSICOSCmds* _TSPICOSCmds;
typedef struct _TSDefIdent* _TSPDefIdent;
typedef struct _TSICOSWave* _TSPICOSWave;
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
typedef struct _TPrule_35* _TPPrule_35;
typedef struct _TPrule_36* _TPPrule_36;
typedef struct _TPrule_37* _TPPrule_37;
typedef struct _TPrule_38* _TPPrule_38;
typedef struct _TPrule_39* _TPPrule_39;
typedef struct _TPrule_40* _TPPrule_40;
typedef struct _TPrule_41* _TPPrule_41;
typedef struct _TPrule_42* _TPPrule_42;
typedef struct _TPrule_43* _TPPrule_43;
typedef struct _TPrule_44* _TPPrule_44;
typedef struct _TPrule_45* _TPPrule_45;
typedef struct _TPrule_46* _TPPrule_46;
typedef struct _TPrule_47* _TPPrule_47;
typedef struct _TPrule_48* _TPPrule_48;
typedef struct _TPrule_49* _TPPrule_49;
typedef struct _TPrule_50* _TPPrule_50;
typedef struct _TPrule_51* _TPPrule_51;
typedef struct _TPrule_52* _TPPrule_52;
typedef struct _TPrule_062* _TPPrule_062;
typedef struct _TPrule_061* _TPPrule_061;
typedef struct _TPrule_060* _TPPrule_060;
typedef struct _TPrule_059* _TPPrule_059;
typedef struct _TPrule_058* _TPPrule_058;
typedef struct _TPrule_057* _TPPrule_057;
typedef struct _TPrule_056* _TPPrule_056;
typedef struct _TPrule_055* _TPPrule_055;
typedef struct _TPrule_054* _TPPrule_054;
typedef struct _TPrule_053* _TPPrule_053;
typedef struct _TPrule_052* _TPPrule_052;
typedef struct _TPrule_051* _TPPrule_051;
typedef struct _TPrule_050* _TPPrule_050;
typedef struct _TPrule_049* _TPPrule_049;
typedef struct _TPrule_048* _TPPrule_048;
typedef struct _TPrule_047* _TPPrule_047;
typedef struct _TPrule_046* _TPPrule_046;
typedef struct _TPrule_045* _TPPrule_045;
typedef struct _TPrule_044* _TPPrule_044;
typedef struct _TPrule_043* _TPPrule_043;
typedef struct _TPrule_042* _TPPrule_042;
typedef struct _TPrule_041* _TPPrule_041;
typedef struct _TPrule_040* _TPPrule_040;
typedef struct _TPrule_039* _TPPrule_039;
typedef struct _TPrule_038* _TPPrule_038;
typedef struct _TPrule_037* _TPPrule_037;
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

struct _TSRingCmd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const53;
PTGNode _AT_const54;
int _AT_const55;
};

struct _TSICOSCmd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
long _AT_const69;
double _AT_const70;
int _AT_cICOSRampCount_post;
int _ATrcnt_post;
};

struct _TSG1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDAC3def
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

struct _TSConfigCmds
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSQCLIConfig
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDigitizer
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSConfigCmd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRingStepsize
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRingCount
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRingStep
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSCurrentSteps
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATIramp;
};

struct _TSRingCurrent
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTpreVal
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTonVal
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTpreDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTonDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRingNsampleDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSToffDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRingRateDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSRingData
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSDAC3Value
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSSampleSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
};

struct _TSTzTime
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
};

struct _TSTzSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const66;
int _ATrcnt_pre;
double _ATTz;
};

struct _TSRateDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
};

struct _TSNsample
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSNsampleDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
};

struct _TSNaverage
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSNcoadd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSICOSRamp
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATrcnt_pre;
int _ATICOSRampCount;
int _ATSrampi;
double _ATTramp;
double _ATdIdt;
DefTableKey _ATWaveKey;
};

struct _TSdIdt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSPrepTime
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
double _ATValue;
};

struct _TSIstop
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
double _ATValue;
};

struct _TSIstart
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
double _ATValue;
};

struct _TSPercent
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
};

struct _TSRateUnit
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTimeUnit
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSTime
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSCurrentUnit
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSFloatVal
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATValue;
};

struct _TSCurrent
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSICOSRateDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSICOSNsampleDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSNcoaddDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATNcoadd;
DefTableKey _ATKey;
};

struct _TSIzDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATIz;
DefTableKey _ATKey;
};

struct _TSTzDef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _AT_const70;
DefTableKey _ATKey;
};

struct _TSPrefix
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSDigitizerType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSQCLIConfigType
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSSourceFile
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
int _ATPrefix;
int _ATDigitizer;
int _ATQCLIConfig;
DefTableKey _ATKey;
};

struct _TSWave
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATWaveName;
long _ATLoopAddr;
int _ATWaveNum;
double _ATIz;
WaveDtoAP _ATDtoAs;
int _ATNcoadd;
DefTableKey _ATKey;
};

struct _TSRingCmds
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATToffD;
long _ATNsample;
double _ATRawRate;
long _ATTpre;
DefTableKey _ATKey;
};

struct _TSRingWave
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _AT_const6;
int _AT_const7;
int _AT_const8;
};

struct _TSICOSCmds
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
WaveDtoAP _ATDtoAs;
int _ATICOSRampCountResult;
long _ATSSzi;
int _ATSplitFactor;
int _ATSplitCycle;
long _ATStepsize;
int _ATNaverage;
double _ATRawRate;
double _ATTramps;
};

struct _TSDefIdent
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATSym;
};

struct _TSICOSWave
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _AT_const6;
int _AT_const7;
int _AT_const8;
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPCurrent _desc1;
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATIramp;
_TSPCurrent _desc1;
_TSPCurrent _desc2;
_TSPRingStep _desc3;
POSITION _AT_pos;
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTime _desc1;
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
POSITION _AT_pos;
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTime _desc1;
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
_TSPFloatVal _desc1;
POSITION _AT_pos;
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const66;
int _ATrcnt_pre;
double _ATTz;
_TSPSampleSpec _desc1;
POSITION _AT_pos;
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
int _ATTERM_1;
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
int _ATTERM_1;
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const66;
int _ATrcnt_pre;
double _ATTz;
_TSPPercent _desc1;
POSITION _AT_pos;
};

struct _TPrule_14
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
_TSPTime _desc1;
};

struct _TPrule_15
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _AT_const66;
int _ATrcnt_pre;
double _ATTz;
_TSPTzTime _desc1;
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
_TSPRateUnit _desc1;
_TSPNaverage _desc2;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_17
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
_TSPNsample _desc1;
int _ATTERM_1;
};

struct _TPrule_18
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_19
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_20
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATNcoadd;
DefTableKey _ATKey;
_TSPNcoadd _desc1;
POSITION _AT_pos;
};

struct _TPrule_21
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATrcnt_pre;
int _ATICOSRampCount;
int _ATSrampi;
double _ATTramp;
double _ATdIdt;
DefTableKey _ATWaveKey;
_TSPIstop _desc1;
_TSPPrepTime _desc2;
POSITION _AT_pos;
};

struct _TPrule_22
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATrcnt_pre;
int _ATICOSRampCount;
int _ATSrampi;
double _ATTramp;
double _ATdIdt;
DefTableKey _ATWaveKey;
_TSPIstart _desc1;
_TSPPrepTime _desc2;
POSITION _AT_pos;
};

struct _TPrule_23
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATrcnt_pre;
int _ATICOSRampCount;
int _ATSrampi;
double _ATTramp;
double _ATdIdt;
DefTableKey _ATWaveKey;
_TSPIstart _desc1;
_TSPIstop _desc2;
POSITION _AT_pos;
};

struct _TPrule_24
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATrcnt_pre;
int _ATICOSRampCount;
int _ATSrampi;
double _ATTramp;
double _ATdIdt;
DefTableKey _ATWaveKey;
_TSPIstart _desc1;
_TSPIstop _desc2;
_TSPPrepTime _desc3;
POSITION _AT_pos;
};

struct _TPrule_25
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
_TSPCurrent _desc1;
_TSPTimeUnit _desc2;
POSITION _AT_pos;
};

struct _TPrule_26
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATValue;
int _ATTERM_1;
};

struct _TPrule_27
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATValue;
int _ATTERM_1;
};

struct _TPrule_28
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTimeUnit _desc1;
};

struct _TPrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_36
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_37
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_38
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPTimeUnit _desc2;
};

struct _TPrule_39
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPCurrentUnit _desc2;
};

struct _TPrule_40
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_41
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_42
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_43
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_44
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_45
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_46
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_47
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_48
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_49
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
POSITION _AT_pos;
};

struct _TPrule_50
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
int _ATSym;
POSITION _AT_pos;
};

struct _TPrule_51
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _AT_const6;
int _AT_const7;
int _AT_const8;
_TSPDefIdent _desc1;
_TSPRingCmds _desc2;
};

struct _TPrule_52
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _AT_const6;
int _AT_const7;
int _AT_const8;
_TSPDefIdent _desc1;
_TSPICOSCmds _desc2;
};

struct _TPrule_062
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATWaveName;
long _ATLoopAddr;
int _ATWaveNum;
double _ATIz;
WaveDtoAP _ATDtoAs;
int _ATNcoadd;
DefTableKey _ATKey;
_TSPRingWave _desc1;
};

struct _TPrule_061
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATWaveName;
long _ATLoopAddr;
int _ATWaveNum;
double _ATIz;
WaveDtoAP _ATDtoAs;
int _ATNcoadd;
DefTableKey _ATKey;
_TSPICOSWave _desc1;
};

struct _TPrule_060
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _AT_const70;
DefTableKey _ATKey;
_TSPTzSpec _desc1;
POSITION _AT_pos;
};

struct _TPrule_059
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTpreVal _desc1;
POSITION _AT_pos;
};

struct _TPrule_058
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTonVal _desc1;
POSITION _AT_pos;
};

struct _TPrule_057
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTime _desc1;
POSITION _AT_pos;
};

struct _TPrule_056
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
int _ATPrefix;
int _ATDigitizer;
int _ATQCLIConfig;
DefTableKey _ATKey;
_TSPConfigCmds _desc1;
_TSPG1 _desc2;
};

struct _TPrule_055
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRingStepsize _desc1;
};

struct _TPrule_054
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRingCount _desc1;
};

struct _TPrule_053
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRateDef _desc1;
POSITION _AT_pos;
};

struct _TPrule_052
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPNsampleDef _desc1;
POSITION _AT_pos;
};

struct _TPrule_051
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRingCurrent _desc1;
};

struct _TPrule_050
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPCurrentSteps _desc1;
};

struct _TPrule_049
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPCurrent _desc1;
POSITION _AT_pos;
};

struct _TPrule_048
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATToffD;
long _ATNsample;
double _ATRawRate;
long _ATTpre;
DefTableKey _ATKey;
_TSPG4 _desc1;
POSITION _AT_pos;
};

struct _TPrule_047
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTpreDef _desc1;
};

struct _TPrule_046
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTonDef _desc1;
};

struct _TPrule_045
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPToffDef _desc1;
};

struct _TPrule_044
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRingRateDef _desc1;
};

struct _TPrule_043
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRingNsampleDef _desc1;
};

struct _TPrule_042
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPRingData _desc1;
};

struct _TPrule_041
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPNcoaddDef _desc1;
};

struct _TPrule_040
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPIzDef _desc1;
};

struct _TPrule_039
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDAC3def _desc1;
};

struct _TPrule_038
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPQCLIConfigType _desc1;
};

struct _TPrule_037
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
double _ATValue;
_TSPTime _desc1;
};

struct _TPrule_036
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
double _ATValue;
_TSPTime _desc1;
};

struct _TPrule_035
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
_TSPFloatVal _desc1;
};

struct _TPrule_034
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_033
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_032
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_031
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_030
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_029
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_028
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATIz;
DefTableKey _ATKey;
_TSPCurrent _desc1;
POSITION _AT_pos;
};

struct _TPrule_027
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
double _ATValue;
_TSPCurrent _desc1;
};

struct _TPrule_026
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
PTGNode _ATSummary;
double _ATValue;
_TSPCurrent _desc1;
};

struct _TPrule_025
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
_TSPRateDef _desc1;
POSITION _AT_pos;
};

struct _TPrule_024
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
_TSPNsampleDef _desc1;
POSITION _AT_pos;
};

struct _TPrule_023
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
WaveDtoAP _ATDtoAs;
int _ATICOSRampCountResult;
long _ATSSzi;
int _ATSplitFactor;
int _ATSplitCycle;
long _ATStepsize;
int _ATNaverage;
double _ATRawRate;
double _ATTramps;
_TSPG3 _desc1;
POSITION _AT_pos;
};

struct _TPrule_022
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPdIdt _desc1;
};

struct _TPrule_021
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPTzDef _desc1;
};

struct _TPrule_020
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPNcoaddDef _desc1;
};

struct _TPrule_019
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPIzDef _desc1;
};

struct _TPrule_018
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPICOSRateDef _desc1;
};

struct _TPrule_017
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPICOSRamp _desc1;
};

struct _TPrule_016
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPICOSNsampleDef _desc1;
};

struct _TPrule_015
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDAC3def _desc1;
};

struct _TPrule_014
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const53;
PTGNode _AT_const54;
int _AT_const55;
_TSPRingCmd _desc1;
};

struct _TPrule_013
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _AT_const53;
PTGNode _AT_const54;
int _AT_const55;
_TSPG4 _desc1;
_TSPRingCmd _desc2;
};

struct _TPrule_012
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
long _AT_const69;
double _AT_const70;
int _AT_cICOSRampCount_post;
int _ATrcnt_post;
_TSPICOSCmd _desc1;
};

struct _TPrule_011
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
long _AT_const69;
double _AT_const70;
int _AT_cICOSRampCount_post;
int _ATrcnt_post;
_TSPG3 _desc1;
_TSPICOSCmd _desc2;
};

struct _TPrule_010
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG2 _desc1;
_TSPConfigCmd _desc2;
};

struct _TPrule_09
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_08
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPWave _desc1;
};

struct _TPrule_07
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
_TSPWave _desc2;
};

struct _TPrule_06
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDigitizerType _desc1;
};

struct _TPrule_05
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDAC3Value _desc1;
};

struct _TPrule_04
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG2 _desc1;
};

struct _TPrule_03
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPQCLIConfig _desc1;
};

struct _TPrule_02
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPrefix _desc1;
};

struct _TPrule_01
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPDigitizer _desc1;
};

#undef _NODECOMMON
#endif
