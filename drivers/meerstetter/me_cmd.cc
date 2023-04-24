#include <stdio.h>
#include "meerstetter_int.h"
#include "meerstetter.h"
#include "dasio/msg.h"
#include "nl.h"

/*
 * Cmd client: Me_Cmd -> Cmd_Selectee
 * TM client: TM_Selectee
 * Serial client: Me_Ser -> Ser_Selectee
 */

static const char *cmd_name(const char *name) {
  static char nbuf[80];
  int nc = snprintf(nbuf,80,"cmd/%s", name);
  if (nc >= 80)
    msg(MSG_FATAL, "Name length exceeded in cmd_name()");
  return nbuf;
}

Me_Cmd::Me_Cmd(Me_Ser *ser)
    : Cmd_Selectee(cmd_name(Me_Name), 80),
      ser(ser) {
}

/**
 * Command formats:
 *  W<address_decimal>:<MeParID_decimal>:<hex_encoded_32bit_value>
 *  RI<address_decimal>:<MeParID_decimal>
 *  RF<address_decimal>:<MeParID_decimal>
 *  Q
 */
bool Me_Cmd::app_input() {
  uint32_t hex32;
  uint8_t address;
  uint16_t MeParID;
  int index;
  Me_Query *Q;
  if (nc == 0) return true;
  if (not_any("RWQ")) {
    consume(nc);
    return false;
  }
  cp = 1;
  switch (buf[0]) {
    case 'Q': return true;
    case 'W':
      if (not_uint8(address) || not_str(":") ||
          not_uint16(MeParID) || not_str(":") ||
          not_hex(hex32) || not_str("\n")) {
        if (cp >= nc)
          report_err("Invalid or incomplete write command");
        consume(nc);
        return false;
      }
      index = get_addr_index(address);
      if (index < 0) {
        report_err("Invalid address");
        consume(nc);
        return false;
      }
      Q = ser->new_query();
      Q->setup_uint32_cmd(address, MeParID, hex32,
        &meerstetter.drive[index].Mask, 0x20);
      ser->enqueue_request(Q);
      consume(nc);
      report_ok();
      break;
    case 'R':
      if (not_any("IF") ||
          not_uint8(address) || not_str(":") ||
          not_uint16(MeParID) || not_str("\n")) {
        if (cp >= nc)
          report_err("Invalid or incomplete read command");
        consume(nc);
        return false;
      }
      index = get_addr_index(address);
      if (index < 0) {
        report_err("Invalid address");
        consume(nc);
        return false;
      }
      Q = ser->new_query();
      if (buf[1] == 'I') {
        Q->setup_int32_query(address, MeParID, 0,
        &meerstetter.drive[index].Mask, 0x20);
      } else {
        Q->setup_float32_query(address, MeParID, 0,
        &meerstetter.drive[index].Mask, 0x20);
      }
      ser->enqueue_request(Q);
      consume(nc);
      report_ok();
      break;
    default:
      report_err("Invalid command");
      consume(nc);
      break;
  }
  return false;
}

/**
 * Parsing utility function to read in a hex integer starting
 * at the current position. Integer may be proceeded by optional
 * whitespace.
 * @param[out] hexval The integer value
 * @return zero if an integer was converted, non-zero if the current char is not a digit.
 */
int Me_Cmd::not_hex(uint32_t &hexval) {
  hexval = 0;
  while (cp < nc && isspace(buf[cp]))
    ++cp;
  if (! isxdigit(buf[cp])) {
    if (cp < nc)
      report_err("No hex digits at col %d", cp);
    return 1;
  }
  while ( cp < nc && isxdigit(buf[cp]) ) {
    uint16_t digval = isdigit(buf[cp]) ? ( buf[cp] - '0' ) :
           ( tolower(buf[cp]) - 'a' + 10 );
    hexval = hexval * 16 + digval;
    ++cp;
  }
  return 0;
}
