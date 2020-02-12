#ifndef CPU_USAGE_H_INCLUDED
#define CPU_USAGE_H_INCLUDED

#ifdef __QNXNTO__
  #include <sys/types.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <devctl.h>
  #include <sys/procfs.h>
  #include "nortlib.h"

  class cpu_usage {
    public:
      cpu_usage();
      ~cpu_usage();
      void init(unsigned int n_cpus = 1);
      unsigned char report(double rate);
      unsigned char *PCT;
    private:
      int fd;
      int n_cores;
      _Uint64t *last_sutime;
  };

#else
  #include "dasio/interface.h"

  namespace DAS_IO {

    class cpu_usage : public Interface {
      public:
        cpu_usage();
        uint8_t report();
      private:
        int fd;
    };

  }
#endif

#endif
