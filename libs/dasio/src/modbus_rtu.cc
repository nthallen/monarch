/** @file modbus_rtu.cc */
#include <string.h>
#include <fcntl.h>
#include "dasio/modbus_rtu.h"
#include "nl.h"
#include "dasio/msg.h"
#include "dasio/ascii_escape.h" // Until I rewrite ascii_escape() here
#include "nl_assert.h"

namespace DAS_IO { namespace Modbus {
  
  RTU::RTU(const char *iname, int bufsz, const char *path)
      : DAS_IO::Serial(iname, bufsz, path, O_RDWR|O_NONBLOCK) {
    flags |= gflag(0);
    pending = 0;
    turn_around_delay = false;
    cur_poll = polls.begin();
  }
  
  RTU::RTU(const char *iname, int bufsz) : DAS_IO::Serial(iname, bufsz) {
    flags |= gflag(0);
    pending = 0;
    cur_poll = polls.begin();
  }
  
  RTU::~RTU() {}
  
  bool RTU::ProcessData(int flag) {
    if (DAS_IO::Interface::ProcessData(flag))
      return true;
    if (pending) {
      // Temporarily disable, since it isn't working
      // update_tc_vmin(pending->rep_sz - nc);
    }
    return false;
  }
  
  bool RTU::protocol_input() {
    if (!pending) {
      report_err("%s: Unexpected input", iname);
      consume(nc);
    } else if (turn_around_delay) {
      report_err("%s: Unexpected input during turn around delay", iname);
      consume(nc);
    } else {
      if (nc < 5) return false; /* dev, cmd|err, exc. code, CRC */
      else if (!(buf[1] & 0x80) && (nc < pending->rep_sz)) return false;
      else if (buf[0] != pending->req_buf[0]) {
        report_err("%s: Reply address mismatch. Expected 0x%02X, Recd 0x%02X",
            iname, pending->req_buf[0], buf[0]);
        consume(nc);
      } else if ((buf[1] & 0x7F) != pending->req_buf[1]) {
        report_err("%s: Reply function code mismatch. Expected 0x%02X, Recd 0x%02X",
            iname, pending->req_buf[1], buf[1] & 0x7F);
        consume(nc);
      } else if (buf[1] & 0x80) {
        if (crc_ok(buf, 5)) {
          report_err("%s: Modbus error code %d", iname, buf[2]);
        } else {
          report_err("%s: CRC error on Modbus error message", iname);
        }
        if (not_suppressing())
          msg(0, "%s: Request was: %s", iname, pending->ascii_escape());
        consume(nc);
      } else if (!crc_ok(buf, pending->rep_sz)) {
        msg(MSG_ERROR, "%s: %s on reply", iname,
          nc > pending->rep_sz ? "CRC error + extra chars" : "CRC error");
        msg(0, "%s: Request was: %s", iname, pending->ascii_escape());
        consume(nc);
      } else {
        cp = pending->rep_sz;
        pending->process_pdu();
        if (nc > cp) {
          report_err("%s: Extra chars after reply", iname);
          consume(nc);
        } else {
          report_ok(nc);
        }
      }
      turn_around_delay = true;
      TO.Set(0, 10); // 5 msecs helped, what about 10?
      // This should probably be configurable
      // dispose_pending(); // moved to protocol_timeout
    }
    // process_requests(); // moved to protocol_timeout
    return false;
  }
  
  const char *RTU::ascii_escape() {
    static std::string s;
    char snbuf[8];
    uint8_t func = buf[1];
    int rep_sz;
    int i = 0;
    s.clear();
    if (nc > 0) {
      s.append("DevID:");
        s.append(RTU::modbus_req::byte_escape(buf[0]));
      if (nc > 1) {
        s.append(" Func:"); s.append(RTU::modbus_req::byte_escape(buf[1]));
        if (func & 0x80) {
          s.append(" Err:");
            s.append(RTU::modbus_req::byte_escape(buf[2]));
            s.append(RTU::modbus_req::byte_escape(buf[3]));
          rep_sz = 6;
        } else if (func <= 4) {
          int NB = buf[2];
          rep_sz = NB+5;
          s.append(" NB:");
            s.append(RTU::modbus_req::byte_escape(NB));
          s.append(" Data:");
          for (i = 0; i < NB; ++i) {
            s.append(RTU::modbus_req::byte_escape(buf[3+i]));
          }
        } else {
          rep_sz = 8;
          s.append(" Addr:");
            s.append(RTU::modbus_req::byte_escape(buf[3]));
            s.append(RTU::modbus_req::byte_escape(buf[4]));
          s.append(" Other: ");
            s.append(RTU::modbus_req::byte_escape(buf[5]));
            s.append(RTU::modbus_req::byte_escape(buf[6]));
        }
        if (rep_sz <= nc) {
          s.append(" CRC:");
            s.append(RTU::modbus_req::byte_escape(buf[rep_sz-2]));
            s.append(RTU::modbus_req::byte_escape(buf[rep_sz-1]));
        }
      }
    }
    return s.c_str();
  }
  
