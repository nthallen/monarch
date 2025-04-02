/** @file tm_ip_export.h
 * tm_client sub class for telemetry export
 */
#ifndef TM_IP_EXPORT_H_INCLUDED
#define TM_IP_EXPORT_H_INCLUDED
#include <deque>
#include "dasio/tm_client.h"
#include "dasio/serio_pkt.h"
#include "dasio/cmd_reader.h"
#include "dasio/server.h"

using namespace DAS_IO;

class ipx_relay;

class ipx_type {
  public:
    inline ipx_type(bool is_UDP) : is_UDP(is_UDP) {}
    bool is_UDP;
    static ipx_type ipx_tcp;
    static ipx_type ipx_udp;
};

class ipx_client : public Serverside_client
{
  public:
    ipx_client(Authenticator *auth, const char *iname, ipx_type *xtype);
    void xfer_confirmed(uint16_t nbytes);
    inline const uint8_t *get_current_packet() { return buf; }
    bool tcp_txfr_requested;

    static void attach(Server *S, ipx_type *xtype);
    static Serverside_client *new_ipx_client(
        Authenticator *auth, SubService *SS);
  protected:
    /**
     * Receives serio_pkt-encoded messages for UDP or TCP
     * downlink, depending on the Subservice.
     */
    bool protocol_input();
    bool is_UDP;
    ipx_relay *relay;
};

/**
 * Establishes connection to the remote tm_ip_import server.
 * Maintains the Client TCP connection to receive commands and
 * uses UDP to transmit telemetry.
 */
class ipx_cmd_in : public Client {
  public:
    ipx_cmd_in(const char *iname);
    bool app_input();
    bool send_tcp(const uint8_t *pkt, uint16_t len);
    inline bool CTS() { return obuf_empty(); }
  protected:
    // ~ipx_cmd_in();
    /** reset() instead of returning true */
    bool process_eof();
};

/**
 * Sends telemetry data to tm_ip_import via UDP
 */

class ipx_tm_out : public Socket {
  public:
    ipx_tm_out(const char *iname);
    void send_row(uint16_t MFCtr, const uint8_t *raw);
    void update_MTU(int new_MTU);
    /**
     * Called by ipx_tm_out::flush() and ipx_client::
     */
    void send_udp(const uint8_t *data, int length);
    inline bool CTS() { return obuf_empty(); }
    static const int max_MTU = 1500;
    static const int IP_header_len = 20;
    static const int UDP_header_len = 8;
  protected:
    virtual ~ipx_tm_out();
    void flush();
    ipx_relay *relay;
    uint16_t row_len;
    uint16_t rows_per_row; //*< Scan rows transmitted per TM row
    uint16_t rows_this_row; //*< Scan rows transmitted so far this TM row
    bool dropping_tx_rows;
    int n_tx_rows_dropped;
    int total_tx_rows_dropped;
    int MTU;
    int max_udp_payload;
    uint8_t *payload;
    unsigned int pyld_nc;
};

class ipx_relay : public Interface {
  public:
    ipx_relay(const char *iname, ipx_tm_out *udp, ipx_cmd_in *tcp);
    /**
     * Forwards packets to tm_ip_import by UDP without regulation.
     * @param hdr Pointer to the header of a validated serio_pkt message.
     * @param len If zero, length will be determined from the packet header.
     *   If non-zero, payload may consist of more than one header.
     * @returns true on a significant failure
     */
    bool send_udp(const uint8_t *hdr, uint16_t len = 0);
    /**
     * Forwards packets to tm_ip_import by TCP with regulation. hdr cannot
     * be modified until the ipx_client's xfer_confirmed() is called.
     * @returns true on a significant failure
     */
    bool send_tcp_req(ipx_client *clt);
    static inline void set_instance(ipx_relay *x) { instance = x; }
    static ipx_relay *get_instance();
    static const int TCP_header_len = 16; // does not include options, etc.
  protected:
    void record_nbytes(int nbytes);
    void process_queue();
    std::deque<ipx_client*> tcp_queue;
    ipx_tm_out *udp;
    ipx_cmd_in *tcp;
    bool dropping_udp;
    int n_udp_dropped;
    struct timespec when_queued;
    int msecs_queued;
    static ipx_relay *instance;
};

/**
 * Receives TM data from tm_bfr and forwards it to ipx_tm_out
 */
class ipx_tm_in : public tm_client {
  public:
    ipx_tm_in(ipx_tm_out *tm_out);
  protected:
    virtual ~ipx_tm_in();
    unsigned int process_data();
    void process_init();
    void process_quit();
    ipx_tm_out *tm_out;
};

class ipx_ctrl : public Cmd_reader {
  public:
    ipx_ctrl(const char *iname, const char *cmdchannel, ipx_tm_out *tm_out);
    bool app_input() override;
  protected:
    ipx_tm_out *tm_out;
    // virtual ~ipx_ctrl();
};

extern const char *ip_export_cross_exp;
inline void set_cross_exp(const char *exp) { ip_export_cross_exp = exp; }

#endif
