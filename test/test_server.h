#ifndef TEST_SERVER_H_INCLUDED
#define TEST_SERVER_H_INCLUDED
#include "dasio/server.h"

extern int scenario;
extern int comm_delay;

class test_socket : public DAS_IO::Serverside_client {
  public:
    inline test_socket(DAS_IO::Authenticator *orig, const char *iname) :
      DAS_IO::Serverside_client(orig, iname, 80), state(st_init) {}
  protected:
    bool protocol_timeout();
    bool protocol_input();
    bool process_eof();
    enum state_val { st_init, st_comm_delay, st_ack_sent,
                     st_quit_delay, st_quit_sent, st_quit_received } state;
    int n_txrx; //< The number of round trips before termination when client is in control
    bool end_after_tx; //< Whether we quit before or after sending another request
    int quit_delay; //< Delay before quitting. Must be less than comm_delay
  private:
    void setup_times(unsigned low, unsigned high);
};

test_socket *new_test_socket(DAS_IO::Authenticator *Auth, DAS_IO::SubService *SS);

#endif
