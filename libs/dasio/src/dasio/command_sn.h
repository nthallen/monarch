#ifndef COMMAND_SN_H_INCLUDED
#define COMMAND_SN_H_INCLUDED
#include <cstdint>

typedef struct {
  uint16_t latest_SN_rx;
  uint8_t recent_duplicates;
} Command_SN_t;

extern Command_SN_t Command_SN;

#endif
