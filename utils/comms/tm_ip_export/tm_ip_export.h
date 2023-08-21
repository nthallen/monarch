/** @file tm_ip_export.h
 * tm_client sub class for telemetry export
 */
#ifndef TM_IP_EXPORT_H_INCLUDED
#define TM_IP_EXPORT_H_INCLUDED
#include "dasio/tm_client.h"
#include "dasio/serio_pkt.h"

using namespace DAS_IO;

/**
 * Establishes connection to the remote tm_ip_import server.
 * Maintains the Client TCP connection to receive commands and
 * uses UDP to transmit telemetry.
 */
class ipx_cmd_in : public Client {
  public:
    ipx_cmd_in(const char *iname);
    bool app_input();
    void send_row(uint16_t MFCtr, const uint8_t *raw);
  protected:
    // ~ipx_cmd_in();
};

/**
 * Sends telemetry data to tm_ip_import via UDP
 */

class ipx_tm_out : public Socket {
  public:
    ipx_tm_out(const char *iname);
    void send_row(uint16_t MFCtr, const uint8_t *raw);
#ifdef HAVE_SCAN_DATA
    void enqueue_scan(int32_t scannum);
    void ipx_tm_out::send_scan_data();
#endif
  protected:
    // ~ipx_tm_out();
    uint16_t row_len;
    uint16_t rows_per_row; //*< Scan rows transmitted per TM row
    uint16_t rows_this_row; //*< Scan rows transmitted so far this TM row
    bool connect_waiting;
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
    void process_quit();
    ipx_tm_out *tm_out;
};

extern const char *ip_export_cross_exp;
inline void set_cross_exp(const char *exp) { ip_export_cross_exp = exp; }

#endif
