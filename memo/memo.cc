#include <stdio.h>
#include <getopt.h>
#include "nl.h"
#include "oui.h"
#include "memo.h"
#include "dasio/appid.h"
#include "dasio/loop.h"
#include "dasio/server.h"

DAS_IO::AppID_t DAS_IO::AppID("boerfd", "boerf server", "V1.0");

  MemoServer::MemoServer(const char *service, int bufsz) :
      service(service),
      bufsz(bufsz),
      Unix(0),
      TCP(0) { }

  MemoServer::~MemoServer() {}

  void MemoServer::Start(MemoServer::Srv_type which) {
    if (which & Srv_Unix) {
      Unix = new Server_socket("Unix", bufsz, service, Socket::Socket_Unix, &Subs);
      Unix->connect();
      ELoop.add_child(Unix);
    }
    if (which & Srv_TCP) {
      TCP = new Server_socket("TCP", bufsz, service, Socket::Socket_TCP, &Subs);
      TCP->connect();
      ELoop.add_child(TCP);
    }
    nl_error(0, "%s %s Starting", AppID.fullname, AppID.rev);
    ELoop.event_loop();
    nl_error(0, "Terminating");
  }

  memo_socket::~memo_socket() {}
  
static FILE *ofp, *ofp2;
static char *output_filename;
static int opt_V = 0;

void memo_init_options( int argc, char **argv ) {
  int c;
  ofp = stdout;
  ofp2 = NULL;
  optind = OPTIND_RESET;
  opterr = 0;
  while ((c = getopt(argc, argv, opt_string)) != -1 ) {
    switch (c) {
      case 'o':
        output_filename = optarg;
        break;
      case 'V':
        opt_V = 1;
        break;
      case '?':
        nl_error( 3, "Unrecognized commandline option -%c", optopt );
        break;
      default:
        break;
    }
  }
}

memo_socket *new_memo_socket(Authenticator *Auth, SubService *SS) {
  memo_socket *memo = new memo_socket(Auth, Auth->get_iname());
  return memo;
}

bool memo_socket::protocol_input() {
  //If there's a new line at the end of the buffer, don't add another
  //else add another
  //or just remove new line characters and then add one
  
  if (DAS_IO::Interface::nc > 0) {
    if (DAS_IO::Interface::buf[nc] == 0) {
      if (DAS_IO::Interface::buf[nc-1] != '\n') {
        DAS_IO::Interface::buf[nc] = '\n';
        DAS_IO::Interface::buf[nc+1] = 0;
        // question: if the last char (buf[nc-1]) isn't a new line,
        // and the one after it (buf[nc]) is null,
        // should I be altering buf[nc+1] to be newline?
      }
    } else {
      return true; //maybe?
    }
  } else {
    //buffer is empty
  }
  
  //at end, must call report_ok(nc);
  // calls consume(), gets rid of chars in buffer, etc.
  DAS_IO::Interface::report_ok(DAS_IO::Interface::nc);
  return false;
  //never returns true
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  int bufsize = 1000;
  
  //to be built up
  MemoServer memoserver("boerf", bufsize);
  memoserver.Subs.add_subservice(new SubService("memo", (socket_clone_t)new_memo_socket, (void*)0));
  memoserver.Start(MemoServer::Srv_Unix);
  return 0;
}