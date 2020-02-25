#ifndef ALICAT_INT_H_INCLUDED
#define ALICAT_INT_H_INCLUDED
#include <stdint.h>
#include "dasio/modbus_rtu.h"

namespace DAS_IO { namespace Modbus {

    class alicat_device : public Modbus::RTU::modbus_device {
      public:
        inline alicat_device(const char *dev_name, uint8_t devID, alicat_tm_t *TM) :
          RTU::modbus_device(dev_name, devID), TM(TM) {}
        void enqueue_polls();
        static void RH_alicat_regs(RTU::modbus_req *req, RTU::modbus_device *dev,
            RTU *MB);
      protected:
        alicat_tm_t *TM;
        uint8_t xbuf[4*6];
    };

    class alicat_cmd : public Cmd_reader {
      public:
        alicat_cmd();
        bool app_input();
      protected:
    };

} }

extern const char *Alicat_port;

#endif
