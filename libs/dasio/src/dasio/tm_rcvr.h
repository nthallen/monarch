/**
 * @file tm_rcvr.h
 */

#include "tm.h"
#include "interface.h"

class DAS_IO::tm_rcvr {
  public:
    tm_rcvr(DAS_IO::Interface* interface);
    virtual ~tm_rcvr();
    void load_tmdac(char *path);
    tm_msg_t *tm_msg;
    static unsigned int next_minor_frame, majf_row, minf_row;
    enum tm_state_t {TM_STATE_HDR, TM_STATE_DATA};
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
  private:
    DAS_IO::Interface* interface;
    int nQrows;
    // int bufsize;
    tm_state_t tm_state;
    unsigned int bytes_read; /// number of bytes currently in buf
    unsigned int toread; /// number of bytes needed before next action
    bool tm_info_ready;
    // char *buf;
    // void init(int bufsize_in, const char *srcfile, bool non_block);
    
};
