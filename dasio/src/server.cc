/** @file server.cc */
#include <cctype>
#include <string.h>
#include "dasio/server.h"
#include "dasio/loop.h"
#include "dasio/appid.h"

namespace DAS_IO {

  SubService::SubService(std::string name, socket_clone_t func, void *svc_data)
      : name(name), func(func), svc_data(svc_data) {}
  SubService::~SubService() {}

  SubServices::SubServices() {}
  SubServices::~SubServices() {}
  
  bool SubServices::add_subservice(SubService *def) {
    std::pair<std::map<std::string,SubService *>::iterator,bool> ret;
    ret = subs.insert( std::pair<std::string,SubService *>(def->name, def));
    return ret.second;
  }
  
  SubService *SubServices::find_subservice(std::string subservice) {
    std::map<std::string,SubService *>::iterator pos;
    
    pos = subs.find(subservice);
    return (pos == subs.end()) ? 0 : pos->second;
  }

  Server::Server(const char *iname, int bufsz, const char *service,
        Socket::socket_type_t socket_type)
      : Socket(iname, bufsz, service, socket_type) {}

  Server::~Server() {}
  
  Socket *Server::new_client(const char *iname, int fd) {
    Authenticator *rv = new Authenticator(this, iname, fd, &Subs);
    if (ELoop) ELoop->add_child(rv);
    return rv;
  }
  
  bool Server::add_subservice(SubService *def) {
    return Subs.add_subservice(def);
  }
  
  Authenticator::Authenticator(Server *orig, const char *iname,
            int fd, SubServices *SS)
        : Socket(orig, iname, fd), Subsp(SS) {}
  Authenticator::~Authenticator() {}
  
  bool Authenticator::protocol_input() {
    const char *clt_app, *svc;
    int clt_app_len, svc_len;
    if (not_str("AuthLE ") ||
        not_str(AppID.Experiment) ||
        not_word(clt_app, clt_app_len) ||
        not_str(" ") ||
        not_svc(svc, svc_len)) { // Can also check for CRC
      close();
      if (ELoop)
        ELoop->delete_child(this);
      return false;
    } else {
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
      Socket *clone = ssvc->func(this, ssvc);
      if (clone == 0) return true; // bad craziness
      this->fd = -1;
      if (ELoop) {
        ELoop->delete_child(this);
        ELoop->add_child(clone);
      }
      return clone->connected();
    }
  }

  bool Authenticator::not_word(const char *&w, int len) {
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
  
  bool Authenticator::not_svc(const char *&svc, int len) {
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

}
