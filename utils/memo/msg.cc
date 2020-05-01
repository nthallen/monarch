#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "dasio/appid.h"
#include "oui.h"
#include "nl.h"
#include "dasio/msg.h"
#include "msg_internal.h"

/**
 * This program should serve as a command-line utility
 * to print a one-off message to memo.
 */

DAS_IO::AppID_t DAS_IO::AppID("msg", "msg internal client", "V1.0");

int main(int argc, char** argv) {
  oui_init_options(argc,argv);
  
  std::string message = "";
  
  /* This loop adds every word after the cmd options onto a string. */
  for (int i = optind; i < argc; i++) {
    message.append(argv[i]);
    message.append(" ");
  }
  
	const char *messagech = message.c_str();
	
  /* Then, it prints the message to memo, or wherever. */
  msg(MSG,messagech);
}
