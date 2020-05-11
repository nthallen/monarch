#ifndef ALICAT_INT_H_INCLUDED
#define ALICAT_INT_H_INCLUDED
#include <stdint.h>
#include "dasio/modbus_rtu.h"
#include "dasio/client.h"
#include "alicat.h"

namespace DAS_IO { namespace Modbus {

  class alicat_device : public Modbus::RTU::modbus_device {
    public:
      inline alicat_device(const char *dev_name, uint8_t devID, alicat_tm_t *TM) :
        RTU::modbus_device(dev_name, devID), TM(TM) {}
      void enqueue_polls();
      void tm_sync();
      static void myswap(uint8_t *dest, uint8_t *src);
      static void RH_alicat_regs(RTU::modbus_req *req,
          RTU::modbus_device *dev, RTU *MB);
      alicat_tm_t *TM;
      uint8_t xbuf[4*6];
    protected:
  };

} }

extern const char *Alicat_port;
extern const char *address_opts;
#define ALICAT_MIN_ADDRESS 1
#define ALICAT_MAX_ADDRESS 254
#define MNEM_LEN 10

typedef struct {
  uint16_t device_index;
  uint16_t device_address;
  char     mnemonic[MNEM_LEN];
} board_id_t;

extern board_id_t *board_id;

#endif