  /**
   * Terminates the current request/response and advances
   * to the next request.
   * @return true if the event loop should terminate
   */
  bool RTU::protocol_timeout() {
    if (pending) {
      if (turn_around_delay) {
        turn_around_delay = false;
      } else {
        if (MSG_IS_VERBOSE(0)) {
          report_err("%s: Timeout awaiting reply", iname);
          if (not_suppressing())
            msg(MSG_DBG(0), "%s: Request was: %s", iname, pending->ascii_escape());
        }
      }
      consume(nc);
      dispose_pending();
    }
    process_requests();
    return false;
  }

  bool RTU::protocol_gflag(int flag) {
    update_polls(flag);
    std::deque<RTU::modbus_device *>::iterator pos;
    for (pos = devices.begin(); pos != devices.end(); ++pos) {
      (*pos)->protocol_gflag(flag);
    }
    return process_requests();
  }

  void RTU::add_device(modbus_device *dev) {
    uint8_t devID = dev->get_devID();
    modbus_device *other = find_device(devID);
    if (other) {
      msg(MSG_FATAL, "%s: Device with ID %d already exists", iname, devID);
    } else {
      devices.push_back(dev);
      dev->set_MB(this);
      dev->enqueue_polls();
    }
  }
  
  RTU::modbus_device *RTU::find_device(uint8_t devID) {
    std::deque<RTU::modbus_device *>::iterator pos;
    for (pos = devices.begin(); pos != devices.end(); ++pos) {
      RTU::modbus_device *dev = *pos;
      if (dev->get_devID() == devID) {
        return dev;
      }
    }
    return 0;
  }

  void RTU::enqueue_command(modbus_req *req) {
    if (req->get_req_state() == RTU::modbus_req::Req_ready) {
      cmds.push_back(req);
    }
  }

  void RTU::enqueue_poll(modbus_req *req, int gflag_no) {
    if (req->get_req_state() == RTU::modbus_req::Req_ready) {
      polls.push_back(req);
      req->persistent = true;
    }
  }

  bool RTU::crc_ok(uint8_t *rep, unsigned nb) {
    if (pending) {
      unsigned short crc_rep = (rep[nb-1]<<8) + rep[nb-2];
      unsigned short crc_calc = pending->crc(rep, nb-2);
      return crc_rep == crc_calc;
    } else {
      return false;
    }
  }
  
  void RTU::read_pdu_4321(uint32_t *dest, int count) {
    int offset = 3;
    for (int i = 0; count > 0; ++i, --count) {
      RTU::modbus_req::swap32_4321((uint8_t*)dest, (uint8_t*)&buf[offset+4*i]);
      ++dest;
    }
  }
  
  void RTU::read_pdu(uint16_t *dest, int count, int offset) {
    for (int i = 0; count > 0; ++i, --count) {
      RTU::modbus_req::swap16((uint8_t*)dest, (uint8_t*)&buf[offset+2*i]);
      ++dest;
    }
  }
  
  void RTU::read_pdu(uint8_t *dest, int count, int offset) {
    for (int i = 0; count > 0; ++i, --count) {
      dest[i] = buf[offset+i];
    }
  }
  
  bool RTU::process_requests() {
    while (!pending) {
      pending = next_poll();
      if (pending) {
        if (pending->get_req_state() == RTU::modbus_req::Req_ready) {
          bool rv = iwrite((const char *)&pending->req_buf[0], pending->req_sz);
          if (rv) TO.Clear();
          else TO.Set(0, 500);
          return rv;
        } else {
          dispose_pending();
        }
      } else {
        TO.Clear();
        break;
      }
    }
    return false;
  }
  
