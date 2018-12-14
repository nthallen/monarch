/** @file tm_server.cc */
#include <string.h>
#include "dasio/tm_server.h"
#include "dasio/appid.h"
#include "nl.h"

namespace DAS_IO {
  
  TM_server::TM_server(Authenticator *auth, const char *iname, TM_server_def *def)
        : Socket(auth, iname, auth->fd), def(def) {
    def->interface = this;
  }
  
  TM_server::~TM_server() {}
  
  TM_server *TM_server::new_tm_server(Authenticator *auth, SubService *ss) {
    // Set iname from client_app and datum
    const char *clt_app = auth->get_client_app();
    TM_server_def *def = (TM_server_def *)(ss->svc_data);
    if (def->interface != 0) {
      nl_error(2, "Datum %s already owned by %s, attempted by %s",
        def->datum, def->interface->get_iname(), clt_app);
      return 0;
    }
    int inamelen = strlen(clt_app) + strlen(def->datum) + 2;
    char *iname = (char *)new_memory(inamelen);
    snprintf(iname, inamelen, "%s/%s", clt_app, def->datum);
    return new TM_server(auth, iname, def);
  }
  
  bool TM_server::protocol_input() {
    if (nc < def->size) return false;
    if (nc > def->size) {
      report_err("%s: Excess input", iname);
    } else {
      memcpy(def->data, buf, def->size);
      def->stale_count = 0;
    }
    consume(nc);
    return false;
  }
  
  void TM_server::close() {
    def->close();
    Socket::close();
  }
  
  void TM_server::sync() {
    iwrite("\n");
  }
  
  void TM_server_def::sync() {
    ++stale_count;
    if (interface != 0)
      interface->sync();
  }
  
  uint16_t TM_server_def::Stale(uint16_t limit) {
    return (stale_count > limit) ? limit : stale_count;
  }
  
  void TM_server_def::close() {
    interface = 0;
  }
}
