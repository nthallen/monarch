/** @file dasio/cmd_server.h */
#ifndef DASIO_CMD_SERVER_H_INCLUDED
#define DASIO_CMD_SERVER_H_INCLUDED
#include <list>
#include "server.h"
#include "client.h"
#include "tm_data_sndr.h"
#include "loop.h"

class command_out_t;
class cmdif_rd;

namespace DAS_IO {
  
  class Cmd_Server : public Server {
    public:
      inline Cmd_Server() : Server("cmd"), quit_processed(false) {}
      void process_quit();
      /** The maximum input command length, including headers */
      static const int MAX_COMMAND_IN = 300;
      /** The maximum message size out to drivers. Must match
       *  MAX_COMMAND_IN for transmission.
       */
      static const int MAX_COMMAND_OUT = 300;
      static bool opt_Q;
    protected:
      bool ready_to_quit();
      bool quit_processed;
  };

  extern Cmd_Server *CmdServer;
  
  class cmd_hdr_parser {
    public:
      cmd_hdr_parser();
      ~cmd_hdr_parser();
      /**
       * @param ibuf Pointer to command string
       * The string at ibuf must remain unchanged until the
       * command has been fully processed.
       * Checks the command string for header data and sets
       * hdrID_buf, SN, mode and cmd values accordingly.
       * If no header is present, hdrID_buf[0], SN and mode
       * will all be set to zero.
       * @return true if a syntax error is found.
       */
      bool parse(const unsigned char *ibuf);
      /**
       * Formats the previously parsed command into fmtcmd.
       * @return The number of characters in fmtcmd or zero
       * on overflow.
       */
      int format();
      /**
       * Sets SN and warns if the message already has one assigned.
       */
      void assign_sn();
      /**
       * Checks whether the SN has already been executed.
       * @return true if it has already been executed
       */
      bool check_sn();
      inline const char *hdrID() {
        return hdrID_buf[0] ? hdrID_buf : hdrID_default;
      }
      char *hdrID_default; // Initialized from AppID.name
      char *hdrID_buf; // allocated and extended as necessary
      int SN;
      char mode;
      const unsigned char *cmd; // points into ibuf, assumed to remain constant
      char fmtcmd[Cmd_Server::MAX_COMMAND_IN];

      /** Number of duplicates received of the last N_SN_MAX SNs */
      static int recent_duplicates;
      static int latest_SN_rx; ///< The last SN received
    private:
      int hdrID_len;
      
      typedef struct {
        int SN;
        int retrans;
      } recent_SN_t;
      static const int N_SN_MAX = 10;
      static recent_SN_t recent_SN[N_SN_MAX]; ///< Storage for most recent SNs
      static int latest_SN_created; ///< The last SN created here
      static int first_SN_idx; ///< index of the oldest SN recorded
      static int N_SN; ///< Number of SNs recorded, <= N_SN_MAX

      /**
       * @param ibuf The source string
       * @param suffix The required suffix string
       * @return true if ibuf ends with the suffix string
       */
      bool chk_trailing(const unsigned char *ibuf, const char *suffix);
      int inline remaining(int nc) {
        return nc < Cmd_Server::MAX_COMMAND_IN ?
          Cmd_Server::MAX_COMMAND_IN-nc : 0;
      }
      int inline retcode(int nc) {
        return nc < Cmd_Server::MAX_COMMAND_IN ? nc : 0;
      }
  };
  
  /**
   * @brief Class for cmd/server server clients.
   * No special svc_data is required, since we just
   * parse incoming commands.
   */
  class Cmd_receiver : public Serverside_client {
    public:
      Cmd_receiver(Authenticator *auth, const char *iname);
      bool protocol_input();
      // bool iwritten(int nb);
      /** process quit for each Cmd_receiver */
      static void process_quits();
      static Cmd_receiver *new_cmd_receiver(Authenticator *auth,
        SubService *ss);
    protected:
      ~Cmd_receiver();
      cmd_hdr_parser CHP;
      bool protocol_timeout();
      void process_quit();
      bool quit_recd;
      static std::list<Cmd_receiver *> rcvrs;
      static const int OBUF_SIZE = 120;
      char obuf[OBUF_SIZE];
  };
  
  /**
   * @brief Class for cmd/<driver> server-side clients.
   *
   * ss links to the <cmdif_rd> object that defines the
   * subservice.
   */
  class Cmd_turf : public Serverside_client {
    public:
      Cmd_turf(Authenticator *auth, const char *iname, cmdif_rd *ss);
      /** Checks whether next_command is ready to transmit. */
      void turf_check();
      bool iwritten(int nb);
      static Serverside_client *new_cmd_turf(Authenticator *auth,
        SubService *ss);
    protected:
      ~Cmd_turf();
      /** For handling shutdown gracefully. */
      bool protocol_timeout();
      /** Head of a linked list of commands pending output */
      command_out_t *next_command;
      /** true if we have written out the next_command */
      bool written;
      /** Pointer to the cmdif_rd defining this subservice */
      cmdif_rd *ss;
  };

} // End of DAS_IO

/**
 * @brief Class to handle command output from the
 * command server to the cmd/<driver> subservices.
 */
