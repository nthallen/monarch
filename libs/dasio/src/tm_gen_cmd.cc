#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
// #include "dasio/tm_gen_client.h"
#include "dasio/tm_gen_cmd.h"
#include "nl.h"
#include "nl_assert.h"
#include "dasio/tm.h"

namespace DAS_IO {
  
static tm_gen_cmd *Cmd;

/**
 * buf is guaranteed to be nul-terminated
 * We will strip any trailing newlines before forwarding to tmg->execute()
 */
bool tm_gen_cmd::protocol_input() {
  // In arp_das, we replied to the sender, presumably to unblock it.
  // I don't think the sender will be blocked here, so I won't reply
  return tmg->execute((const char *)buf);
}

bool tm_gen_cmd::process_eof() {
  return tmg->execute("");
}

tm_gen_cmd::tm_gen_cmd(Authenticator *Auth, const char *iname, tm_generator *tm_gen)
    : DAS_IO::Serverside_client(Auth, iname, tm_gen_CMD_BUFSIZE) {
  tmg = tm_gen;
}

void tm_gen_cmd::attach(tm_generator *tmgp) {
  tmgp->add_subservice(new SubService("tm_gen/cmd", new_tm_gen_cmd,
    (void *)tmgp));
}

tm_gen_cmd::~tm_gen_cmd() { }

Serverside_client *new_tm_gen_cmd(Authenticator *Auth, SubService *SS) {
  tm_generator *tmgp = (tm_generator*)(SS->svc_data);
  return new tm_gen_cmd(Auth, Auth->get_client_app(), tmgp);
}

}
