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
   * 
   * An implementation can create a subclass that inherits
   * from an Interface class and tm_rcvr, or a subclass
   * could inherit from tm_rcvr and simply refer to another
   * Interface class.
   */

class tm_rcvr {
  public:
    tm_rcvr(DAS_IO::Interface* interface);
    virtual ~tm_rcvr();
    void load_tmdac(char *path);
    tm_msg_t *tm_msg;
    static unsigned int next_minor_frame, majf_row, minf_row;
    enum tm_state_t {TM_STATE_HDR, TM_STATE_INIT, TM_STATE_TSTAMP,
                     TM_STATE_DATA_HDR, TM_STATE_DATA};
  protected:
    /**
     * process_message() can generally be called directly from
     * a protocol_input() or app_input() function. It uses the
     * Interface's buf.
     */
    void process_message();
    virtual void process_init();
    void init_tm_type();
    virtual void process_tstamp();
    /**
     * Called when one or more contiguous rows of data are
     * ready for processing in buf. buf_mfctr, rows_in_buf
     * and data_row are all defined before the call, and
     * it is assumed that process_data() will process that
     * data before returning.
     */
    virtual unsigned int process_data() = 0;
    void seek_tmid();
    void tm_expect_hdr();
    virtual const char *context();
    /** number of chars in interface->buf that have not been processed */
    unsigned int ncc;
    /** number of chars in interface->buf that have been processed */
    unsigned int cp;
    /** number of bytes in a row of storage in the tm_queue.
     *  This may differ from nbrow if stripping MFCtr & Synch.
     */
    int nbQrow;
    /** number of bytes in the TM header for this stream's
     *  data type (currently fixed at TMTYPE_DATA_T3)
     */
    int nbDataHdr;
    /** The streams data type. (currently fixed at TMTYPE_DATA_T3) */
    tm_hdrw_t input_tm_type;
    /** MFCtr of first row in buf.
     *  Defined before calling process_data();
     */
    mfc_t buf_mfctr;
    /** Number of contiguous data rows currently at buf[cp].
     *  Defined before calling process_data();
     */
    unsigned int rows_in_buf;
    /** Start of first row in buf at buf[cp].
     *  Defined before calling process_data();
     */
    uint8_t *data_row;
    /**
     * true if in process_message() to prevent reentrancy.
     */
    bool processing_message;
  private:
    DAS_IO::Interface* interface;
    int nQrows;
    tm_state_t tm_state;
    /** number of bytes currently in buf */
    unsigned int bytes_read;
    /** for tracking progress through large data records */
    unsigned int rows_left_in_msg;
    /** number of bytes beyond cp needed before next action */
    unsigned int toread;
    /** true if we have received the tm_info data */
    bool tm_info_ready;
    
};

}

#endif

