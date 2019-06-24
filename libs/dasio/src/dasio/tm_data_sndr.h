/** @file dasio/tm_data_sndr.h */
#ifndef DASIO_TM_DATA_SNDR_H_INCLUDED
#define DASIO_TM_DATA_SNDR_H_INCLUDED

#include "client.h"

namespace DAS_IO {

  class TM_data_sndr : public Client {
    public:
      /**
       * Connects to the DG service, subservice data/<datum>
       * @param iname The interface name
       * @param datum The name of the TM data structure
       * @param data Pointer to the data structure
       * @param size The size of the data structure
       */
      TM_data_sndr(const char *iname, const char *datum, void *data, uint16_t size);
      /**
       * Connects to the DG service on the specified host, subservice
       * data/<datum>
       * @param hostname The host location of the server
       * @param iname The interface name
       * @param datum The name of the TM data structure
       * @param data Pointer to the data structure
       * @param size The size of the data structure
       */
      TM_data_sndr(const char *iname, const char *hostname, const char *datum,
        void *data, uint16_t size);
      bool app_input(); // read nl, write data and set gflag(0)
      virtual bool app_connected();
    protected:
      virtual ~TM_data_sndr();
    private:
      static const int subsvc_len = 40;
      char sub_service[subsvc_len];
      void *data;
      uint16_t data_len;
  };

}

#endif
