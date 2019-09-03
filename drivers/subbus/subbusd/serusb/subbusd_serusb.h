#ifndef SERUSB_H_INCLUDED
#define SERUSB_H_INCLUDED
#include "subbusd_int.h"

/**
 SB_SERUSB_MAX_REQUEST is the maximum allowable string
 for a serialized command over the USB.
 The longest request will be for the multi-read
 command, and we may see fit to extend this size.

 The multi-read response may also be even longer, but
 we do not necessarily have to allocate buffer space for
 the entire response, since we can process it as it comes
 in.
 */
#define SB_SERUSB_MAX_REQUEST 256
#define SB_SERUSB_MAX_RESPONSE 2501

typedef struct {
  int type;
  int status;
  int rcvid;
  unsigned short n_reads;
  char request[SB_SERUSB_MAX_REQUEST];
} sbd_request_t;

#define SBDR_TYPE_INTERNAL 0
#define SBDR_TYPE_CLIENT 1
#define SBDR_TYPE_MAX 1
#define SBDR_STATUS_QUEUED 0
#define SBDR_STATUS_SENT 1

/* SUBBUSD_MAX_REQUESTS is the size of the request queue,
   so it determines the number of simultaneous requests 
   we can handle. Current usage suggests we will have
   a small number of programs accessing the subbus
   (col,srvr,idxr,dccc,ana104,card,digital) so 20 is
   not an unreasonable upper bound */
#define SUBBUSD_MAX_REQUESTS 20

extern int int_attach(int rcvid, subbusd_req_t *req, char *sreq);
extern int int_detach(int rcvid, subbusd_req_t *req, char *sreq);

class subbusd_serusb_client : public subbusd_client {
  public:
    subbusd_serusb_client(DAS_IO::Authenticator *auth, subbusd_serusb *fl);
    ~subbusd_serusb_client();
    bool incoming_sbreq();
    void request_complete(int16_t status, uint16_t n_bytes);
    // static const int subbusd_serusb_max_req_size = 512;
    // static const int subbusd_serusb_max_rep_size = 512;
  private:
    /**
     * Sets up the framework for processing an mread request, then calls process_mread().
     */
    void setup_mread();
    /**
     * Process a step in the mread
     */
    void process_mread();
    void format_mread_rd();
    subbusd_serusb *flavor;
    /** Where we assemble serusb messages */
    uint16_t mread_word_space_remaining;
    uint16_t mread_words_requested;
    can_msg_t can_msg;
};

class serusb_if : public DAS_IO::Serial {
  public:
    serusb_if(const char *port, int baud_rate);
    // ~serusb_if();
    bool protocol_input();
    bool protocol_timeout();
  private:
    void process_requests();
    std::list<serusb_request> reqs;
    bool request_pending;
    bool request_processing;
};

class subbusd_serusb : public subbusd_flavor {
  public:
    subbusd_serusb(const char *port, int baud_rate);
    ~subbusd_serusb();
    void init_subbus();
    void shutdown_subbus();
    inline void enqueue_request(can_msg_t *can_msg, uint8_t *rep_buf,
        int buflen, subbusd_serusb_client *clt) {
          serusb->enqueue_request(can_msg, rep_buf, buflen, clt);
      }
  private:
    // serusb sockets, states, etc.
    serusb_if *serusb;
};

// extern const char *serusb_port;
// extern int serusb_baud_rate;

#endif
