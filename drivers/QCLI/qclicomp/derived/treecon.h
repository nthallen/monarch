
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MkRingCmd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG4 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkICOSCmd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG3 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG1 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDAC3def ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG2 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConfigCmds ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkQCLIConfig ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDigitizer ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConfigCmd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingStepsize ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingCount ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingStep ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkCurrentSteps ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingCurrent ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTpreVal ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTonVal ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTpreDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTonDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingNsampleDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkToffDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingRateDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingData ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDAC3Value ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkSampleSpec ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTzTime ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTzSpec ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRateDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNsample ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNsampleDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNaverage ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNcoadd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkICOSRamp ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkdIdt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPrepTime ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkIstop ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkIstart ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPercent ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRateUnit ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTimeUnit ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTime ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkCurrentUnit ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkFloatVal ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkCurrent ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkICOSRateDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkICOSNsampleDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkNcoaddDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkIzDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkTzDef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPrefix ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDigitizerType ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkQCLIConfigType ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkSourceFile ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkWave ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingCmds ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkRingWave ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkICOSCmds ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkDefIdent ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkICOSWave ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_3 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_4 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_5 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_6 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_7 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_8 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_9 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_10 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_11 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_12 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_13 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_14 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_15 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_16 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_17 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, int _TERM1));
extern NODEPTR Mkrule_18 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_19 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_20 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, int _TERM1));
extern NODEPTR Mkrule_21 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_22 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_23 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_24 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3));
extern NODEPTR Mkrule_25 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_26 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_27 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_28 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_29 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_30 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_31 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_32 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_33 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_34 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_35 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_36 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_37 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_38 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_39 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_40 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_41 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_42 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_43 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_44 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_45 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_46 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_47 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_48 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_49 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_50 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_51 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_52 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_062 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_061 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_060 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_059 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_058 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_057 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_056 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_055 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_054 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_053 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_052 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_051 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_050 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_049 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_048 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_047 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_046 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_045 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_044 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_043 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_042 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_041 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_040 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_039 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_038 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_037 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_036 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_035 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_034 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_033 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_032 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_031 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_030 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_029 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_028 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_027 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_026 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_025 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_024 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_023 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_022 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_021 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_020 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_019 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_018 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_017 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_016 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_015 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_014 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_013 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_012 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_011 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_010 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_09 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_08 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_07 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_06 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_05 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_04 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_03 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_02 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_01 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
#define MkIdent(pos,val) (val)
#define MkFloat(pos,val) (val)
#define MkInteger(pos,val) (val)
#endif
