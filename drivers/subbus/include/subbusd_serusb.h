#ifndef SERUSB_H_INCLUDED
#define SERUSB_H_INCLUDED
#include <stdint.h>
#include "dasio/serial.h"
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

class subbusd_serusb_client;
class subbusd_serusb;

extern int int_attach(int rcvid, subbusd_req_t *req, char *sreq);
extern int int_detach(int rcvid, subbusd_req_t *req, char *sreq);

class subbusd_serusb_client : public subbusd_client {
  public:
    subbusd_serusb_client(DAS_IO::Authenticator *auth, subbusd_serusb *fl);
    ~subbusd_serusb_client();
    bool incoming_sbreq();
    void request_complete(uint16_t n_bytes);
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
    char sreq[SB_SERUSB_MAX_REQUEST];
    /** Size of the request in sreq */
    int req_size;
    //uint16_t mread_word_space_remaining;
    //uint16_t mread_words_requested;
};

#define SBDR_TYPE_INTERNAL 0
#define SBDR_TYPE_CLIENT 1
#define SBDR_TYPE_UNDEF 2
#define SBDR_TYPE_MAX 1

/* SUBBUSD_MAX_REQUESTS is the size of the request queue,
   so it determines the number of simultaneous requests 
   we can handle. Current usage suggests we will have
   a small number of programs accessing the subbus
   (col,srvr,idxr,dccc,ana104,card,digital) so 20 is
   not an unreasonable upper bound */
#define SUBBUSD_MAX_REQUESTS 20

class serusb_request {
  public:
    inline serusb_request()
      : type(SBDR_TYPE_UNDEF),
        clt(0),
        request(0),
        repp(0),
        n_reads(0) {}
    inline serusb_request(uint16_t type, subbusd_serusb_client *clt,
      const char *request, subbusd_rep_t *repp, uint16_t n_reads = 0)
      : type(type),
        clt(clt),
        request(request),
        repp(repp),
        n_reads(n_reads) {}
    uint16_t type;
    subbusd_serusb_client *clt;
    const char *request;
    /**
     * Pointer to the client's reply buffer
     */
    subbusd_rep_t *repp;
    uint16_t n_reads;
};

// typedef struct {
  // int type;
  // int status;
  // int rcvid;
  // uint16_t n_reads;
  // char request[SB_SERUSB_MAX_REQUEST];
// } sbd_request_t;

class serusb_if : public DAS_IO::Serial {
  public:
    serusb_if(const char *port);
    // ~serusb_if();
    void enqueue_request(uint16_t type, subbusd_serusb_client *clt,
      const char *request, subbusd_rep_t *repp, uint16_t n_reads);
    uint16_t type;
    subbusd_serusb_client *clt;
    uint16_t n_reads;
    const char *request;
  private:
    bool protocol_input();
    bool protocol_timeout();
    bool advance_if_char(unsigned char c);
    bool read_hex(uint16_t &arg);
    void process_response();
    #ifdef SUBBUS_INTERRUPTS
    void process_interrupt();
    #endif
    void process_requests();
    /**
     * @param status Request status (SBS_* codes) returned to client
     * @param n_args The number of arguments in the reply
     * @param arg0 Optional uint16_t argument
     * @param arg1 Optional uint16_t argument
     * @param s String argument for SBRT_CAP
     */
    void dequeue_request(int16_t status, int n_args, uint16_t arg0,
                         uint16_t arg1, const char *s);
    std::list<serusb_request> reqs;
    bool request_pending;
    bool request_processing;
    // Do I need reply structure here, or should it live in the flavor?
};

class subbusd_serusb : public subbusd_flavor {
  public:
    subbusd_serusb(const char *port, int baud_rate);
    ~subbusd_serusb();
    void init_subbus();
    void shutdown_subbus();
    inline void enqueue_request(uint16_t type, subbusd_serusb_client *clt,
      const char *request, subbusd_rep_t *repp, uint16_t n_reads) {
          serusb->enqueue_request(type, clt, request, repp, n_reads);
      }
  private:
    // serusb sockets, states, etc.
    serusb_if *serusb;
};

// extern const char *serusb_port;
// extern int serusb_baud_rate;

#endif
