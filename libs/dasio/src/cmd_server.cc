/** @file cmd_server.cc
 * @brief Methods required for command servers
 */
#include <cctype>
#include <string.h>
#include "dasio/cmd_server.h"
#include "dasio/cmd_version.h"
#include "dasio/msg.h"
#include "cmdalgo.h"
#include "nl_assert.h"

static bool quit_received = false;

namespace DAS_IO {
  
  Server *CmdServer;
  
  Cmd_receiver::Cmd_receiver(Authenticator *auth, const char *iname)
      : Serverside_client(auth, iname, CMD_MAX_COMMAND_IN) {
    quit_recd = false;
  }
  
  Cmd_receiver::~Cmd_receiver() {}
  
  /**
   * Get content from io_write() below
   * This is where commands are recieved. We'll require that only one
   * command be received per write. That prevents doing something like
   *   cat commandlist.txt > /dev/huarp/Exp/cmd/server
   * but there's no particular reason why we'd want to do that. In
   * actual use, commands come in one at a time. Also, it's easy enough
   * to do:
   *  cat commandlist.txt | while read line; do
   *    echo $line >/dev/huarp/Exp/cmd/server; done
   */
  bool Cmd_receiver::protocol_input() {
    int status;

    if ( nc > CMD_MAX_COMMAND_IN ) {
      report_err("%s: Command too long", iname);
      consume(nc);
      return false;
    }

    // Parse leading options
    // No spaces, colons or right brackets allowed in mnemonics 
    { const char *mnemonic = "--";
      int quiet = 0;
      int testing = 0;
      unsigned char *s = buf;

      if ( *s == '[' ) {
        s++;
        if ( isgraph(*s) && *s != ':' && *s != ']' ) {
          mnemonic = (const char *)s++;
          while ( isgraph(*s) && *s != ':' && *s != ']' )
            s++;
        }
        if ( !isgraph(*s) ) {
           report_err("%s: Invalid mnemonic string", iname);
          consume(nc);
          return iwrite("E0: Invalid mnemonic string\n");
        }
        if ( *s == ':' ) {
          int end_of_opts = 0;
          unsigned char *ver;

          *s++ = '\0'; // terminate the mnemonic
          // and then handle the options
          while (!end_of_opts) {
            switch (*s) {
              case 'T': testing = 1; s++; break;
              case 'Q': quiet = 1; s++; break;
              case 'X': process_quit(); return false;
              case 'V': // handle version command
                ver = ++s;
                while ( *s != ']' && *s != '\0' ) s++;
                if ( *s == '\0' ) {
                  report_err("%s: Unterminated version string", iname);
                  consume(nc);
                  return iwrite("E1: Unterminated version string\n");
                }
                *s = '\0';
                if ( strcmp( (const char *)ver, ci_version ) == 0 ) {
                  report_ok(nc);
                  return iwrite("K\n");
                } else {
                  report_err("%s: Command Versions don't match", iname);
                  consume(nc);
                  return iwrite("E2: Command Versions don't match\n");
                }
              case ']': end_of_opts = 1; break;
              default:
                report_err("%s: Invalid option", iname);
                consume(nc);
                return iwrite("E3: Invalid option\n");
            }
          }
        }
        // blank out trailing ']' in case it's the end of the mnemonic
        *s++ = '\0';
      }
      { unsigned char *cmd = s;
        int len = 0;
        int rv;
        int clen;

        // Now s points to a command we want to parse.
        // Make sure it's kosher
        while ( *s ) {
          if ( ! isprint(*s) && *s != '\n' ) {
            report_err("%s: Invalid character in command", iname);
            consume(nc);
            return iwrite("E4: Invalid character in command\n");
          }
          len++;
          s++;
        }
        if ( len > 0 && cmd[len-1] == '\n' ) len--;
        msg( quiet ? -2 : 0, "%s: %*.*s",
          mnemonic, len, len, cmd );
        cmd_init();
        rv = cmd_batch( (char *)cmd, testing );
        cp = s - &buf[0];
        switch ( CMDREP_TYPE(rv) ) {
          case 0:
            report_ok(cp);
            return iwrite("K\n");
          case 1:
            report_ok(cp);
            if (testing) return iwrite("K\n");
            process_quit();
            return true;
          case 2: /* Report Syntax Error */
            if ( nl_response ) {
              msg( 2, "%s: Syntax Error", mnemonic );
              msg( 2, "%*.*s", len, len, cmd);
              msg( 2, "%*s", rv - CMDREP_SYNERR, "^");
            }
            len = snprintf(obuf, OBUF_SIZE, "S%d: Syntax Error at column %d\n",
              rv - CMDREP_SYNERR, rv - CMDREP_SYNERR);
            // report_err("%s: %s", iname, obuf);
            consume(cp);
            return iwrite(obuf, len);
          default:
            len = snprintf(obuf, OBUF_SIZE, "E5: I/O error %d\n",
              rv - CMDREP_EXECERR);
            report_err("%s: %s", iname, obuf);
            consume(cp);
            return iwrite(obuf, len);
        }
      }
    }
  }

