/** @file dasio_tm.h */
#ifndef DASIO_TM_H_INCLUDED
#define DASIO_TM_H_INCLUDED

#include "client.h"

namespace DAS_IO {

  class TM : public Client {
    public:
      TM(const char *iname, const char *datum, const char *data, uint16_t size);
      TM(const char *iname, const char *hostname, const char *datum,
        const char *data, uint16_t size);
      virtual ~TM();
      bool app_input(); // read nl, write data and set gflag(0)
      bool app_connected();
    private:
      static const int subsvc_len = 40;
      char sub_service[subsvc_len];
      const char *data;
      uint16_t data_len;
  };

}

#endif
