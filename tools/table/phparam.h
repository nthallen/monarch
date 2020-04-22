#ifndef PHPARAM_H_INCLUDED
#define PHPARAM_H_INCLUDED

void preview_window( PTG_OUTPUT_FILE f, const char *name, int w, int h );
void preview_label( PTG_OUTPUT_FILE f, const char *str, int r, int c );
void preview_field( PTG_OUTPUT_FILE f, int fldnum, int r, int c, int w, int h );
void preview_loop( PTG_OUTPUT_FILE f );
void preview_vrule( PTG_OUTPUT_FILE f, int r, int c, int h, int dbl );
void preview_hrule( PTG_OUTPUT_FILE f, int r, int c, int w, int dbl );

#endif
