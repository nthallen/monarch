#ifndef LGR_H_INCLUDED
#define LGR_H_INCLUDED

#include <stdio.h>
#include "mlf.h"
#include "dasio/tm_client.h"

#ifdef __cplusplus
using namespace DAS_IO;
  class tmc_lgr : public DAS_IO::tm_client {
    public:
      tmc_lgr();
      static char *mlf_config;
      static unsigned int file_limit;
    protected:
      ~tmc_lgr();
      void process_data_t1();
      void process_data_t2();
      unsigned int process_data_t3();
      unsigned int process_data();
      void process_init();
      void process_tstamp();
      mlf_def_t *mlf;
      FILE *ofp;
      int nb_out;
      void next_file();
      void write_tstamp();
      void lgr_write(void *buf, int nb, const char *where);
  };

extern "C" {
#endif

  extern void lgr_init( int argc, char **argv );

#ifdef __cplusplus
};
#endif

#endif
