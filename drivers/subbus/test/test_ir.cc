/** @file test_can.cc
 * @brief Test interfaces to subbus modules
 */
#include <stdio.h>
#include <stdint.h>
#include <strings.h>
#include "dasio/appid.h"
#include "oui.h"
#include "subbuspp.h"
#include "nl.h"
#include "test_ir.h"

DAS_IO::AppID_t DAS_IO::AppID("test_IR", "IRMon Rev B (CAN) Test Program", "V1.0");

bool pwm_disable;
bool pwm_enable;
const char *pwm_period;
const char *pwm_duty_cycle;

typedef struct {
  uint16_t n_words;
  char name[0x50];
} device_name_t;

void identify_board(subbuspp *P, uint8_t bdid) {
  uint16_t bdid_hi = bdid<<8;
  msg(0,"read_ack(0x%02X02)", bdid);
  uint16_t value;
  if (! P->read_ack(bdid_hi | 0x02, &value)) {
    msg(2, "No acknowledge from board %d", bdid);
    return;
  }
  msg(0, "  Board ID: %u", value);
  value = P->read_subbus(bdid_hi | 0x04);
  msg(0, "  Board S/N:  %u", value);
  value = P->read_subbus(bdid_hi | 0x03);
  msg(0, "  Build No:   %u", value);
  value = P->read_subbus(bdid_hi | 0x05);
  msg(0, "  Inst ID:  %u", value);
  
  char mreqstr[30];
  snprintf(mreqstr, 30, "%X|28@%X", bdid_hi|6, bdid_hi|7);
  subbus_mread_req *mreq = P->pack_mread_request(0x29, mreqstr);
  device_name_t devname;
  uint16_t nread;
  int rv = P->mread_subbus_nw(mreq, (uint16_t*)&devname, &nread);
  if (rv < 0) {
    msg(2, "Error %d from mread", rv);
  } else {
    msg(0, "nr:%u/%u '%s'", nread, devname.n_words, &devname.name[0]);
  }
}

void test_ack(subbuspp *P, uint16_t addr) {
  // msg(0, "Test read from non-existant address on existing board");
  uint16_t value;
  if (! P->read_ack(addr, &value)) {
    msg(2, "No acknowledge from address 0x%04X", addr);
  } else {
    msg(0, "ACK from addr 0x%04X", addr);
  }
}

void test_nack(subbuspp *P, uint16_t addr) {
  // msg(0, "Test read from non-existant address on existing board");
  uint16_t value;
  if (! P->read_ack(addr, &value)) {
    msg(0, "No acknowledge from address 0x%04X", addr);
  } else {
    msg(2, "Unexpected ACK from addr 0x%04X", addr);
  }
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  subbuspp *P = new subbuspp("subbusd", "CAN");
  int subfunc = P->load();
  if (subfunc) {
    msg(0, "Subbus subfunction %d, name %s", subfunc, P->get_subbus_name());
  } else {
    msg(3, "Failed to connect with subbus");
  }

  identify_board(P, 1);
  
  uint16_t HeaterV = P->read_subbus(0x0121);
  uint16_t IRSetV = P->read_subbus(0x0122);
  uint16_t ADS_N = P->read_subbus(0x0123);
  msg(0, "  HeaterV: %5u", HeaterV);
  msg(0, "  IRSetV:  %5u", IRSetV);
  msg(0, "  ADS_N:   %5u", ADS_N);
  uint16_t PWM_Stat = P->read_subbus(0x0140);
  uint16_t PWM_Period = P->read_subbus(0x0141);
  uint16_t PWM_Duty_Cycle = P->read_subbus(0x0142);
  msg(0, "  PWM_Stat: %5u", PWM_Stat);
  msg(0, "  Period:   %5u", PWM_Period);
  msg(0, "  DutyCyc:  %5u", PWM_Duty_Cycle);
  
  if (pwm_disable) {
    P->write_ack(0x0140, 0);
    msg(0, "Disabling PWM");
  }
  if (pwm_enable) {
    P->write_ack(0x0140, 1);
    msg(0, "Enabling PWM");
  }
  if (pwm_period) {
    uint16_t per = strtoul(pwm_period, NULL, 10);
    P->write_ack(0x0141, per);
    msg(0, "Setting PWM period to %u", per);
  }
  if (pwm_duty_cycle) {
    uint16_t duty = strtoul(pwm_duty_cycle, NULL, 10);
    P->write_ack(0x0142, duty);
    msg(0, "Setting PWM duty cycle to %u", duty);
  }
  
  // P->subbus_quit();
  return 0;
}
