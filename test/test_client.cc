#include <stdlib.h>
#include <unistd.h>
#include "dasio/loop.h"
#include "test_client.h"
#include "oui.h"
#include "nl.h"

const char *server_hostname;
int scenario = 1;
int comm_delay = 100; // 100 msec delay

test_client::test_client(const char *hostname) :
      DAS_IO::Client("Client", 80, hostname, "test", 0) {
  state = st_init;
}

bool test_client::app_connected() {
  char obuf[80];
  msg(0, "Connected");
  snprintf(obuf, 80, "S%d\n", scenario);
  TO.Set(0, comm_delay); 
  state = st_scenario_sent;
  return iwrite(obuf);
}

bool test_client::app_input() {
  cp = 0;
  while (nc > 0) {
    switch (buf[cp]) {
      case 'A':
        switch (state) {
          case st_scenario_sent:
            if (scenario < 10) {
              // Client will drive scenario
              setup_times(2,8);
            }
            break;
          case st_info_sent:
            if (scenario < 10) {
              // Client in control.
              if (--n_txrx <= 0 && !end_after_tx) {
                TO.Set(0, quit_delay);
                state = st_quit_delay;
              }
            }
            break;
          default:
            msg(2, "Unexpected input? State=%d", state);
            break;
        }
        if (state != st_quit_delay) {
          TO.Set(0,comm_delay);
          state = st_comm_delay;
        }
        break;
      case 'Q':
        TO.Clear();
        msg(0, "Quit received");
        iwrite("Q\n");
        close();
        state = st_quit_received;
        break;
      default:
        report_err("%s: Unexpected input", iname);
        break;
    }
    if (!not_found('\n')) {
      consume(cp);
    }
  }
  return (state == st_quit_received);
}

bool test_client::protocol_timeout() {
  TO.Clear();
  switch (state) {
    case st_comm_delay:
      iwrite("I\n");
      if (scenario < 10 && n_txrx <= 0) {
        TO.Set(0, quit_delay);
        state = st_quit_delay;
      } else {
        state = st_info_sent;
      }
      break;
    case st_quit_delay:
      switch (scenario) {
        case 1: // quit using protocol
          state = st_quit_sent;
          msg(0, "Quit sent");
          iwrite("Q\n");
          close();
          return true;
        case 2:
          state = st_quit_sent;
          msg(0, "Closing without prior notification");
          close();
          return true;
        default:
          msg(2, "Unknown scenario: %d", scenario);
          return true;
      }
      break;
    default:
      msg(1, "Timeout in wrong state: %d", state);
      break;
  }
  return false;
}

bool test_client::app_process_eof() {
  msg(0, "Remote server closed connection");
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
void test_client::setup_times(unsigned low, unsigned high) {
  int range = high-low;
  unsigned int seed = mix(clock(), time(NULL), getpid());
  srandom(seed);
  uint32_t M = 0x100000;
  uint32_t N = 500;
  uint32_t R = random() & (M-1);
  uint32_t delay = (R*(high-low)*N)/M + low*N;
  n_txrx = delay/N;
  quit_delay = delay - n_txrx*N;
  end_after_tx = delay >= N/2;
  if (end_after_tx)
    quit_delay -= N/2;
  msg(MSG_DEBUG, "setup_times %d rxtx %d msec %s tx",
    n_txrx, quit_delay, end_after_tx ? "after" : "before");
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  DAS_IO::Loop ELoop;
  test_client *clt = new test_client(server_hostname);
  clt->connect();
  ELoop.add_child(clt);
  msg(0, "Starting scenario #%d", scenario);
  ELoop.event_loop();
  msg(0, "Terminating");
}
