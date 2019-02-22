#include <stdio.h>
#include <getopt.h>
#include "nl.h"
#include "nl_assert.h"
#include "oui.h"
#include "memo.h"
#include "dasio/appid.h"
#include "dasio/loop.h"
#include "dasio/server.h"
#define MSG_INTERNAL
#include "dasio/msg.h"

DAS_IO::AppID_t DAS_IO::AppID("memo", "memo server", "V1.0");

memo_socket::~memo_socket() {}

void memo_init_options( int argc, char **argv ) {
  set_we_are_memo();
}

memo_socket *new_memo_socket(Authenticator *Auth, SubService *SS) {
  memo_socket *memo = new memo_socket(Auth, Auth->get_iname());
  return memo;
}

bool memo_socket::protocol_input() {
  nl_assert(DAS_IO::Interface::nc > 0);
  nl_assert(DAS_IO::Interface::buf[nc] == '\0');
  
  /* If we encounter a newline character, we replace it with null. */
  if (DAS_IO::Interface::buf[nc-1] == '\n') {
    DAS_IO::Interface::buf[nc-1] = '\0';
  }
  /* And then we printf() with a newline added, for cleanliness. */
  printf("%s\n", DAS_IO::Interface::buf);
  
  DAS_IO::Interface::report_ok(DAS_IO::Interface::nc);
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  int threshold = 10;
  
  Server server("memo");
  server.add_subservice(new SubService("memo", (socket_clone_t)new_memo_socket, (void*)0));
  server.set_passive_exit_threshold(threshold);
  server.Start(Server::Srv_Unix);
  return 0;
}
