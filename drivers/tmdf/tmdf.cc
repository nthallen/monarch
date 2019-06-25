#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/statvfs.h>
#include <time.h>
#include <unistd.h>
#include "nl.h"
#include "oui.h"
#include "tmdf_int.h"
#include "tmdf.h"
#include "dasio/appid.h"
#include "dasio/loop.h"

using namespace DAS_IO;

DAS_IO::AppID_t DAS_IO::AppID("tmdf", "TMDF", "V1.0");

const char *df_path = "/";
const char *tmdf_name = "tmdf_driver";
TMDF_t TMDF;

TMDF_data_sndr::TMDF_data_sndr( unsigned seconds, const char *name,
	void *data, unsigned short size )
    : TM_data_sndr("TM", name, data, size ) {
  fd = open(df_path, O_RDONLY);
  next = 0;
  secs = seconds;
  if (fd < 0) {
    msg( MSG_ERROR, "Error opening %s: %s", df_path, strerror(errno) );
  } else {
    report_size();
  }
  flags |= gflag(0) | Fl_Read;
}

bool TMDF_data_sndr::app_connected() {
  flags |= gflag(0);
  return false;
}

TMDF_data_sndr::~TMDF_data_sndr() {
  report_size();
  if (fd >= 0) close(/*fd*/);
}

void TMDF_data_sndr::report_size() {
  if (fd >= 0) {
    struct statvfs buf;
    if (fstatvfs(fd, &buf) ) {
      msg(MSG_ERROR, "fstatvfs reported %s", strerror(errno));
    } else {
      double fdsize = buf.f_blocks * buf.f_frsize;
      double used = buf.f_blocks - buf.f_bavail;
      const char *units = "Bytes";
      used = 100. * used / buf.f_blocks;
      if (fdsize > 1024*1024*1024) {
        fdsize /= 1024*1024*1024;
        units = "GB";
      } else if (fdsize > 1024*1024) {
        fdsize /= 1024*1024;
        units = "MB";
      } else if (fdsize > 1024) {
        fdsize /= 1024;
        units = "KB";
      }
      msg(0, "Drive '%s' total size: %.1lf %s: In use: %.1lf %%",
        df_path, fdsize, units, used);
    }
  }
}

bool TMDF_data_sndr::tm_sync() {
  time_t now = time(NULL);
  if ( next == 0 || now >= next ) {
    next = now + secs;
    if (fd < 0)
      fd = open(df_path, O_RDONLY);
    if (fd >= 0) {
      struct statvfs buf;
      if (fstatvfs(fd, &buf) ) {
        msg(MSG_ERROR, "fstatvfs reported %s", strerror(errno));
        TMDF.usage = 65535;
      } else {
        double blks;
        blks = (buf.f_blocks - buf.f_bavail);
        blks = blks * 65534. / buf.f_blocks;
        TMDF.usage = (blks > 65534) ? 65534 : ((unsigned short)blks);
        msg(MSG_DEBUG, "f_blocks = %d  f_bavail = %d", buf.f_blocks, buf.f_bavail );
      }
    } else {
      TMDF.usage = 65535;
    }
  } else {
    //msg(-3, "next: %lu  now: %lu", next, now );
    msg(MSG_DBG(3), "next: %lu  now: %lu", next, now );
  }
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  msg(0, "Startup");
  
  DAS_IO::Client QC("cmd", 5, "cmd", "Quit");
  QC.flags = Interface::Fl_Read;
  TMDF_data_sndr TM( 60, tmdf_name, &TMDF, sizeof(TMDF) );
  QC.connect();
  TM.connect();
  
  Loop ELoop;
  ELoop.add_child(&QC);
  ELoop.add_child(&TM);
  ELoop.event_loop();
  
  /* { Selector S;
    DAS_IO::Client QC("cmd", 5, "cmd", "cmd", "quit");
    TMDF_data_sndr TM( 60, tmdf_name, &TMDF, sizeof(TMDF));
    S.add_child(&QC);
    S.add_child(&TM);
    S.event_loop();
  } */
  
  msg(0, "Terminating");
}
