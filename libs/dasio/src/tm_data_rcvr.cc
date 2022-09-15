/** @file tm_data_rcvr.cc */
#include <string.h>
#include "dasio/tm_data_rcvr.h"
#include "dasio/tm_gen.h"
#include "dasio/tm_gen_col.h"
#include "dasio/appid.h"
#include "nl.h"
//#include "dasio/msg.h"

namespace DAS_IO {
  
  // Server TM_server("DG");
  
  TM_data_rcvr::TM_data_rcvr(Authenticator *auth, const char *iname,
                             TM_data_rcvr_def *def)
        : Serverside_client(auth, iname, def->size*3),
          def(def),
          overrun_ibuf(false),
          underrun_ibuf(false) {
    def->interface = this;
    set_binary_mode();
  }
  
  TM_data_rcvr::~TM_data_rcvr() {
    if (def) {
      def->interface = 0;
    }
  }
  
  Serverside_client *TM_data_rcvr::new_tm_data_rcvr(Authenticator *auth, SubService *ss) {
    // Set iname from client_app and datum
    const char *clt_app = auth->get_client_app();
    TM_data_rcvr_def *def = (TM_data_rcvr_def *)(ss->svc_data);
    if (def->interface != 0) {
      msg(MSG_ERROR, "Datum %s already owned by %s, attempted by %s",
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
    while (nc-cp >= def->size) {
      memcpy(def->data, buf+cp, def->size);
      def->stale_count = 0;
      cp += def->size;
      if (nc > cp && !overrun_ibuf) {
        msg(MSG_WARN, "%s: Excess input: %d/%d", iname, nc, def->size);
        overrun_ibuf = true;
      }
    }
    consume(cp);
    if (nc > 0 && !underrun_ibuf) {
      msg(MSG_WARN, "%s: TM data underrun: %d/%d",
            iname, nc, def->size);
      underrun_ibuf = true;
    }
    return false;
  }
  
  void TM_data_rcvr::close() {
    def->close();
    Socket::close();
  }
  
  void TM_data_rcvr::synch() {
    if (obuf_empty())
      iwrite("\n");
  }
  
  void TM_data_rcvr_def::synch() {
    if (interface != 0)
      interface->synch();
  }
  
  uint16_t TM_data_rcvr_def::Stale(uint16_t limit) {
    uint16_t rv = (stale_count > limit) ? limit : stale_count;
    ++stale_count;
    return rv;
  }
  
  void TM_data_rcvr_def::close() {
    interface = 0;
  }
  
  TM_data_rcvr_def *collector::receive(const char *name, void *data, int data_size, int synch) {
    TM_data_rcvr_def *def = new TM_data_rcvr_def(name, data, data_size);
    int svclen = snprintf(0, 0, "%s/data/%s",
      get_service(), name);
    char *subservice = (char *)new_memory(svclen+1);
    snprintf(subservice, svclen+1, "%s/data/%s",
      get_service(), name);
    add_subservice(
      new SubService(
        subservice,
        TM_data_rcvr::new_tm_data_rcvr,
        def
      )
    );
    return def;
  }
}
