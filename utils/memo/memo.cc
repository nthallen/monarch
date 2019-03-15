#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "nl.h"
#include "nl_assert.h"
#include "oui.h"
#include "memo.h"
#include "dasio/appid.h"
#include "dasio/loop.h"
#include "dasio/server.h"
#define MSG_INTERNAL /* Required to make we_are_memo() and msg_internal() visible */
#include "dasio/msg.h"

DAS_IO::AppID_t DAS_IO::AppID("memo", "memo server", "V1.0");

memo_socket::~memo_socket() {}

int memo_quit_threshold = 1;

void memo_init_options( int argc, char **argv ) {
  set_we_are_memo();
	int c;

  optind = OPTIND_RESET;
  opterr = 0;
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'l':
        memo_quit_threshold = atoi(optarg);
        break;
      case '?':
        fprintf( stderr, "Unrecognized option: '-%c'\n", optopt );
        exit(1);
      default: break; // could check for errors
    }
  }
}

memo_socket *new_memo_socket(Authenticator *Auth, SubService *SS) {
  memo_socket *memo = new memo_socket(Auth, Auth->get_iname());
  return memo;
}

bool memo_socket::protocol_input() {
  nl_assert(nc > 0);
  nl_assert(buf[nc] == '\0');
  
  /* Add a newline if necessary */
  if (buf[nc-1] != '\n') {
    buf[nc++] = '\n';
  }
  msg_internal(0, (const char*)buf, nc);
  
  report_ok(nc);
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  
  Server server("memo");
  server.add_subservice(new SubService("memo", (socket_clone_t)new_memo_socket, (void*)0));
  server.set_passive_exit_threshold(memo_quit_threshold);
  server.Start(Server::Srv_Unix);
  return 0;
}