  bool Cmd_receiver::iwritten(int nb) {
    if (obuf_empty() && quit_recd && (CmdServer != 0)) {
      CmdServer->Shutdown();
      return true;
    }
    return false;
  }
  
  Cmd_receiver *Cmd_receiver::new_cmd_receiver(Authenticator *auth,
      SubService *ss) {
    Cmd_receiver *cr = new Cmd_receiver(auth, auth->get_client_app());
    ss = ss; // We don't have any subservice info
    return cr;
  }

  void Cmd_receiver::process_quit() {
    msg( -2, "Processing Quit" );
    quit_received = quit_recd = true;
    iwrite("Q\n");
    // ELoop->delete_child(this);
    cis_interfaces_close();
    cmdif_rd::all_closed();
  }
  
  Cmd_turf::Cmd_turf(Authenticator *auth, const char *iname, cmdif_rd *ss)
      : Serverside_client(auth, iname, CMD_MAX_COMMAND_IN), ss(ss) {
    next_command = ss->first_cmd;
    ++ss->first_cmd->ref_count;
    written = false;
    ss->add_reader(this);
  }
  
  Cmd_turf::~Cmd_turf() {
    if (ss) {
      ss->rm_reader(this);
      ss = 0;
    }
  }
 
  /*
   * Strategy here is:
   * next_command->cmdlen == 0 until there is something to write
   * next_command->next == 0 until there is something to write
   * we cannot write unless and until obuf_empty()
   * if there is something to write, and we can write, we write it
   * and we set written == true
   * 
   */
  void Cmd_turf::turf_check() {
    while (obuf_empty()) {
      if (written) {
        --next_command->ref_count;
        next_command = next_command->next;
        ++next_command->ref_count;
        written = false;
      }
      if (next_command->next) {
        if (next_command->cmdlen) {
          iwrite((const char *)next_command->command, next_command->cmdlen);
        } else if (ELoop) {
          ELoop->delete_child(this);
        }
        written = true;
      } else break;
    }
  }
  
  bool Cmd_turf::iwritten(int nb) {
    if (written && obuf_empty())
      turf_check();
    return false;
  }
  
  /**
   * Ideally we would combine auth->get_client_app() with the
   * cmdif_rd.name. I was going to say it is common for drivers
   * to read from both a cmd/<driver> interface and cmd/Quit,
   * but the latter would be redundant. So maybe this is perfectly
   * fine.
   */
  Serverside_client *Cmd_turf::new_cmd_turf(Authenticator *auth, SubService *ss) {
    return new Cmd_turf(auth, auth->get_client_app(), (cmdif_rd*)(ss->svc_data));
  }
  
}


// These will be generated by cmdgen and included in a separate module.
// char ci_version[] = "";
// void cis_initialize(void) {}
// void cis_terminate(void) {}
// void cis_interfaces(void) {}
// void cis_interfaces_close(void) {}
// int  cmd_batch( char *cmd, int test ) {
//   cmd = cmd;
//   test = test;
// }

void ci_server(void) {
  cis_initialize(); // not actually implemented
  nl_assert(DAS_IO::CmdServer == 0);
  DAS_IO::CmdServer = new DAS_IO::Server("cmd");
  nl_assert(DAS_IO::CmdServer != 0);
  DAS_IO::CmdServer->add_subservice(new DAS_IO::SubService("cmd/server",
    (DAS_IO::socket_clone_t)DAS_IO::Cmd_receiver::new_cmd_receiver, (void *)0));

  // Call the cmdgen-generated initialization routine
  cis_interfaces();
  DAS_IO::CmdServer->Start(DAS_IO::Server::Srv_Unix);
  // while (!(quit_received && cmdif_rd::all_closed())) {
    // cs->ELoop.event_loop();
  // }
}

cmdif_rd::cmdif_rd(const char *name)
    : svcsname("cmd") {
  this->name = name;
  first_cmd = last_cmd = 0;
}

/**
 * Since the cmdif_rd interfaces are statically defined, this destructor
 * is called during exit() processing. Needs to remove SubService
 * from CmdServer and also from the rdrs list (or cmdif_rd::all_closed()
 * could handle that, since it already has the position)
 */
