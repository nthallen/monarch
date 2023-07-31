/** @file tm_ip_import.h
 * tm_client sub class for telemetry import
 */
#ifndef TM_IP_IMPORT_H_INCLUDED
#define TM_IP_IMPORT_H_INCLUDED
#include "dasio/server.h"
#include "dasio/client.h"
#include "dasio/serio_pkt.h"

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
 * Sends telemetry data to serin
 */

class ipi_tm_out : public Client {
  public:
    ipi_tm_out(const char *iname);
    void send_row(uint16_t MFCtr, const uint8_t *raw);
  protected:
    // ~ipi_tm_out();
};

/**
 * Receives TM data from ipx_tm_out via UDP and forwards it to ipi_tm_out
 */
class ipi_tm_in : public Socket {
  public:
    ipi_tm_in(ipi_tm_out *tm_out);
  protected:
    // virtual ~ipi_tm_in();
    /**
     * Check incoming data for packet validity, then forward
     * to ipi_tm_out (for TM data at least) to forward to serin.
    unsigned int protocol_input();
    ipi_tm_out *tm_out;
};

#endif
