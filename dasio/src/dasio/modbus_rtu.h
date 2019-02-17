/** @file modbus_rtu.h */
#ifndef DASIO_MODBUS_RTU_H_INCLUDED
#define DASIO_MODBUS_RTU_H_INCLUDED

#include <deque>
#include "serial.h"

namespace DAS_IO { namespace Modbus {

/**
 * @brief Class for Modbus RTU communication over RS485
 *
 * This class should not need to be subclassed. It should only be necessary to
 * subclass new modbus_devices, but we'll see how that goes.
 */
class RTU : public DAS_IO::Serial {
  public:
    class modbus_device;
    class modbus_req;
    typedef void (*RepHandler)(modbus_req *req, modbus_device *device,
      RTU *MB);
    
    /**
     * Initializes interface and opens the device.
     * @param iname Interface name for messages
     * @param bufsz The input buffer size
     * @param path Path to the device
     */
    RTU(const char *iname, int bufsz, const char *path);
    /**
     * Initializes interface without opening device.
     * @param iname Interface name for messages
     * @param bufsz The input buffer size
     */
    RTU(const char *iname, int bufsz);
    ~RTU();
        
    /**
     * @brief Thin wrapper on Interface::ProcessData() to handle update_tc_vmin()
     */
    bool ProcessData(int flag);
    /**
     * Provide hex output instead of ASCII
     */
    const char *ascii_escape();
    /**
     * Parses the incoming response, checking that the incoming
     * address and function code match the pending request.
     *
     * If an error is indicated, it is reported.
     *
     * The CRC is verified and any error is reported.
     *
     * If no errors are found, calls device->process_pdu()
     * @return true if the event loop should terminate
     */
    bool protocol_input();
    bool protocol_timeout();
    bool tm_sync();

    /**
     * Called from within the modbus_device constructor. add_device() cannot
     * access any methods or attributes of dev during this call.
     * @param dev Pointer to a modbus_device.
     */
    void add_device(modbus_device *dev);
    
    /**
     * @param devID The device ID to search for
     * @return Pointer to the modbus_device object with the matching devID
     * or zero if none was found.
     *
     * Searches the list of devices for the matching devID.
     */
    modbus_device *find_device(uint8_t devID);
    
    /**
     * Adds the specified request to the command queue.
     */
    void enqueue_command(modbus_req *req);
    
    /**
     * Adds the specified request to the polls list and marks the
     * request as persistent.
     */
    void enqueue_poll(modbus_req *req);
    
    /**
     * @param rep pointer to buffer
     * @param nb size of buffer including 2-byte crc
     * @return true if the CRC checks out OK
     */
    bool crc_ok(uint8_t *rep, unsigned nb);
    
    /**
     * @param dest Where the data should be written
     * @param count The number of uint32_t words to copy
     *
     * Copies data from the data portion of the response PDU, which
     * starts with the 5th byte of the overall MODBUS SERIAL LINE PDU.
     * (Technically, the data block starts on the 3rd byte, but
     * in almost all cases, we are interested in data starting at the
     * 5th byte, after the address or subfunction code, which we already
     * know. Using this definition allows for consistent usage between
     * 8, 16, and 32-bit versions of this method.)
     */
    void read_pdu_4321(uint32_t *dest, int count);
    /**
     * @param dest Where the data should be written
     * @param count The number of uint16_t words to copy
     * @param offset The byte offset of the data portion of
     * the PDU. Defaults to 3, which is valid for all function codes
     * except 8.
     *
     * Copies data from the data portion of the response PDU, which
     * starts with the 5th byte of the overall MODBUS SERIAL LINE PDU.
     * (Technically, the data block starts on the 3rd byte, but
     * in almost all cases, we are interested in data starting at the
     * 5th byte, after the address or subfunction code, which we already
     * know. Using this definition allows for consistent usage between
     * 8, 16, and 32-bit versions of this method.)
     */
    void read_pdu(uint16_t *dest, int count, int offset = 3);
    /**
     * @param dest Where the data should be written
     * @param count The number of bytes to copy
     * @param offset The byte offset of the data portion of
     * the PDU. Defaults to 3, which is valid for all function codes
     * except 8.
     *
     * Copies data from the data portion of the response PDU, which
     * starts with the 5th byte of the overall MODBUS SERIAL LINE PDU.
     * (Technically, the data block starts on the 3rd byte, but
     * in almost all cases, we are interested in data starting at the
     * 5th byte, after the address or subfunction code, which we already
     * know. Using this definition allows for consistent usage between
     * 8, 16, 32-bit versions of this method.)
     */
    void read_pdu(uint8_t *dest, int count, int offset = 3);
    
