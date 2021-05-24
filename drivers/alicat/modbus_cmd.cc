#include "modbus_cmd.h"
#include "dasio/msg.h"

namespace DAS_IO { namespace Modbus {

modbus_cmd::modbus_cmd(const char *channel, DAS_IO::Modbus::RTU *MB)
    : DAS_IO::Cmd_reader("Cmd", 40, channel),
      MB(MB) {}

bool modbus_cmd::app_input() {
  uint16_t devID, func, addr, count, data[2];
  if (cp < nc) {
    int arg_count;
    if (buf[cp] == 'Q') return true;
    if (not_str("W") ||
        not_hex(devID) || not_str(":") ||
        not_hex(func) || not_str(":") ||
        not_hex(addr) || not_str(":") ||
        not_hex(count)) {
      if (cp < nc)
        consume(nc);
      return false;
    }
    arg_count = (func == 15) ? (count+7)/8 : count;
    if (arg_count < 1 || arg_count > 2) {
      report_err("%s: Unsupported count %d for function %d", iname, count, func);
      consume(nc);
      return false;
    }
    for (int i = 0; i < arg_count; ++i) {
      if (not_str(":") || not_hex(data[i])) {
        if (cp < nc) consume(nc);
        return false;
      }
    }
    if (func == 15 && arg_count == 2) {
      data[0] = (data[0] & 0xFF) | ((data[1] << 8) & 0xFF00);
    }
    DAS_IO::Modbus::RTU::modbus_device *dev = MB->find_device(devID);
    if (devID > 0xFF || !dev) {
      report_err("%s: Invalid device ID %d", iname, devID);
      consume(nc);
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
    report_ok(nc);
  }
  return false;
}

} }
