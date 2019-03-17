/** @file cmd_version.cc */
#include <stdio.h>
#include <stdlib.h>
#include "dasio/cmd_version.h"

void ci_report_version() {
  printf( "%s\n", ci_version );
  exit(0);
}
