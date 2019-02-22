/** @file
 subbuspp.h defines the interface to the subbus resident library
 Before calling the subbus routines, you must first call
 load_subbus().  This returns the subfunction of the resident
 subbus library or 0 if none is installed.
 */
#ifndef SUBBUSPP_H_INCLUDED
#define SUBBUSPP_H_INCLUDED
#include <sys/uio.h>
// #include <sys/siginfo.h>
#include <stdint.h>
#include "dasio/client.h"
#include "dasio/loop.h"
#include "subbus.h"
#include "subbusd.h"

#define SUBBUS_VERSION 0x600 /* subbus version 6.00 Portable */
// #define SUBBUS_INTERRUPTS

using namespace DAS_IO;

/**
 * @brief Synchronous subbus interface.
 *
 * [It is possible to implement an asynchronous interface, but
 * that is not this interface.]
 *
 */
class subbuspp : Client {
  public:
    subbuspp(const char *service, const char *sub_service);
    ~subbuspp();
    bool app_connected();
    bool app_input();
    int load();
    const char *get_subbus_name();
    int write_ack(uint16_t addr, uint16_t data);
    int read_ack(uint16_t addr, uint16_t *data);
    uint16_t read_subbus(uint16_t addr);
    uint16_t inline sbrd(uint16_t addr) { return read_subbus(addr); }
    int mread_subbus( subbus_mread_req *req, uint16_t *data);
    int mread_subbus_nw(subbus_mread_req *req, uint16_t *data,
                          uint16_t *nwords);
    subbus_mread_req *pack_mread_requests( unsigned int addr, ... );
    subbus_mread_req *pack_mread_request( int n_reads, const char *req );
    #ifdef SUBBUS_INTERRUPTS
      int subbus_int_attach( char *cardID, uint16_t address,
          uint16_t region, struct sigevent *event );
      int subbus_int_detach( char *cardID );
    #endif
    int subbus_quit(void);

  private:
    int send_to_subbusd( uint16_t command, void *data,
      int data_size, uint16_t exp_type );
    int send_CSF( uint16_t command, uint16_t val );
    subbus_mread_req *pack_mread( int req_len, int n_reads, const char *req_str );
    
    static const uint16_t subbus_version = SUBBUS_VERSION;
    uint16_t subbus_subfunction; // undefined until initialization
    uint16_t subbus_features; // ditto
    char local_subbus_name[SUBBUS_NAME_MAX];
    struct iovec sb_iov[2];
    uint16_t expected_type;
    subbusd_req_hdr_t sb_req_hdr;
    subbusd_rep_t *sb_reply;
    /** Private Loop for synchronous processing */
    Loop PELoop;
};

#endif
