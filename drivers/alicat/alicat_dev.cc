#include "alicat_int.h"

namespace DAS_IO { namespace Modbus {
  
  void alicat_device::enqueue_polls() {
    nl_assert(MB);
    RTU::modbus_req *req;
    
    req = MB->new_modbus_req();
    req->setup(this, 4, 1201, 2*6, xbuf, RH_alicat_regs);
    MB->enqueue_poll(req);
  }

  void RH_alicat_regs(RTU::modbus_req *req, RTU::modbus_device *dev,
            RTU *MB) {
    swap32_4321(&TM->status, &xbuf[0]);
    swap32_4321(&TM->pressure, &xbuf[4]);
    swap32_4321(&TM->flow_temp, &xbuf[8]);
    swap32_4321(&TM->volumetric_flow, &xbuf[12]);
    swap32_4321(&TM->mass_flow, &xbuf[16]);
    swap32_4321(&TM->mass_flow_setpoint, &xbuf[20]);
    // could set a fresh bit somewhere...
  }

} }
