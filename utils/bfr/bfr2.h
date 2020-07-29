#ifndef TMBFR_H_INCLUDED
#define TMBFR_H_INCLUDED
#include <pthread.h>
#include "dasio/tm.h"
#include "dasio/tm_rcvr.h"
#include "dasio/tm_queue.h"
#include "dasio/server.h"

namespace DAS_IO {
  
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

enum state_t {
  TM_STATE_HDR, TM_STATE_HDR2, TM_STATE_INFO, TM_STATE_DATA
};

class bfr2_output_client;

class bfr2_input_client : public Serverside_client, public tm_rcvr,
                         public tm_queue {
  friend class bfr2_output_client;
  public:
    bfr2_input_client(Authenticator *Auth, const char *iname,
          bool blocking);
    ~bfr2_input_client();
    static const int bfr2_input_client_ibufsize = 4096*3;
    static bool auth_hook(Authenticator *Auth, SubService *SS);
    static bool tmg_opened;
    static bfr2_input_client *tm_gen;
  protected:
    bool protocol_input();
    bool process_eof();
    void process_init();
    void process_tstamp();
    unsigned int process_data();
    void run_input_queue();
    void run_output_queue();
    void read_reply(bfr2_output_client *ocb);
    /**
       Handles the actual trasmission after the message
       has been packed into struct iovecs. It may allocate a
       partial buffer if the request size is smaller than the
       message size.
       @param ocb The reading client's Serverside_client
       @param nb Total number of bytes to write
       @param iov The struct iovec vector
       @param n_parts The number of elements in iov
     */
    void do_read_reply(bfr2_output_client *ocb, int nb,
                        struct iovec *iov, int n_parts);
    /**
     * Delete unreferenced tmq_refs from the head of the chain,
     * then identify how many, if any, Qrows can be retired and
     * retire them.
     */
    void tmq_retire_check();
    /**
     * @param tmqr Pointer to the tmq_ref we will evaluate
     * @param if true, only report minimum of rows referenced
     * by clients with non-empty output buffers.
     * @return The minimum number of Qrows that have been processed
     * by all of the bfr2_output_clients in all_readers.
     */
    int min_reader(tmq_ref *tmqr, bool forcing = false);
    bool blocking;
    state_t state;
    /** Count of rows not transmitted to some or all clients */
    int rows_dropped;
    /** Count of rows dropped dangerously */
    int rows_forced;
    
    // struct part_s {
      // tm_hdrs_t hdr;
      // // char *dptr; // pointer into other buffers
      // // int nbdata; // How many bytes are still expected in this sub-transfer
      // // part.nbdata is replaced with Interface::bufsize. As received data is
      // // processed, buf is advanced and bufsize is reduced until all data is
      // // consumed. This differs from standard Interface semantics, where
      // // consume(n) shifts remaining data
    // } part;
    
    // struct write_s {
      // int nbrow_rec; // bytes per row received
      // int nbhdr_rec; // bytes in the header of data messages
      // int off_msg; // bytes already read from this write
      // int nb_rec; // bytes remaining in this record
      // int off_queue; // bytes already written in this queue block
    // } write;
  private:
    bool process_tm_info();
    // int (bfr2_input_client::*data_state_eval)();
    // int data_state_T3();
};

class bfr2_output_client : public Serverside_client {
  friend class bfr2_input_client;
  public:
    bfr2_output_client(Authenticator *Auth, const char *iname, bool is_fast);
    ~bfr2_output_client();
    static const int bfr2_output_client_ibufsize = 80;
  protected:
    void transmit();
    bool iwritten(int nb);
    bool is_fast;
    struct iovec iov[3];
    
    tm_hdrs_t hdr; // was part.hdr
    
    struct data_s {
      /** Our current timestamp */
      tmq_tstamp_ref *tsp;
      /** The tmq_ref we are referencing */
      tmq_ref *tmqr;
      /** The number of Qrows relative to tmqr we have
          already processed */
      int n_Qrows;
      /** The number of Qrows tied up for output */
      int n_Qrows_pending;
    } data;
    
    struct read_s {
      /** max number of Qrows to be returned with any request */
      int maxQrows;
      int rows_missing; // cumulative count
      bool ready;
    } output;
};

class bfr : public Server {
  public:
    inline bfr() : Server("tm_bfr") {}
    void add_subservices();
  protected:
    bool ready_to_quit();
}

} // namespace DAS_IO

#endif
