#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "dasio/mlf_packet_logger.h"
#include "nl.h"
#include "nl_assert.h"

namespace DAS_IO {

mlf_packet_logger::mlf_packet_logger(const char *iname,
      const char *mlf_base, const char *mlf_config)
    : miname(iname),
      mlf(0),
      ofd(-1),
      Bytes_in_File(0),
      Bytes_per_File(default_Bytes_per_File)
{
  mlf = mlf_init(3, 60, 1, mlf_base, "dat", mlf_config);
}

mlf_packet_logger::~mlf_packet_logger()
{
  if (ofd >= 0) {
    ::close(ofd);
    ofd = -1;
  }
}

void mlf_packet_logger::log_packet(const uint8_t *bfr, uint32_t pkt_len,
          log_mode mode)
{
  if (ofd < 0 || (mode == log_newfile) ||
      ((ofd >= 0) && (mode != log_curfile) &&
        Bytes_in_File + (int)pkt_len > Bytes_per_File)) {
    msg(MSG_DBG(1), "%s: log_packet %u mode %d",
      miname, pkt_len, mode);
    next_file();
  }
  nl_assert(ofd >= 0);
  int rv = write(ofd, bfr, pkt_len);
  if (rv < 0)
    msg(MSG_ERROR, "%s: error %d writing to file: strerror(errno)",
      miname, errno, strerror(errno));
  else if (rv < (int)pkt_len)
    msg(MSG_ERROR, "%s: short write to file: %d/%d", miname, rv, pkt_len);
  else
  {
    Bytes_in_File += pkt_len;
    return;
  }
  // Try moving on to another file on error:
  ::close(ofd);
  ofd = -1;
}

void mlf_packet_logger::next_file()
{
  if ((ofd >= 0) && ::close(ofd)) {
    msg(MSG_ERROR, "%s: Error closing file: %s", miname, strerror(errno));
  }
  ofd = mlf_next_fd(mlf);
  if (ofd < 0)
    msg(MSG_FATAL, "%s: Unable to open output file", miname);
  Bytes_in_File = 0;
  // write_tstamp();
}

} // end of DAS_IO
