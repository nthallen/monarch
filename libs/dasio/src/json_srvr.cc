#include "dasio/json_srvr.h"
#include "nl_assert.h"
#include "nl.h"

namespace DAS_IO {
  
  json_listener::json_listener(const char *hostname, json_server *jsrvr)
    : Socket("listener", "jsonext", Socket_TCP),
      jsrvr(jsrvr) {
    if (hostname) {
      this->hostname = hostname;
    }
  }
  
  Socket *json_listener::new_client(const char *iname, int fd) {
    json_client *rv =
      new json_client(this, iname, this->bufsize, fd, jsrvr);
    if (ELoop) ELoop->add_child(rv);
    jsrvr->add_client(rv);
    return rv;
  }
 
  json_client::json_client(Socket *orig, const char *iname,
          int ibufsize, int fd, json_server *jsrvr)
    : Socket(orig, iname, ibufsize, fd),
      jsrvr(jsrvr) {
    flags = Fl_Read;
  }
  
  void json_client::jwrite(const char *buf, int len) {
    if (obuf_empty()) {
      if (len > obufsize) {
        set_obufsize(len+100);
      }
      iwrite(buf, len);
    }
  }
  
  bool json_client::protocol_input() {
    msg(MSG_DEBUG, "Received input from client");
    report_ok(nc);
  }
  
  bool json_client::process_eof() {
    jsrvr->rm_client(this);
    jsrvr->ELoop.delete_child(this);
    return false;
  }

  json_server::json_server(const char *hostname)
      : writing(false) {
    nl_assert(jserver == 0);
    json_listener *TCP = new json_listener(hostname, this);
    ELoop.add_child(TCP);
    TCP->connect();
    jserver = this;
  }
  
  void json_server::add_client(json_client *clt) {
    clients.push_back(clt);
  }
  
  void json_server::rm_client(json_client *clt) {
    // Make sure we don't do this while traversing clients
    rmclts.push_back(clt);
    rm_clients();
  }
  
  void json_server::rm_clients() {
    if (!writing) {
      while (!rmclts.empty()) {
        json_client *clt = rmclts.front();
        clients.remove(clt);
        rmclts.pop_front();
      }
    }
  }
  
  json_server *json_server::jserver;
  
  void json_server::jcallback(const char *buf, int nc) {
    nl_assert(!writing);
    writing = true;
    std::list<json_client *>::iterator pos;
    for (pos = clients.begin(); pos != clients.end(); ++pos) {
      json_client *clt = *pos;
      clt->jwrite(buf, nc);
    }
    writing = false;
    rm_clients();
  }
  
  void json_server::jcb(const char *buf, int nc) {
    nl_assert(jserver);
    jserver->jcallback(buf, nc);
  }
  
}