  void RTU::dispose_pending() {
    if (pending) {
      if (!pending->persistent) {
        req_free.push_back(pending);
      }
      pending = 0;
    }
  }

  void RTU::update_polls(int flag) {
    if (cur_poll == polls.end()) {
      cur_poll = polls.begin();
    }
  }

  /**
   * The default implementation returns either the next
   * command request or the next poll request. If no
   * requests are queued, it returns zero.
   * @return the next queued request or zero
   */
  RTU::modbus_req *RTU::next_poll() {
    nl_assert(!pending);
    RTU::modbus_req *rv = 0;
    if (!cmds.empty()) {
      rv = cmds.front();
      cmds.pop_front();
    } else if (cur_poll != polls.end()) {
      rv = *cur_poll;
      ++cur_poll;
    }
    return rv;
  }
  
  RTU::modbus_req *RTU::new_modbus_req() {
    RTU::modbus_req *req;
    if (req_free.empty()) {
      req = new RTU::modbus_req;
    } else {
      req = req_free.front();
      req_free.pop_front();
    }
    req->set_MB(this);
    return req;
  }
  
  RTU::modbus_req::modbus_req()
      : req_state(Req_unconfigured),
        device(0),
        address(0),
        rep_sz(0),
        req_sz(0),
        count(0),
        devID(0),
        persistent(false),
        MB(0),
        fresh_byte(0),
        fresh_bit_mask(0) {}
  
  void RTU::modbus_req::setup(RTU::modbus_device *device,
          uint8_t function_code, uint16_t address, uint16_t count,
          void *dest, RepHandler handler) {
    uint8_t byte_count;
    this->device = device;
    this->devID = device->get_devID();
    this->count = count;
    this->function_code = function_code;
    this->address = address;
    this->dest = dest;
    req_buf[0] = devID;
    req_buf[1] = function_code;
    swap16(&req_buf[2], (uint8_t*)&address);
    switch (function_code) {
      case 1: // Read Coils
      case 2: // Read Discrete Inputs
        swap16(&req_buf[4], (uint8_t*)&count);
        req_sz = 8;
        byte_count = (count+7)/8;
        rep_sz = 5+byte_count;
        req_state = Req_pre_crc;
        crc_set();
        this->handler = handler ? handler : RTU::modbus_device::RH_uint8;
        rep_count = byte_count;
        return;
      case 3: // Read Holding Registers
      case 4: // Read Input Registers
        swap16(&req_buf[4], (uint8_t*)&count);
        req_sz = 8;
        rep_sz = 5+2*count;
        req_state = Req_pre_crc;
        crc_set();
        this->handler = handler ? handler : RTU::modbus_device::RH_uint16;
        rep_count = count;
        return;
      case 5: // Write Single Coil
      case 6: // Write Single Register
        req_sz = 8;
        rep_sz = 8;
        if (count != 1) {
          msg(MSG_WARN, "%s: Invalid count %d for function code %d: must be 1",
            device->get_iname(), count, function_code);
          this->count = 1;
        }
        this->handler = handler ? handler : RTU::modbus_device::RH_null;
        rep_count = 0;
        break;
      case 8: // Serial line diagnostics
        req_sz = 6+2*count;
        rep_sz = 6+2*count;
        switch (address) {
          case 0: 
          case 10:
          case 12:
          case 13:
          case 14:
            if ((address == 0 && count == 0) ||
                (address != 0 && count != 1)) {
              msg(MSG_ERROR, "%s: Invalid count/data for Func/Sub 8/%d",
                device->get_iname(), address);
              req_state = Req_invalid;
              return;
            }
            break;
          default:
            msg(MSG_ERROR, "%s: Invalid subfunction code %d for function 8",
              device->get_iname(), address);
            req_state = Req_invalid;
            return;
        }
        this->handler = handler ? handler : RTU::modbus_device::RH_uint16;
        rep_count = 1;
        break;
      case 15: // Write Multiple Coils
        swap16(&req_buf[4], (uint8_t*)&count);
        byte_count = (count+7)/8;
        req_buf[6] = byte_count;
        req_sz = 9 + byte_count;
        rep_sz = 8;
        this->handler = handler ? handler : RTU::modbus_device::RH_null;
        rep_count = 0;
        break;
      case 16: // Write Multiple Registers
        swap16(&req_buf[4], (uint8_t*)&count);
        byte_count = 2*count;
        req_buf[6] = byte_count;
        req_sz = 9 + byte_count;
        rep_sz = 8;
        this->handler = handler ? handler : RTU::modbus_device::RH_null;
        rep_count = 0;
        break;
      default:
        msg(MSG_ERROR, "%s: modbus_req::setup: Unsupported function code: %d", function_code);
        req_state = Req_unconfigured;
        return;
    }
    req_state = Req_addressed;
    return;
  }