cmdif_rd::~cmdif_rd() {
  nl_assert(turfs.empty());
  if (DAS_IO::CmdServer)
    DAS_IO::CmdServer->rm_subservice(svcsname);
  command_out_t *cmd1 = first_cmd;
  while (cmd1) {
    command_out_t *cmd2 = cmd1->next;
    free_memory(cmd1);
    cmd1 = cmd2;
  }
  first_cmd = last_cmd = 0;
}

void cmdif_rd::Setup() {
  first_cmd = last_cmd = new_command();
  rdrs.push_back(this);
  // cmdif_rd::Setup is called from generated code in cis_interfaces()
  // which is called from ci_server(), which initializes CmdServer first.
  nl_assert(DAS_IO::CmdServer);
  if (name && name[0]) {
    svcsname.append("/");
    svcsname.append(name);
  }
  DAS_IO::CmdServer->add_subservice(
      new DAS_IO::SubService(svcsname,
        DAS_IO::Cmd_turf::new_cmd_turf, this));
}

void cmdif_rd::Turf(const char *format, ...) {
  va_list arglist;
  command_out_t *cmd;
  int nb;

  // I think this assertion is wrong
  // nl_assert(CmdServer &&
  //  CmdServer->SU != NULL );
  cmd = last_cmd;
  va_start( arglist, format );
  nb = vsnprintf( cmd->command, CMD_MAX_COMMAND_OUT, format, arglist );
  va_end( arglist );
  if ( nb >= CMD_MAX_COMMAND_OUT ) {
    msg( 2, "%s: Output buffer overflow", svcsname.c_str());
    cmd->command[0] = '\0';
  } else {
    cmd->cmdlen = nb;
    cmd->next = last_cmd = new_command();
    // Now run the queue of blocked clients:
    std::list<DAS_IO::Cmd_turf *>::iterator ctp;
    for (ctp = turfs.begin(); ctp != turfs.end(); ++ctp) {
      DAS_IO::Cmd_turf *ct = *ctp;
      ct->turf_check();
    }
    // Now clean out commands with no refs
    while (first_cmd->next && first_cmd->ref_count == 0) {
      first_cmd = free_command(first_cmd);
    }
  }
}

void cmdif_rd::Shutdown() {
  Turf("");
}

void cmdif_rd::add_reader(DAS_IO::Cmd_turf *rdr) {
  turfs.push_back(rdr);
}

void cmdif_rd::rm_reader(DAS_IO::Cmd_turf *rdr) {
  turfs.remove(rdr);
}

// Go through rdrs list of cmdif_rd. If turfs.empty(),
// we can shutdown the subservice. This involves
// - removing subservice from CmdServer->Subs
// - freeing first_cmd and any others
// - remove cmdif_rd from rdrs list
// - delete cmdif_rd
// - if all rdrs are gone, then free free_commands
bool cmdif_rd::all_closed() {
  std::list<cmdif_rd *>::iterator rp, crp;
  rp = rdrs.begin();
  // msg(0, "all_closed: %d rdrs", rdrs.size());
  while (rp != rdrs.end()) {
    crp = rp;
    cmdif_rd *cur_rdr = *crp;
    rp++;
    if ( cur_rdr->turfs.empty() ) {
      rdrs.erase(crp);
      // delete(cur_rdr); // don't delete! These are statically allocated
    }
  }
  if (rdrs.empty()) {
    // free free_commands
    command_out_t *next;
    while (free_commands) {
      next = free_commands->next;
      free_memory(free_commands);
      free_commands = next;
    }
    return true;
  }
  return false;
}

command_out_t *cmdif_rd::new_command() {
  command_out_t *cmd;
  if ( free_commands ) {
    cmd = free_commands;
    free_commands = cmd->next;
  } else {
    cmd = (command_out_t *)new_memory(sizeof(command_out_t));
  }
  cmd->next = 0;
  cmd->ref_count = 0;
  cmd->command[0] = '\0';
  cmd->cmdlen = 0;
  return cmd;
}

// Returns the next command so it's easy to free the
// first command in a list:
// list = free_command( list );
command_out_t *cmdif_rd::free_command( command_out_t *cmd ) {
  command_out_t *nxt;
  assert( cmd != NULL );
  assert( cmd->ref_count == 0 );
  cmd->cmdlen = 0; // mark it as empty
  nxt = cmd->next; // save the next for return
  // Add cmd to the front of the free_commands list
  cmd->next = free_commands;
  free_commands = cmd;
  return nxt;
}

command_out_t *cmdif_rd::free_commands;

