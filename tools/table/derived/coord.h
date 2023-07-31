#ifndef COORD_H
#define COORD_H

/* Copyright 2018, The Regents of the University of Colorado */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

#include "eliproto.h"

	/* Types exported by the Coordinate Module */

typedef struct {	/* Source text coordinates */
	int line;	   /* Left line number */
	int col;	   /* Left character position */
#ifdef RIGHTCOORD
	int rline;	   /* Right line number */
	int rcol;	   /* Right character position */
#endif
#ifdef MONITOR
	int cumcol;	   /* Left cumulative chararcter position */
	int rcumcol;	   /* Right cumulative chararcter position */
#endif
} POSITION;

typedef POSITION *CoordPtr;

#define NoPosition	((POSITION *)0)
#define LineOf(pos)     ((pos).line)
#define ColOf(pos)      ((pos).col)
#ifdef RIGHTCOORD
#define RLineOf(pos)    ((pos).rline)
#define RColOf(pos)     ((pos).rcol)
#endif
#ifdef MONITOR
#define CumColOf(pos)	((pos).cumcol)
#define RCumColOf(pos)	((pos).rcumcol)
#endif

	/* Variables exported by the Coordinate Module */

extern int LineNum;	/* Index of the current line in the total source text */
extern char *StartLine;	/* Adjusted beginning of the current line */
extern POSITION NoCoord;  /* The NULL coordinate */
extern POSITION curpos;	/* Position variable for general use */

	/* Routines exported by the Coordinate Module */

extern int
earlier ELI_ARG((CoordPtr p, CoordPtr q));
/* Check relative position
 *    On exit-
 *       earlier != 0 if p defines a position in the source text that
 *          preceeds the position defined by q
 ***/

	/* Monitoring support for structured values */

#ifdef MONITOR
#define DAPTO_RESULTCoordPtr(p) DAPTO_RESULT_PTR(p)
#define DAPTO_ARGCoordPtr(p)    DAPTO_ARG_PTR(p, CoordPtr)

#define DAPTO_RESULTPOSITION(p) \
  DAPTO_RESULT_STR \
    (_dap_format ("%d,%d-%d,%d", LineOf(p), ColOf(p), RLineOf(p), RColOf(p)))
#endif

#endif

	/* Macros for setting curpos */

/* Set the coordinates of the current token
 *   On entry-
 *     LineNum=index of the current line in the entire source text
 *     p=index of the current column in the entire source line
 *   On exit-
 *     curpos has been updated to contain the current position as its
 *     left coordinate
 */
#ifndef SETCOORD
#ifdef MONITOR
#define SETCOORD(p) { LineOf (curpos) = LineNum; \
		      ColOf (curpos) = CumColOf (curpos) = (p); }
#else
#define SETCOORD(p) { LineOf (curpos) = LineNum; ColOf (curpos) = (p); }
#endif
#endif

#ifdef RIGHTCOORD
/* Set the coordinates of the end of the current token
 *   On entry-
 *     LineNum=index of the current line in the entire source text
 *     p=index of the current column in the entire source line
 *   On exit-
 *     curpos has been updated to contain the current position as its
 *     right coordinate
 */
#ifndef SETENDCOORD
#ifdef MONITOR
#define SETENDCOORD(p) { RLineOf (curpos) = LineNum; \
			 RColOf (curpos) = RCumColOf (curpos) = (p); }
#else
#define SETENDCOORD(p) { RLineOf (curpos) = LineNum; \
			 RColOf (curpos) = (p); }
#endif
#endif
#endif
