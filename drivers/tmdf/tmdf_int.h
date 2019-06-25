#ifndef TMDF_INT_H_INCLUDED
#define TMDF_INT_H_INCLUDED

#include "dasio/tm_data_sndr.h"

using namespace DAS_IO;

extern const char *df_path;
extern const char *tmdf_name;

class TMDF_data_sndr : public TM_data_sndr {
  public:
    TMDF_data_sndr( unsigned seconds, const char *name, void *data, unsigned short size );
    ~TMDF_data_sndr();
    bool tm_sync();
  private:
    int fd;
    unsigned secs;
    time_t next;
    void report_size();
  protected:
    bool app_connected();
};

#endif
