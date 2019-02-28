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
    bool protocol_input();
    bool iwritten();
    virtual bool incoming_sbreq();
  protected:
    bool status_return(uint16_t err_code);
    bool request_pending;
    subbusd_req_t *req;
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
    unsigned short address;
    unsigned int reg_id;
    unsigned int bitno;
    struct sigevent event;
    int owner;
  } card_def;

  typedef struct {
    unsigned short address;
    unsigned short bits;
    card_def *def[8];
  } region;
  #define MAX_REGIONS 4

  extern card_def *carddefs;
  extern region regions[MAX_REGIONS];
  extern int expint_attach( int rcvid, char *cardID, unsigned short address,
                        int region, struct sigevent *event, card_def **card );
  extern int expint_detach( int rcvid, char *cardID, unsigned short *addr,
                        unsigned int *bn );

#endif // SUBBUS_INTERRUPTS

#ifdef SUBBUS_CACHE
  extern char *cache_hw_range, *cache_sw_range;
  extern void sb_cache_init(void);
  extern int sb_cache_write( unsigned short addr, unsigned short data );
  extern int sb_cache_read( unsigned short addr, unsigned short *data );
#endif

#endif
