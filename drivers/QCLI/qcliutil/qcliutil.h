#ifndef QCLI_H_INCLUDED
#define QCLI_H_INCLUDED 1
#include <stdint.h>
#include "subbuspp.h"

#define ANAIO_BASE 0xC00
#define ANAIO_INC 0x80
#define ANAIO_STATUS_OFFSET 6
#define ANAIO_DAC_OFFSET 0x60
#define ANAIO_HRDAC_OFFSET 0x70
#define ANAIO_HRADC_OFFSET 0x78
#define DAC_MODE_BITS 0x0C
#define QCLI_BASE 0x1000
#define QCLI_INC  0x0010

#define QCLI_S_BUSY     0x8000
#define QCLI_S_CHKSUM   0x4000
#define QCLI_S_CMDERR   0x2000
#define QCLI_S_LASEROFF 0x1000
#define QCLI_S_CORDTE   0x0800
#define QCLI_S_READY    0x0200
#define QCLI_S_WAVEERR  0x0100
#define QCLI_S_FLSHDATA 0x0080
#define QCLI_S_FLSHTGL  0x0040
#define QCLI_S_DOT      0x0020
#define QCLI_S_LOT      0x0010
#define QCLI_S_LOC      0x0008
#define QCLI_S_MODE     0x0007
#define QCLI_S_HWERR (QCLI_S_DOT|QCLI_S_LOT|QCLI_S_LOC)
#define QCLI_S_FWERR (QCLI_S_CMDERR|QCLI_S_CORDTE)
#define QCLI_S_ERR (QCLI_S_HWERR|QCLI_S_FWERR)
#define QCLI_IDLE_MODE 0
#define QCLI_PROGRAM_MODE 1
#define QCLI_PSECTOR_MODE 2
#define QCLI_RUN_MODE 3
#define QCLI_SELECT_MODE 4

#define QCLI_NOOP 0x0000
#define QCLI_STOP 0x0100
#define QCLI_LOAD_MSB 0x0200
#define QCLI_WRITE_ADDRESS 0x0300
#define QCLI_WRITE_DATA 0x0400
#define QCLI_READ_DATA  0x0500
#define QCLI_WRITE_CHKSUM  0x0600
#define QCLI_PROGRAM_SECTOR  0x0700
#define QCLI_CLEAR_ERROR 0x0800
#define QCLI_SELECT_WAVEFORM 0x0900
#define QCLI_RUN_WAVEFORM 0x0A00
#define QCLI_SELECT_DAC 0x0B00
#define QCLI_WRITE_DAC 0x0C00
#define QCLI_WRITE_TON 0x0D00
#define QCLI_WRITE_TOFF 0x0E00
#define QCLI_WRITE_TPRE 0x0F00
#define QCLI_BAD_CMD 0x1000

class qcli_util {
  public:
    qcli_util(/* const char *service, const char *sub_service */);
    void report_status(uint16_t status);
    uint16_t read_qcli(bool fresh);
    void write_qcli(uint16_t value);
    uint16_t wr_rd_qcli(uint16_t value);
    void wr_stop_qcli(uint16_t value);
    int diags(int verbose);
    int verify_block(uint16_t addr, uint16_t *prog, int blocklen);
    static int board_number;
  protected:
    void sbwr_chk(uint16_t addr, uint16_t val);
    uint16_t sbw_chk(uint16_t addr);
    void delay(int msec);
    bool check_status(uint16_t status, uint16_t mask,
            uint16_t value, const char *text, bool dump);
    subbuspp *sb;
    uint16_t subfunction;
    uint16_t board_base;
    uint16_t qcli_waddr, qcli_raddr;
    uint16_t qcli_wsaddr, qcli_vaddr;
    uint16_t vbuf[32];
    subbus_mread_req *vreq;
    bool qcli_error_reported;
};
void qclisrvr_init(int argc, char **argv);

#endif
