
/* encoding of tree node types and symbols */

#ifndef NODECODE_H
#define NODECODE_H

extern int LHSMAP[];

#define IsSymb(_n,_c) (LHSMAP[(_n)->_prod] == (_c))

#define SYMBRingCmd 0
#define SYMBG4 1
#define SYMBICOSCmd 2
#define SYMBG3 3
#define SYMBG1 4
#define SYMBDAC3def 5
#define SYMBG2 6
#define SYMBConfigCmds 7
#define SYMBQCLIConfig 8
#define SYMBDigitizer 9
#define SYMBConfigCmd 10
#define SYMBRingStepsize 11
#define SYMBRingCount 12
#define SYMBRingStep 13
#define SYMBCurrentSteps 14
#define SYMBRingCurrent 15
#define SYMBTpreVal 16
#define SYMBTonVal 17
#define SYMBTpreDef 18
#define SYMBTonDef 19
#define SYMBRingNsampleDef 20
#define SYMBToffDef 21
#define SYMBRingRateDef 22
#define SYMBRingData 23
#define SYMBDAC3Value 24
#define SYMBSampleSpec 25
#define SYMBTzTime 26
#define SYMBTzSpec 27
#define SYMBRateDef 28
#define SYMBNsample 29
#define SYMBNsampleDef 30
#define SYMBNaverage 31
#define SYMBNcoadd 32
#define SYMBICOSRamp 33
#define SYMBdIdt 34
#define SYMBPrepTime 35
#define SYMBIstop 36
#define SYMBIstart 37
#define SYMBPercent 38
#define SYMBRateUnit 39
#define SYMBTimeUnit 40
#define SYMBTime 41
#define SYMBCurrentUnit 42
#define SYMBFloatVal 43
#define SYMBCurrent 44
#define SYMBICOSRateDef 45
#define SYMBICOSNsampleDef 46
#define SYMBNcoaddDef 47
#define SYMBIzDef 48
#define SYMBTzDef 49
#define SYMBPrefix 50
#define SYMBDigitizerType 51
#define SYMBQCLIConfigType 52
#define SYMBSourceFile 53
#define SYMBWave 54
#define SYMBRingCmds 55
#define SYMBRingWave 56
#define SYMBICOSCmds 57
#define SYMBDefIdent 58
#define SYMBICOSWave 59
#define RULErule_011 0
#define RULErule_012 1
#define RULErule_015 2
#define RULErule_016 3
#define RULErule_017 4
#define RULErule_018 5
#define RULErule_019 6
#define RULErule_020 7
#define RULErule_021 8
#define RULErule_022 9
#define RULErule_24 10
#define RULErule_23 11
#define RULErule_22 12
#define RULErule_21 13
#define RULErule_048 14
#define RULErule_51 15
#define RULErule_05 16
#define RULErule_07 17
#define RULErule_08 18
#define RULErule_013 19
#define RULErule_014 20
#define RULErule_039 21
#define RULErule_040 22
#define RULErule_041 23
#define RULErule_042 24
#define RULErule_043 25
#define RULErule_044 26
#define RULErule_045 27
#define RULErule_046 28
#define RULErule_047 29
#define RULErule_060 30
#define RULErule_061 31
#define RULErule_062 32
#define RULErule_52 33
#define RULErule_9 34
#define RULErule_8 35
#define RULErule_01 36
#define RULErule_02 37
#define RULErule_03 38
#define RULErule_04 39
#define RULErule_06 40
#define RULErule_09 41
#define RULErule_010 42
#define RULErule_023 43
#define RULErule_024 44
#define RULErule_025 45
#define RULErule_028 46
#define RULErule_038 47
#define RULErule_50 48
#define RULErule_49 49
#define RULErule_48 50
#define RULErule_47 51
#define RULErule_46 52
#define RULErule_45 53
#define RULErule_44 54
#define RULErule_43 55
#define RULErule_42 56
#define RULErule_41 57
#define RULErule_40 58
#define RULErule_25 59
#define RULErule_20 60
#define RULErule_15 61
#define RULErule_13 62
#define RULErule_10 63
#define RULErule_026 64
#define RULErule_027 65
#define RULErule_029 66
#define RULErule_030 67
#define RULErule_031 68
#define RULErule_032 69
#define RULErule_033 70
#define RULErule_034 71
#define RULErule_035 72
#define RULErule_036 73
#define RULErule_037 74
#define RULErule_049 75
#define RULErule_050 76
#define RULErule_051 77
#define RULErule_052 78
#define RULErule_053 79
#define RULErule_054 80
#define RULErule_055 81
#define RULErule_056 82
#define RULErule_057 83
#define RULErule_058 84
#define RULErule_059 85
#define RULErule_39 86
#define RULErule_38 87
#define RULErule_37 88
#define RULErule_36 89
#define RULErule_35 90
#define RULErule_34 91
#define RULErule_33 92
#define RULErule_32 93
#define RULErule_31 94
#define RULErule_30 95
#define RULErule_29 96
#define RULErule_28 97
#define RULErule_27 98
#define RULErule_26 99
#define RULErule_19 100
#define RULErule_18 101
#define RULErule_17 102
#define RULErule_16 103
#define RULErule_14 104
#define RULErule_12 105
#define RULErule_11 106
#define RULErule_7 107
#define RULErule_6 108
#define RULErule_5 109
#define RULErule_4 110
#define RULErule_3 111
#define RULErule_2 112
#define RULErule_1 113
#endif
