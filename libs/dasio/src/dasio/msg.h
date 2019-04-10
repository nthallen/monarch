#ifndef MSG_H_INCLUDED
#define MSG_H_INCLUDED

#include <stdarg.h>
#include "nl.h"
#include "dasio/client.h"
#include "dasio/loop.h"

class memo_client: public DAS_IO::Client {
  public:
    memo_client();
    bool init();
    void send(const char* msg);
    void cleanup();
  protected:
    ~memo_client();
    bool app_connected();
    bool connect_failed();
    bool iwritten(int nb);
  private:
    DAS_IO::Loop ELoop;
};

extern "C" {
  
extern void msg_init_options(int argc, char **argv);
extern int msg_func(int level, const char *s, ...);
extern int msgv_func(int level, const char *s, va_list args);

#ifdef MSG_INTERNAL
extern int msg_internal(int level, const char *msgbuf, int nb);
extern void set_we_are_memo(void);
#endif

};

#endif
