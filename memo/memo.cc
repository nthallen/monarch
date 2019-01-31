#include <stdio.h>
#include <getopt.h>
#include "nl.h"
#include "oui.h"
#ifdef undefined
#include "memo.h"

class MemoServer {
  public:
  MemoServer::MemoServer(const char *service, int bufsz) :
      service(service),
      bufsz(bufsz),
      Unix(0),
      TCP(0) { }

  MemoServer::~MemoServer() {}

  void MemoServer::Start(Server::Srv_type which) {
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
  protected:
  const char *service;
  int bufsz;
}
#endif

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

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  int bufsize = 1000;
  
  //to be built up
  MemoServer memoserver = new MemoServer("boerf", bufsize);
  memoserver.Subs.add_subservice(new SubService("boerf", (socket_clone_t)new_boerf_ssclient, (void *)0));
  memoserver.Start(Srv_Unix);
  return 0;
}