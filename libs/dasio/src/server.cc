/** @file server.cc */
#include <cctype>
#include <string.h>
#include "dasio/server.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "dasio/host_session.h"
#include "nl.h"
#include "nl_assert.h"
#include "dasio/msg.h"

namespace DAS_IO {

  DAS_IO::Server::Srv_type DAS_IO::Server::server_type = DAS_IO::Server::Srv_type::Srv_Unix;

  SubService::SubService(std::string name, socket_clone_t func, void *svc_data,
        Authentication_hook hook)
      : name(name), func(func), svc_data(svc_data), auth_hook(hook) {}
  SubService::~SubService() {}

  SubServices::SubServices() {}
  SubServices::~SubServices() {}
  
  bool SubServices::add_subservice(SubService *def) {
    std::pair<std::map<std::string,SubService *>::iterator,bool> ret;
    ret = subs.insert( std::pair<std::string,SubService *>(def->name, def));
    if (!ret.second) {
      msg(MSG_ERROR, "SubService %s already defined", def->name.c_str());
    }
    return ret.second;
  }
  
  bool SubServices::rm_subservice(std::string subservice) {
    std::map<std::string,SubService *>::iterator pos;
    
    pos = subs.find(subservice);
    if (pos == subs.end()) {
      return false;
    } else {
      subs.erase(pos);
      return true;
    }
  }
  
  SubService *SubServices::find_subservice(std::string subservice) {
    std::map<std::string,SubService *>::iterator pos;
    
    pos = subs.find(subservice);
    return (pos == subs.end()) ? 0 : pos->second;
  }

  Server_socket::Server_socket(const char *iname, const char *service,
        Socket::socket_type_t socket_type, Server *srvr,
        const char *function)
      : Socket(iname, function, service, socket_type),
        srvr(srvr) {}

  Server_socket::~Server_socket() {}
  
  Socket *Server_socket::new_client(const char *iname, int fd) {
    Authenticator *rv = new Authenticator(this, iname, fd);
    if (ELoop) ELoop->add_child(rv);
    return rv;
  }
  
  Serverside_client::Serverside_client(Authenticator *auth,
        const char *iname, int bufsize)
      : Socket(auth, iname, bufsize, auth->fd), srvr(auth->srvr) {
    srvr->client_added();
  }
  
  Serverside_client::~Serverside_client() {
    srvr->client_removed();
  }

  bool Serverside_client::srvr_has_shutdown() {
    return srvr->has_shutdown();
  }
  
  Authenticator::Authenticator(Server_socket *orig, const char *iname,
            int fd)
        : Socket(orig, iname, 128, fd), srvr(orig->srvr), client_app(0) {}
  Authenticator::~Authenticator() {}
  
  bool Authenticator::protocol_input() {
    const char *clt_app, *svc;
    int clt_app_len, svc_len;
    if (not_str("AuthLE ") ||
        not_str(AppID.Experiment) ||
        not_str(" ") ||
        not_word(clt_app, clt_app_len) ||
        not_str(" ") ||
        not_svc(svc, svc_len)) { // Can also check for CRC
      msg(MSG_ERROR, "%s: Rejecting client connection at column %d",
                    iname, cp);
      msg(MSG_ERROR, "%s: Auth string was '%s'", ascii_escape());
      close();
      if (ELoop)
        ELoop->delete_child(this);
      return false;
    } else {
      std::string subservice(svc, svc_len);
      SubService *ssvc = srvr->Subs.find_subservice(subservice);
      if (ssvc == 0) {
        report_err("%s: Undefined subservice:'%s'", iname, subservice.c_str());
        close();
        if (ELoop)
          ELoop->delete_child(this);
        return false;
      }
      if (ssvc->auth_hook && !ssvc->auth_hook(this, ssvc)) {
        report_err("%s: Rejecting connection due to auth_hook", iname);
        close();
        if (ELoop)
          ELoop->delete_child(this);
        return false;
      }
      report_ok(nc);
      char *clt_app_tmp = (char *)new_memory(clt_app_len+1);
      strncpy(clt_app_tmp, clt_app, clt_app_len);
      clt_app_tmp[clt_app_len] = '\0';
      client_app = (const char *)clt_app_tmp;
      Socket *clone = ssvc->func(this, ssvc);
      if (clone == 0) {
        msg(MSG_ERROR, "%s: clone function failed, rejecting connection from %s", iname, client_app);
        close();
        if (ELoop)
          ELoop->delete_child(this);
        return false;
      }
      msg(MSG_DEBUG, "Accepted connection from %s for %s",
          client_app, subservice.c_str());
      this->fd = -1;
      if (ELoop) {
        Loop *elp = ELoop;
        ELoop->delete_child(this);
        elp->add_child(clone);
      }
      return clone->iwrite("OK\n") || clone->connected();
    }
  }

