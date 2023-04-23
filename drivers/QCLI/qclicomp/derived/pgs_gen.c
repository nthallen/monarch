#include "gsdescr.h"
#include "treestack.h"
#include "HEAD.h"

#define TokenStack(i)	(ZAttributKeller[(i)])

#ifdef RIGHTCOORD
extern POSITION rightpos;
#endif

#if defined(__cplusplus) || defined(__STDC__) 
void
StrukturAnknuepfung(unsigned PR, GRUNDSYMBOLDESKRIPTOR *ZAttributKeller)
#else
void
StrukturAnknuepfung(PR, ZAttributKeller)
unsigned  PR;
register GRUNDSYMBOLDESKRIPTOR  *ZAttributKeller;
#endif
{
  curpos = ZAttributKeller->Pos;
#ifdef RIGHTCOORD
  RLineOf (curpos) = RLineOf (rightpos);
  RColOf (curpos) = RColOf (rightpos);
#ifdef MONITOR
  RCumColOf (curpos) = RCumColOf (rightpos);
#endif
#endif
  switch (PR) {
  case 1: _nsp -= 1;_nst[_nsp]=Mkrule_010(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 2: _nst[_nsp]=Mkrule_01(&curpos, _nst[_nsp+0]); break;
  case 3: _nst[_nsp]=Mkrule_02(&curpos, _nst[_nsp+0]); break;
  case 4: _nst[_nsp]=Mkrule_03(&curpos, _nst[_nsp+0]); break;
  case 5: _nst[_nsp]=Mkrule_08(&curpos, _nst[_nsp+0]); break;
  case 6: _nst[_nsp]=Mkrule_061(&curpos, _nst[_nsp+0]); break;
  case 7: _nst[_nsp]=Mkrule_062(&curpos, _nst[_nsp+0]); break;
  case 8: _nsp -= 1;_nst[_nsp]=Mkrule_07(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 9: _nst[_nsp]=Mkrule_015(&curpos, _nst[_nsp+0]); break;
  case 10: _nst[_nsp]=Mkrule_016(&curpos, _nst[_nsp+0]); break;
  case 11: _nst[_nsp]=Mkrule_017(&curpos, _nst[_nsp+0]); break;
  case 12: _nst[_nsp]=Mkrule_018(&curpos, _nst[_nsp+0]); break;
  case 13: _nst[_nsp]=Mkrule_019(&curpos, _nst[_nsp+0]); break;
  case 14: _nst[_nsp]=Mkrule_020(&curpos, _nst[_nsp+0]); break;
  case 15: _nst[_nsp]=Mkrule_021(&curpos, _nst[_nsp+0]); break;
  case 16: _nst[_nsp]=Mkrule_022(&curpos, _nst[_nsp+0]); break;
  case 17: _nst[_nsp]=Mkrule_024(&curpos, _nst[_nsp+0]); break;
  case 18: _nst[_nsp]=Mkrule_025(&curpos, _nst[_nsp+0]); break;
  case 19: _nst[_nsp]=Mkrule_039(&curpos, _nst[_nsp+0]); break;
  case 20: _nst[_nsp]=Mkrule_040(&curpos, _nst[_nsp+0]); break;
  case 21: _nst[_nsp]=Mkrule_041(&curpos, _nst[_nsp+0]); break;
  case 22: _nst[_nsp]=Mkrule_052(&curpos, _nst[_nsp+0]); break;
  case 23: _nst[_nsp]=Mkrule_053(&curpos, _nst[_nsp+0]); break;
  case 24: _nst[_nsp]=Mkrule_042(&curpos, _nst[_nsp+0]); break;
  case 25: _nst[_nsp]=Mkrule_043(&curpos, _nst[_nsp+0]); break;
  case 26: _nst[_nsp]=Mkrule_044(&curpos, _nst[_nsp+0]); break;
  case 27: _nst[_nsp]=Mkrule_045(&curpos, _nst[_nsp+0]); break;
  case 28: _nst[_nsp]=Mkrule_046(&curpos, _nst[_nsp+0]); break;
  case 29: _nst[_nsp]=Mkrule_047(&curpos, _nst[_nsp+0]); break;
  case 30: _nst[_nsp]=Mkrule_026(&curpos, _nst[_nsp+0]); break;
  case 31: _nsp -= 1;_nst[_nsp]=Mkrule_22(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 32: _nst[_nsp]=Mkrule_027(&curpos, _nst[_nsp+0]); break;
  case 33: _nsp -= 1;_nst[_nsp]=Mkrule_21(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 34: _nst[_nsp]=Mkrule_028(&curpos, _nst[_nsp+0]); break;
  case 35: _nst[_nsp]=Mkrule_13(&curpos, _nst[_nsp+0]); break;
  case 36: _nst[_nsp]=Mkrule_15(&curpos, _nst[_nsp+0]); break;
  case 37: _nst[_nsp]=Mkrule_10(&curpos, _nst[_nsp+0]); break;
  case 38: _nst[_nsp]=Mkrule_060(&curpos, _nst[_nsp+0]); break;
  case 39: _nst[_nsp]=Mkrule_05(&curpos, _nst[_nsp+0]); break;
  case 40: _nst[_nsp]=Mkrule_050(&curpos, _nst[_nsp+0]); break;
  case 41: _nst[_nsp]=Mkrule_051(&curpos, _nst[_nsp+0]); break;
  case 42: _nst[_nsp]=Mkrule_057(&curpos, _nst[_nsp+0]); break;
  case 43: _nst[_nsp]=Mkrule_7(&curpos, _nst[_nsp+0]); break;
  case 44: _nst[_nsp]=Mkrule_058(&curpos, _nst[_nsp+0]); break;
  case 45: _nst[_nsp]=Mkrule_5(&curpos, _nst[_nsp+0]); break;
  case 46: _nst[_nsp]=Mkrule_059(&curpos, _nst[_nsp+0]); break;
  case 47: _nsp -= 1;_nst[_nsp]=Mkrule_39(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 48: _nsp -= 2;_nst[_nsp]=Mkrule_24(&curpos, _nst[_nsp+0], _nst[_nsp+1], _nst[_nsp+2]); break;
  case 49: _nst[_nsp]=Mkrule_036(&curpos, _nst[_nsp+0]); break;
  case 50: _nst[_nsp]=Mkrule_037(&curpos, _nst[_nsp+0]); break;
  case 51: _nsp -= 1;_nst[_nsp]=Mkrule_38(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 52: _nst[_nsp]=Mkrule_28(&curpos, _nst[_nsp+0]); break;
  case 53: _nsp -= 1;_nst[_nsp]=Mkrule_16(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2))), _nst[_nsp+0], _nst[_nsp+1]); break;
  case 54: _nsp -= 1;_nst[_nsp]=Mkrule_25(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 55: _nst[_nsp]=Mkrule_1(&curpos, _nst[_nsp+0]); break;
  case 56: _nst[_nsp]=Mkrule_054(&curpos, _nst[_nsp+0]); break;
  case 57: _nst[_nsp]=Mkrule_055(&curpos, _nst[_nsp+0]); break;
  case 58: _incrnodestack();_nst[_nsp]=Mkrule_09(&curpos); break;
  case 59: _nst[_nsp]=Mkrule_04(&curpos, _nst[_nsp+0]); break;
  case 61: _incrnodestack();_nst[_nsp]=Mkrule_43(&curpos); break;
  case 62: _incrnodestack();_nst[_nsp]=Mkrule_42(&curpos); break;
  case 63: _incrnodestack();_nst[_nsp]=Mkrule_41(&curpos); break;
  case 64: _incrnodestack();_nst[_nsp]=Mkrule_47(&curpos); break;
  case 65: _incrnodestack();_nst[_nsp]=Mkrule_46(&curpos); break;
  case 66: _incrnodestack();_nst[_nsp]=Mkrule_45(&curpos); break;
  case 67: _incrnodestack();_nst[_nsp]=Mkrule_49(&curpos); break;
  case 68: _incrnodestack();_nst[_nsp]=Mkrule_44(&curpos); break;
  case 69: _incrnodestack();_nst[_nsp]=Mkrule_48(&curpos); break;
  case 70: _nsp -= 1;_nst[_nsp]=Mkrule_056(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 71: _nst[_nsp]=Mkrule_06(&curpos, _nst[_nsp+0]); break;
  case 72: _incrnodestack();_nst[_nsp]=Mkrule_40(&curpos, MkIdent(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 73: _nst[_nsp]=Mkrule_038(&curpos, _nst[_nsp+0]); break;
  case 74: _incrnodestack();_nst[_nsp]=Mkrule_029(&curpos); break;
  case 75: _incrnodestack();_nst[_nsp]=Mkrule_030(&curpos); break;
  case 76: _incrnodestack();_nst[_nsp]=Mkrule_031(&curpos); break;
  case 77: _incrnodestack();_nst[_nsp]=Mkrule_032(&curpos); break;
  case 78: _incrnodestack();_nst[_nsp]=Mkrule_033(&curpos); break;
  case 79: _incrnodestack();_nst[_nsp]=Mkrule_034(&curpos); break;
  case 80: _nst[_nsp]=Mkrule_012(&curpos, _nst[_nsp+0]); break;
  case 81: _nst[_nsp]=Mkrule_023(&curpos, _nst[_nsp+0]); break;
  case 82: _nst[_nsp]=Mkrule_52(&curpos, Mkrule_50(&(T_POS(TokenStack(2))), MkIdent(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))), _nst[_nsp+0]); break;
  case 83: _nst[_nsp]=Mkrule_014(&curpos, _nst[_nsp+0]); break;
  case 84: _nst[_nsp]=Mkrule_048(&curpos, _nst[_nsp+0]); break;
  case 85: _nst[_nsp]=Mkrule_51(&curpos, Mkrule_50(&(T_POS(TokenStack(2))), MkIdent(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))), _nst[_nsp+0]); break;
  case 86: _incrnodestack();_nst[_nsp]=Mkrule_27(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 87: _incrnodestack();_nst[_nsp]=Mkrule_26(&curpos, MkFloat(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 88: _nst[_nsp]=Mkrule_17(&curpos, _nst[_nsp+0], MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 89: _nst[_nsp]=Mkrule_20(&curpos, _nst[_nsp+0], MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 90: _nsp -= 1;_nst[_nsp]=Mkrule_011(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 91: _nsp -= 1;_nst[_nsp]=Mkrule_013(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 92: _incrnodestack();_nst[_nsp]=Mkrule_37(&curpos); break;
  case 93: _incrnodestack();_nst[_nsp]=Mkrule_36(&curpos); break;
  case 94: _incrnodestack();_nst[_nsp]=Mkrule_35(&curpos); break;
  case 95: _nsp -= 1;_nst[_nsp]=Mkrule_23(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 96: _incrnodestack();_nst[_nsp]=Mkrule_31(&curpos); break;
  case 97: _incrnodestack();_nst[_nsp]=Mkrule_29(&curpos); break;
  case 98: _incrnodestack();_nst[_nsp]=Mkrule_30(&curpos); break;
  case 99: _incrnodestack();_nst[_nsp]=Mkrule_11(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 100: _nst[_nsp]=Mkrule_035(&curpos, _nst[_nsp+0]); break;
  case 101: _incrnodestack();_nst[_nsp]=Mkrule_33(&curpos); break;
  case 102: _incrnodestack();_nst[_nsp]=Mkrule_34(&curpos); break;
  case 103: _incrnodestack();_nst[_nsp]=Mkrule_32(&curpos); break;
  case 104: _nst[_nsp]=Mkrule_8(&curpos, _nst[_nsp+0]); break;
  case 105: _incrnodestack();_nst[_nsp]=Mkrule_9(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 106: _nst[_nsp]=Mkrule_049(&curpos, _nst[_nsp+0]); break;
  case 107: _nst[_nsp]=Mkrule_6(&curpos, _nst[_nsp+0]); break;
  case 108: _incrnodestack();_nst[_nsp]=Mkrule_4(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 109: _incrnodestack();_nst[_nsp]=Mkrule_19(&curpos); break;
  case 110: _incrnodestack();_nst[_nsp]=Mkrule_12(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 111: _incrnodestack();_nst[_nsp]=Mkrule_18(&curpos, MkInteger(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 112: _incrnodestack();_nst[_nsp]=Mkrule_2(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 113: _nsp -= 2;_nst[_nsp]=Mkrule_3(&curpos, _nst[_nsp+0], _nst[_nsp+1], _nst[_nsp+2]); break;
  } /* end switch */
}