  void RTU::modbus_req::setup_data(uint8_t *data) {
    if (req_state == Req_invalid) return;
    if (req_state != Req_addressed) {
      msg(MSG_ERROR, "%s: setup_data(): Invalid input state %d", device->get_iname(), req_state);
    } else {
      uint8_t function_code = req_buf[1];
      uint8_t byte_count;
      switch (function_code) {
        case 1:
        case 2:
        case 3:
        case 4:
          msg(MSG_ERROR, "%s: setup_data() invalid for read functions", device->get_iname());
          break;
        case 5:
        case 6:
        case 8:
        case 16:
          msg(MSG_ERROR,
            "%s: setup_data(uint8_t) incorrect data type for function_code %d",
            device->get_iname(), function_code);
          req_state = Req_invalid;
          break;
        case 15:
          byte_count = req_buf[6];
          memcpy(&req_buf[7], data, byte_count);
          req_state = Req_pre_crc;
          crc_set();
          return;
        default:
          msg(MSG_ERROR, "%s: setup_data() Invalid function %d",
            device->get_iname(), function_code);
          break;
      }
    }
    req_state = Req_unconfigured;
    return;
  }

  void RTU::modbus_req::setup_data(uint16_t *data) {
    if (req_state == Req_invalid) return;
    if (req_state != Req_addressed) {
      msg(MSG_ERROR, "%s/%s: setup_data(): Invalid input state %d",
          device->get_iname(), device->get_dev_name(), req_state);
    } else {
      uint8_t function_code = req_buf[1];
      uint8_t word_count;
      uint16_t subfunc;
      switch (function_code) {
        case 1:
        case 2:
        case 3:
        case 4:
          msg(MSG_ERROR, "%s/%s: setup_data() invalid for read functions",
            device->get_iname(), device->get_dev_name());
          req_state = Req_invalid;
          return;
        case 5:
        case 6:
        case 16:
          swap16(&word_count, &req_buf[4]);
          for (int i = 0; i < word_count; ++i) {
            swap16(&req_buf[7+2*i], (uint8_t*)&data[i]);
          }
          req_state = Req_pre_crc;
          crc_set();
          return;
        case 8:
          for (int i = 0; i <= count; ++i) {
            swap16(&req_buf[2+2*i], (uint8_t*)&data[i]);
          }
          req_state = Req_pre_crc;
          crc_set();
          return;
        case 15:
          msg(MSG_ERROR,
            "%s/%s: setup_data(uint8_t) incorrect data type for function_code %d",
            device->get_iname(), device->get_dev_name(), function_code);
          break;
        default:
          msg(MSG_ERROR, "%s/%s: setup_data() Invalid function %d",
            device->get_iname(), device->get_dev_name(), function_code);
          break;
      }
    }
    req_state = Req_unconfigured;
    return;
  }
  
  void RTU::modbus_req::setup_fresh_bit(uint8_t *byte, uint8_t bitnum) {
    fresh_byte = byte;
    fresh_bit_mask = 1<<bitnum;
  }

  const char *RTU::modbus_req::byte_escape(uint8_t byte) {
    static char obuf[4];
    snprintf(obuf, 4, " %02X", byte);
    return (const char*)obuf;
  }
  
  const char *RTU::modbus_req::ascii_escape() {
    static std::string s;
    char snbuf[8];
    int i = 0;
    s.clear();
    s.append("Dev:"); s.append(byte_escape(req_buf[0]));
    s.append(" Func:"); s.append(byte_escape(req_buf[1]));
    s.append(" Addr:");
      s.append(byte_escape(req_buf[2]));
      s.append(byte_escape(req_buf[3]));
    s.append(" Data:");
    for (i = 4; i < req_sz-2; ++i) {
      s.append(byte_escape(req_buf[i]));
    }
    s.append(" CRC:");
      s.append(byte_escape(req_buf[req_sz-2]));
      s.append(byte_escape(req_buf[req_sz-1]));
    return s.c_str();
  }
  
