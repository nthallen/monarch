#ifndef SUBBUSD_CAN_ID_H_INCLUDED
#define SUBBUSD_CAN_ID_H_INCLUDED

/**
 * @brief subbusd CAN ID
 *
 * The Monarch implementation of a CAN interface imposes certain
 * subbus restrictions on our CAN bus and takes advantage of
 * various assumptions, including:
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

#endif
