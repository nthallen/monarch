#ifndef TM_RCVR_H_INCLUDED
#define TM_RCVR_H_INCLUDED

/**
 * @file tm_rcvr.h
 */

#include "tm.h"
#include "interface.h"

namespace DAS_IO {

  /**
   * @brief DAS_IO::tm_rcvr is a pure virtual class for
   * subclasses that receive telemetry data. These of course
   * include DAS_IO::tm_client, but also rdr's Reader.
   * Ultimately bfr should also use this class.
   */

class tm_rcvr {
  public:
    tm_rcvr(DAS_IO::Interface* interface);
    virtual ~tm_rcvr();
    void load_tmdac(char *path);
    tm_msg_t *tm_msg;
    static unsigned int next_minor_frame, majf_row, minf_row;
    enum tm_state_t {TM_STATE_HDR, TM_STATE_INIT, TM_STATE_TSTAMP,
                     TM_STATE_DATA};
  protected:
    void process_message();
    virtual void process_init();
    void init_tm_type();
    virtual void process_tstamp();
    virtual void process_data() = 0;
    void seek_tmid();
    void tm_expect_hdr();
    virtual const char *context();
    unsigned int ncc;
    unsigned int cp;
    int nbQrow; // may differ from nbrow if stripping MFCtr & Synch
    int nbDataHdr;
    tm_hdrw_t input_tm_type;
    mfc_t buf_mfctr; /// MFCtr of first row in buf
    unsigned int rows_in_buf; /// Number of data rows currently in buf
    uint8_t *data_row; /// Start of first row in buf
  private:
    DAS_IO::Interface* interface;
    int nQrows;
    tm_state_t tm_state;
    unsigned int bytes_read; /// number of bytes currently in buf
    unsigned int rows_left_in_msg;
    unsigned int toread; /// number of bytes beyond cp needed before next action
    bool tm_info_ready;
    
};

}

#endif

