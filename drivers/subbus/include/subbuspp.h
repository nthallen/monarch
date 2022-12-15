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
#include <cstdint>
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
    /**
     * @param service The name of the service
     * @param sub_service The name of the subservice or 0
     */
    subbuspp(const char *service, const char *sub_service);
    ~subbuspp();
    bool app_connected();
    bool app_input();
    /**
     * Establishes connection to the subbus driver.
     * @return Non-zero library subfunction code on success, zero on failure
     */
    int load();
    /**
     * It is a fatal error to call this before a successful load().
     * @return the name of the subbus driver.
     */
    const char *get_subbus_name();
    /**
     * @param addr The register address
     * @param data The data to be written
     * Writes data to the specified address.
     * @return non-zero value if the hardware acknowledge is
     * observed.
     */
    int write_ack(uint16_t addr, uint16_t data);
    /**
     * @param addr The register address
     * @param data Pointer to where the data is to be written
     * Reads data from the specified register address.
     * @return non-zero value if the hardware acknowledge is
     * observed.
     */
    int read_ack(uint16_t addr, uint16_t *data);
    /**
     * Read subbus ignoring acknowledge.
     * @param addr The subbus address
     * @return The value read or zero if no acknowledge was received
     */
    uint16_t read_subbus(uint16_t addr);
    /**
     * Read subbus ignoring acknowledge. A shorter name for read_subbus()
     * @param addr The subbus address
     * @return The value read or zero if no acknowledge was received
     */
    uint16_t inline sbrd(uint16_t addr) { return read_subbus(addr); }
    /**
     * Takes a zero-terminated list of addresses, generates the appropriate
     * text request string and invokes pack_mread().
     * @return the newly allocated request structure.
     */
    subbus_mread_req *pack_mread_requests( unsigned int addr, ... );
    /**
     * Takes a multi-read <addr-list> string and invokes pack_mread().
     * @return the newly allocated request structure.
     */
    subbus_mread_req *pack_mread_request( int n_reads, const char *req );
    /**
     * @param req structure defining multi-read request
     * @param data pointer to where read data should be stored
     * Passes the raw command directly to the subbus driver and parses
     * the return string for a multi-read. Up to req->n_reads values will be
     * written into the array pointed to by the data argument.
     * If the request returns less data than requested, a warning will
     * be issued unless suppressed by set_response().
     * @return Zero on success. If return value is negative, it is the
     * error code returned by the subbusd driver and no values are reported.
     * If it is positive (SBS_NOACK), it indicates that although the
     * requested number of values are reported, at least one of the
     * values did not have an acknowledge, and a zero value was reported.
     */
    int mread_subbus( subbus_mread_req *req, uint16_t *data);
    /**
     * Passes the raw command directly to the subbus driver and parses
     * the return string for a multi-read. Up to req->n_reads values will be
     * written into the array pointed to by the data argument.
     * If the request returns more data than requested, and error
     * will be reported (MSG_ERROR).
     * @param req structure defining multi-read request
     * @param data pointer to where read data should be stored
     * @param nwords pointer to where actual read length should be stored
     * @return Zero on success.
     * If return value is negative, it is the
     * error code returned by the subbusd driver and no values are reported.
     * If it is positive SBS_NOACK (2), it indicates that although the
     * requested number of values are reported, at least one of the
     * values did not have an acknowledge, and a zero value was reported.
     * SBS_ACK(1) means everything is fine.
     */
    int mread_subbus_nw(subbus_mread_req *req, uint16_t *data,
                          uint16_t *nwords);

    /**
     * Historically, tick_sic() has been associated with two timers.
     * The first is a 2-second timeout that can reboot the system.
     * The second is a 2-minute timeout that lights the main fail
     * light indicating that the instrument is not acquiring data.
     * tick_sic() resets either or both timers, depending on the
     * specific hardware.
     * @return Zero on success
     */
    int tick_sic();
    
    /**
     * Disarm the watchdog timer armed by tick_sic()
     */
    int disarm_sic();

    #ifdef SUBBUS_INTERRUPTS
      int subbus_int_attach( char *cardID, uint16_t address,
          uint16_t region, struct sigevent *event );
      int subbus_int_detach( char *cardID );
    #endif
    int subbus_quit(void);
    inline uint16_t get_subfunction() { return subbus_subfunction; }
    inline uint16_t get_features() { return subbus_features; }
    inline uint16_t get_version() { return subbus_version; }
  protected:
    bool connect_failed();
    /**
     @return Status reply from subbusd. Terminates if
     communication with subbusd fails.
     */
    int send_to_subbusd( uint16_t command, void *data,
      int data_size, uint16_t exp_type );
    /** This is an internal function for sending messages
     * with a single uint16_t argument and a simple
     * status return.
     @return non-zero on success. Zero if unsupported.
     */
    int send_CSF( uint16_t command, uint16_t val );
    /** Internal function to handle read_switches() and read_failure(),
     * which take no arguments, return unsigned short or zero if
     * the function is not supported.
     */
    uint16_t read_special(uint16_t command);
  private:
    /**
     Packages a request string into a newly allocated structure that
     can be passed to mread_subbus(). Called by pack_mread_request()
     and pack_mread_requests(). The req_str syntax is:

     \code{.unparsed}
        <req>
          : M <count> '#' <addr_list> '\n'
        <addr_list>
          : <addr_list_elt>
          : <addr_list> ',' <addr_list_elt>
        <addr_list_elt>
          : <addr>
          : <addr> ':' <incr> ':' <addr>
          : <count> '@' <addr>
          : <addr> '|' <count> '@' <addr>

        <count>, <addr>, <incr> are all 1-4 hex digits
      \endcode

      The four current addr_list_elt syntaxes have the following
      meaning:

      \code{.unparsed}
      <addr>:
        Read one word from the specified address
      <addr1> ':' <incr> ':' <addr2>:
        Read one word from each address, starting at <addr1>,
        incremented the address by <incr> and ending
        when the address exceeds <addr2>
      <count> '@' <addr>:
        Read <count> words from <addr>
      <addr1> '|' <count> '@' <addr>:
        Read count1 from <addr1> and read count1 or <count> words
        from <addr>, whichever is less. Returns between 1 and
        <count>+1 words.
      \endcode

     @return the newly allocated request structure.
     */
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
