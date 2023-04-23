/* sspdrv.h
   structure definition for telemetry
  */
#ifndef SSPDRV_H_INCLUDED
#define SSPDRV_H_INCLUDED
#include <cstdint>

typedef struct {
  uint32_t index;
  uint32_t ScanNum;
  uint32_t Total_Skip;
  uint16_t Flags;
  int16_t T_FPGA;
  int16_t T_HtSink;
  uint8_t Status;
  // uint16_t NChannels;
  // uint16_t NSamples;
  // uint16_t NCoadd;
  // uint16_t NAvg;
  // uint16_t NSkL;
  // uint16_t NSkP;
} __attribute__((packed)) ssp_data_t;

#define SSP_OVF_MASK 0x01FF
#define SSP_CAOVF(x) ((x)&7)
#define SSP_PAOVF(x) (((x)>>3)&7)
#define SSP_ADOOR(x) (((x)>>6)&7)

#define SSP_STATUS_GONE 0
#define SSP_STATUS_CONNECT 1
#define SSP_STATUS_READY 2
#define SSP_STATUS_ARMED 3
#define SSP_STATUS_TRIG 4

typedef struct {
  uint32_t index;
  float amplitude[3];
  float noise[3];
  float noise_percent[3];
} __attribute__((packed)) ssp_amp_data_t;

/*
It could be that Flags (or something derived from flags) and Total_Skip will be sufficient for telemetry.
*/

#endif
