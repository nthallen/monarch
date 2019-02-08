#ifndef MSG_H_INCLUDED
#define MSG_H_INCLUDED

#include <stdarg.h>

//#ifdef __cplusplus

class memo_client: public DAS_IO::Client {
  public:
    memo_client();
    ~memo_client();
    bool init();
    void send(const char* msg);
  protected:
    bool is_negotiated();
    bool connect_failed();
    bool iwritten(int nb);
  private:
    DAS_IO::Loop ELoop;
};

/* extern "C" {
#endif */


extern const char *msghdr_init(const char *hdr_default, int argc, char **argv);
extern void msg_init_options(int argc, char **argv);
extern int msg(int level, const char *s, ...);
extern int msgv(int level, const char *s, va_list args);
extern void msg_set_hdr(const char *hdr);

/* #ifdef __cplusplus
};
#endif */

#endif
