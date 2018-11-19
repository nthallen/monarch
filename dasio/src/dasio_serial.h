/** @file dasio_serial.h Serial interface layer */
#ifndef DASIO_SERIAL_H_INCLUDED
#define DASIO_SERIAL_H_INCLUDED

#include "dasio.h"

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
    virtual ~Serial();
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
     * @param min The minimum number of characters to respond to
     * @param time The time gap value
     */
    void setup( int baud, int bits, char par, int stopbits,
      int min, int time );
    /** Buffer to hold serial parameters */
    termios termios_p;
  protected:
    /**
     * Invokes fillbuf() until there is no input remaining.
     */
    void flush_input();
    /**
     * Updates the VMIN parameter in tc_setattr. This can help to minimize the
     * number of context switches required before meaningful action can occur.
     * @param vmin New VMIN parameter for tcsetattr indicating the minimum
     * number of input characters desired before select() will flag the device
     * ready for reading..
     */
    void update_tc_vmin(int vmin);
    /** Flag to indicate whether or not termios_p has been setup */
    bool termios_init;
};

}
#endif
