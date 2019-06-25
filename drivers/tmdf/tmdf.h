#ifndef TMDF_H_INCLUDED
#define TMDF_H_INCLUDED

#include "dasio/tm_data_sndr.h"

using namespace DAS_IO;

typedef struct __attribute__((__packed__)) {
  unsigned short usage;
} TMDF_t;

class tmdf;

class TMDF_Selectee : public TM_data_sndr {
  public:
    TMDF_Selectee( unsigned seconds, const char *name, void *data, unsigned short size );
    ~TMDF_Selectee();
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
