#ifndef TM_QUEUE_H_INCLUDED
#define TM_QUEUE_H_INCLUDED
#include "dasio/tm.h"

// I prefer not to allocate and free these structures routinely, but
// I'll start that way. It makes sense to keep a free list for the
// basic types: tstamp_q, tmq_tstamp_ref and tmq_data_ref. Actually,
// I guess that can be optimized via definition of new and delete
// operators.

// Define a hierarchy here. A tmq_descriptor can either hold
// a timestamp or reference data rows in the tmq.
// This works within tm_gen because we don't have readers starting
// and stopping. We have exactly one reader that will go
// through all the data.

namespace DAS_IO {

enum tmqtype { tmq_tstamp, tmq_data  };

class tmq_ref {
  public:
    tmq_ref(tmqtype mytype);
    tmq_ref *next(tmq_ref *tmqr);
    tmq_ref *next_tmqr;
    tmqtype type;
};

class tmq_tstamp_ref : public tmq_ref {
  public:
    tmq_tstamp_ref( mfc_t MFCtr, time_t time );
    tstamp_t TS;
};

class tmq_data_ref : public tmq_ref {
  public:
    tmq_data_ref(mfc_t MFCtr, int mfrow, int Qrow_in, int nrows_in );
    void append_rows( int nrows );
    mfc_t MFCtr_start, MFCtr_next;
    int row_start, row_next;
    int Qrow;
    int n_rows;
};

/* Semantics of tm_queue
   tm_queue.first, .last are indices into row and range from
     [0..total_Qrows)
   .first is where the next row will be read from
   .last is where the next row will be written to
   first==last means either full or empty, depending on the value of full.
   
   if collection is true, then allocate_rows will throw rather than block
*/
extern void tminitfunc();
class tm_queue {
  public:
    tm_queue( int n_Qrows, int low_water );
    void init(); // allocate space for the queue

  protected:
    int allocate_rows(unsigned char **rowp);
    void commit_rows( mfc_t MFCtr, int mfrow, int n_rows );
    void commit_tstamp( mfc_t MFCtr, time_t time );
    void retire_rows( tmq_data_ref *tmqd, int n_rows );
    void retire_tstamp( tmq_tstamp_ref *tmqts );
    virtual void lock(const char * by = 0, int line = -1);
    virtual void unlock();

    unsigned char *raw;
    unsigned char **row;
    tm_hdrw_t output_tm_type;
    int total_Qrows;
    int nbQrow; // may differ from nbrow if stripping MFCtr & Synch
    int nbDataHdr;
    int first;
    int last;
    bool full;
    
    tmq_ref *first_tmqr;
    tmq_ref *last_tmqr;
    int tmq_low_water;
};

}

#endif
