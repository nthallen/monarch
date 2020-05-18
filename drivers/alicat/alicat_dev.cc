#include "alicat_int.h"
#include "nl_assert.h"

namespace DAS_IO { namespace Modbus {
  
  void alicat_device::enqueue_polls() {
    nl_assert(MB);
    RTU::modbus_req *req;
    
    req = MB->new_modbus_req();
    req->setup(this, 3, 1200, 2*6, xbuf, RH_alicat_regs);
    // req->setup(this, 3, 2041, 2*5, xbuf, RH_alicat_regs);
    MB->enqueue_poll(req);
  }
  
  void alicat_device::tm_sync() {
    TM->stale = TM->stale < 255 ? ++TM->stale : 255;
  }

  #define myswap_be(x,y) \
    myswap((uint8_t*)&ali->TM->x, y)
  void alicat_device::myswap(uint8_t *dest, uint8_t *src) {
    dest[3] = src[0];
    dest[2] = src[1];
    dest[1] = src[2];
    dest[0] = src[3];
  }

  void alicat_device::RH_alicat_regs(RTU::modbus_req *req,
        RTU::modbus_device *dev, RTU *MB) {
    alicat_device *ali = (alicat_device *)dev;
    uint32_t rawbuf[6];
#if 1
    MB->read_pdu_4321(rawbuf, 6);
    ali->TM->status = rawbuf[0];
    ali->TM->pressure = *(float*)&rawbuf[1];
    ali->TM->flow_temp = *(float*)&rawbuf[2];
    ali->TM->volumetric_flow = *(float*)&rawbuf[3];
    ali->TM->mass_flow = ali->TM->volumetric_flow
      * (ali->TM->pressure / 1013.25)
      * ( 273.15 / (273.15+ali->TM->flow_temp) );
    ali->TM->flow_setpoint = *(float*)&rawbuf[5];
#else
    myswap_be(status, &ali->xbuf[0]);
    myswap_be(pressure, &ali->xbuf[0]);
    myswap_be(flow_temp, &ali->xbuf[4]);
    myswap_be(volumetric_flow, &ali->xbuf[8]);
    myswap_be(mass_flow, &ali->xbuf[12]);
    myswap_be(flow_setpoint, &ali->xbuf[16]);
#endif
    ali->TM->stale = 0;
    // could set a fresh bit somewhere...
  }

} }
