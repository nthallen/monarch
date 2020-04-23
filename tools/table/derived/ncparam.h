#ifndef NCPARAM_H_INCLUDED
#define NCPARAM_H_INCLUDED

void Setupncurses(int preview, char *name, int w, int h);
void preview_label( PTG_OUTPUT_FILE f, const char *str, int a, int r, int c );
void preview_field( PTG_OUTPUT_FILE f, int r, int c, int w );
void preview_loop( PTG_OUTPUT_FILE f );
void preview_vrule( PTG_OUTPUT_FILE f, int a, int r, int c, int rule_id );
void preview_hrule( PTG_OUTPUT_FILE f, int a, int r, int c, int rule_id );

#endif
