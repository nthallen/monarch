#include "alicat_int.h"
#include "nl_assert.h"

namespace DAS_IO { namespace Modbus {
  
  void alicat_device::enqueue_polls() {
    nl_assert(MB);
    RTU::modbus_req *req;
    
    req = MB->new_modbus_req();
    req->setup(this, 4, 1201, 2*6, xbuf, RH_alicat_regs);
    MB->enqueue_poll(req);
  }

  #define myswap_be(x,y) \
    RTU::modbus_req::swap32_4321((uint8_t*)&ali->TM->x, y)

  void alicat_device::RH_alicat_regs(RTU::modbus_req *req,
        RTU::modbus_device *dev, RTU *MB) {
    alicat_device *ali = (alicat_device *)dev;
    myswap_be(status, &ali->xbuf[0]);
    myswap_be(pressure, &ali->xbuf[4]);
    myswap_be(flow_temp, &ali->xbuf[8]);
    myswap_be(volumetric_flow, &ali->xbuf[12]);
    myswap_be(mass_flow, &ali->xbuf[16]);
    myswap_be(mass_flow_setpoint, &ali->xbuf[20]);
    // could set a fresh bit somewhere...
  }

} }
