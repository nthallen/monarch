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
  case 1: _nst[_nsp]=Mkrule_4(&curpos, _nst[_nsp+0]); break;
  case 2: _nsp -= 1;_nst[_nsp]=Mkrule_3(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 3: _nsp -= 1;_nst[_nsp]=Mkrule_9(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 4: _nst[_nsp]=Mkrule_8(&curpos, Mkrule_7(&(T_POS(TokenStack(0))), MkBareWord(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))), _nst[_nsp+0]); break;
  case 5: _nst[_nsp]=Mkrule_12(&curpos, _nst[_nsp+0]); break;
  case 6: _nst[_nsp]=Mkrule_15(&curpos, _nst[_nsp+0]); break;
  case 7: _nst[_nsp]=Mkrule_13(&curpos, _nst[_nsp+0]); break;
  case 8: _nst[_nsp]=Mkrule_11(&curpos, _nst[_nsp+0]); break;
  case 9: _nst[_nsp]=Mkrule_16(&curpos, _nst[_nsp+0]); break;
  case 10: _nst[_nsp]=Mkrule_14(&curpos, _nst[_nsp+0]); break;
  case 11: _nst[_nsp]=Mkrule_15(&curpos, _nst[_nsp+0]); break;
  case 12: _nst[_nsp]=Mkrule_035(&curpos, _nst[_nsp+0]); break;
  case 13: _nst[_nsp]=Mkrule_21(&curpos, _nst[_nsp+0]); break;
  case 14: _nst[_nsp]=Mkrule_09(&curpos, _nst[_nsp+0]); break;
  case 15: _nst[_nsp]=Mkrule_013(&curpos, _nst[_nsp+0]); break;
  case 16: _nst[_nsp]=Mkrule_10(&curpos, _nst[_nsp+0]); break;
  case 17: _nst[_nsp]=Mkrule_014(&curpos, _nst[_nsp+0]); break;
  case 18: _nst[_nsp]=Mkrule_015(&curpos, _nst[_nsp+0]); break;
  case 19: _nst[_nsp]=Mkrule_034(&curpos, _nst[_nsp+0]); break;
  case 20: _nst[_nsp]=Mkrule_06(&curpos, _nst[_nsp+0]); break;
  case 21: _nst[_nsp]=Mkrule_02(&curpos, _nst[_nsp+0]); break;
  case 22: _nsp -= 1;_nst[_nsp]=Mkrule_012(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 23: _nsp -= 1;_nst[_nsp]=Mkrule_08(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 24: _nst[_nsp]=Mkrule_016(&curpos, _nst[_nsp+0]); break;
  case 25: _nst[_nsp]=Mkrule_12(&curpos, _nst[_nsp+0]); break;
  case 26: _nst[_nsp]=Mkrule_15(&curpos, _nst[_nsp+0]); break;
  case 27: _nst[_nsp]=Mkrule_13(&curpos, _nst[_nsp+0]); break;
  case 28: _nst[_nsp]=Mkrule_11(&curpos, _nst[_nsp+0]); break;
  case 29: _nst[_nsp]=Mkrule_16(&curpos, _nst[_nsp+0]); break;
  case 30: _nst[_nsp]=Mkrule_14(&curpos, _nst[_nsp+0]); break;
  case 31: _nst[_nsp]=Mkrule_28(&curpos, _nst[_nsp+0]); break;
  case 32: _nst[_nsp]=Mkrule_27(&curpos, _nst[_nsp+0]); break;
  case 33: _nsp -= 1;_nst[_nsp]=Mkrule_07(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 34: _nst[_nsp]=Mkrule_023(&curpos, _nst[_nsp+0]); break;
  case 35: _nst[_nsp]=Mkrule_022(&curpos, _nst[_nsp+0]); break;
  case 36: _nsp -= 2;_nst[_nsp]=Mkrule_01(&curpos, _nst[_nsp+0], _nst[_nsp+1], _nst[_nsp+2]); break;
  case 37: _nsp -= 1;_nst[_nsp]=Mkrule_04(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 38: _nsp -= 1;_nst[_nsp]=Mkrule_033(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 39: _nsp -= 1;_nst[_nsp]=Mkrule_011(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 40: _nsp -= 1;_nst[_nsp]=Mkrule_021(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 41: _nsp -= 1;_nst[_nsp]=Mkrule_17(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 42: _incrnodestack();_nst[_nsp]=Mkrule_1(&curpos); break;
  case 44: _incrnodestack();_nst[_nsp]=Mkrule_25(&curpos, MkCString(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 45: _nsp -= 1;_nst[_nsp]=Mkrule_2(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 46: _incrnodestack();_nst[_nsp]=Mkrule_22(&curpos); break;
  case 47: _incrnodestack();_nst[_nsp]=Mkrule_23(&curpos); break;
  case 48: _incrnodestack();_nst[_nsp]=Mkrule_030(&curpos); break;
  case 49: _incrnodestack();_nst[_nsp]=Mkrule_33(&curpos, MkCString(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 50: _incrnodestack();_nst[_nsp]=Mkrule_025(&curpos); break;
  case 51: _incrnodestack();_nst[_nsp]=Mkrule_34(&curpos, MkBareWord(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 52: _incrnodestack();_nst[_nsp]=Mkrule_26(&curpos, MkRuleString(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 53: _incrnodestack();_nst[_nsp]=Mkrule_24(&curpos, MkInteger(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 54: _nst[_nsp]=Mkrule_024(&curpos, _nst[_nsp+0]); break;
  case 55: _incrnodestack();_nst[_nsp]=Mkrule_30(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 56: _nst[_nsp]=Mkrule_036(&curpos, _nst[_nsp+0]); break;
  case 57: _nst[_nsp]=Mkrule_032(&curpos, _nst[_nsp+0]); break;
  case 58: _nst[_nsp]=Mkrule_028(&curpos, _nst[_nsp+0]); break;
  case 59: _nst[_nsp]=Mkrule_029(&curpos, _nst[_nsp+0]); break;
  case 60: _nsp -= 1;_nst[_nsp]=Mkrule_03(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 61: _incrnodestack();_nst[_nsp]=Mkrule_19(&curpos); break;
  case 62: _incrnodestack();_nst[_nsp]=Mkrule_017(&curpos); break;
  case 63: _incrnodestack();_nst[_nsp]=Mkrule_6(&curpos, Mkrule_5(&(T_POS(TokenStack(1))), MkBareWord(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1))))); break;
  case 64: _incrnodestack();_nst[_nsp]=Mkrule_010(&curpos); break;
  case 65: _nst[_nsp]=Mkrule_05(&curpos, _nst[_nsp+0]); break;
  case 66: _nst[_nsp]=Mkrule_031(&curpos, _nst[_nsp+0]); break;
  case 67: _nsp -= 1;_nst[_nsp]=Mkrule_20(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 68: _nst[_nsp]=Mkrule_019(&curpos, _nst[_nsp+0]); break;
  case 69: _nst[_nsp]=Mkrule_020(&curpos, _nst[_nsp+0]); break;
  case 70: _nst[_nsp]=Mkrule_026(&curpos, _nst[_nsp+0]); break;
  case 71: _incrnodestack();_nst[_nsp]=Mkrule_027(&curpos); break;
  case 72: _incrnodestack();_nst[_nsp]=Mkrule_29(&curpos, MkInteger(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1)))); break;
  case 73: _nst[_nsp]=Mkrule_18(&curpos, _nst[_nsp+0]); break;
  case 74: _nst[_nsp]=Mkrule_018(&curpos, _nst[_nsp+0]); break;
  } /* end switch */
}
