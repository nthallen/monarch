/* nl_error.c provides a default error routine for nortlib routines.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "nl.h"

/**
 * The default nl_error() function, which simply writes
 * output to stderr.
 * @param level The message severity code. See nl_error() for details.
 * @param s A printf-style format string.
 * @return For non-fatal messages, returns the error level code.
 */
int nl_err(int level, const char *s, ...) {
  va_list arg;

  va_start(arg, s);
  nl_verror(level, s, arg);
  va_end(arg);
  return(level);
}

/**
nl_error() is a retargettable standard error message function.
It is actually a function pointer which may be modified either
statically or dynamically as the application requires.

nl_error() functions provide standard printf-style formatting
for status messages. The level argument determines how the
message is handled:

Macro                   | Value | Meaning
------------------------|:-----:|--------
MSG                     | 0     | Informational Message
MSG_WARN                | 1     | Warning Message
MSG_ERROR               | 2     | Error Message
MAG_FATAL               | 3     | Fatal Error Message
MSG_EXIT_ABNORM         | 4     | Internal Fatal Error Message
MSG_EXIT                | -1    | Normal Exit with Message
MSG_DEBUG, MSG_DBG(0)   | -2    | Debug level 1 Message
MSG_DBG(1)              | -3    | Debug level 2 Message

Debug messages normally do not appear, but you can adjust the
debug level to see some or all of your debugging messages. For
the default functions nl_err() and nl_verror(), the current
debug level is stored in the variable nl_debug_level, which may
be adjustable by command line flags. For msg(), the debug level
is controlled via the -l flag and does not use
nl_debug_level.

The nortlib library provides a default function, nl_err(),
which reports warnings to stderr and normal messages to stdout.
The default function is included in the same module with the
default definition of the nl_error pointer. In order to
override the default, you must include your own definition of
nl_error and initialize it to point to your own function.

This is done automatically for programs developed using the ARP
Data Acquisition Systems architecture, where nl_error is mapped
to the msg() function, which routes messages to a central memo
utility. nl_error is also retargetted for many of our compilers
to a function which prints out the current input file name and
line number. It is then dynamically remapped to the default
when input processing is completed. RTG and other QNX
Windows-based programs remap nl_error to a function which pops
up a window.

The point here is that library functions can count on calling a
standard error message routine, and their messages will be
mapped to the correct output processor depending on the
application they are linked into.
  
@return For non-fatal errors, returns the error level code.
*/
int (*msg)(int level, const char *s, ...) = nl_err;
