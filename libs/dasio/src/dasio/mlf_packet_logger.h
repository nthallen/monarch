#ifndef MLF_PACKET_LOGGER_H_INCLUDED
#define MLF_PACKET_LOGGER_H_INCLUDED

#include "mlf.h"

namespace DAS_IO {

typedef enum { log_default, log_newfile, log_curfile } log_mode;

class mlf_packet_logger {
  public:
    mlf_packet_logger(const char *iname,
      const char *mlf_base, const char *mlf_config);
    ~mlf_packet_logger();
    void log_packet(const uint8_t *bfr, uint32_t pkt_len,
          log_mode mode=log_default);
    void next_file();
    /**
     * @param n_bytes
     * Specifies the maximum number of bytes that should be written
     * to each file in the log_default mode. The intention is that
     * the packets being logged should not be split between files,
     * so if a packet is logged that exceeds this limit, it will be
     * written to its own file. Use of the log_newfile and log_curfile
     * modes allows the caller to make these choices explicit.
     */
    inline void set_bytes_per_file(int n_bytes) { Bytes_per_File = n_bytes; }
  protected:
    const char *miname;
    mlf_def_t *mlf;
    int ofd;
    int Bytes_in_File;
    int Bytes_per_File;
    const static int default_Bytes_per_File = 4096;
};

}

#endif
