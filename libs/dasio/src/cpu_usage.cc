/**
   cpu_usage module for use with telemetry data collection.
   This is based on QNX6 documentation:
    QNX Realtime Operating System
      Programmer's Guide
        Processes
          Controlling processes via the /proc filesystem
            DCMD_PROC_SYSINFO
            DCMD_PROC_TIDSTATUS
 */
#include <sys/types.h>
#include <unistd.h>
#include "dasio/cpu_usage.h"
#include "nl.h"

namespace DAS_IO {
  
cpu_usage::cpu_usage() : Interface("procstat", 256) {
  fd = open("/proc/stat", O_RDONLY);
  if (fd < 0) msg(MSG_ERROR, "%s: Unable to open /proc/stat", iname);
}

/**
 * @param rate The rate at which this function is called in Hz.
 * @return Percent CPU utilization since the last call.
 */
uint8_t cpu_usage::report() {
  if (fd < 0) return 255; // error value
  if (lseek(fd, 0, SEEK_SET) < 0) {
    msg(MSG_ERROR, "%s: Error %d calling lseek", iname, errno);
    return true;
  }
  if (fillbuf()) {
    close();
    return 255;
  }
  cp = 0;
  uint64_t total = 0;
  uint64_t idle = 0;
  
  if (not_str("cpu")) {
    if (cp >= nc) report_err("%s: Short read: nc = %u", iname, nc);
    consume(nc);
    return 255;
  }
  int i;
  for (i = 1; ; ++i) {
    uint64_t cur_cts;
    if (cp >= nc || buf[cp] == '\n')
      break;
    if (not_uint64(cur_cts)) {
      if (cp >= nc) report_err("%s: Expected numbers", iname);
      consume(nc);
      return 255;
    }
    total += cur_cts;
    if (i == 4)
      idle = cur_cts;
  }
  report_ok(nc);
  uint64_t ratio = (total - idle)*100/total;
  if (ratio > 100 || ratio < 0)
    ratio = 255;
  return (uint8_t) ratio;
}

} // DAS_IO namespace
