/** @file tm_ip_import.h
 * tm_client sub class for telemetry import
 */
#ifndef TM_IP_IMPORT_H_INCLUDED
#define TM_IP_IMPORT_H_INCLUDED
#include "dasio/server.h"
#include "dasio/client.h"
#include "dasio/cmd_reader.h"
#include "dasio/serio_pkt.h"
#include "mlf_packet_logger.h"

using namespace DAS_IO;

/**
 * Supports locally logging of all serio_pkt data, including telemetry
 * and forwarding of all packets to a relay process. The relay may
 * provide selective packet relaying.
 */
class ipi_relay : public Interface, mlf_packet_logger {
  public:
    ipi_relay(const char *iname);
    /**
     * Logs packets based on mlf_base and mlf_config inputs, then
     * forwards them to any connected Clients.
     * @param hdr Pointer to the header of a validated serio_pkt message.
     * @returns true on a significant failure
     */
    bool forward(const unsigned char *hdr);
    static ipi_relay *get_instance();
    static ipi_relay *instance;
    static const char *mlf_base;
    static const char *mlf_config;
  protected:
};

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
    ipi_cmd_out(Authenticator *auth, const char *iname);
    
    /**
     * @param buf pointer to command string
     * @param nc number of characters in buf
     * @return true if send_cmd() returns true
     * Sends the command if a connection exists,
     * otherwise reports a warning and drops the
     * command.
     */
    static bool cond_send_cmd(uint8_t *buf, unsigned int nc);
    static void attach(Server *S, const char *service);
    static Serverside_client *new_ipi_cmd_out(
        Authenticator *auth, SubService *SS);
    // static const int ipi_cmd_out_bufsize = 256;
    static ipi_cmd_out *cmd_out;
    static int cmds_dropped;
  protected:
    ~ipi_cmd_out();
    bool protocol_input() override;
    bool connected();
    void close();
    
    /**
     * @param buf pointer to command string
     * @param nc number of characters in buf
     * @return true if the write fails
     * Wraps the command according to serio_pkt protocol
     * and sends it.
     */
    bool send_serio_pkt(uint8_t *buf, unsigned int nc);
    void send_ACK(uint16_t nbytes);

    ipi_relay *relay;
    uint32_t bytes_received;
    uint32_t bytes_acknowledged;
    uint32_t bytes_unacknowledged;
};

class ipi_tm_out;

/**
 * Receives TM data from ipx_tm_out via UDP and forwards it to ipi_tm_out
 */
class ipi_tm_in : public Socket {
  public:
    ipi_tm_in(ipi_tm_out *tm_out);
  protected:
    virtual ~ipi_tm_in();
    /**
     * Check incoming data for packet validity, then forward
     * to ipi_tm_out (for TM data at least) to forward to serin.
     */
    bool protocol_input();
    void dump_buf();
    bool buffer_dumped;
    ipi_relay *relay;
    ipi_tm_out *tm_out;
};

/**
 * Sends telemetry data to serin
 */

class ipi_tm_out : public Client {
  public:
    ipi_tm_out(const char *iname, Server *srvr);
    /**
     * @param pkt Pointer to the complete serio packet
     * @param length The number of bytes in the packet
     * @return true if the packet could not be sent
     */
    bool forward_packet(const char *pkt, int length);
  protected:
    // ~ipi_tm_out();
    /**
     * Calls srvr->Shutdown(true)
     *
     * The correct approach may be to override app_process_eof() instead
     * to avoid a possible race condition at startup.
     *
     * @return false, although it really doesn't matter, since the
     * Shutdown() call takes care of termination.
     */
    bool process_eof();
    Server *srvr;
};

#endif
