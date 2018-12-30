/** @file dasio/tm_server.h */
#ifndef DASIO_TM_SERVER_H_INCLUDED
#define DASIO_TM_SERVER_H_INCLUDED

#include "server.h"

namespace DAS_IO {
  
  class TM_data_rcvr;
  
  /**
   * @brief Per-datum class for DG to receive data from drivers
   */
  class TM_data_rcvr_def {
    friend class TM_data_rcvr;
    public:
      inline TM_data_rcvr_def(const char *datum, void *data, int size)
        : datum(datum), data(data), size(size),
          interface(0), stale_count(0) {}
      void synch();
      uint16_t Stale(uint16_t limit = 0xFFFF);
      void close();
      const char *datum;
      void *data;
      int size;
    protected:
      TM_data_rcvr *interface;
      uint16_t stale_count;
  };
  
  /**
   * @brief Class for server side of TM_data_sndr socket connection
   */
  class TM_data_rcvr : public Socket {
    public:
      TM_data_rcvr(Authenticator *auth, const char *iname, TM_data_rcvr_def *def);
      ~TM_data_rcvr();
      static TM_data_rcvr *new_tm_data_rcvr(Authenticator *auth, SubService *ss);
      bool protocol_input();
      void close();
      void synch();
    protected:
      TM_data_rcvr_def *def;
  };
  
  class TM_cmd : public Socket {
    public:
      TM_cmd(Authenticator *auth, const char *iname);
      ~TM_cmd();
      bool protocol_input();
      static TM_cmd *new_tm_cmd(Authenticator *auth, SubService *ss);
    protected:
  };
}

#endif
