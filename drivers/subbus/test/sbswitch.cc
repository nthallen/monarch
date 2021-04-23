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

int main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  uint16_t sw;
  uint16_t mask = 0xF;
  uint16_t addr = 0x7;

  if ( switch_mask ) {
    unsigned long tmp_mask = strtoul(switch_mask,NULL,0);
    mask = (uint16_t)tmp_mask;
  }
  
  if (subbus_addr) {
    unsigned long tmp_addr = strtoul(subbus_addr,NULL,0);
    addr = (uint16_t)tmp_addr;
  }

  subbuspp *SB = new subbuspp(subbus_svc, subbus_subsvc);
  if (SB->load()) {
    sw = ((SB->read_subbus(addr) & mask) | ~mask) & 0xFF;
    printf( "%02X\n", sw );
  } else {
    msg( 3, "Unable to load %s/%s", subbus_svc, subbus_subsvc);
  }
  return 0;
}
