#include <stdlib.h>
#include "monarch_cmd.h"
#include "nl.h"
#include "oui.h"

using namespace DAS_IO;

const char *monarch_cmd;

void monarch_set_cmd(const char *cmd) {
  if (monarch_cmd) msg(3, "Only one command allowed");
  monarch_cmd = cmd;
}

void monarch_set_exp(const char *exp) {
  msg(MSG, "Setting Experiment to '%s'", exp);
  if ( setenv( "Experiment", exp, 1 ) )
    msg(MSG_FATAL, "Error from setenv" );
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  if (!monarch_cmd)
    msg(MSG_FATAL, "Must specify command text on the command line");
  if (cic_init())
    msg(MSG_FATAL, "cic_init() failed");
  int rv = ci_sendfcmd(Cmd_Send, "%s\n", monarch_cmd);
  msg(0, "Terminating: response code %d", rv);
  return 0;
}
