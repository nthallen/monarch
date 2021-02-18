#ifndef SERIO_PKT_H_INCLUDED
#define SERIO_PKT_H_INCLUDED

enum serio_pkt_type : uint8_t {
  pkt_type_TM = 'T',
  pkt_type_PNG_Start = 'P',
  pkt_type_PNG_Cont = 'N',
  pkt_type_CMD = 'C'
};

typedef struct __attribute__((packed)) {
  uint8_t LRC;
  serio_pkt_type type;
  uint16_t length;
  uint16_t CRC;
} serio_pkt_hdr;

class serio {
  public:
    static const int max_pkt_payload = 400;
    static const int max_cmd_packet_size = max_pkt_payload;
    static const int min_cmd_packet_size = 50;
};

#endif
