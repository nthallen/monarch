#ifndef AGILENT_H_INCLUDED
#define AGILENT_H_INCLUDED
#include <stdint.h>

typedef struct {
  double data[20];
  uint8_t count;
  uint8_t stale;
} agilent_t;

extern agilent_t Agilent;

#endif