  bool Authenticator::not_word(const char *&w, int &len) {
    len = 0;
    w = (const char *)&buf[cp];
    if (cp < nc && isalpha(buf[cp])) {
      ++len;
      ++cp;
      while (cp < nc && (isalnum(buf[cp]) || buf[cp] == '_'
              || buf[cp] == '-' || buf[cp] == '.')) {
        ++len;
        ++cp;
      }
      return false;
    }
    if (cp < nc) {
      report_err("%s: Expected word at column %d", iname, cp);
    }
    return true;
  }
  
  bool Authenticator::not_svc(const char *&svc, int &len) {
    if (not_word(svc, len)) return true;
    while (cp < nc && buf[cp] == '/') {
      const char *node;
      int node_len;
      ++len; ++cp;
      if (not_word(node, node_len)) return true;
      len += node_len;
    }
    return false;
  }

  Server::Server(const char *service, int passive_quit_threshold) :
      Unix(0), TCP(0), active_clients(0), total_clients(0),
      passive_exit_threshold(0), service(service),
      has_shutdown_b(false),
      shutdown_requested(false),
      full_shutdown_requested(false),
      sigif(0)
      { }

  Server::~Server() {}

  void Server::Start(Server::Srv_type which = server_type,
                     const char *function) {
    signal(SIGHUP);
    signal(SIGINT);
    if (which & Srv_Function) {
      nl_assert(function);
      const char *res = hs_registry::query_host(function);
      if (res) which = Srv_TCP;
      res = hs_registry::query_session(function);
      if (res) {
        if (which == Srv_TCP)
          which = Srv_Both;
        else
          which = Srv_Unix;
      }
    }
    if (which & Srv_Unix) {
      Unix = new Server_socket("Unix", service, Socket::Socket_Unix,
                               this, function);
      Unix->reference();
      Unix->connect();
      ELoop.add_child(Unix);
    }
    if (which & Srv_TCP) {
      TCP = new Server_socket("TCP", service, Socket::Socket_TCP, this);
      TCP->reference();
      TCP->connect();
      ELoop.add_child(TCP);
    }
    do {
      ELoop.event_loop();
    } while (!ready_to_quit());
  }

  bool Server::ready_to_quit() {
    if (shutdown_requested && !has_shutdown_b) {
      do_shutdown(full_shutdown_requested);
      // As documented, if full shutdown is not requested,
      // we return true to exit Server::Start and leave
      // the final details to the application:
      if (!full_shutdown_requested)
        return true;
    }
    if (nl_debug_level < -1) {
      static int active_clients_reported = -1;
      if (active_clients != active_clients_reported) {
        msg(MSG_DBG(0), "ready_to_quit: active_clients = %d",
          active_clients);
        active_clients_reported = active_clients;
      }
    }
    return active_clients == 0;
  }
  
  void Server::Shutdown(bool full) {
    if (sigif) {
      Interface::dereference(sigif);
      sigif = 0;
    }
    shutdown_requested = true;
    full_shutdown_requested = full;
    ELoop.set_loop_exit();
  }
  
  void Server::do_shutdown(bool full) {
    msg(MSG_DEBUG, "Shutting down listening sockets");
    if (Unix) {
      if (!Unix->ref_check(2)) {
        msg(MSG_ERROR, "Unix ref_count <2 in Shutdown");
      } else {
        Interface::dereference(Unix);
      }
      ELoop.delete_child(Unix);
      Unix = 0;
    }
    if (TCP) {
      if (!TCP->ref_check(2)) {
        msg(MSG_ERROR, "TCP ref_count <2 in Shutdown");
      } else {
        Interface::dereference(TCP);
      }
      ELoop.delete_child(TCP);
      TCP = 0;
    }
    has_shutdown_b = true;
    if (full) {
      ELoop.delete_children();
    }
    ELoop.set_loop_exit();
  }

  void Server::client_added() {
    ++active_clients;
    ++total_clients;
  }

  void Server::client_removed() {
    msg(MSG_DBG(1), "client_removed(): 1 of %d", active_clients);
    if (--active_clients == 0 &&
        passive_exit_threshold > 0 &&
        total_clients >= passive_exit_threshold) {
      Shutdown();
    }
  }
  
  void Server::set_passive_exit_threshold(int N) {
    passive_exit_threshold = N;
  }

  void Server::signal(int signum) {
    if (!sigif) {
      sigif = new server_sigif(this);
      ELoop.add_child(sigif);
      sigif->reference();
    }
    sigif->signal(signum);
  }
  
  void Server::set_sigif(server_sigif *sigif) {
    if (this->sigif)
      msg(MSG_FATAL, "Server sigif already defined");
    this->sigif = sigif;
  }

  bool server_sigif::serialized_signal_handler(uint32_t signals_seen) {
    msg(0, "%s: Signal(s) %08X observed", iname, signals_seen);
    srvr->Shutdown(false);
    return true;
  }
}
