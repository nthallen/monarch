#ifndef MSG_H_INCLUDED
#define MSG_H_INCLUDED

#include <stdarg.h>
#include "nl.h"

#ifdef __cplusplus

#include "client.h"
#include "loop.h"

namespace DAS_IO {

class memo_client : public DAS_IO::Client {
  public:
    memo_client();
    bool init();
    void send(const char* msg, int nb);
    void cleanup();
  protected:
    ~memo_client();
    bool app_connected();
    bool connect_failed();
    bool iwritten(int nb);
  private:
    Loop ELoop;
};

}

extern "C" {
#endif

extern void msg_init_options(int argc, char **argv);
extern int msg_func(int level, const char *s, ...);
extern int msgv_func(int level, const char *s, va_list args);

#ifdef MSG_INTERNAL
extern int msg_internal(int level, const char *msgbuf, int nb);
extern void set_we_are_memo(void);
#endif

#ifdef __cplusplus
};
#endif

#endif
