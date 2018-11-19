/**
 * \file dasio.h
 * Header for the Harvard Link Engineering Data Acquisition System I/O library
 */
#ifndef DAS_IO_H_INCLUDED
#define DAS_IO_H_INCLUDED
#include <string>
#include <vector>
#include <atomic>
#include "Timeout.h"

namespace DAS_IO {
  
class Loop;

/**
 */
class Interface {
  public:
    Interface(const char *name, int bufsz);
    virtual ~Interface();
    /**
     * @param flag bit-mapped value indicating which event(s) triggered this call.
     * @return true if we should quit
     */
    virtual bool ProcessData(int flag);
    /**
     * @return a pointer to a Timeout object or zero if no timeout is required.
     * The default implementation returns zero.
     */
    virtual Timeout *GetTimeout();
    /** The file descriptor for this interface */
    int fd;
    /** Bit-mapped register to indicate which events this interface is sensitive to. */
    int flags;
    static const int Fl_Read = 1;
    static const int Fl_Write = 2;
    static const int Fl_Except = 4;
    static const int Fl_Timeout = 8;
    /**
     * Set the threshold to a negative value to report all errors.
     * The default threshold value is 5.
     * @param thr New qualified protocol error threshold value
     */
    void set_qerr_threshold(int thr);
    Loop *Loop;
    /**
     * Method to map a global flag number to a bit mask to be
     * set in a Interface's flags word.
     * @param gflag_index global flag bit number
     * @return bit mask selecting the specified global flag.
     */
    static inline int gflag(unsigned gflag_index) {
      return( 1 << (gflag_index+4) );
    }
  protected:
    /**
     * Sets up a write of nc bytes from the buffer pointed to by str.
     * If the write cannot be accomplished immediately, the information
     * is saved and handled transparently. The caller is
     * responsible for allocating the output buffer(s) and ensuring
     * they are not overrun.
     * @param str Pointer to the output buffer
     * @param nc The total number of bytes in the output buffer
     * @param cp The starting offset within the output buffer
     * @return true if a fatal error occurs
     */
    bool iwrite(const char *str, unsigned int nc, unsigned int cp = 0);
    /**
     * Sets up a write of the string s by invoking iwrite(str, nc, 0).
     * There are risks associated with this invocation if the resulting
     * string is not transmitted immediately. The string argument must
     * remain unmodified until entirely transmitted.
     * @param s The string to output
     * @return true if write ran to completion
     */
    bool iwrite(const std::string &s);
    /**
     * Sets up a write of the string s by invoking iwrite(str, strlen(str), 0).
     * The string must remain unmodified until the data has been entirely
     * transmitted.
     * @param str The string to output
     * @return true if a fatal error occurs
     */
    bool iwrite(const char *str);
    /**
     * Called when iwrite() returns false and enqueued data is subsequently
     * written to the interface.
     * @param nb The number of bytes written
     */
    virtual void iwritten(int nb);
    /**
     * @return true if the error is fatal, false if it has been handled
     */
    virtual bool iwrite_error(int my_errno);
    /**
     * Internal function to output data
     * @return true if a fatal error occurs
     */
    bool iwrite_check();
    /**
     * @return true if there is no pending data in obuf
     */
    inline bool obuf_empty() { return ocp >= onc; }
    /**
     * @return true if the error is fatal, false if it has been handled
     */
    virtual bool read_error(int my_errno);
    
    /**
     * Called by ProcessData() when new data is available to the protocol level.
     * @return true on an error requiring termination of the driver
     */
    virtual bool protocol_input();
    /**
     * Called by ProcessData() when timeout is reported by select() and
     * this interface has a timeout set, and this interface's timeout
     * has expired. If the interface is also waiting for input, protocol_input()
     * will be called before protocol_timeout(). If the protocol_input()
     * clears the timeout, then protocol_timeout() will not be called.
     * @return true on a condition requiring termination of the driver
     */
    virtual bool protocol_timeout();
    /**
     * Called by ProcessData() when an exception occurs.
     * I have yet to encounter and exceptional condition, so I don't know what to expect.
     * That may not be true: maybe if a socket gets closed or something?
     * @return true on a condition requiring termination of the driver
     */
    virtual bool protocol_except();
    /**
     * Called by ProcessData() when gflag(0) is received.
     * @return true on a condition requiring termination of the driver
     */
    virtual bool tm_sync();

    /**
     * Updates the input buffer size, reallocating memory as necessary.
     * Failure to allocate the buffer is a fatal error.
     * @param bufsz The size of the input buffer.
     */
    void set_ibufsize(int bufsz);
    
