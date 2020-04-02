#ifndef SER_CHK_H_INCLUDED
#define SER_CHK_H_INCLUDED
#include <termios.h>
#include "dasio/interface.h"
#include "dasio/serial.h"

class ser_chk_stdin;

extern int ser_chk_baud;
extern const char *ser_chk_port;

class ser_chk_ser : public DAS_IO::Serial {
  public:
    ser_chk_ser(const char *path, int baud);
    bool send_data(const uint8_t *data, int nb);
  protected:
    bool protocol_input();
};

class ser_chk_stdin : public DAS_IO::Interface {
  public:
    ser_chk_stdin(ser_chk_ser *ser);
    ~ser_chk_stdin();
    bool protocol_input();
  protected:
    ser_chk_ser *ser;
    termios termios_p;
    termios termios_sav;
};

#endif