    modbus_req *new_modbus_req();
    std::deque<modbus_req *> polls;
    std::deque<modbus_req *> cmds;
    std::deque<modbus_req *> req_free;
    std::deque<modbus_req *>::const_iterator cur_poll;
    modbus_req *pending;
    
  protected:
    /**
     * If pending is not set, checks for pending commands or polls
     * and issues the next request. Called from protocol_input() after
     * a reply has been received, from protocol_timeout(), from tm_sync()
     * and when new command requests are received.
     * @return true if event loop should terminate, which would be true on
     * a write error to the device.
     */
    bool process_requests();
    
    /**
     * If pending is set, decides whether to place the request on the
     * free list or not, then clears pending.
     */
    void dispose_pending();
    /**
     * List of devices
     */
    std::deque<modbus_device *> devices;
    
  public:
    class modbus_req {
      public:
        typedef enum { Req_unconfigured, Req_addressed, Req_pre_crc,
          Req_ready, Req_invalid } req_state_t;

        modbus_req();
        ~modbus_req();
        
        /**
         * @brief Performs initial setup of a modbus_req object
         * @param device The modbus_device this request pertains to
         * @param function_code The Modbus function code
         * @param address The Modbus address
         * @param count the relevant count describing the transfer.
         * The interpretation of count is function_code dependent.
         * @param dest A pointer to where data from the reply should be recorded
         * @param handler Method used to extract data from the reply.
         *
         * If the handler is omitted, a likely default method will be
         * selected.
         *
         * For function codes 1, 2 and 15 count is the number of single-bit
         * values to read or write. The number of bytes of data returned will
         * be ceil(count/8). The default handler is RH_uint8()
         *
         * For function codes 3 and 4, count is the number of 16-bit
         * words to read. The default handler is RH_uint16()
         *
         * For function codes 5 and 6, count must be 1. The default
         * handler is RH_null();
         *
         * For function code 8, count is the number of uint16_t in
         * the data portion of the request and reply. The address is the
         * subfunction code. For subfunction code 0, the data array
         * must be count words long. For subfunctions 10, 12, 13 and 14,
         * count must be 1, and data[0] must be zero. The default
         * handler is RH_uint16()
         *
         * For function code 16, count is the 16-bit words to write.
         * The default handler is RH_null()
         */
        void setup(modbus_device *device, uint8_t function_code, uint16_t address,
          uint16_t count, void *dest = 0, RepHandler handler = 0);
        /**
         * Fills in all the data for the specified request in byte order.
         * Request must be in state Req_addressed, and data must point to
         * as much data as is required by the request. On success, the
         * request state will be Req_ready.
         * @param data Pointer to data
         */
        void setup_data(uint8_t *data);
        /**
         * Fills in all the data for the specified request in word order,
         * i.e. with the bytes in each word swapped.
         * Request must be in state Req_addressed, and data must point to
         * as much data as is required by the request. On success, the
         * request state will be Req_ready.
         * @param data Pointer to data
         */
        void setup_data(uint16_t *data);
        // void setup_data(uint32_t *data);
        inline req_state_t get_req_state() { return req_state; }
        const char *ascii_escape();
        static const char *byte_escape(uint8_t byte);
        
        /**
         * Called by RTU::protocol_input() as a relay to the appropriate
         * modbus_device.
         */
        void process_pdu();
        
