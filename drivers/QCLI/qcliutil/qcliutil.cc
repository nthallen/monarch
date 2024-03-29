#include <time.h>
#include <unistd.h>
#include "nl.h"
#include "qcliutil.h"

#define USE_DELAY 1

typedef struct {
  uint16_t bits;
  const char *text;
} bitdef;
bitdef qcli_bits[] = {
  { QCLI_S_BUSY, "BUSY" },
  { QCLI_S_CHKSUM, "CHKSUM" },
  { QCLI_S_CMDERR, "CMDERR" },
  { QCLI_S_LASEROFF, "LASERON" },
  { QCLI_S_CORDTE, "CORDTE" },
  { QCLI_S_READY, "READY" },
  { QCLI_S_WAVEERR, "WAVEERR" },
  /* QCLI_S_FLSHDATA, "FLSHDATA", */
  /* QCLI_S_FLSHTGL, "FLSHTGL", */
  { QCLI_S_DOT, "DOT" },
  { QCLI_S_LOT, "LOT" },
  { QCLI_S_LOC, "LOC" },
  { 0, 0 }
};

#define REPORT_MAX 80
void qcli_util::report_status(uint16_t status) {
  int i;
  char buf[REPORT_MAX+1];
  int nb;
  nb = snprintf( buf, REPORT_MAX, "Status = 0x%04X", status );
  status ^= QCLI_S_LASEROFF;
  for ( i = 0; qcli_bits[i].bits; i++ ) {
    if ( nb < REPORT_MAX && status & qcli_bits[i].bits )
      nb += snprintf( buf+nb, REPORT_MAX-nb, " %s", qcli_bits[i].text );
  }
  msg(0, "%s Mode bits: %d", buf, status & QCLI_S_MODE);
}

/**
 * @param status The current status value
 * @param mask A mask applied to status before comparing
 * @param value The value compared to the masked status
 * @param text String to include in error report
 * @param dump If true, include full status dump in error report
 * @return false if the masked status is equal to value.
 **/
bool qcli_util::check_status(uint16_t status, uint16_t mask,
        uint16_t value, const char *text, bool dump) {
  if ( (status & mask) == value ) return false;
  qcli_error_reported = true;
  msg( 2, "%s", text );
  if (dump) report_status(status);
  return true;
}

