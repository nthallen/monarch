#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "nl.h"
#include "subbuspp.h"
#include "oui.h"

const char *subbus_svc = "subbus";
const char *subbus_subsvc = "serusb";
const char *subbus_addr = 0;
const char *switch_mask = 0;
const char *switch_invert = 0;
bool quit_if_nonzero = false;

void sbswitch_args(const char *arg) {
  if (switch_invert) {
    msg(3, "Expected no more than two parameters");
  } else if (switch_mask) {
    switch_invert = arg;
  } else {
    switch_mask = arg;
  }
}

int main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  uint16_t sw = 0xFF;
  uint16_t mask = 0xF;
  uint16_t addr = 0x7;
  uint16_t invert = 0;
  int rv = quit_if_nonzero ? 1 : 0; // default to flight mode

  if ( switch_mask ) {
    unsigned long tmp_mask = strtoul(switch_mask,NULL,0);
    mask = (uint16_t)tmp_mask;
  }

  if ( switch_invert ) {
    unsigned long tmp_invert = strtoul(switch_invert,NULL,0);
    invert = (uint16_t)tmp_invert;
  }
  
  if (subbus_addr) {
    unsigned long tmp_addr = strtoul(subbus_addr,NULL,0);
    addr = (uint16_t)tmp_addr;
  }

  subbuspp *SB = new subbuspp(subbus_svc, subbus_subsvc);
  if (SB->load()) {
    sw = (((SB->read_subbus(addr) & mask) | ~mask) ^ invert) & 0xFF;
  } else {
    msg(2, "Unable to load %s/%s", subbus_svc, subbus_subsvc);
  }
  if (quit_if_nonzero) {
    if (sw != 0xFF ) {
      SB->subbus_quit();
      rv = 0; // not flight mode
    }
  } else {
    printf( "%02X\n", sw );
  }
  return rv;
}
