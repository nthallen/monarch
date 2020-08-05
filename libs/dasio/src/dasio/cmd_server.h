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
  
  extern Server *CmdServer;
  
  /**
   * @brief Class for cmd/server server clients.
   * No special svc_data is required, since we just
   * parse incoming commands.
   */
  class Cmd_receiver : public Serverside_client {
    public:
      Cmd_receiver(Authenticator *auth, const char *iname);
      bool protocol_input();
      bool iwritten(int nb);
      static Cmd_receiver *new_cmd_receiver(Authenticator *auth,
        SubService *ss);
    protected:
      ~Cmd_receiver();
      void process_quit();
      bool quit_recd;
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
    char command[CMD_MAX_COMMAND_OUT];
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
    void Shutdown();
    void add_reader(DAS_IO::Cmd_turf *rdr);
    void rm_reader(DAS_IO::Cmd_turf *rdr);
    static bool all_closed();
    command_out_t *new_command();
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

class cmdif_wr_clt : public DAS_IO::Client {
  public:
    cmdif_wr_clt(const char *iname, const char *service,
      const char *subservice);
    void Turf(const char *cmd, int cmdlen);
  protected:
    ~cmdif_wr_clt();
};

/**
 * Class to make a connection to initiate a connection
 * to a server to forward commands. This is instantiated
 * for the cmdgen '%INTERFACE <driver:service/subservice>'
 * syntax, specifically for <tm_gen:tm_gen/cmd>. No response
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
    char obuf[CMD_MAX_COMMAND_OUT];
    // const char *path;
};

/**
 * Class to make a connection to DG for DG/data based
 * on the cmdgen syntax '%INTERFACE <datum:DG/data>'.
 * In le-dasng terminology, the service is DG and the
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
 */
void ci_server();

#endif
