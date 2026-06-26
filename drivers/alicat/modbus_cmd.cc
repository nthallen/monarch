#include "modbus_cmd.h"
#include "dasio/msg.h"

namespace DAS_IO { namespace Modbus {

modbus_cmd::modbus_cmd(const char *channel, DAS_IO::Modbus::RTU *MB)
    : DAS_IO::Cmd_reader("Cmd", 40, channel),
      MB(MB) {}

bool modbus_cmd::app_input() {
  while (cp < nc) {
    // First check to see if we have a complete command
    int look_ahead = cp;
    while (look_ahead < nc && buf[look_ahead] != '\n')
      ++look_ahead;
    if (look_ahead >= nc)
      break;
    ++look_ahead;
    bool rv = process_cmd();
    if (cp >= look_ahead)
      report_err("%s: cp >= look_ahead after process_cmd()", iname);
    consume(look_ahead);
    if (rv) return true;
  }
  return false;
}

/**
 * Broken out of app_input() to avoid breaking out of deeply nested
 * loops. This method will not consume() and chars, but will call
 * report_ok() when a command is successfully processed.
 * app_input() will be responsible for consuming the entire command,
 * whether is was valid or erroneous. We are confident that cp will
 * not advance beyond app_input()'s look_ahead, since that denotes
 * the existence of a newline in the buffer, and none of the
 * parsing functions in process_cmd() should advance past a newline.
 * We'll add a check after the call.
 */
bool modbus_cmd::process_cmd() {
  uint16_t devID, func, addr, count, data[2];
  int arg_count;
  if (buf[cp] == 'Q') {
    report_ok();
    return true;
  }
  if (not_str("W") ||
      not_hex(devID) || not_str(":") ||
      not_hex(func) || not_str(":") ||
      not_hex(addr) || not_str(":") ||
      not_hex(count)) {
    return false;
  }
  arg_count = (func == 15) ? (count+7)/8 : count;
  if (arg_count < 1 || arg_count > 2) {
    report_err("%s: Unsupported count %d for function %d", iname, count, func);
    return false;
  }
  for (int i = 0; i < arg_count; ++i) {
    if (not_str(":") || not_hex(data[i])) {
      return false;
    }
  }
  if (func == 15 && arg_count == 2) {
    data[0] = (data[0] & 0xFF) | ((data[1] << 8) & 0xFF00);
  }
  DAS_IO::Modbus::RTU::modbus_device *dev = MB->find_device(devID);
  if (devID > 0xFF || !dev) {
    report_err("%s: Invalid device ID %d", iname, devID);
    return false;
  }
  DAS_IO::Modbus::RTU::modbus_req *req = MB->new_modbus_req();
  req->setup(dev, func, addr, count);
  if (func == 15) {
    req->setup_data((uint8_t*)&data[0]);
  } else {
    req->setup_data(&data[0]);
  }
  if (count == 1)
    msg(MSG_DEBUG, "%s: Recd %02X:%02X:%04X:%04X:%04X",
      iname, devID, func, addr, count, data[0]);
  else
    msg(MSG_DEBUG, "%s: Recd %02X:%02X:%04X:%04X:%04X:%04X",
      iname, devID, func, addr, count, data[0], data[1]);
  MB->enqueue_command(req);
  report_ok();
  return false;
}

} }