  void RTU::modbus_req::process_pdu() {
    this->handler(this, device, MB);
    if (fresh_byte) {
      *fresh_byte |= fresh_bit_mask;
    }
  }
  
  /**
   * Requires no arguments because this is only called on the
   * request, and the buffer and size are stored in the object.
   */
  void RTU::modbus_req::crc_set() {
    if (req_state == Req_pre_crc) {
      uint16_t crc_calc = crc(req_buf, req_sz-2);
      req_buf[req_sz-2] = crc_calc & 0xFF;
      req_buf[req_sz-1] = (crc_calc>>8) & 0xFF;
      req_state = Req_ready;
    } else if (req_state != Req_invalid) {
      msg(MSG_ERROR, "%s: Incomplete request in crc_set(): %d", device->get_iname(),
        req_state);
      req_state = Req_unconfigured;
    }
  }

  uint16_t RTU::modbus_req::crc(uint8_t *puchMsg, uint16_t usDataLen) {

    /* Table of CRC values for high�order byte */
    static unsigned char auchCRCHi[] = {
      0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
      0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
      0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
      0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
      0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
      0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
      0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
      0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
      0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
      0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
      0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
      0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
      0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
      0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
      0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
      0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
      0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
      0x40
    };

    /* Table of CRC values for low�order byte */
    static unsigned char auchCRCLo[] = {
      0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
      0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
      0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
      0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
      0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
      0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
      0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
      0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
      0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
      0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
      0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
      0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
      0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
      0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
      0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
      0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
      0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
      0x40
    };
    
    uint8_t uchCRCHi = 0xFF ; /* high byte of CRC initialized */
    uint8_t uchCRCLo = 0xFF ; /* low byte of CRC initialized */
    uint8_t uIndex ; /* will index into CRC lookup table */
    while (usDataLen--) {
      uIndex = uchCRCLo ^ *puchMsg++ ; /* calculate the CRC */
      uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex] ;
      uchCRCHi = auchCRCLo[uIndex] ;
    }
    return (uchCRCHi << 8 | uchCRCLo) ;
  }
  
  /* This byte order comes from the Watlow driver, for which the documentation was very
   * sketchy. Modbus is supposed to use BigEndian, and it appears to do so on the
   * 16-bit register level, but apparently the combination of registers to form longer
   * data types (such as 32-bit floats), may be application dependent.
   * As such, verify the correct byte order, and make necessary changes.
   */
  void RTU::modbus_req::swap32_4321(uint8_t *dest, uint8_t *src) {
    swap16(dest+2, src);
    swap16(dest, src+2);
  }
  
  void RTU::modbus_req::swap16(uint8_t *dest, uint8_t *src) {
    dest[1] = src[0];
    dest[0] = src[1];
  }

  RTU::modbus_device::modbus_device(
      const char *dev_name, uint8_t devID)
      : dev_name(dev_name), devID(devID) {
    if (!dev_name) {
      msg(MSG_FATAL, "Invalid modbus_device construction");
    }
    MB = 0;
  }

  RTU::modbus_device::~modbus_device() { }
  
  void RTU::modbus_device::RH_null(RTU::modbus_req *req, RTU::modbus_device *dev,
          RTU *MB) {}

  void RTU::modbus_device::RH_uint8(RTU::modbus_req *req, RTU::modbus_device *dev,
          RTU *MB) {
    MB->read_pdu((uint8_t*)(req->dest), req->rep_count);
  }

  void RTU::modbus_device::RH_uint16(RTU::modbus_req *req, RTU::modbus_device *dev,
          RTU *MB) {
    MB->read_pdu((uint16_t*)(req->dest), req->rep_count,
      req->function_code == 8 ? 4 : 3);
  }

  void RTU::modbus_device::RH_uint32(RTU::modbus_req *req, RTU::modbus_device *dev,
          RTU *MB) {
    MB->read_pdu_4321((uint32_t*)(req->dest), req->rep_count/2);
  }
  
  void RTU::modbus_device::protocol_gflag(int flag) {}

} } // Close out Modbus and DAS_IO namespaces
