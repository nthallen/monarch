/* A template file for a main function */

#include "dasio/appid.h"
#include "oui.h"

DAS_IO::AppID_t AppID("boerf", "The boerf driver for the fuermflauz", "v1.0");

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  msg(0, "Startup %s, %s", AppID.fullname, AppID.rev);
  
  //do_the_work();
  
  msg(0, "Termination");
  return 0;
}