class command_out_t {
  public:
    command_out_t();
    ~command_out_t();
    command_out_t *new_command();
    command_out_t *free_command(command_out_t *cmd);
    command_out_t *next; // forms a linked list
    int ref_count;
    char command[DAS_IO::Cmd_Server::MAX_COMMAND_OUT];
    int cmdlen;
};

/**
 * @brief Class to define a cmd/<driver> subservice
 *
 * Class to define a cmd/<driver> subservice which
 * Cmd_reader clients (connections from drivers) can
 * read from to get driver-specific commands. This is
 * instantiated for the cmdgen syntax '%INTERFACE <driver>'.
 * Since there may be more than one reader, the
 * server-side Cmd_turf objects need to keep track
 * of which commands have been read.
 *
 * The cmdif_rd is the context structure that is
 * included in the SubService definition and
 * passed to each connecting Cmd_turf. The SubService
 * is defined in cmdif_rd::Setup().
 */
class cmdif_rd {
  public:
    cmdif_rd( const char *name );
    ~cmdif_rd();
    void Setup();
    void Turf(const char *fmt, ...);
    /** Start the shutdown process */
    void Shutdown();
    /** Release memory after client shutdowns */
    void Teardown();
    void add_reader(DAS_IO::Cmd_turf *rdr);
    void rm_reader(DAS_IO::Cmd_turf *rdr);
    static bool all_closed();
    command_out_t *new_command();
    /**
     * @param cmd should be the first in a linked list of commands
     * @return the next command so it's easy to free the
     * first command in a list:
     * list = free_command( list );
     */
    command_out_t *free_command(command_out_t *cmd);
    command_out_t *first_cmd;
  private:
    const char *name;
    command_out_t *last_cmd;
    std::string svcsname;
    std::list<DAS_IO::Cmd_turf *> turfs;
    static command_out_t *free_commands;
    static std::list<cmdif_rd *> rdrs;
};

class cmdif_tx : public cmdif_rd {
  public:
    cmdif_tx(const char *name);
    void Turf(const char *fmt, ...);
    static void req_retransmit();
    void do_retransmit();
    char last_cmd_txd[DAS_IO::Cmd_Server::MAX_COMMAND_IN];
    static cmdif_tx *txmtr;
  protected:
    bool retransmit_reqd;
};

class cmdif_wr_clt : public DAS_IO::Client {
  public:
    cmdif_wr_clt(const char *iname, const char *service,
      const char *subservice);
    void Turf(const char *cmd, int cmdlen);
  protected:
    ~cmdif_wr_clt();
};

/**
 * Class to make a connection to a server to forward
 * commands. This is instantiated for the cmdgen
 * '%INTERFACE <driver:service/subservice>' syntax,
 * specifically for <tm_gen:tm_gen/cmd>. No response
 * is expected from the server.
 *
 * The name_in and path_in come directly from the
 * %INTERFACE statement, so %INTERFACE <tm_gen:tm_gen/cmd>
 * results in cmdif_wr("tm_gen", "tm_gen/cmd"). The path
 * must be separated into service and subservice,
 * and since the input is const char *, we need to
 * allocate space for this.
 */
class cmdif_wr {
  public:
    cmdif_wr(const char *name, const char *path);
    ~cmdif_wr();
    void Setup();
    void Turf(const char *fmt, ...);
    void Shutdown();
  private:
    cmdif_wr_clt *client;
    char obuf[DAS_IO::Cmd_Server::MAX_COMMAND_OUT];
    const char *wrname;
    const char *wrpath;
};

/**
 * Class to make a connection to DG for DG/data based
 * on the cmdgen syntax '%INTERFACE <datum:DG/data>'.
 * In monarch terminology, the service is DG and the
 * subservice is "data/datum", but this is handled by
 * the TM_data_sndr class.
 */
class cmdif_dgdata_sndr : public DAS_IO::TM_data_sndr {
  public:
    cmdif_dgdata_sndr(const char *name, void *data, int dsize);
};

class cmdif_dgdata {
  public:
    cmdif_dgdata(const char *name, void *data, int dsize);
    void Setup();
    void Turf();
    void Shutdown();
  protected:
    cmdif_dgdata_sndr *sndr;
};

/** @brief Command server main loop
 * Does all the work for a command server. It does
 * not return until cmd_batch() returns a CMDREP_QUIT
 * or it receives a CMDINTERP_QUIT message.
 *
 * It registers the appropriate sockets, then
 * loops to Receive messages. For each received command, ci_server()
 * calls cmd_init() and cmd_batch(). If needed, a hook could
 * be added to Receive other messages.
 *
 * These will be generated by cmdgen and included in a separate module.
 * char ci_version[];
 * void cis_initialize(void);
 * void cis_terminate(void);
 * void cis_interfaces(void);
 * void cis_interfaces_close(void);
 * int  cmd_batch_chp(DAS_IO::cmd_hdr_parser *CHPP);
 * int  cmd_batch( char *cmd, int test );
 */
void ci_server();
int cmd_batch_chp(DAS_IO::cmd_hdr_parser *CHPP);

#endif
