/** @file template_server2.cc
 * @brief Template for a multi-subservice server application
 *
 * Replace boerf with a suitable name
 */
#include "dasio/appid.h"
#include "dasio/server.h"
#include "oui.h"

using namespace DAS_IO;

AppID_t DAS_IO::AppID("boerfd", "boerf server", "V1.0");

/**
 * @brief Subservice shared data
 *
 * A class needs to be defined for any socket_clone_t that needs to distinguish
 * between client connections. If all clients using a specific Serverside_Client
 * subclass are identical, then this isn't necessary. This is needed for:
 *   - DG/data/<var>
 *   - cmd/<driver>
 * In these cases, a single Serverside_Client subclass targets distincly
 * different destinations in a similar way, so a subservice info class is
 * necessary to distinguish between the targets.
 */
class boerf_info {
  public:
    inline boerf_info(const char *ident) : ident(ident) {}
    // Whatever a subservice needs to know
  private:
    const char *ident;
};

class boerf_ssclient : public Serverside_client {
  public:
    boerf_ssclient(Authenticator *Auth, const char *iname, boerf_info *bi);
    static const int boerf_ssclient_ibufsize = 80;
    // Include whatever virtual function overrides you need here
  protected:
    ~boerf_ssclient();
    boerf_info *bi;
    // Include any local data here
};

/**
 * @brief the Serverside_Client socket
 * If you don't need subservice identifying information (if this class supports
 * only one subservice, for example), you can leave out all references to bi
 * here and in new_boerf_ssclient()
 */
boerf_ssclient::boerf_ssclient(Authenticator *Auth, const char *iname, boerf_info *bi)
    : Serverside_client(Auth, iname, boerf_ssclient_ibufsize), bi(bi) {}

boerf_ssclient::~boerf_ssclient() {}

Serverside_client *new_boerf_ssclient(Authenticator *Auth, SubService *SS) {
  return new boerf_ssclient(Auth, Auth->get_client_app(), (boerf_info*)(SS->svc_data));
}

void add_subservices(Server *S) {
  S->add_subservice(new SubService("boerf/svc1", new_boerf_ssclient,
      (void *)(new boerf_info("svc1"))));
  S->add_subservice(new SubService("boerf/svc2", new_boerf_ssclient,
      (void *)(new boerf_info("svc2"))));
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  Server S("boerf");
  add_subservices(&S);
  S.Start(Server::Srv_Unix);
  return 0;
}
