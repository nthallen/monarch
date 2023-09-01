/** @file cmd_server.cc
 * @brief Methods required for command servers
 */
#include <cctype>
#include <string.h>
#include "dasio/appid.h"
#include "dasio/cmd_server.h"
#include "dasio/cmd_version.h"
#include "dasio/msg.h"
#include "nl_assert.h"
#include "cmdalgo.h"

namespace DAS_IO {
  
  bool Cmd_Server::ready_to_quit() {
    Server::ready_to_quit();
    return cmdif_rd::all_closed() && active_clients == 0;
  }
  
  void Cmd_Server::process_quit() {
    if (quit_processed) return;
    quit_processed = true;
    msg( MSG_DEBUG, "Processing Quit" );
    cis_interfaces_close();
    Cmd_receiver::process_quits();
    Shutdown(false);
  }
  
  Cmd_Server *CmdServer;
  
  Cmd_receiver::Cmd_receiver(Authenticator *auth, const char *iname)
      : Serverside_client(auth, iname, Cmd_Server::MAX_COMMAND_IN) {
    quit_recd = false;
    rcvrs.push_back(this);
  }
  
  Cmd_receiver::~Cmd_receiver() {
    rcvrs.remove(this);
  }
  
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
    int verlen, len;
    int testing = 0;
    int quiet = 0;
    int rv;

    msg(MSG_DEBUG, "%s: recd: %s", iname, buf);
    if (CHP.parse(buf)) return false;
    switch (CHP.mode) {
      case 'T': testing = 1; break;
      case 'Q': quiet = 1; break;
      case 'X': CmdServer->process_quit(); return false;
      case 'V': // handle version command
        verlen = strlen(ci_version);
        if (strncmp((const char *)CHP.cmd, ci_version, verlen) == 0 &&
            CHP.cmd[verlen] == '\n') {
          report_ok(nc);
          return iwrite("K\n");
        } else {
          report_err("%s: Command Versions don't match", iname);
          consume(nc);
          return iwrite("E2: Command Versions don't match\n");
        }
      default: break;
    }
    msg( quiet ? -2 : 0, "%s#%d: %s", CHP.hdrID(), CHP.SN, CHP.cmd );
    cmd_init();
    rv = cmd_batch_chp(&CHP);
    switch ( CMDREP_TYPE(rv) ) {
      case CMDREP_OK:
        report_ok(nc);
        return iwrite("K\n");
      case CMDREP_TYPE(CMDREP_QUIT):
        report_ok(nc);
        if (testing) return iwrite("K\n");
        CmdServer->process_quit();
        return true;
      case CMDREP_TYPE(CMDREP_SYNERR): /* Report Syntax Error */
        if ( nl_response ) {
          msg( MSG_ERROR, "%s: Syntax Error", CHP.hdrID() );
          msg( MSG_ERROR, "%s", CHP.cmd);
          msg( MSG_ERROR, "%*s", rv - CMDREP_SYNERR, "^");
        }
        len = snprintf(obuf, OBUF_SIZE,
          "S%d: Syntax Error at column %d\n",
          rv - CMDREP_SYNERR, rv - CMDREP_SYNERR);
        consume(cp);
        return iwrite(obuf, len);
      case CMDREP_TYPE(CMDREP_DUPLICATE):
        msg(MSG_DEBUG, "%s#%d: Duplicate", CHP.hdrID(), CHP.SN);
        report_ok(nc);
        return iwrite("K\n");
      default:
        len = snprintf(obuf, OBUF_SIZE, "E5: I/O error %d\n",
          rv - CMDREP_EXECERR);
        report_err("%s: %s", iname, obuf);
        consume(cp);
        return iwrite(obuf, len);
    }
  }
  
  void Cmd_receiver::process_quits() {
    std::list<Cmd_receiver *>::iterator cri;
    for (cri = rcvrs.begin(); cri != rcvrs.end(); ++cri) {
      Cmd_receiver *cr = *cri;
      cr->process_quit();
    }
  }

  // bool Cmd_receiver::iwritten(int nb) {
    // if (obuf_empty() && quit_recd && (CmdServer != 0)) {
      // CmdServer->Shutdown(false);
      // return true;
    // }
    // return false;
  // }
  
  Cmd_receiver *Cmd_receiver::new_cmd_receiver(Authenticator *auth,
      SubService *ss) {
    Cmd_receiver *cr = new Cmd_receiver(auth, auth->get_client_app());
    ss = ss; // We don't have any subservice info
    return cr;
  }

  bool Cmd_receiver::process_timeout() {
    msg(MSG_DEBUG, "%s: Received timeout", iname);
    ELoop->delete_child(this);
    return false;
  }
  
  void Cmd_receiver::process_quit() {
    if (quit_recd) return;
    quit_recd = true;
    msg(MSG_DEBUG, "%s: Processing Quit", iname);
    iwrite("Q\n");
    TO.Set(1,0);
    flags |= Fl_Timeout;
  }

  std::list<Cmd_receiver *> Cmd_receiver::rcvrs;
  
  Cmd_turf::Cmd_turf(Authenticator *auth, const char *iname, cmdif_rd *ss)
      : Serverside_client(auth, iname, Cmd_Server::MAX_COMMAND_IN), ss(ss) {
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
   * next_command->next == 0 until there is something to write.
   * next_command->cmdlen == 0 indicates a quit/shutdown command.
   *
   * We cannot write unless and until obuf_empty().
   * If there is something to write, and we can write, we write it
   * and we set written == true.
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
          iwrite((const char *)next_command->command,
                  next_command->cmdlen);
        } else {
          iwrite("Q\n");
          TO.Set(1,0);
          flags |= Fl_Timeout;
        }
        written = true;
      } else break;
    }
  }
  
  bool Cmd_turf::protocol_timeout() {
    msg(MSG_DEBUG, "%s: Received timeout after quit", iname);
    nl_assert(ELoop);
    ELoop->delete_child(this);
    return false;
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
  DAS_IO::CmdServer = new DAS_IO::Cmd_Server();
  nl_assert(DAS_IO::CmdServer != 0);
  DAS_IO::CmdServer->add_subservice(new DAS_IO::SubService("cmd/server",
    (DAS_IO::socket_clone_t)DAS_IO::Cmd_receiver::new_cmd_receiver, (void *)0));

  // Call the cmdgen-generated initialization routine
  cis_interfaces();
  msg(0, "%s %s Starting", DAS_IO::AppID.fullname, DAS_IO::AppID.rev);
  DAS_IO::CmdServer->Start(DAS_IO::Server::Srv_Function, "srvr");
  msg(0, "Terminating");
}

