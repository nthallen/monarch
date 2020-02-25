#ifndef ALICAT_H_INCLUDED
#define ALICAT_H_INCLUDED
#include <stdint.h>

typedef struct __attribute__((__packed__)) {
  uint32_t status;
  float pressure;
  float flow_temp;
  float volumetric_flow;
  float mass_flow;
  float mass_flow_setpoint;
} alicat_tm_t;

typedef struct __attribute__((__packed__)) {
  alicat_tm_t Dev[2];
} alicat_t;

extern alicat_t Alicat;

#endif
