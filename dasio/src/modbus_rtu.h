/** @file modbus_rtu.h */
#ifndef MODBUS_RTU_H_INCLUDED
#define MODBUS_RTU_H_INCLUDED
#include "dasio_serial.h"

namespace DAS_IO {

class Serial::Modbus : public Serial {
  public:
    /**
     * Initializes interface and opens the device.
     * @param iname Interface name for messages
     * @param bufsz The input buffer size
     * @param path Path to the device
     * @param open_flags Flags passed to ::open()
     */
    Modbus(const char *iname, int bufsz, const char *path, int open_flags);
    /**
     * Initializes interface without opening device.
     * @param iname Interface name for messages
     * @param bufsz The input buffer size
     */
    Modbus(const char *iname, int bufsz);
    ~Modbus();
    bool protocol_input();
    bool protocol_timeout();
    bool tm_sync();

    class modbus_req {
      public:
        typedef enum { Req_unconfigured, Req_addressed, Req_pre_crc, Req_ready }
          req_state_t;

        modbus_req();
        ~modbus_req();
        void setup(uint8_t device, uint8_t function_code, uint16_t address,
          uint16_t count);
        /**
         * Fills in all the data for the specified request in byte order.
         * Request must be in state Req_addressed, and data must point to
         * as much data as is required by the request.
         * @param data Pointer to data
         */
        void setup_data(uint8_t *data);
        /**
         * Fills in all the data for the specified request in word order,
         * i.e. with the bytes in each word swapped.
         * Request must be in state Req_addressed, and data must point to
         * as much data as is required by the request.
         * @param data Pointer to data
         */
        void setup_data(uint16_t *data);
        // void setup_data(uint32_t *data);
        inline req_state_t get_req_state() { return req_state; }
        const char *ascii_escape();
        // uint8_t MB_err_code;
        uint8_t req_buf[MODBUS_RTU_REQ_MAX];
        unsigned rep_sz;
        unsigned req_sz;
        uint16_t count;
        uint8_t devID;
        static const int MODBUS_RTU_REQ_MAX = 256;
      protected:
        // virtual void process_pdu(uint8_t *rep) = 0;
        
        /**
         * Sets the CRC bytes in the request. The request must
         * be in the Req_pre_crc state, as set by setup() and/or
         * setup_data().
         */
        void crc_set();
        
        /**
         * @param rep pointer to buffer
         * @param nb size of buffer including 2-byte crc
         * @return true if the CRC checks out OK
         */
        bool crc_ok(uint8_t *rep, unsigned nb);
        
        /**
         * @param buf pointer to buffer
         * @param nb size of buffer not counting 2-byte crc
         * @return the 16-bit CRC code
         */
        uint16_t crc(uint8_t *buf, unsigned nb);
        
        void float_swap(uint8_t *dest, uint8_t *src);
        void word_swap(uint8_t *dest, uint8_t *src);
        // unsigned reqb_sz;
      private:
        req_state_t req_state;
    };
    
    modbus_req *new_modbus_req();
    std::deque<modbus_req *> polls;
    std::deque<modbus_req *> cmds;
    std::deque<modbus_cmd_float *> req_free;
    std::deque<modbus_req *>::const_iterator cur_poll;
    modbus_req *pending;
    
    class modbus_device {
      public:
        /**
         * @param MB Pointer to the DAS_IO::Serial::Modbus object
         * @param address The device's Modbus RTU address
         */
        modbus_device(Modbus *MB, unit8_t address);
        virtual ~modbus_device();
        /**
         * The Modbus RTU device address
         */
        uint8_t device_addr;
        /**
         * Called during Modbus::add_device().
         */
        virtual void enqueue_polls();
      protected:
        Modbus *MB;
    };

    /**
     * Iterates through devices calling enqueue_polls()
     */
    void enqueue_polls();
    /**
     * Called from within the modbus_device constructor. add_device() cannot
     * access any methods or attributes of dev during this call.
     * @param dev Pointer to a modbus_device.
     */
    void add_device(modbus_device *dev);
    
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
};

}

#endif
