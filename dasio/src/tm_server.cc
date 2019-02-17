/** @file tm_server.cc */
#include <string.h>
#include "dasio/tm_server.h"
#include "dasio/appid.h"
#include "nl.h"

namespace DAS_IO {
  
  Server TM_server("DG", 128);
  
  TM_data_rcvr::TM_data_rcvr(Authenticator *auth, const char *iname, TM_data_rcvr_def *def)
        : Socket(auth, iname, auth->fd), def(def) {
    def->interface = this;
  }
  
  TM_data_rcvr::~TM_data_rcvr() {}
  
  TM_data_rcvr *TM_data_rcvr::new_tm_data_rcvr(Authenticator *auth, SubService *ss) {
    // Set iname from client_app and datum
    const char *clt_app = auth->get_client_app();
    TM_data_rcvr_def *def = (TM_data_rcvr_def *)(ss->svc_data);
    if (def->interface != 0) {
      nl_error(2, "Datum %s already owned by %s, attempted by %s",
        def->datum, def->interface->get_iname(), clt_app);
      return 0;
    }
    int inamelen = strlen(clt_app) + strlen(def->datum) + 2;
    char *iname = (char *)new_memory(inamelen);
    snprintf(iname, inamelen, "%s/%s", clt_app, def->datum);
    return new TM_data_rcvr(auth, iname, def);
  }
  
  bool TM_data_rcvr::protocol_input() {
    // protocol_input() can be called when there is no input
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
  
  void TM_data_rcvr::close() {
    def->close();
    Socket::close();
  }
  
  void TM_data_rcvr::synch() {
    iwrite("\n");
  }
  
  void TM_data_rcvr_def::synch() {
    ++stale_count;
    if (interface != 0)
      interface->synch();
  }
  
  uint16_t TM_data_rcvr_def::Stale(uint16_t limit) {
    return (stale_count > limit) ? limit : stale_count;
  }
  
  void TM_data_rcvr_def::close() {
    interface = 0;
  }
  
  TM_data_rcvr_def *TM_receive(const char *name, void *data, int data_size, int synch) {
    int svclen = snprintf(0, 0, "%s/data/%s", TM_server.get_service(), name);
    char *subservice = (char *)new_memory(svclen+1);
    snprintf(subservice, svclen+1, "%s/data/%s", TM_server.get_service(), name);
    TM_server.add_subservice(
      new SubService(
        subservice,
        (socket_clone_t)TM_data_rcvr::new_tm_data_rcvr,
        new TM_data_rcvr_def(name, data, data_size)
      )
    );
  }
}
