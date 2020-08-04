#ifndef TEST_CLIENT_H_INCLUDED
#define TEST_CLIENT_H_INCLUDED
#include "dasio/client.h"

extern const char *server_hostname;
extern int scenario;
extern int comm_delay;

class test_client : public DAS_IO::Client {
  public:
    test_client(const char *hostname);
    bool app_connected();
    bool app_input();
    bool app_process_eof();
  protected:
    bool protocol_timeout();
    enum state_val { st_init, st_scenario_sent, st_comm_delay, st_info_sent,
                     st_quit_delay, st_quit_sent, st_quit_received } state;
    int n_txrx; //< The number of round trips before termination when client is in control
    bool end_after_tx; //< Whether we quit before or after sending another request
    int quit_delay; //< Delay before quitting. Must be less than comm_delay
  private:
    void setup_times(unsigned low, unsigned high);
};

#endif
