/** @file tm_ip_export.h
 * tm_client sub class for telemetry export
 */
#ifndef TM_IP_EXPORT_H_INCLUDED
#define TM_IP_EXPORT_H_INCLUDED
#include <netdb.h>
#include <netinet/in.h>
#include "dasio/tm_client.h"
#include "serio_pkt.h"

using namespace DAS_IO;

/**
 * Establishes connection to the remote tm_ip_import server.
 * Maintains the Client TCP connection to receive commands and
 * uses UDP to transmit telemetry.
 */
class ipx_cmd_in : public Client {
  public:
    ipx_cmd_in();
    bool app_input();
    void send_row(uint16_t MFCtr, const uint8_t *raw);
  protected:
    virtual ~ipx_cmd_in();
    bool not_serio_pkt_hdr();
};

/**
 * Sends telemetry data to tm_ip_import via UDP
 */

class UDP : public Socket {
  public:
    typedef enum { UDP_READ, UDP_WRITE, UDP_BROADCAST } UDP_mode_t;
    UDP(const char *iname, UDP_mode_t mode, const char *function,
        const char *service, int bufsz);
    ~UDP();
  protected:
    udp_mode_t mode;
  private:
    // int UDP_init();
    // char *buf;
    // int buflen;
    // const char *broadcast_ip;
    // const char *broadcast_port;
    // int bcast_sock;
    // bool ok_status;
    // bool ov_status;
    // struct sockaddr_in s;
    // socklen_t addrlen;
    // bool sendto_err_reported;
};

class ipx_tm_out : public UDP {
  public:
    ipx_tm_out();
  protected:
    ~ipx_tm_out();
    bool dropping_tx_rows;
    int n_tx_rows_dropped;
    int total_tx_rows_dropped;
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
    ipx_tm_out *tm_out;
};

#endif
