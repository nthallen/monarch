#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "dasio/appid.h"
#include "oui.h"
#include "nl.h"
#include "test_msg.h"

DAS_IO::AppID_t DAS_IO::AppID("test_msg", "memo client", "V1.0");

int main(int argc, char** argv) {
  //create a test client, connect?
  
  oui_init_options(argc,argv);
  nl_error(MSG,"Hello?");
  nl_error(MSG,"Hello again!");
  
}
