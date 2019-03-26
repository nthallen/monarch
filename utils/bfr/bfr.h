#ifndef TMBFR_H_INCLUDED
#define TMBFR_H_INCLUDED
#include <pthread.h>
#include "dasio/tm.h"
#include "dasio/tm_queue.h"

typedef struct tsqueue {
  int ref_count;
  tstamp_t TS;
} TS_queue_t;

/* Semantics of the dq_descriptor
   next points to a later descriptor. A separate descriptor is
     required when a new TS arrives or a row is skipped.
   ref_count indicates how many OCBs point to this dqd
   starting_Qrow is the index into Data_Queue.row for the first data
     row of this dqd that is still present in the Data_Queue, or the location
     of the next record if no rows are present.
   n_Qrows is the number of Qrows of this dqd still present in the
     Data_Queue, hence must be <= Data_Queue.total_Qrows.
   Qrows_expired indicates the number of Qrows belonging to this dqd
     that have been expired out of the Data_Queue
    min_reader is the number of rows in this dqd that the slowest
      reader has processed (including expired rows)
   TSq is the TS record our data is tied to
   MFCtr is the MFCtr for the starting row (possibly expired) of this
     dqd
   Row_num is the row number (0 <= Row_num < nrowminf) for the
     starting row (possibly expired) of this dqd

   n_Qrows + Qrows_expired is the total number of Qrows for this dqd
   
   To get the MFCtr and Row_Num for the current first row:
   XRow_Num = Row_Num + Qrows_expired
   NMinf = XRow_Num/tm->nrowminf
   MFCtr_start = MFCtr + NMinf
   Row_Num_start = XRow_Num % tm->nrowminf
   
   If n_Qrows == 0 and Qrows_expired == 0, MFCtr and Row_num can be
   redefined. After that, progress simply involves updating
   starting_Qrow, n_Qrows and Qrows_expired.
*/
typedef struct dq_descriptor {
  struct dq_descriptor *next;
  int ref_count;
  int starting_Qrow;
  int n_Qrows;
  int Qrows_expired;
  int min_reader;
  TS_queue_t *TSq;
  mfc_t MFCtr;
  int Row_num;
} dq_descriptor_t;

typedef struct {
  dq_descriptor_t *first;
  dq_descriptor_t *last;
} DQD_Queue_t;

typedef enum {
  TM_STATE_HDR, TM_STATE_INFO, TM_STATE_DATA
} state_t;

class bfr_input_client : public Serverside_client {
  public:
    bfr_input_client(Authenticator *Auth, const char *iname, bool blocking);
    ~bfr_input_client();
    static const int bfr_input_client_ibufsize = 16384;
    static bool auth_hook(Authenticator *Auth, Subservice *SS);
    static bool tmg_opened;
  protected:
    bool protocol_input();
    bool blocking;
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