        /**
         * @param buf pointer to buffer
         * @param nb size of buffer not counting 2-byte crc
         * @return the 16-bit CRC code
         */
        uint16_t crc(uint8_t *buf, uint16_t nb);
        static void swap32_4321(uint8_t *dest, uint8_t *src);
        static void swap16(uint8_t *dest, uint8_t *src);
        /**
         * Called from RTU::modbus_device::new_modbus_req().
         * @param MB Pointer to the Modbus::RTU object
         */
        inline void set_MB(RTU *MB) { this->MB = MB; }
        
        static const int MODBUS_RTU_REQ_MAX = 256;
        uint8_t req_buf[MODBUS_RTU_REQ_MAX];
        unsigned rep_sz;
        unsigned req_sz;
        uint8_t function_code;
        uint16_t address;
        uint16_t count;
        uint8_t devID;
        bool persistent; //* true for polls, false for cmds
        uint16_t rep_count;
        // rep_type_t rep_type;
        RepHandler handler;
        void *dest;
      protected:
        /**
         * Sets the CRC bytes in the request. The request must
         * be in the Req_pre_crc state, as set by setup() and/or
         * setup_data().
         */
        void crc_set();
        
        // unsigned reqb_sz;
        modbus_device *device; // should this be protected?
        RTU *MB;
      private:
        req_state_t req_state;
    };
    
    class modbus_device {
      public:
        /**
         * @param dev_name a short descriptor for this device
         * @param devID The device's Modbus RTU address
         */
        modbus_device(const char *dev_name, uint8_t devID);
        virtual ~modbus_device();
        
        /**
         * @brief Null Reply handler
         * @param req The current request.
         * @param dev The modbus_device
         * @param MB The Modbus::RTU interface
         * 
         * This handler is useful for commands that do not
         * require any direct data record--say because the
         * status of the device is already being reported.
         */
        static void RH_null(modbus_req *req, modbus_device *dev,
          RTU *MB);
        /**
         * @brief Reply handler for simple byte-oriented data
         * @param req The current request.
         * @param dev The modbus_device
         * @param MB The Modbus::RTU interface
         * 
         * The request must be set up with an appropriate
         * dest and rep_count. rep_count indicates the number
         * of bytes to transfer to the destination.
         */
        static void RH_uint8(modbus_req *req, modbus_device *dev,
          RTU *MB);
        /**
         * @brief Reply handler for simple 16 bit word-oriented data
         * @param req The current request.
         * @param dev The modbus_device
         * @param MB The Modbus::RTU interface
         * 
         * The request must be set up with an appropriate
         * dest and rep_count. rep_count indicates the number
         * of 16 bit words to transfer to the destination,
         * swapping the bytes to match Modbus ordering.
         */
        static void RH_uint16(modbus_req *req, modbus_device *dev,
          RTU *MB);
        /**
         * @brief Reply handler for 32 bit word-oriented data
         * @param req The current request.
         * @param dev The modbus_device
         * @param MB The Modbus::RTU interface
         * 
         * The request must be set up with an appropriate
         * dest and rep_count. rep_count indicates the number
         * of 16 bit words to transfer to the destination,
         * swapping the bytes to match Modbus ordering.
         */
        static void RH_uint32(modbus_req *req, modbus_device *dev,
          RTU *MB);

        inline uint8_t get_devID() { return devID; }
        inline const char *get_iname() { return MB ? MB->get_iname() : "unknown"; }
        inline const char *get_dev_name() { return dev_name; }
        /**
         * Called during RTU::add_device().
         * @param MB Pointer to the Modbus::RTU object
         */
        inline void set_MB(RTU *MB) { this->MB = MB; }
        /**
         * Called during RTU::add_device().
         */
        virtual void enqueue_polls() = 0;
      protected:
        /**
         * The Modbus RTU device address. Must be unique among
         * devices on this Modbus.
         */
        uint8_t devID;
        RTU *MB;
        const char *dev_name;
    };
};

} } // Closeout Modbus and DAS_IO namespaces

#endif
