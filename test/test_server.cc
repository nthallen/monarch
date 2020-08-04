#include <stdlib.h>
#include <unistd.h>
#include "test_server.h"
#include "oui.h"
#include "nl.h"

int scenario = 1;
int comm_delay = 100; // 30 msec delay

test_socket *new_test_socket(DAS_IO::Authenticator *Auth,
        DAS_IO::SubService *SS) {
  test_socket *test = new test_socket(Auth, Auth->get_iname());
  test->flags |= DAS_IO::Interface::Fl_Timeout;
  return test;
}

bool test_socket::protocol_input() {
  uint16_t scu;
  cp = 0;
  switch (buf[cp]) {
    case 'S':
      if (state != st_init) {
        msg(2, "Unexpected 'S' in state %d", state);
      }
      if (not_str("S") || not_uint16(scu) || not_str("\n")) {
        report_err("%s: Unrecognized message", iname);
      } else {
        scenario = scu;
        msg(0, "Received scenario %d", scenario);
        TO.Set(0, comm_delay);
        state = st_comm_delay;
        if (scenario >= 10) {
          setup_times(2, 8);
        }
      }
      break;
    case 'I':
      msg(MSG_DEBUG, "Received Info");
      switch (scenario) {
        case 11:
        case 12:
        case 13:
          if (n_txrx <= 0 && !end_after_tx) {
            TO.Set(0, quit_delay);
            state = st_quit_delay;
          }
          break;
        default:
          if (scenario >= 10)
            msg(2, "Undefined scenario: %d", scenario);
          break;
      }
      if (state != st_quit_delay) {
        TO.Set(0,comm_delay);
        state = st_comm_delay;
      }
      break;
    case 'Q':
      msg(0, "Received Quit");
      state = st_quit_received;
      TO.Set(3, 0);
      break;
    default:
      report_err("Invalid message");
      break;
  }
  consume(nc);
  return false;
}

bool test_socket::protocol_timeout() {
  TO.Clear();
  switch (state) {
    case st_comm_delay:
      msg(MSG_DEBUG, "Sending Ack");
      iwrite("A\n");
      state = st_ack_sent;
      if (--n_txrx <= 0 && scenario > 10 && end_after_tx) {
        TO.Set(0, quit_delay);
        state = st_quit_delay;
      }
      break;
    case st_quit_delay:
      switch (scenario) {
        case 11:
        case 12:
          msg(MSG_DEBUG, "Sending Quit");
          iwrite("Q\n");
          if (scenario == 11) {
            state = st_quit_sent;
            TO.Set(3, 0);
            break;
          } // else fall through and just close:
        case 13:
          close();
          srvr->ELoop.delete_child(this);
          return true;
        default:
          msg(3, "Undefined scenario: %d", scenario);
      }
      break;
    case st_quit_received:
      msg(2, "Timeout without observed EOF");
      return true;
    default:
      msg(2, "Unexpected timeout in state %d", state);
      return true;
  }
  return false;
}

bool test_socket::process_eof() {
  srvr->ELoop.delete_child(this);
  switch (state) {
    case st_quit_received:
      msg(0, "Received expected EOF after Quit");
      break;
    case st_comm_delay:
    case st_ack_sent:
      switch (scenario) {
        case 1:
          msg(2, "Unexpected EOF before Quit in scenario 1");
          break;
        case 2:
          msg(0, "Received expected EOF without Quit in scenario 2");
          break;
        default:
          break;
      }
      break;
    default:
      msg(2, "Unexpected EOF in state %d", state);
      break;
  }
  return true;
}

unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

/**
 * Select random quit time between 2 and 8 times comm_delay
 * The resolution I want is say .01 seconds or 1/N seconds,
 * so I'd like to have a random number larger than N*(high-low)
 * Given a number R in the range 0-M, (R*(high-low)*N)/M + low*N
 * is a random number between low*N and high*N
 
 */
void test_socket::setup_times(unsigned low, unsigned high) {
  int range = high-low;
  unsigned int seed = mix(clock(), time(NULL), getpid());
  srandom(seed);
  uint32_t M = 0x100000;
  uint32_t N = 500;
  uint32_t R = random() & (M-1);
  uint32_t delay = (R*(high-low)*N)/M + low*N;
  n_txrx = delay/N;
  quit_delay = delay - n_txrx*N;
  end_after_tx = quit_delay >= N/2;
  if (end_after_tx)
    quit_delay -= N/2;
  quit_delay = (quit_delay * comm_delay) / N;
  msg(0, "setup_times %d rxtx %d msec %s tx",
    n_txrx, quit_delay, end_after_tx ? "after" : "before");
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  DAS_IO::Server *S = new DAS_IO::Server("test");
  S->add_subservice(new DAS_IO::SubService("test",
    (DAS_IO::socket_clone_t)new_test_socket, (void*)0));
  msg(0, "Starting");
  S->Start(DAS_IO::Server::server_type);
  msg(0, "Terminating");
  return 0;
}
