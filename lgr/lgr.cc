#include <string.h>
#include <time.h>
#include <errno.h>
#include "tm_client.h"
#include "nl.h"
#include "dasio/msg.h"
#include "nl_assert.h"
#include "oui.h"
#include "lgr.h"

void lgr_init( int argc, char **argv ) {
  int c;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'N':
        tmc_lgr::mlf_config = optarg;
        break;
      case '?':
        msg(3, "Unrecognized Option -%c", optopt);
    }
  }
}

char *tmc_lgr::mlf_config;
unsigned int tmc_lgr::file_limit = 4096*3;

tmc_lgr::tmc_lgr() : tm_client( 4096, 0, 0 ) {
  mlf = mlf_init( 3, 60, 1, "LOG", "dat", mlf_config );
  ofp = NULL;
}

// Since we accept data from any frame, we need to copy the incoming
// frame definition into tm_info so tm_client::process_init()
// will be happy.
void tmc_lgr::process_init() {
  memcpy(&tm_info, &tm_msg->body.init.tm, sizeof(tm_dac_t));
  tm_client::process_init();
}

void tmc_lgr::process_tstamp() {
  tm_client::process_tstamp();
  // There should be room for the TS and at least one row
  // otherwise just move on to the next file.
  if (ofp == NULL ||
      nb_out + sizeof(tm_hdr_t) + sizeof(tstamp_t) +
      nbDataHdr + nbQrow > file_limit) {
    next_file();
  } else {
    write_tstamp();
  }
}

void tmc_lgr::lgr_write(void *buf, int nb, const char *where ) {
  if ( fwrite( buf, nb, 1, ofp ) < 1 )
    msg( 3, "Error %s: %s", where, strerror(errno) );
  fflush(ofp);
  nb_out += nb;
}

void tmc_lgr::next_file() {
  if ( ofp != NULL && fclose(ofp) ) {
    msg( 2, "Error closing file: %s", strerror(errno) );
  }
  ofp = mlf_next_file(mlf);
  if ( ofp == NULL )
    msg( 3, "Unable to open output file" );
  nb_out = 0;
  write_tstamp();
}

void tmc_lgr::write_tstamp() {
  nl_assert( ofp != NULL );
  static tm_hdr_t ts_hdr = { TMHDR_WORD, TMTYPE_TSTAMP };
  lgr_write(&ts_hdr, sizeof(tm_hdr_t), "writing tstamp hdr" );
  lgr_write( &tm_info.t_stmp, sizeof(tstamp_t), "writing tstamp" ); 
}

void tmc_lgr::process_data_t3() {
  tm_data_t3_t *data = &tm_msg->body.data3;
  int n_rows = data->n_rows;
  unsigned short mfctr = data->mfctr;
  unsigned char *wdata = &data->data[0];
  tm_msg_t wmsg;

  wmsg.hdr.tm_id = TMHDR_WORD;
  wmsg.hdr.tm_type = TMTYPE_DATA_T3;
  if ( ofp == NULL ) next_file();

  while (n_rows > 0) {
    int space_remaining = file_limit - nb_out;
    int rows_fit = ( space_remaining - nbDataHdr ) / nbQrow;
    if ( rows_fit < 1 && nb_out == sizeof(tm_hdr_t) + sizeof(tstamp_t) ) 
      rows_fit = 1;
    if ( rows_fit < 1 ) {
      next_file();
    } else {
      if ( rows_fit > n_rows )
	rows_fit = n_rows;
      wmsg.body.data3.n_rows = rows_fit;
      wmsg.body.data3.mfctr = mfctr;
      lgr_write( &wmsg, nbDataHdr, "writing data header" );
      lgr_write( wdata, nbQrow*rows_fit, "writing data" );
      n_rows -= rows_fit;
      mfctr += rows_fit;
      wdata += nbQrow*rows_fit;
      if ( n_rows ) next_file();
    }
  }
}

void tmc_lgr::process_data() {
  switch ( input_tm_type ) {
    case TMTYPE_DATA_T1:
    case TMTYPE_DATA_T2:
      msg(3,"Data type not implemented" );
    case TMTYPE_DATA_T3:
      process_data_t3();
      break;
  }
}

void tminitfunc() {}

int main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  tmc_lgr tmc;
  tmc.operate();
  return 0;
}

