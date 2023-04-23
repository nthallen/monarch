/** @file subbus_mig.cc Migration library for DACS-era experiments */
#include "subbus_mig.h"

uint16_t subbus_subfunction;
uint16_t subbus_features;
uint16_t subbus_version;

subbus_mig::subbus_mig() : subbuspp("subbus", 0) {}

subbus_mig::~subbus_mig() {
  sb = 0;
}

subbus_mig * subbus_mig::sb;

int subbus_mig::load_subbus() {
  if (!sb) {
    sb = new subbus_mig();
  }
  ::subbus_subfunction = sb->load();
  ::subbus_features = sb->get_features();
  ::subbus_version = sb->get_version();
  return ::subbus_subfunction;
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
