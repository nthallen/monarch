/** @file dasio/tm_data_sndr.h */
#ifndef DASIO_TM_DATA_SNDR_H_INCLUDED
#define DASIO_TM_DATA_SNDR_H_INCLUDED

#include "client.h"

namespace DAS_IO {

  class TM_data_sndr : public Client {
    public:
      /**
       * Connects to the DG service on the specified host, subservice
       * data/<datum>
       * @param iname The interface name
       * @param hostname The host location of the server or 0 for localhost
       * @param datum The name of the TM data structure
       * @param data Pointer to the data structure
       * @param size The size of the data structure
       */
      TM_data_sndr(const char *iname, const char *hostname,
        const char *datum, const void *data, uint16_t size);
      /**
       * Calls Send() when sync data is received.
       * @return false
       */
      bool app_input();
      /**
       * Calls Send() to kick off synchronization.
       * @return the value from Send().
       */
      bool app_connected();
      /**
       * Writes data to DG and sets gflag(0) if successful.
       * @return true if iwrite() returns true.
       */
      bool Send();
      /**
       * @param n The gflag index that will be set by Send().
       */
      inline void set_gflag_no(int n) { gflag_no = n; }
    private:
      static const int subsvc_len = 40;
      char sub_service[subsvc_len];
      const void *data;
      uint16_t data_len;
      int gflag_no;
      bool overrun_obuf;
  };

}

#endif
