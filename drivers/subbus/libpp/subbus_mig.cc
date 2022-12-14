/** @file subbus_mig.cc Migration library for DACS-era experiments */
#include "subbus_mig.h"

subbus_mig::subbus_mig

int subbus_mig::load_subbus() {
  if (!sb) {
    sb = new subbus_mig();
  }
  return sb->load();
}

/** Internal function to handle read_switches() and read_failure(),
  which take no arguments, return unsigned short or zero if
  the function is not supported.
  */
uint16_t subbus_mig::read_special(uint16_t command) {
  int rv;
  rv = send_to_subbusd(command, NULL, 0, SBRT_US);
  return (rv == SBS_OK) ? sb_reply.data.value : 0;
}

uint16_t subbus_mig::sbrb(uint16_t addr) {
  uint16_t word;
  
  word = read_subbus(addr);
  return ((addr&1) ? word>>8 : word) & 0xFF;
}

/* returns zero if no acknowledge */
uint16_t subbus_mig::sbrba(uint16_t addr) {
  uint16_t word;
  
  if (read_ack(addr, &word)) {
    if (addr & 1) word >>= 8;
    return word & 0xFF;
  } else return 0;
}

uint16_t subbus_mig::sbrwa(uint16_t addr) {
  uint16_t word;
  return read_ack(addr, &word) ? word : 0;
}
