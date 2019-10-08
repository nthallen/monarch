#ifndef SUBBUSD_INT_H_INCLUDED
#define SUBBUSD_INT_H_INCLUDED
#include "dasio/server.h"
#include "subbusd.h"

/** \file
  * \brief Defines interface between QNX6 resource manager and subbus hardware
  *
  * A different hardware architecture can be supported by reimplementing these
  * functions.
  */

extern const char *subbusd_service;
extern bool subbusd_cmd_quit;
void subbusd_init_options(int argc, char **argv);

class subbusd_flavor {
  public:
    subbusd_flavor(const char *flavor, DAS_IO::socket_clone_t cloner);
    ~subbusd_flavor();
    const char *flavor;
    virtual void init_subbus();
    virtual void shutdown_subbus();
    DAS_IO::socket_clone_t cloner;
};

class subbusd_client : public DAS_IO::Serverside_client {
  public:
    subbusd_client(DAS_IO::Authenticator *orig);
    ~subbusd_client();
    /**
     * Performs sanity checks on the incoming request from the client,
     * then calls incoming_sbreq() to process the request in a
     * flavor-specific way.
     * @return true if the event loop should terminate.
     */
    bool protocol_input();
    /**
     * Marks request as complete when the reply has been fully transmitted.
     * @return true if event loop should terminate. Always returns false.
     */
    bool iwritten(int nb);
    /**
     * Incoming request is a subbusd_req_t in the underlying Interface's buf
     * and also pointed to by req.
     * 
     * @return true if event loop should exit.
     */
    virtual bool incoming_sbreq();
  protected:
    /**
     * Utility function to return the reply structure along with the
     * specified return code.
     * @param err_code to send to the client.
     * @return false
     */
    bool status_return(uint16_t err_code);
    /**
     * True if a request from this client is not complete.
     */
    bool request_pending;
    /**
     * Pointer to the client's request, contained in buf.
     */
    subbusd_req_t *req;
    /**
     * The reply data structure.
     */
    subbusd_rep_t rep;
};

class subbusd_core {
  public:
    subbusd_core(const char *service);
    ~subbusd_core();
    void register_flavor(subbusd_flavor *);
    DAS_IO::Server srvr;
    void Start(DAS_IO::Server::Srv_type type);
    static subbusd_core *subbusd;
  private:
    std::list<subbusd_flavor*> devs;
};

#ifdef SUBBUS_INTERRUPTS

  typedef struct carddef {
    struct carddef *next;
    char cardID[ CardID_MAX ];
    uint16_t address;
    unsigned int reg_id;
    unsigned int bitno;
    struct sigevent event;
    int owner;
  } card_def;

  typedef struct {
    uint16_t address;
    uint16_t bits;
    card_def *def[8];
  } region;
  #define MAX_REGIONS 4

  extern card_def *carddefs;
  extern region regions[MAX_REGIONS];
  extern int expint_attach( int rcvid, char *cardID, uint16_t address,
                        int region, struct sigevent *event, card_def **card );
  extern int expint_detach( int rcvid, char *cardID, uint16_t *addr,
                        unsigned int *bn );

#endif // SUBBUS_INTERRUPTS

#ifdef SUBBUS_CACHE
  extern char *cache_hw_range, *cache_sw_range;
  extern void sb_cache_init(void);
  extern int sb_cache_write( uint16_t addr, uint16_t data );
  extern int sb_cache_read( uint16_t addr, uint16_t *data );
#endif

#endif
