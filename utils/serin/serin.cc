#include "serin.h"
#include "oui.h"

using namespace DAS_IO;

serin::serin() : tm_generator() {}

void serin::start() {
  execute("TMc"); // autostart so we can send data whenever it arrives
  Start(Server::server_type);
  ELoop.delete_children();
  ELoop.clear_delete_queue(true);
}

void serin::service_row_timer() {
  if (regulated) transmit_data(true);
}

serin_serin::serin_serin(Authenticator *auth, const char *iname,
                         serin *srvr)
    : Serverside_client(auth, iname, serin_bufsize),
      srvr(srvr) {}

void serin_serin::attach(serin *srvr) {
  srvr->add_subservice(new SubService("tm_gen/serin", new_serin_serin,
    (void *)srvr));
}

Serverside_client *serin_serin::new_serin_serin(
            Authenticator *Auth, SubService *SS) {
  serin *srvr = (serin *)(SS->svc_data);
  return new serin_serin(Auth, Auth->get_client_app(), srvr);
}

bool serin_serin::protocol_input() {
  report_ok(nc);
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  msg(MSG, "Starting");
  load_tmdac(0);
  serin *srvr = new serin();
  srvr->init(4, true);
  serin_serin::attach(srvr);
  srvr->start();
  msg(MSG, "Terminating");
  return 0;
}
