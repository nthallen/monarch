/** @file server.cc */
#include <cctype>
#include <string.h>
#include "dasio/server.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "nl.h"

namespace DAS_IO {

  SubService::SubService(std::string name, socket_clone_t func, void *svc_data)
      : name(name), func(func), svc_data(svc_data) {}
  SubService::~SubService() {}

  SubServices::SubServices() {}
  SubServices::~SubServices() {}
  
  bool SubServices::add_subservice(SubService *def) {
    std::pair<std::map<std::string,SubService *>::iterator,bool> ret;
    ret = subs.insert( std::pair<std::string,SubService *>(def->name, def));
    if (!ret.second) {
      nl_error(2, "SubService %s already defined", def->name.c_str());
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

  Server_socket::Server_socket(const char *iname, int bufsz, const char *service,
        Socket::socket_type_t socket_type, SubServices *Subsp)
      : Socket(iname, bufsz, service, socket_type), Subsp(Subsp) {}

  Server_socket::~Server_socket() {}
  
  Socket *Server_socket::new_client(const char *iname, int fd) {
    Authenticator *rv = new Authenticator(this, iname, fd, Subsp);
    if (ELoop) ELoop->add_child(rv);
    return rv;
  }
  
  Authenticator::Authenticator(Server_socket *orig, const char *iname,
            int fd, SubServices *SS)
        : Socket(orig, iname, fd), Subsp(SS), client_app(0) {}
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
      close();
      if (ELoop)
        ELoop->delete_child(this);
      return false;
    } else {
      nl_error(0, "%s: svc_len = %d", iname, svc_len);
      std::string subservice(svc, svc_len);
      SubService *ssvc = Subsp->find_subservice(subservice);
      if (ssvc == 0) {
        report_err("%s: Undefined subservice:'%s'", iname, subservice.c_str());
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
        close();
        if (ELoop)
          ELoop->delete_child(this);
        return false;
      }
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
      while (cp < nc && (isalnum(buf[cp]) || buf[cp] == '_')) {
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

  Server::Server(const char *service, int bufsz) :
      service(service),
      bufsz(bufsz),
      Unix(0),
      TCP(0) { }

  Server::~Server() {}

  void Server::Start(Server::Srv_type which) {
    if (which & Srv_Unix) {
      Unix = new Server_socket("Unix", bufsz, service, Socket::Socket_Unix, &Subs);
      Unix->connect();
      ELoop.add_child(Unix);
    }
    if (which & Srv_TCP) {
      TCP = new Server_socket("TCP", bufsz, service, Socket::Socket_TCP, &Subs);
      TCP->connect();
      ELoop.add_child(TCP);
    }
    nl_error(0, "%s %s Starting", AppID.fullname, AppID.rev);
    ELoop.event_loop();
    nl_error(0, "Terminating");
  }
}
