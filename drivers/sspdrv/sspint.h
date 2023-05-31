/* sspint.h: Internal defintions for sspdrv */
#ifndef SSPINT_H_INCLUDED
#define SSP_INT_H_INCLUDED

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dasio/interface.h>
#include <dasio/cmd_reader.h>
#include <dasio/tm_data_sndr.h>
#include "sspdrv.h"
#include "ssp_ad.h"
#include "mlf.h"

enum fdstate { FD_IDLE, FD_READ, FD_WRITE, FD_CONNECT };
// extern enum fdstate tcp_state, udp_state;

extern void sspdrv_init(int argc, char * const *argv);

// extern int udp_create(const char *interface, const char *portspec);
// extern int udp_socket;
// extern int udp_receive(long int *scan, size_t length );
// extern void udp_close(void);
// extern void udp_read(mlf_def_t *mlf, int do_amp);

using namespace DAS_IO;

class SSP_TCP;
class SSP_UDP;

class SSP_Cmd : public Cmd_reader {
  public:
    SSP_Cmd(SSP_TCP *TCP, SSP_UDP *UDP);
  protected:
    bool app_input();
    bool is_eocmd(unsigned char c);
    bool report_invalid();
    SSP_TCP *TCP;
    SSP_UDP *UDP;
};

// extern int tcp_create(const char *hostname);
// extern void tcp_reset(const char *hostname);
// extern void tcp_enqueue( char *cmd );
// extern int tcp_send(void);
// extern int tcp_recv(void);
// extern void tcp_connected(void);

class SSP_TCP : public Socket {
  public:
    SSP_TCP();
    void enqueue(const unsigned char *cmd);
    fdstate state;

  protected:
    bool protocol_input();
    bool protocol_timeout();
    bool connected();
    void send();
    inline bool empty() { return !Q.full && Q.front == Q.back; }

    static const int TCP_QSIZE = 20;
    static const int TCP_SEND_SIZE = 30;
    static const int RECV_BUF_SIZE = SSP_MAX_CTRL_MSG;
    struct {
      int front, back;
      bool full;
      unsigned char q[TCP_QSIZE][TCP_SEND_SIZE];
    } Q;
};

class SSP_UDP : public Interface {
  public:
    SSP_UDP(mlf_def_t *mlf, TM_data_sndr *tm_amp_data);
    /**
     * Opens a new listening UDP socket. Uses the global
     * ssp_config to initialize scan parameters.
     * @return The automatically selected port number
     */
    int connect();
    void disconnect();
    fdstate state;
  protected:
    // bool fillbuf() override;
    bool protocol_input();
    void output_scan(uint32_t *scan);
  private:
    int port; //< The current UDP port number
    int n_channels; //< Number of channels enabled: 1-3
    int raw_length; //< Number of 32-bit words in scan
    int scan_size; //< Number of bytes in scan
    int cur_word; //< Number of 32-bit words received so far
    bool scan_OK; //< T
    uint32_t scan_buf[SSP_CLIENT_BUF_LENGTH];
    uint32_t scan_serial_number;
    static const uint32_t scan0 = 6;
    uint32_t scan1;
    static const uint32_t scan5 = 1;
    uint32_t frag_hold;
    mlf_def_t *mlf;
    TM_data_sndr *tm_amp_data;
    bool do_amp;
};

typedef struct {
	uint16_t NS, NA, NC;
	uint16_t NE;
  uint16_t NF; /* Frequency Divisor */
	int NP; /* udp port number */
  int LE; /* logging enabled */
} ssp_config_t;
extern ssp_config_t ssp_config;
extern ssp_data_t ssp_data;
extern ssp_amp_data_t ssp_amp_data;

typedef struct {
  uint16_t NZ, NN, NM, NSamp;
  float meanX, sumX2;
  int modified;
} noise_config_t;

extern noise_config_t noise_config;

#endif
