#ifndef TMBFR_H_INCLUDED
#define TMBFR_H_INCLUDED
#include <pthread.h>
#include "dasio/tm.h"
#include "dasio/tm_queue.h"

typedef enum {
  TM_STATE_HDR, TM_STATE_INFO, TM_STATE_DATA
} state_t;

class bfr_input_client : public Serverside_client {
  public:
    bfr_input_client(Authenticator *Auth, const char *iname);
    ~bfr_input_client();
    static const int bfr_input_client_ibufsize = 16384;
    // Include whatever virtual function overrides you need here
  protected:
    enum state_t state;
    
    struct part_s {
      tm_hdrs_t hdr;
      char *dptr; // pointer into other buffers
      int nbdata; // How many bytes are still expected in this sub-transfer
    } part;
    
    struct data_s {
      dq_descriptor_t *dqd; // Which dq_desc we reference
      int n_Qrows; // The number of Qrows in dq we have already processed
    } data;
    
    struct write_s {
      char *buf; // allocated temp buffer
      //int rcvid; // Who is writing
      int nbrow_rec; // bytes per row received
      int nbhdr_rec; // bytes in the header of data messages
      int nb_msg; // bytes remaining in this write
      int off_msg; // bytes already read from this write
      int nb_rec; // bytes remaining in this record
      int off_queue; // bytes already read in this queue block
    } write;
};

class bfr_output_client : public Serverside_client {
  public:
    bfr_output_client(Authenticator *Auth, const char *iname, bool is_fast);
    ~bfr_output_client();
    static const int bfr_output_client_ibufsize = 80;
    // Include whatever virtual function overrides you need here
  protected:
    bool is_fast;
    enum state_t state;
    
    struct part_s {
      tm_hdrs_t hdr;
      char *dptr; // pointer into other buffers
      int nbdata; // How many bytes are still expected in this sub-transfer
    } part;
    
    struct data_s {
      dq_descriptor_t *dqd; // Which dq_desc we reference
      int n_Qrows; // The number of Qrows in dq we have already processed
    } data;
    
    struct read_s {
      char *buf; // allocated temp buffer
      //int rcvid; // Who requested
      int nbytes; // size of request
      int maxQrows; // max number of Qrows to be returned with this request
      int rows_missing; // cumulative count
      //bool blocked;
    } read;
};

#endif