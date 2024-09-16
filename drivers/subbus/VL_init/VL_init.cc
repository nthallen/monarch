#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "oui.h"
#include "nl.h"
#include "nl_assert.h"
#include "VL_init.h"

const char *VL_port = "/dev/ttyS0";

uint8_t read_port(int fd, int addr) {
  int rv = lseek(fd, addr, SEEK_SET);
  uint8_t val;
  if (rv == -1) {
    msg(MSG_FATAL, "lseek error %d: %s\n", errno, strerror(errno));
  }
  rv = read(fd, &val, 1);
  if (rv != 1) {
    if (rv == -1) {
      msg(MSG_FATAL, "read from /dev/port returned error %d: %s\n",
        errno, strerror(errno));
    } else {
      msg(MSG_FATAL, "read from /dev/port returned unexpected count %d\n", rv);
    }
  }
  return val;
}

uint8_t write_port(int fd, int addr, uint8_t val) {
  int rv = lseek(fd, addr, SEEK_SET);
  if (rv == -1) {
    msg(MSG_FATAL, "lseek error %d: %s\n", errno, strerror(errno));
  }
  rv = write(fd, &val, 1);
  if (rv != 1) {
    if (rv == -1) {
      msg(MSG_FATAL, "write to /dev/port 0x%3X returned error %d: %s\n",
        addr, errno, strerror(errno));
    } else {
      msg(MSG_FATAL, "write to /dev/port 0x%3X returned unexpected count %d\n", addr, rv);
    }
  }
  return rv;
}

void do_VL_init(const char *port)
{
  int port_id, len;
  int N = sscanf(port, "/dev/ttyS%d%n", &port_id, &len);
  int addr = 0;
  if (!(N == 1 && (port_id==0 || port_id==1) && port[len] == '\0')) {
    msg(MSG_FATAL,
      "-M option only applies to ports /dev/ttyS[01]");
  }
  switch (port_id) {
    case 0: addr = 0x3F8; break;
    case 1: addr = 0x2F8; break;
    default: nl_assert(false);
  }
  addr += 4; // target MCR register.
  
  int iofd = open("/dev/port", O_RDWR);
  if (iofd == -1) {
    msg(MSG_FATAL, "open /dev/port reported error %d: %s\n",
      errno, strerror(errno));
  }
  uint8_t cur_val = read_port(iofd, addr);
  uint8_t new_val = cur_val &= ~2; // Clear the RTS bit
  if (cur_val != new_val) {
    msg(MSG, "Updating MCR register from 0x%02X to 0x%02X",
      cur_val, new_val);
    write_port(iofd, addr, new_val);
  } else {
    msg(MSG_WARN, "No change to MCR register: 0x%02X",
      cur_val);
  }
  close(iofd);
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  do_VL_init(VL_port);
}
