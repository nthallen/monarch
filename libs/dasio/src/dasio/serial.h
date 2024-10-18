/** @file dasio/serial.h Serial interface layer */
#ifndef DASIO_SERIAL_H_INCLUDED
#define DASIO_SERIAL_H_INCLUDED

#include <termios.h>
#include "interface.h"

namespace DAS_IO {
  
class Serial : public Interface {
  public:
    /**
     * Initializes interface and opens the device.
     * @param iname Interface name for messages
     * @param bufsz The input buffer size
     * @param path Path to the device
     * @param open_flags Flags passed to open()
     */
    Serial(const char *iname, int bufsz, const char *path, int open_flags);
    /**
     * Initializes interface without opening device.
     * @param iname Interface name for messages
     * @param bufsz The input buffer size
     */
    Serial(const char *iname, int bufsz);
    /**
     * init() can be used to initialize the device if the path is
     * not known at construction.
     * @param path The path to the device
     * @param open_flags flags to be passed to open()
     */
    void init(const char *path, int open_flags);
    /**
     * Initializes the serial parameters for the device. The min
     * and time parameters can be used to optimize reads. See
     * tcsetattr VMIN and VTIME parameters for more information.
     * @param baud The desired baud rate
     * @param bits number of data bits (5-8)
     * @param par 'n', 'e', 'o', 'm', 's' for none, even, odd, mark or space.
     * @param stopbits The number of stop bits: 1 or 2
     * @param min The minimum number of characters to respond to. Set to -1
     *   to retain basic canonical mode functionality without echo.
     * @param time In non-canonical mode, this is the VTIME time gap value
     *   in deciseconds specified in TERMIOS(3). If min is -1
     *   (canonical mode), this value is assigned to termios' VEOL, defining
     *   a terminator character in addition to \n. A value of zero defines
     *   no additional terminator characters.
     */
    void setup( int baud, int bits, char par, int stopbits,
      int min, int time );
    /**
     * @param enable true to enable RTS/CTS flow control
     */
    void hwflow_enable(bool enable);
    /**
     * Invokes fillbuf() until there is no input remaining.
     */
    void flush_input();
    /**
     * Checks baud rate for validity and returns code for termios.
     */
    static speed_t get_baud_code(int baud);
    /** Buffer to hold serial parameters */
    termios termios_p;
    class Modbus;
  protected:
    virtual ~Serial();
    /**
     * Updates the VMIN parameter in tc_setattr. This can help to minimize the
     * number of context switches required before meaningful action can occur.
     * @param vmin New VMIN parameter for tcsetattr indicating the minimum
     * number of input characters desired before select() will flag the device
     * ready for reading..
     */
    void update_tc_vmin(int vmin, int vtime = -1);
    /** Flag to indicate whether or not termios_p has been setup */
    bool termios_init;
};

}
#endif