    /**
     * Calls fillbuf(bufsize); If an error is encountered,
     * will return the response from read_error(errno)
     * @return true on an error requiring termination of the driver 
     */
    inline bool fillbuf() { return fillbuf(bufsize); }
    /**
     * Reads up to N-nc characters into buf. If an error is encountered,
     * will return the response from read_error(errno)
     * @return true on an error requiring termination of the driver 
     */
    bool fillbuf(int N);
    /**
     * Remove nchars from the front of buf, and shift the remain
     * characters, if any, to the beginning of the buffer, adjusting
     * cp and nc accordingly
     * Each call to consume() increments the n_empties counter which is
     * reported at termination. If n_fills is much greater than n_empties,
     * you may need to adjust your min and time settings for more efficient
     * operation.
     * @param nchars number of characters to remove from front of buffer
     */
    void consume(int nchars);
    /**
     * Reports a protocol error message, provided the qualified error count
     * is not above the limit. report_ok() will decrement the qualified
     * error count. It is assumed that all messages are of severity
     * MSG_ERR. Messages at other levels, either more or less severe,
     * should be sent directly to msg().
     */
    void report_err( const char *msg, ... );
    /**
     * Signals that a successful protocol transfer occurred,
     * reducing the qualified error count, potentially reenabling
     * logging of errors.
     */
    void report_ok();
    /**
     * Parsing routines useful for parsing ASCII input data.
     * All of these operate on buf with the current offset
     * at cp and the total number of characters being nc.
     * These all return true if the thing they are looking
     * for was not found. The idea is to string a bunch
     * of these together as:
     *  if (not_a() || not_b() || not_c()) {
     *    report_err("Something went wrong");
     *  } else {
     *    process
     *  }
     * If the error occurs before the end of the input, then
     * an error message is reported via report_err(). In general
     * this should mean that the only error that would need to
     * be manually reported would be for syntax that is not
     * supported by one of the not_*() functions or a timeout.
     */
    int not_found(unsigned char c);
    int not_hex(unsigned short &hexval);
    int not_int(int &val );
    int not_str(const char *str, unsigned int len);
    int not_str(const std::string &s);
    int not_str(const char *str);
    int not_float( float &val );
    /** The name of this interface. Used in diagnostic messages. */
    const char *iname;
    /** The number of characters in buf */
    unsigned int nc;
    /** The current character offset in buf */
    unsigned int cp;
    /** The input buffer */
    unsigned char *buf;
    /** The current size of the input buffer */
    int bufsize;
    int n_fills, n_empties;
    int n_eagain, n_eintr;
    /** The current output buffer */
    unsigned char *obuf;
    /** The number of characters in obuf */
    unsigned int onc;
    /** The current character offset in obuf */
    unsigned int ocp;
    /** Timeout object */
    Timeout TO;
  private:
    /** The qualified protocol error threshold */
    int qerr_threshold;
    /** Number of qualified protocol errors. Decremented by report_ok() */
    int n_errors;
    /** Number of protocol error messages currently suppressed. */
    int n_suppressed;
    /** Total number of errors found. */
    int total_errors;
    int total_suppressed;
};

typedef std::vector<Interface *> InterfaceVec;

/**
 * The class formerly known as Selector
 */
class Loop {
  public:
    Loop();
    virtual ~Loop();
    
    /**
     * Adds the interface as a child of the loop. This adds the interface's fd
     * to the list of fds in the loop's select() call, depending on the
     * interface's flags.
     */
    void add_child(Interface *P);
    // I don't think these functions are used currently, but they may become
    // relevant in a server. In that case, though, I feel as though the interface
    // should have an opportunity to cleanup before the child is deleted.
    // I'll defer the definition until I come across the application.
    // void delete_child(int fd_in);
    // int update_flags(int fd_in, int flag);

    /**
     * Sets a bit in the global flags word. Selectees can set
     * a corresponding bit in their flags word to request
     * notification when the bit gets set. The function
     * Selector::gflag(gflag_index) returns the bit that
     * corresponds to set_gflag(gflag_index). gflag_index
     * can take on values from 0 to 8*sizeof(int)-4.
     * @param gflag_index non-negative gflag index.
     */
    void set_gflag( unsigned gflag_index );
    /**
     * Loops waiting on select(), using the fds and flags of
     * each Interface registered via add_child(). When select()
     * indicates that an fd is ready, the corresponding Interface's
     * ProcessData() method is invoked with the flag value indicating
     * what action is ready.
     */
    void event_loop();
  private:
    InterfaceVec S;
    InterfaceVec::iterator find_child_by_fd(int fd);
    bool children_changed;
    std::atomic<int> gflags;
    /**
     * Virtual method called whenever select() returns 0. The default does nothing,
     * but it can be overridden.
     * @return non-zero if the event loop should terminate.
     */
    virtual int ProcessTimeout();
    /**
     * Virtual method to allow Selector to bid on the select() timeout
     * along with the Selectee children. The minimum timeout value is used.
     * @return a Timeout * indicating the requested timeout value or 0.
     */
    virtual Timeout *GetTimeout();
};

}

extern const char *ascii_escape(const char *str, int len);
extern const char *ascii_escape(const std::string &s);
extern const char *ascii_esc(const char *str);

#endif
