/**
 * @file tm_rcvr.h
 */

class tm_rcvr {
  public:
    tm_rcvr(DAS_IO::Interface* interface);
    virtual ~tm_rcvr();
    tm_msg_t *tm_msg;
    static unsigned int next_minor_frame, majf_row, minf_row;
  protected:
    void process_message();
    virtual void process_init();
    void init_tm_type();
    virtual void process_tstamp();
    virtual void process_data() = 0;
    void seek_tmid();
    void tm_expect_hdr();
    virtual const char *context();
    unsigned int nc;
    int nbQrow; // may differ from nbrow if stripping MFCtr & Synch
    int nbDataHdr;
    tm_hdrw_t input_tm_type;
  private:
    DAS_IO::Interface* interface;
    int nQrows;
    // int bufsize;
    int tm_state;
    unsigned int bytes_read; /// number of bytes currently in buf
    unsigned int toread; /// number of bytes needed before next action
    bool tm_info_ready;
    // char *buf;
    // void init(int bufsize_in, const char *srcfile, bool non_block);
    
}