cmdif_wr_clt::cmdif_wr_clt(const char *iname, const char *service,
        const char *subservice)
      : DAS_IO::Client(iname, 80, service, subservice) {
}

std::list<cmdif_rd *> cmdif_rd::rdrs;

cmdif_wr_clt::~cmdif_wr_clt() {}

void cmdif_wr_clt::Turf(const char *cmd, int cmdlen) {
  if (!obuf_empty()) {
    report_err("%s: Output buffer overflow", iname);
    return;
  }
  iwrite(cmd, cmdlen);
}

std::list<cmdif_rd *> rdrs;

cmdif_wr::cmdif_wr(const char *name, const char *path) {
  char *ss = nl_strdup(path);
  const char *service = (const char *)ss;
  const char *subservice;
  int i;
  for (i = 0; ; ++i) {
    if (ss[i] == '/') {
      ss[i] = '\0';
      subservice = (const char *)&ss[i+1];
      break;
    } else if (ss[i] == '\0') {
      subservice = (const char *)&ss[i];
      break;
    }
  }
  client = new cmdif_wr_clt(name, service, subservice);
  // this->path = path;
}

cmdif_wr::~cmdif_wr() {}

void cmdif_wr::Setup() {
  nl_assert(DAS_IO::CmdServer != 0);
  DAS_IO::CmdServer->ELoop.add_child(client);
  client->connect();
}

void cmdif_wr::Turf(const char *format, ...) {
  va_list arglist;
  int nb;

  if (client == 0 || client->fd < 0) {
    msg(2, "%s: Cannot forward command while disconnected",
      client->get_iname());
    return;
  }
  // if (ocp < onc) {
    // msg(2, "%s: Output buffer overflow", client->get_iname());
    // return;
  // }
  va_start( arglist, format );
  nb = vsnprintf( obuf, CMD_MAX_COMMAND_OUT, format, arglist );
  va_end( arglist );
  if ( nb >= CMD_MAX_COMMAND_OUT ) {
    msg( 2, "%s: Output buffer overflow", client->get_iname());
  } else if (nb == 0) {
    if (client->ELoop)
      client->ELoop->delete_child(client);
    client = 0;
  } else {
    client->Turf(obuf, nb);
  }
}

void cmdif_wr::Shutdown() {
  if (client) {
    if (client->ELoop)
      client->ELoop->delete_child(client);
    client = 0;
  }
}

cmdif_dgdata::cmdif_dgdata(const char *name_in, void *data_in, int dsize_in)
    : TM_data_sndr(name_in, name_in, (const char *)data_in, dsize_in) {
}

cmdif_dgdata::~cmdif_dgdata() {}

void cmdif_dgdata::Turf() {
  if (ELoop == 0) {
    nl_assert(DAS_IO::CmdServer != 0);
    DAS_IO::CmdServer->ELoop.add_child(this);
  }
  iwrite((const char *)data, dsize);
}

void cmdif_dgdata::Shutdown() {
  if (ELoop)
    ELoop->delete_child(this);
}

/*
=Name ci_server(): Command server main loop
=Subject Command server and Client

=Synopsis

#include "tm.h"
void ci_server(void);

=Description

ci_server() does all the work for a command server. It does
not return until =cmd_batch=() returns a CMDREP_QUIT or it receives
a CMDINTERP_QUIT message.<P>

It registers the CMDINTERP_NAME with the operating system, then
loops to Receive messages. For each received command, ci_server()
calls =cmd_init=() and =cmd_batch=(). If needed, a hook could
be added to Receive other messages.

=Returns
Nothing.

=SeeAlso
=Command server and Client= functions.

=End

=Name cmd_batch(): Parse a command in batch mode
=Subject Command server and Client
=Name cmd_init(): Initialize command parser
=Subject Command server and Client
=Synopsis

#include "cmdalgo.h"
int cmd_batch( char *cmd, int test );
void cmd_init( void );
void cis_initialize(void);
void cis_terminate(void);
void cis_interfaces(void);

=Description

  These functions are all generated by CMDGEN. cmd_init()
  resets the parser to its start state. cmd_batch() provides an
  input string that the parser will act on. If test is non-zero,
  no actions associated with the command will be executed.
  cis_initialize() is called at the very beginning of ci_server(),
  and cis_terminate() is called at the very end. These are used
  by cmdgen and soldrv to handle proxy-based commands in QNX4.
  It remains to be seen if these will be used in QNX6.
  cis_interfaces() is called from ci_server() to initialize
  reader interfaces in QNX6.

=Returns

  cmd_batch() returns the same error codes as =ci_sendcmd=().

=SeeAlso

  =Command server and Client= functions.

=End

*/
