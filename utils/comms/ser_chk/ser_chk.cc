#include <unistd.h>
#include <fcntl.h>
#include "ser_chk.h"
#include "oui.h"
#include "dasio/msg.h"

ser_chk_ser::ser_chk_ser(const char *path, int baud)
      : DAS_IO::Serial("ser", 256, path, O_RDWR)
{
  if (path == 0)
    msg(3, "Must specify path option");
  setup(baud, 8, 'n', 1, 0, 0);
  set_obufsize(256);
}

bool ser_chk_ser::send_data(const uint8_t *data, int nb) {
  return iwrite((const char*)data, nb);
}

bool ser_chk_ser::protocol_input() {
  ::write(STDOUT_FILENO, buf, nc);
  report_ok(nc);
  return false;
}

int ser_chk_baud = 57600;
const char *ser_chk_port;

ser_chk_stdin::ser_chk_stdin(ser_chk_ser *ser)
      : DAS_IO::Interface("kbd", 256),
        ser(ser) {
  fd = STDIN_FILENO;
  if (tcgetattr(fd, &termios_p) || tcgetattr(fd, &termios_sav)) {
    msg(3, "%s: Error on tcgetattr()", iname);
  }
  termios_p.c_cc[VMIN]  =  1;
  termios_p.c_cc[VTIME] =  0;
  termios_p.c_lflag &= ~( ECHO|ICANON|ISIG|
              ECHOE|ECHOK|ECHONL );
  termios_p.c_oflag &= ~( OPOST );
  if (tcsetattr( fd, TCSADRAIN, &termios_p ))
    msg(2, "%s: Error from tcsetattr", iname);
  flags = DAS_IO::Interface::Fl_Read;
}

ser_chk_stdin::~ser_chk_stdin() {
  tcsetattr(fd, TCSADRAIN, &termios_sav);
  if (ser) {
    dereference(ser);
    ser = 0;
  }
}

bool ser_chk_stdin::protocol_input() {
  for (int i = 0; i < nc; ++i) {
    if (buf[i] == 1) // ctrl-A
      return true;
  }
  ser->send_data(buf, nc);
  report_ok(nc);
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  DAS_IO::Loop ELoop;
  ser_chk_ser *ser = new ser_chk_ser(ser_chk_port, ser_chk_baud);
  ELoop.add_child(ser);
  ser_chk_stdin *kbd = new ser_chk_stdin(ser);
  ELoop.add_child(kbd);
  ELoop.event_loop();
  ELoop.remove_child(kbd);
  DAS_IO::Interface::dereference(kbd);
  ELoop.delete_children();
  return 0;
}
