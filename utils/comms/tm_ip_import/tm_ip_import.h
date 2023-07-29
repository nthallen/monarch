/** @file tm_ip_import.h
 * tm_client sub class for telemetry import
 */
#ifndef TM_IP_IMPORT_H_INCLUDED
#define TM_IP_IMPORT_H_INCLUDED
#include "dasio/server.h"
#include "dasio/client.h"
#include "serio_pkt.h"

using namespace DAS_IO;

class ipi_cmd_out;

/**
 * Connect to the local command txsrvr to receive commands,
 * then forwards them to ipi_cmd_out.
 */
class ipi_cmd_in : public Cmd_reader {
  public:
    ipi_cmd_in(const char *iname);
    bool app_input();
  protected:
    // ~ipi_cmd_in();
    // bool not_serio_pkt_hdr();
};

/**
 * Server accepts connection from remote ip_tm_export
 */
class ipi_cmd_out : public Serverside_client {
  public:
    ipi_cmd_out(Authenticator *auth, SubService *SS);
    
    /**
     * @param buf pointer to command string
     * @param nc number of characters in buf
     * @return true if the write fails
     * Wraps the command according to serio_pkt protocol
     * and sends it.
     */
    bool send_cmd(const char *buf, unsigned int nc);
    
    /**
     * @param buf pointer to command string
     * @param nc number of characters in buf
     * @return true if send_cmd() returns true
     * Sends the command if a connection exists,
     * otherwise reports a warning and drops the
     * command.
     */
    static bool cond_send_cmd(const char *buf, unsigned int nc);
    static void attach(Server *S, const char *service);
    static Serverside_client *new_ipi_cmd_out(
        Authenticator *auth, SubService *SS);
    static const int ipi_cmd_out_bufsize = 256;
    static ipi_cmd_out *cmd_out;
    static int cmds_dropped;
  protected:
    bool connected();
    bool close();
    bool app_input(); // unexpected input
}

/**
 * Sends telemetry data to tm_ip_import via UDP
 */

class ipi_tm_out : public Client {
  public:
    ipi_tm_out(const char *iname);
    void send_row(uint16_t MFCtr, const uint8_t *raw);
#ifdef HAVE_SCAN_DATA
    void enqueue_scan(int32_t scannum);
    void ipi_tm_out::send_scan_data();
#endif
  protected:
    // ~ipi_tm_out();
    uint16_t row_len;
    uint16_t rows_per_row; //*< Scan rows transmitted per TM row
    uint16_t rows_this_row; //*< Scan rows transmitted so far this TM row
    bool connect_waiting;
    bool dropping_tx_rows;
    int n_tx_rows_dropped;
    int total_tx_rows_dropped;
};

/**
 * Receives TM data from tm_bfr and forwards it to ipi_tm_out
 */
class ipi_tm_in : public Socket {
  public:
    ipi_tm_in(ipi_tm_out *tm_out);
  protected:
    virtual ~ipi_tm_in();
    unsigned int process_data();
    void process_quit();
    ipi_tm_out *tm_out;
};

#endif
