/** \file tm_client.h
 * TM Client Classes
 */
#ifndef TM_CLIENT_H_INCLUDED
#define TM_CLIENT_H_INCLUDED
#include <stdio.h>
#include "tm.h"

#ifdef __cplusplus

/**
 * \brief Defines interface for tm client connection to TMbfr
 */
class tm_client {
  public:
    tm_client(int bufsize_in, int fast = 0, int non_block = 0);
    tm_client(int bufsize_in, int non_block, char *srcfile);
    void operate(); // event loop
    void resize_buffer(int bufsize_in);
    void load_tmdac(char *path);
    static unsigned int next_minor_frame, majf_row, minf_row;
    static char *srcnode;
  protected:
    virtual void process_data() = 0;
    virtual void process_init();
    virtual void process_tstamp();
    virtual int process_eof();
    int bfr_fd;
    void read();
    bool tm_quit;
    virtual const char *context();
    void tm_init();
    void seek_tmid();
    tm_msg_t *tm_msg;
    int nbQrow; // may differ from nbrow if stripping MFCtr & Synch
    int nbDataHdr;
    tm_hdrw_t input_tm_type;
    void init_tm_type();
  private:
    void process_message();
    int nQrows;
    int bufsize;
    int tm_state;
    unsigned int bytes_read; /// number of bytes currently in buf
    unsigned int toread; /// number of bytes needed before next action
    bool tm_info_ready;
    char *buf;
    void init(int bufsize_in, int non_block, const char *srcfile);
};

#define TM_STATE_HDR 0
#define tm_state_DATA 1

class ext_tm_client : public tm_client {
  public:
    inline ext_tm_client(int bufsize_in, int fast = 0, int non_block = 0) :
      tm_client(bufsize_in, fast, non_block) {}
  protected:
    void process_data();
};

extern void tminitfunc();

extern "C" {
#endif

/* This is all that is exposed to a C module */
extern void tm_set_srcnode(char *nodename);

#ifdef __cplusplus
};
#endif

#endif