cmdif_rd::cmdif_rd(const char *name)
    : svcsname("cmd") {
  this->name = name;
  first_cmd = last_cmd = 0;
}

/**
 * Most processing handled in Teardown().
 */
cmdif_rd::~cmdif_rd() {
  nl_assert(turfs.empty());
  if (first_cmd)
    msg(MSG_WARN, "first_cmd != 0 in ~cmdif_rd()");
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

  cmd = last_cmd;
  va_start( arglist, format );
  nb = vsnprintf(cmd->command, DAS_IO::Cmd_Server::MAX_COMMAND_OUT, format, arglist);
  va_end( arglist );
  if ( nb >= DAS_IO::Cmd_Server::MAX_COMMAND_OUT ) {
    msg( MSG_ERROR, "%s: Output buffer overflow", svcsname.c_str());
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

/**
 * Needs to remove SubService from CmdServer
 */
void cmdif_rd::Teardown() {
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
      cur_rdr->Teardown();
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

cmdif_tx::cmdif_tx(const char *name) : cmdif_rd(name) {
  nl_assert(txmtr == 0);
  last_cmd_txd[0] = '\0';
  retransmit_reqd = false;
  txmtr = this;
}

void cmdif_tx::Turf(const char *fmt, ...) {
  va_list arglist;
  int nb;

  va_start(arglist, fmt);
  nb = vsnprintf(last_cmd_txd, DAS_IO::Cmd_Server::MAX_COMMAND_IN,
                  fmt, arglist);
  va_end( arglist );
  cmdif_rd::Turf("%s", last_cmd_txd);
}

void cmdif_tx::do_retransmit() {
  if (retransmit_reqd && last_cmd_txd[0]) {
    cmdif_rd::Turf("%s", last_cmd_txd);
  }
  retransmit_reqd = false;
}

void cmdif_tx::req_retransmit() {
  if (cmdif_tx::txmtr)
    cmdif_tx::txmtr->retransmit_reqd = true;
}

cmdif_wr_clt::cmdif_wr_clt(const char *iname, const char *service,
        const char *subservice)
      : DAS_IO::Client(iname, service, service, subservice, 80) {}

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

cmdif_wr::cmdif_wr(const char *name, const char *path)
  : wrname(name),
    wrpath(path) {}

cmdif_wr::~cmdif_wr() {}

void cmdif_wr::Setup() {
  nl_assert(DAS_IO::CmdServer != 0);
  char *ss = nl_strdup(wrpath);
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
  client = new cmdif_wr_clt(wrname, service, subservice);
  DAS_IO::CmdServer->ELoop.add_child(client);
  client->connect();
}

void cmdif_wr::Turf(const char *format, ...) {
  va_list arglist;
  int nb;

  if (client == 0 || client->fd < 0) {
    msg(MSG_ERROR, "%s: Cannot forward command while disconnected",
      client->get_iname());
    return;
  }
  // if (ocp < onc) {
    // msg(2, "%s: Output buffer overflow", client->get_iname());
    // return;
  // }
  va_start( arglist, format );
  nb = vsnprintf( obuf, DAS_IO::Cmd_Server::MAX_COMMAND_OUT, format, arglist );
  va_end( arglist );
  if ( nb >= DAS_IO::Cmd_Server::MAX_COMMAND_OUT ) {
    msg( MSG_ERROR, "%s: Output buffer overflow", client->get_iname());
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

cmdif_dgdata_sndr::cmdif_dgdata_sndr(const char *name_in, void *data_in, int dsize_in)
    : DAS_IO::TM_data_sndr(name_in, 0, name_in, data_in, dsize_in) {
}

cmdif_dgdata::cmdif_dgdata(const char *name, void *data, int dsize) {
  sndr = new cmdif_dgdata_sndr(name, data, dsize);
  sndr->reference();
}

void cmdif_dgdata::Setup() {
  nl_assert(DAS_IO::CmdServer != 0);
  DAS_IO::CmdServer->ELoop.add_child(sndr);
  sndr->connect();
}

void cmdif_dgdata::Turf() {
  if (sndr)
    sndr->Send();
}

void cmdif_dgdata::Shutdown() {
  if (sndr) {
    DAS_IO::Interface::dereference(sndr);
    if (sndr->ELoop)
      sndr->ELoop->delete_child(sndr);
    sndr = 0;
  }
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
