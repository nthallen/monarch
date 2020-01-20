#ifndef PARENT_H_INCLUDED
#define PARENT_H_INCLUDED
#include "dasio/server.h"
#include "dasio/appid.h"

extern int quit_when_childless;
extern int parent_timeout;
extern pid_t monitor_pid;
extern const char *script_file;

using namespace DAS_IO;

class parent_ssclient : public Serverside_client {
  public:
    parent_ssclient(Authenticator *Auth, const char *iname);
    // Specify how big the ibuf needs to be:
    static const int parent_ssclient_ibufsize = 80;
    // Include whatever virtual function overrides you need here
  protected:
    // ~parent_ssclient();
    bool protocol_input();
    /**
     * @param script name of requested script
     * Writes the script name to the file specified by the -s
     * option, saved in the global script_file variable. If
     * no script_file is specified, no action is taken.
     * If script is zero, the string "/dev/null" is written.
     */
    void write_script_file(const char *script);
    // Include any local data here
};

class parent_sigif : public Interface {
  public:
    parent_sigif(Server *srvr);
    bool serialized_signal_handler(uint32_t signals_seen);
    bool protocol_timeout();
  private:
    inline uint32_t signal_bit(int signal) { return (1<<(signal-1)); }
    inline bool saw_signal(uint32_t signals_seen, int signal) {
      return (signals_seen & signal_bit(signal));
    }
    Server *srvr;
    // bool have_children;
    bool handled_INT;
    bool handled_timeout;
};

#endif
