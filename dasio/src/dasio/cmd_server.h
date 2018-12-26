/** @file dasio/cmd_server.h */
#ifndef DASIO_CMD_SERVER_H_INCLUDED
#define DASIO_CMD_SERVER_H_INCLUDED
#include <list>
#include "server.h"
#include "client.h"
#include "tm_client.h"
#include "loop.h"

#define CMD_MAX_COMMAND_OUT 160 // Maximum command message output length
#define CMD_MAX_COMMAND_IN 300  // Maximum command message input length

class command_out_t;
class cmdif_rd;

namespace DAS_IO {
  
  class Cmd_server {
    public:
      Cmd_server();
      ~Cmd_server();
      
      inline bool add_subservice(SubService *ss) {
        Subs.add_subservice(ss);
      }
      inline bool rm_subservice(std::string svcs) {
        Subs.rm_subservice(svcs);
      }
      
      void StartServer();
      /**
       * Shuts down the listening server socket.
       */
      void Shutdown();
      Loop ELoop;
      Server *server; // ?
      static Cmd_server *CmdServer;
    protected:
      SubServices Subs;
  };
  
  /**
   * @brief Class for cmd/server server clients.
   * No special svc_data is required, since we just
   * parse incoming commands.
   */
  class Cmd_receiver : public Socket {
    public:
      Cmd_receiver(Authenticator *auth, const char *iname);
      ~Cmd_receiver();
      bool protocol_input();
      static Cmd_receiver *new_cmd_receiver(Authenticator *auth,
        SubService *ss);
    protected:
      static const int OBUF_SIZE = 120;
      char obuf[OBUF_SIZE];
  };
  
  /**
   * @brief Class for cmd/<turf_client> server clients.
   * svc_data needs to link to the <cmdif_rd> object.
   * We also need to keep track of which commands this
   * interface has transmitted.
   */
  class Cmd_turf : public Socket {
    public:
      Cmd_turf(Authenticator *auth, const char *iname, cmdif_rd *ss);
      ~Cmd_turf();
      /**
       * Checks whether next_command is ready to transmit.
       */
      void turf_check();
      void iwritten(int nb);
      static Socket *new_cmd_turf(Authenticator *auth,
        SubService *ss);
    protected:
      command_out_t *next_command;
      bool written;
      cmdif_rd *ss;
  };

} // End of DAS_IO

/**
 * @brief Class to handle command output from the
 * command server to the dev/<driver> subservices.
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
    static command_out_t *free_commands;
};

/**
 * Class to define a DG/<interface> subservice which
 * Clients (connections from drivers) can read from to
 * get specific commands. This is instantiated for
 * the cmdgen '%INTERFACE <driver>' syntax.
 * Since there may be more than one reader, the
 * reader Socket objects may need to keep track
 * of which commands have been read...
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
    ~cmdif_wr_clt();
    void Turf(const char *cmd, int cmdlen);
};

/**
 * Class to make a connection to initiate a connection
 * to a server to forward commands. This is instantiated
 * for the cmdgen '%INTERFACE <driver:service/subservice>'
 * syntax, specifically for <DG:DG/cmd>. No response
 * is expected from the server.
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
 * the TM_client class.
 */
class cmdif_dgdata : public DAS_IO::TM_client {
  public:
    cmdif_dgdata(const char *name, void *data, int dsize);
    void Turf();
    void Shutdown();
  private:
    const char *name;
    void *data;
    int dsize;
};

void ci_server();

#endif
