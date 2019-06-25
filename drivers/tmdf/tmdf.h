#ifndef TMDF_H_INCLUDED
#define TMDF_H_INCLUDED

#include "dasio/tm_data_sndr.h"

using namespace DAS_IO;

typedef struct __attribute__((__packed__)) {
  uint16_t usage;
} TMDF_t;

#endif
