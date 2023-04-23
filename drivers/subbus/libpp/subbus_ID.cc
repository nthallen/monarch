#include "nl.h"
#include "nl_assert.h"
#include "subbuspp.h"
#include "subbusd_CAN_ID.h"

static const char *inst_desc[] = {
  "Unspecified",
  "SCoPEx",
  "HCHO",
  "Plant Chamber",
  "Test",
  "Halogens",
  "WI-ICOS/HTW",
  "DPOPS",
  "Moudi",
  "HWV",
  "FOCAL",
  "ES96 Ozone",
  "ES96 HCl",
  "PTR3"
};
#define N_INST_DESC 14

/**
 * @param sb subbuspp object pointer
 * @param addr The address for the desired parameter
 * @param val pointer where parameter will be written
 * @param desc Text to use in error message
 * @return true on error
 */
bool subbus_read_id(subbuspp *sb, uint16_t addr, uint16_t *val,
                    const char *desc) {
  if (!sb->read_ack(addr, val)) {
    msg(2, "NACK reading %s from 0x%X", desc, addr);
    return true;
  }
  return false;
}

void subbus_CAN_ID(subbuspp *sb) {
  uint16_t subfunc = sb->get_subfunction();
  uint16_t CAN_ID;
  uint16_t board_id;
  if (subfunc != 11) {
    msg(2, "Invalid subfunction %u in subbus_CAN_ID()", subfunc);
    return;
  }
  for (CAN_ID == 0; CAN_ID < CAN_ID_N_BDIDS; ++CAN_ID) {
    if (!sb->read_ack((CAN_ID<<8)|0xA,&subfunc)) {
      if (!sb->read_ack((CAN_ID<<8)|0x2,&board_id)) {
        msg(2, "NACK reading board ID from CAN %u:2", CAN_ID);
        return;
      }
      switch (board_id) {
        case 0: case 1: case 2: case 3: case 4: case 5:
          subfunc = 15; // uDACS16
          break;
        case 17:
          subfunc = 17; // B3MB
          break;
        default:
          msg(2, "Unrecognized Board ID %u from CAN_ID %u",
                  board_id, CAN_ID);
          return;
      }
    }

    // ID_REQ must not exceed MAX_ID_READS:
    #define MAX_ID_READS 0x40
    #define ID_REQ "8|3F@9"
    uint16_t values[MAX_ID_READS];
    uint16_t nread;
    subbus_mread_req *mreq = sb->pack_mread_request(MAX_ID_READS, ID_REQ);
    int rv = sb->mread_subbus_nw(mreq, values, &nread);
    free_memory(mreq);
    if (rv == SBS_OK) {
      if (nread <= MAX_ID_READS) {
        msg(1, "CAN_ID:%u: Description exceeded allocated space", CAN_ID);
      }
      values[MAX_ID_READS-1] = 0;
      const char *desc = (const char *)&values[1];
      msg(0, "  CAN_ID:%u Len:%d Desc: %s", CAN_ID, values[0], desc);
    } else if (rv == SBS_NOACK) {
      msg(0, "  CAN_ID:%u NACK in identify_board()", CAN_ID);
    } else {
      msg(2, "CAN_ID:%u Error %d from identify_board() request for %s", CAN_ID, rv);
    }
  }
}

void subbus_ID(subbuspp *sb, uint16_t subfunc, uint16_t offset) {
  uint16_t board_id = 0, inst_id = 0, build = 0, sn = 0;
  const char *board_desc = "";
  const char *subf_desc = "";
  if (!subfunc)
    subfunc = sb->get_subfunction();
  switch (subfunc) {
    case 5: // DACS
      if (subbus_read_id(sb, 0x81, &board_id, "DACS BoardID"))
        return;
      if (subbus_read_id(sb, 0x80, &build, "DACS Build Number"))
        return;
      subf_desc = "DACS";
      switch (board_id) {
        case 1: inst_id = 9; break; // HWV
        case 2: inst_id = 6; break; // WI-ICOS/HTW
        case 3: inst_id = 10; break; // HCIso/FOCAL
        case 4: inst_id = 11; break; // ES96 Ozone
        case 5: inst_id = 12; break; // ES96 HCl
        default : break;
      }
      break;
    case 7: // FCC
      if (subbus_read_id(sb, 0x3, &board_id, "FCC BoardID"))
        return;
      if (subbus_read_id(sb, 0x2, &build, "FCC Build Number"))
        return;
      subf_desc = "FCC";
      switch (board_id) {
        case 10: inst_id = 2; board_desc = "FCC1"; break;
        case 11: inst_id = 2; board_desc = "FCC2"; break;
        case 13: inst_id = 3; board_desc = "FCC3"; break;
        default: break;
      }
    case 16: // FCC V1.5b
      if (subbus_read_id(sb, 0x2, &board_id, "FCC V1.5b BoardID"))
        return;
      if (subbus_read_id(sb, 0x3, &build, "FCC V1.5b Build Number"))
        return;
      subf_desc = "FCC V1.5b";
      switch (board_id) {
        case 10: inst_id = 2; board_desc = "FCC1"; break; // HCHO
        default: break;
      }
      break;
    case 8: // CMOD-A7
      subf_desc = "CMOD-A7";
      if (subbus_read_id(sb, 0x3, &board_id, "CMOD-A7 BoardID"))
        return;
      if (subbus_read_id(sb, 0x2, &build, "CMOD-A7 Build Number"))
        return;
      switch (board_id) {
        case 7: inst_id = 13; board_desc = "PTR3 HVPS"; break; // PTR3
        case 8: inst_id = 2; board_desc = "Binned Counter"; break; // HCHO
        case 9: inst_id = 13; board_desc = "PTR3 RF"; break; // PTR3
        default: break;
      }
      break;
    case 9: // uDACS Rev A
    case 14: // uDACS Rev B
    case 15: // uDACS16
      switch (subfunc) {
        case 9: subf_desc = "uDACS Rev A"; break;
        case 14: subf_desc = "uDACS Rev B"; break;
        case 15: subf_desc = "uDACS16"; break;
      }
      if (subbus_read_id(sb, offset|0x2, &board_id, "uDACS BoardID"))
        return;
      if (subbus_read_id(sb, offset|0x3, &build, "uDACS Build Number"))
        return;
      if (subbus_read_id(sb, offset|0x4, &sn, "uDACS Serial Number"))
        return;
      if (subbus_read_id(sb, offset|0x5, &inst_id, "uDACS Instrument ID"))
        return;
      switch (board_id) {
        case 0: board_desc = "Test Board"; break;
        case 1: board_desc = "DPOPS uDACS A"; break;
        case 2: board_desc = "DPOPS uDACS B"; break;
        case 3: board_desc = "SCoPEx Port Engine Assy"; break;
        case 4: board_desc = "SCoPEx Starboard Engine Assy"; break;
        case 5: board_desc = "Halogen TRU Interface Box"; break;
        default: break;
      }
      break;
    case 11:
      subbus_CAN_ID(sb);
      return;
    default:
      msg(2, "Unsupported subfunction code: %u", subfunc);
      return;
  }
  nl_assert(inst_id < N_INST_DESC);
  nl_assert(subf_desc && board_desc);
  msg(0, "%s %s build %u sn %u for the %s instrument",
    subf_desc, board_desc, build, sn, inst_desc[inst_id]);
}
