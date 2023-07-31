#ifndef PTG_H1
#define PTG_H1
/* Had to use FILE * instead of PTG_OUTPUT_FILE because
   PTG_OUTPUT_FILE is not defined in ptg_gen.h until
   after this code is included, but this is the only
   way to get these definitions delivered to pteg_gen.c
   This would be a problem if I tried to redefine
   PTG_OUTPUT_FILE for some reason.
*/
extern void OutputLine(FILE *f, const char *s);
extern void ptg_output_word(FILE *file, unsigned short value, int count );
#define ptg_output_hex( f, v, c ) ptg_output_word(f,(unsigned short)v,c)

#define PTG_OUTPUT_SHORT(file,value) ptg_output_short(file,value)
#define PTG_OUTPUT_HEX(f,v,c) ptg_output_word(f,(short)(v),c)
#define PTG_OUTPUT_1HEX(f,v) ptg_output_word(f,(short)(v),1)
#define PTG_OUTPUT_1LHEX(f,v) PTG_OUTPUT_HEX(f,v,1)
#define PTG_OUTPUT_ICOSHEX(f,v,c) PTG_OUTPUT_HEX(f,(v)^0x001,c)
#define PTG_OUTPUT_STRING(file,param) OutputLine(file,param)
#endif

#ifndef PTG_H2
#define PTG_H2
/* To influence the output of PTG, write definitions of the
 * PTG-Output-Macros into a .ptg.phi-file and include it into
 * your .specs-file. Read (ptg)Macros. for further information.
 */
#endif

