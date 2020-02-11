#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "dasio/interface.h"
#include "nl.h"

class meminfo : public DAS_IO::Interface {
  public:
    meminfo();
    /**
     * @return Amount of memory that is free as a multiple of 20 kB
     */
    int32_t tm_freemem();
    int32_t MemTotal;
    int32_t MemFree;
    int32_t MemAvailable;
  private:
    bool update();
};

int32_t meminfo::tm_freemem() {
  update();
  int32_t oval = MemAvailable ? MemAvailable : MemFree;
  return oval;
}

meminfo::meminfo() : DAS_IO::Interface("meminfo", 200) {
  fd = open("/proc/meminfo", O_RDONLY);
  if (fd < 0) msg(MSG_FATAL, "Unable to open /proc/meminfo");
  MemTotal = 0;
  MemFree = 0;
  MemAvailable = 0;
  update();
  msg(0, "Total Memory is %u kB", MemTotal);
}

bool meminfo::update() {
  char KW3[31];
  int32_t MaybeAvailable;
  if (lseek(fd, 0, SEEK_SET) < 0) {
    msg(MSG_ERROR, "Error %d calling lseek", errno);
    return true;
  }
  if (fillbuf()) return true;
  cp = 0;
  if (not_str("MemTotal:") ||
      not_int32(MemTotal) ||
      not_str(" kB\nMemFree:") ||
      not_int32(MemFree) ||
      not_str(" kB\n") ||
      not_KW(KW3, ':') ||
      not_int32(MaybeAvailable)) {
    if (cp >= nc) report_err("%s: Short read in meminfo::update()", iname);
    consume(nc);
    return true;
  }
  if (strcmp(KW3,"MemAvailable") == 0)
    MemAvailable = MaybeAvailable;
  report_ok(nc);
  return false;
}

int main(int argc, char **argv) {
  meminfo *minfo = new meminfo(); 
  for (;;) {
    int32_t Free = minfo->tm_freemem();
    msg(0, "Free Memory: %8d kB", Free);
    sleep(1);
  }
  return 0;
}
