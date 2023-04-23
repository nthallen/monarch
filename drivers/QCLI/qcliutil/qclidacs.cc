#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "subbuspp.h"
#include "nl.h"
#include "qcliutil.h"
#include "oui.h"

int qcli_dacs::board_number = 0;

qcli_dacs::qcli_dacs(/* const char *service, const char *sub_service */)
      : vreq(0) {
  sb = new subbuspp(/* service, subservice */ "subbus", "serusb");
  subfunction = sb->load();
  if (!subfunction)
    msg(3, "Unable to access subbus library %s/%s",
          "subbus", "serusb");
  board_base = QCLI_BASE + board_number * QCLI_INC;
  qcli_waddr = board_base + 6;
  qcli_wsaddr = board_base + 8;
  qcli_raddr = board_base + 2;
  qcli_vaddr = board_base + 0xA;
  sbw_chk(qcli_raddr);
  sbwr_chk(board_base+0xC, 0); // Reset the controller
}

void qcli_dacs::sbwr_chk( uint16_t addr, uint16_t val ) {
  if (sb->write_ack(addr, val) == 0)
    msg( 3, "No acknowledge writing to QCLI at 0x%03X",
      addr );
}

uint16_t qcli_dacs::sbw_chk(uint16_t addr) {
  uint16_t data;
  if (sb->read_ack(addr, &data) == 0) {
    msg(3, "No acknowledge reading from QCLI at 0x%03X",
        addr);
  }
  return data;
}

/* uint16_t read_qcli(bool fresh);
   If fresh is true, it means a command has just
   been issued, and we want to give the QCLI time
   to process that command before requesting status.

   NOTE: For qclidacs, we have always used the delay regardless of
   the status of fresh.
*/
uint16_t qcli_dacs::read_qcli(bool fresh) {
  delay(10);
  return sbw_chk(qcli_raddr);
}

void qcli_dacs::write_qcli(uint16_t value) {
  sbwr_chk(qcli_waddr, value);
}

uint16_t qcli_dacs::wr_rd_qcli(uint16_t value) {
  sbwr_chk( qcli_wsaddr, value );
  return read_qcli(1);
}

void qcli_dacs::wr_stop_qcli(uint16_t value) {
  sbwr_chk(qcli_wsaddr, value);
}

void qcli_dacs::delay(int msec) {
  struct timespec tp;
  tp.tv_sec = 0;
  tp.tv_nsec = msec * 1000000L;
  if (nanosleep( &tp, NULL ) != 0)
    msg(3, "nano_sleep saw signal");
}

/**
 @return zero on success
 */
int qcli_dacs::verify_block(uint16_t addr, uint16_t *prog, int blocklen) {
  static subbus_mread_req *vreq = 0;
  uint16_t ctrlr_status;
  uint16_t remaining;
  uint16_t blk_addr = addr;
  int rv = 0, retries = 0;
  time_t v_start, v_now;

  if ( vreq == 0 ) {
    char rbuf[15];
    snprintf(rbuf, 15, "%X@%X", 32, board_base+4);
    vreq = sb->pack_mread_request(32, rbuf);
  }
  ctrlr_status = sbw_chk(board_base);
  if (ctrlr_status & 0x7FF) {
    msg( 1,
      "Controller status before verify: 0x%04X, resetting",
      ctrlr_status);
    sbwr_chk(board_base+0xC,0);
    delay(10);
  }
  sbwr_chk(qcli_vaddr, addr); // Request Verify
  v_start = time(NULL);
  for (;;) {
    ctrlr_status = sbw_chk(board_base);
    if (ctrlr_status & 0x200) break;
    if (!(ctrlr_status & 0x100)) {
      msg(2, "Controller not in read mode: %04X", ctrlr_status);
      return 1;
    }
    v_now = time(NULL);
    if (difftime(v_now, v_start) > 3) {
      msg(2, "Timeout waiting for verify on addr %04X. "
        "ctrlr_status: %04X", addr, ctrlr_status);
      if (++retries > 2) return 1;
      // Reset the controller and reissue the verify request
      sbwr_chk(board_base+0xC,0);
      delay(10);
      sbwr_chk(qcli_vaddr, addr); // Request Verify
      v_start = time(NULL);
    }
  }
  remaining = ctrlr_status & 0xFF;
  if (remaining != 128)
    msg(1, "Expected 128 bytes in read FIFO, reporting %u",
          remaining);
  while (remaining > 0) {
    int i;
    if ( remaining < 32 ) {
      for ( i = 0; i < remaining; ++i ) {
        vbuf[i] = sbw_chk(board_base+4);
      }
    } else {
      sb->mread_subbus(vreq, vbuf);
    }
    for (i = 0; i < remaining && i < 32; ++i) {
      if (i < blocklen && vbuf[i] != prog[addr+i]) {
        msg( -2, "  %04X: program=%04X read=%04X",
          addr+i, prog[addr+i], vbuf[i] );
        ++rv;
      }
    }
    addr += i;
    remaining -= i;
    blocklen -= i;
    ctrlr_status = sbw_chk(board_base);
    if (remaining != (ctrlr_status & 0xFF))
      msg(2, "  Remaining count incorrect: %04X expected %02X",
        ctrlr_status, remaining);
  }
  if ( rv ) {
    msg(2, "Block 0x%04X: %d words failed on verify",
            blk_addr, rv );
  }
  return rv;
}

void qclisrvr_init(int argc, char **argv) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'd':
        qcli_dacs::board_number = atoi(optarg);
        break;
      case '?':
        msg(3, "Unrecognized Option -%c", optopt);
    }
  }
}
