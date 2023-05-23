#include "nl.h"
#include "qcliutil.h"
#include "qcliprog.h"

/* Returns zero if block verifies as OK */
int qcli_util::verify_block(uint16_t addr, uint16_t *prog, int blocklen) {
  int rv = 0;
  uint16_t block_addr = addr;
  if ( (addr&0xFF) + blocklen > 256 )
    msg( 4, "Invalid addr/blocklen pair: %04X, %d",
          addr,	blocklen );
  write_qcli( QCLI_LOAD_MSB | ((addr>>8)&0xFF) );
  write_qcli( QCLI_WRITE_ADDRESS | (addr&0xFF) );
  write_qcli( QCLI_READ_DATA );
  for ( ; blocklen-- > 0; addr++ ) {
    uint16_t value;
    uint16_t attempts;
    for ( attempts = 0; attempts < 5; ) {
      attempts++;
      value = wr_rd_qcli( QCLI_WRITE_ADDRESS | (addr&0xFF) );
      if ( value == prog[addr] ) break;
    }
    if ( value != prog[addr] ) {
      msg( -2, "  %04X: program=%04X read=%04X after %d attempts",
        addr, prog[addr], value, attempts );
      ++rv;
    } else if ( attempts > 1 ) {
      msg( 1, "  %04X: program=%04X required %d attempts",
        addr, prog[addr], attempts );
    }
  }
  wr_stop_qcli( QCLI_STOP );
  if (rv) msg(2, "Block %04X: %d words failed on verify",
              block_addr, rv);
  return rv;
}
