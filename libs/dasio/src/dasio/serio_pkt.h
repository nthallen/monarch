#ifndef SERIO_PKT_H_INCLUDED
#define SERIO_PKT_H_INCLUDED

enum serio_pkt_type : uint8_t {
  pkt_type_NULL = 0,
  pkt_type_TM = 'T',
  pkt_type_CTRL = 'c', // will have a small payload
  pkt_type_PNG_Start = 'P',
  pkt_type_PNG_Cont = 'N',
  pkt_type_CMD = 'C',
  pkt_type_XIO = 'X',
  pkt_type_SID = 'S',
  pkt_type_NPH = 'W'
};

typedef struct __attribute__((packed)) {
  uint8_t LRC;
  serio_pkt_type type;
  uint16_t length; //*< Payload length
  uint16_t CRC;
} serio_pkt_hdr;

class serio {
  public:
    /** Max length of the packet data, excluding the header */
    static const int max_pkt_payload = 400;
    /** Min length of packet data, excluding header. Not currently enforced */
    static const int min_pkt_payload = 10;
    /** Size of the the serio_pkt_hdr */
    static const int pkt_hdr_size = sizeof(serio_pkt_hdr);
    /** Max length of a command string, excluding the serio_pkt header */
    static const int max_packet_size = pkt_hdr_size+max_pkt_payload;
    /** Min packet size, not currently enforced */
    static const int min_pkt_size = pkt_hdr_size+min_pkt_payload;
    /** Min buffer size */
    static const int min_buffer_size = max_packet_size + 1;
};

#endif
