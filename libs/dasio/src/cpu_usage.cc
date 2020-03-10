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
  prev_total = 0;
  prev_idle = 0;
  prev_report = 0;
  fd = open("/proc/stat", O_RDONLY);
  if (fd < 0) msg(MSG_ERROR, "%s: Unable to open /proc/stat", iname);
  report();
}

/**
 * @param rate The rate at which this function is called in Hz.
 * @return Percent CPU utilization since the last call times 655.34.
 * 65535 is an error return value.
 */
uint16_t cpu_usage::report() {
  if (fd < 0) return 65535; // error value
  if (lseek(fd, 0, SEEK_SET) < 0) {
    msg(MSG_ERROR, "%s: Error %d calling lseek", iname, errno);
    return true;
  }
  if (fillbuf()) {
    close();
    return 65535;
  }
  cp = 0;
  uint64_t total = 0;
  uint64_t idle = 0;
  
  if (not_str("cpu")) {
    if (cp >= nc) report_err("%s: Short read: nc = %u", iname, nc);
    consume(nc);
    return 65535;
  }
  int i;
  for (i = 1; ; ++i) {
    uint64_t cur_cts;
    if (cp >= nc || buf[cp] == '\n')
      break;
    if (not_uint64(cur_cts)) {
      if (cp >= nc) report_err("%s: Expected numbers", iname);
      consume(nc);
      return 65535;
    }
    total += cur_cts;
    if (i == 4)
      idle = cur_cts;
  }
  report_ok(nc);
  uint64_t dtotal = total - prev_total;
  uint64_t didle = idle - prev_idle;
  prev_total = total;
  prev_idle = idle;
  uint64_t ratio = dtotal ?
    (dtotal - didle)*65534/dtotal : prev_report;
  if (ratio > 65534 || ratio < 0)
    ratio = 65535;
  prev_report = ratio;
  return (uint16_t) ratio;
}

} // DAS_IO namespace
