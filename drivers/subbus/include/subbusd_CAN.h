#ifndef SUBBUSD_CAN_H_INCLUDED
#define SUBBUSD_CAN_H_INCLUDED
#include "dasio/server.h"
#include "subbusd_int.h"
#include "subbusd_CAN_interface.h"

extern void subbusd_CAN_init_options(int argc, char **argv);
class subbusd_CAN;

class subbusd_CAN_client : public subbusd_client {
  public:
    subbusd_CAN_client(DAS_IO::Authenticator *auth, subbusd_CAN *fl);
    ~subbusd_CAN_client();
    bool incoming_sbreq();
    void request_complete(int16_t status, uint16_t n_bytes);
  private:
    /**
     * Sets up the framework for processing an mread request, then calls process_mread().
     */
    void setup_mread();
    /**
     * Process a step in the mread
     */
    void process_mread();
    void format_mread_rd();
    subbusd_CAN *flavor;
    uint16_t mread_word_space_remaining;
    uint16_t mread_words_requested;
    can_msg_t can_msg;
};

class can_request {
  public:
    inline can_request(can_msg_t *can_msg, uint8_t *buf, int bufsz,
      subbusd_CAN_client *clt) : msg(can_msg), clt(clt) {
        can_msg->buf = buf;
        can_msg->bufsz = bufsz;
      }
    can_msg_t *msg;
    subbusd_CAN_client *clt;
};

class CAN_interface;

/**
 * @brief subbusd CAN flavor
 *
 * This implementation of a CAN interface imposes certain subbus
 * restrictions on our CAN bus and takes advantage of various
 * assumptions, including:
 *   -Only devices supporting this protocol will be attached
 *   -Only one controlling device will be attached
 *   -Operation will be half duplex with every request followed
 *    by a reply (or a timeout)
 * Given these constraints, we will split the 11-bit CAN ID in
 * the standard CAN packet into three values:
 *   -A Board ID value (4 bits)
 *   -A Reply bit, which is set to indicate a reply (1 bit)
 *   -A Request ID value (6 bits)
 * The width of the Board ID and the Request ID fields are
 * arbitrary. They could be changed by:
 *   -Changing the CAN_ID_NBITS_BDID definition below
 *   -Changing the corresponding firmware definitions for all attached devices
 */
class subbusd_CAN : public subbusd_flavor {
  public:
    subbusd_CAN();
    ~subbusd_CAN();
    void init_subbus();
    void shutdown_subbus();
    inline void enqueue_request(can_msg_t *can_msg, uint8_t *rep_buf,
        int buflen, subbusd_CAN_client *clt) {
          CAN->enqueue_request(can_msg, rep_buf, buflen, clt);
      }
  private:
    // CAN sockets, states, etc.
    CAN_interface *CAN;
};

/** Number of bits in the Board ID */
#define CAN_ID_NBITS_BDID 4

/** Number of bits in the Request ID */
#define CAN_ID_NBITS_REQID (11-CAN_ID_NBITS_BDID-1)

/** The total number of Board IDs supported */
#define CAN_ID_N_BDIDS (1<<CAN_ID_NBITS_BDID)

/** Mask for the Board ID bits inside the full CAN ID value */
#define CAN_ID_BOARD_MASK ((CAN_ID_N_BDIDS-1)<<(CAN_ID_NBITS_REQID+1))

/** Mask for the reply bit inside the full CAN ID value */
#define CAN_ID_REPLY_BIT (1<<CAN_ID_NBITS_REQID)

/** Mask for the Request ID inside the full CAN ID value */
#define CAN_ID_REQID_MASK (CAN_ID_REPLY_BIT-1)

/**
 * @param x Board ID
 * @return the properly shifted Board ID component of the full CAN ID value
 */
#define CAN_ID_BOARD(x) (((x)<<(11-CAN_ID_NBITS_BDID))&CAN_ID_BOARD_MASK)

/** Mask for all but the reply bit in the full CAN ID value */
#define CAN_ID_BDREQ_MASK (CAN_ID_BOARD_MASK|CAN_ID_REQID_MASK)

/**
 * @param x full CAN ID value
 * @return the Request ID
 */
#define CAN_ID_REQID(x) ((x)&CAN_ID_REQID_MASK)

/**
 * @param bd the Board ID
 * @param req the Request ID
 * @return the full CAN ID for the reply
 */
#define CAN_REPLY_ID(bd,req) \
    (CAN_ID_BOARD(bd)|(req&CAN_ID_REQID)|CAN_ID_REPLY_BIT)

/**
 * @param bd the Board ID
 * @param req the Request ID
 * @return the full CAN ID for request
 */
#define CAN_REQUEST_ID(bd,req) (CAN_ID_BOARD(bd)|(CAN_ID_REQID(req)))

/**
 * @param id An incoming CAN ID
 * @param bd Board ID
 * @return true if the id is a request for the specified Board ID
 */
#define CAN_REQUEST_MATCH(id,bd) \
    ((id & (CAN_ID_BOARD_MASK|CAN_ID_REPLY_BIT)) == CAN_ID_BOARD(bd))

#define CAN_CMD_CODE_MASK 0x7
#define CAN_CMD_CODE(x) ((x) & CAN_CMD_CODE_MASK)
#define CAN_CMD_CODE_RD 0x0
#define CAN_CMD_CODE_RD_INC 0x1
#define CAN_CMD_CODE_RD_NOINC 0x2
#define CAN_CMD_CODE_RD_CNT_NOINC 0x3
#define CAN_CMD_CODE_WR_INC 0x4
#define CAN_CMD_CODE_WR_NOINC 0x5
#define CAN_CMD_CODE_ERROR 0x6
#define CAN_CMD_SEQ_MASK 0xF8 // Can report up to 111 words without wrapping
#define CAN_CMD_SEQ_MAX 0x1F
#define CAN_SEQ_CMD(s) (((s)<<3)&CAN_CMD_SEQ_MASK)
#define CAN_CMD_SEQ(c) (((c)&CAN_CMD_SEQ_MASK)>>3)
#define CAN_CMD(cmd,seq) (CAN_CMD_CODE(cmd)|CAN_SEQ_CMD(seq))

#define CAN_MAX_TXFR 223

#define CAN_ERR_BAD_REQ_RESP 1
#define CAN_ERR_NACK 2
#define CAN_ERR_OTHER 3
#define CAN_ERR_INVALID_CMD 4
#define CAN_ERR_BAD_ADDRESS 5
#define CAN_ERR_OVERFLOW 6
#define CAN_ERR_INVALID_SEQ 7

#endif