/* diags(verbose)
   Returns non-zero on success, zero in case of errors
   verbose:
     0 - prints errors only
     1 - prints progress and errors
*/
int qcli_util::diags(int verbose) {  
  uint16_t qcli_status;

  qcli_error_reported = false;

  /* Verify that no errors are asserted. If any are,
     attempt to clear them */
  if (verbose) msg(0, "QCLI Diagnostics");
  qcli_status = wr_rd_qcli( QCLI_STOP );
  if ( qcli_status & QCLI_S_ERR ) {
    qcli_status = wr_rd_qcli( QCLI_CLEAR_ERROR );
  }
  if ( check_status( qcli_status, QCLI_S_FWERR, 0,
        "Error status observed on startup", 1 ) )
    return 0;

  /* Verify that QCLI is in Idle mode. If not, try
     to put it into Idle */
  if ( verbose ) msg( 0, "Verifying Idle Status:" );
  if ( ( qcli_status & QCLI_S_MODE ) != QCLI_IDLE_MODE ) {
    qcli_status = wr_rd_qcli( QCLI_STOP );
  }
  if ( check_status( qcli_status, QCLI_S_MODE, QCLI_IDLE_MODE,
        "QCLI Not in Idle Mode after issuing STOP", 0 ) +
       check_status( qcli_status, QCLI_S_FWERR, 0,
         "QCLI reports error after issuing STOP", 0 ) ) {
    if ( verbose) report_status(qcli_status);
    return 0;
  }

  /* Test the bad opcode error */
  if ( verbose ) msg( 0, "Issuing invalid opcode:" );
  qcli_status = wr_rd_qcli( QCLI_BAD_CMD );
  if ( ! check_status( qcli_status, QCLI_S_CORDTE, QCLI_S_CORDTE,
        "CORDTE not observed", 1 ) ) {
    if (verbose) msg( 0, "CORDTE Error Observed as expected" );
    qcli_status = wr_rd_qcli( QCLI_CLEAR_ERROR );
    if ( check_status( qcli_status, QCLI_S_CORDTE, 0,
            "CORDTE not cleared", 0 ) |
         check_status( qcli_status, QCLI_S_FWERR, 0,
            "Error bits observed after CLEAR_ERROR", 0 )
        ) report_status( qcli_status );
    else if (verbose) msg( 0, "CORDTE Cleared as expected" );
  }
  
  /* Test CMDERR by issuing Run - but only if we
     are not ready */
  if ( qcli_status & QCLI_S_READY ) {
    if (verbose) msg( 0, "Skipping CMDERR test" );
  } else {
    if (verbose) msg( 0, "Issuing PROGRAM_SECTOR from IDLE:" );
    qcli_status = wr_rd_qcli( QCLI_PROGRAM_SECTOR );
    if ( ! check_status( qcli_status, QCLI_S_CMDERR, QCLI_S_CMDERR,
          "CMDERR not observed", 1 ) ) {
      if (verbose) msg( 0, "CMDERR Observed");
      qcli_status = wr_rd_qcli( QCLI_CLEAR_ERROR );
      if ( !(check_status( qcli_status, QCLI_S_CMDERR, 0,
            "CMDERR not cleared", 1 ) ||
           check_status( qcli_status, QCLI_S_FWERR, 0,
             "Error status observed after CLEAR_ERROR", 1 ))) {
         if (verbose) msg( 0, "CMDERR Cleared as expected" );
      }
    }
  }
  
  if (verbose) msg( 0, "Testing Program Mode:" );
  write_qcli( QCLI_LOAD_MSB | 0 );
  qcli_status = wr_rd_qcli( QCLI_WRITE_ADDRESS | 0 );
  if ( check_status( qcli_status, QCLI_S_MODE, QCLI_PROGRAM_MODE,
        "Not in PROGRAM Mode after WRITE_ADDRESS", 0 ) |
       check_status( qcli_status, QCLI_S_CHKSUM, 0,
         "CHECKSUM bit set after WRITE_ADDRESS", 0 ) )
    report_status( qcli_status );
  qcli_status = wr_rd_qcli( QCLI_WRITE_DATA | 0x55 );
  check_status( qcli_status, QCLI_S_CHKSUM, QCLI_S_CHKSUM,
    "CHKSUM bit not set after writing data", 1 );
  write_qcli( QCLI_LOAD_MSB | 0xFF );
  qcli_status = wr_rd_qcli( QCLI_WRITE_DATA | 0xAB );
  check_status( qcli_status, QCLI_S_CHKSUM, 0,
    "CHKSUM bit not cleared after writing complementary data", 1 );
  write_qcli( QCLI_LOAD_MSB | 0x55 );
  qcli_status = wr_rd_qcli( QCLI_WRITE_DATA | 0x55 );
  check_status( qcli_status, QCLI_S_CHKSUM, QCLI_S_CHKSUM,
    "CHKSUM bit not set after writing 3rd data word", 1 );
  write_qcli( QCLI_LOAD_MSB | 0xAA );
  qcli_status = wr_rd_qcli( QCLI_WRITE_CHKSUM | 0xAB );
  check_status( qcli_status, QCLI_S_CHKSUM, 0,
    "CHKSUM bit not cleared after writing complementary checksum", 1 );
  qcli_status = wr_rd_qcli( QCLI_WRITE_DATA | 0x55 );
  check_status( qcli_status, QCLI_S_CHKSUM, QCLI_S_CHKSUM,
    "CHKSUM bit not set after writing 4th data word", 1 );
  write_qcli( QCLI_LOAD_MSB | 0 );
  qcli_status = wr_rd_qcli( QCLI_WRITE_ADDRESS | 0 );
  check_status( qcli_status, QCLI_S_CHKSUM, 0,
    "CHECKSUM bit not cleared after WRITE_ADDRESS", 1 );
  
  qcli_status = wr_rd_qcli( QCLI_STOP );
  check_status( qcli_status, QCLI_S_MODE, QCLI_IDLE_MODE,
    "Not IDLE after STOP", 1 );

  return !qcli_error_reported;
}

void qcli_util::delay(int msec) {
  struct timespec tp;
  tp.tv_sec = 0;
  tp.tv_nsec = msec * 1000000L;
  if (nanosleep( &tp, NULL ) != 0)
    msg(3, "nano_sleep saw signal");
}
