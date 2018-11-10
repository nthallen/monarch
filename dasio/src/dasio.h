/**
 * \file dasio.h
 * Header for the Harvard Link Engineering Data Acquisition System I/O library
 */
#include <string>
#include <vector>
#include "Timeout.h"

class DAS_IO_Loop;

/**
 */
class DAS_IO_Interface {
  public:
    DAS_IO_Interface(const char *name, int bufsz);
    ~DAS_IO_Interface();
    /**
     * @return non-zero if we should quit
     */
    virtual int ProcessData(int flag);
    /**
     * @return a pointer to a Timeout object or zero if no timeout is required.
     * The default implementation returns zero.
     */
    virtual Timeout *GetTimeout();
    int flags;
    DAS_IO_Loop *Loop;
  protected:
    /**
     * Sets up a write of nc bytes from the buffer pointed to by str.
     * If the write cannot be accomplished immediately, the information
     * is saved and handled transparently. The caller is
     * responsible for allocating the output buffer(s) and ensuring
     * they are not overrun.
     * @return true if write was completed.
     */
    bool iwrite(const char *str, unsigned int nc, unsigned in cp = 0);
    bool iwrite(const std::string &s);
    bool iwrite(const char *str);
    virtual void iwritten(int nb);
    /**
     * @return true if the error is fatal, false if it has been handled
     * The default function returns true.
     */
    virtual bool iwrite_error(int errno);
    /**
     * @return true if the error is fatal, false if it has been handled
     * The default function returns true.
     */
    virtual bool read_error(int errno);
    
    /**
     * Called by ProcessData() when new data is available to the protocol level.
     * The default reports unexpected input and returns false;
     * @return true on an error requiring termination of the driver
     */
    bool protocol_input();
    /**
     * Called by ProcessData() when timeout is reported by select() and
     * this interface has a timeout set, and this interface's timeout
     * has expired. If the interface is also waiting for input, protocol_input()
     * will be called before protocol_timeout(). If the protocol_input()
     * clears the timeout, then protocol_timeout() will not be called.
     * The default does nothing and returns false.
     * @return true on an error requiring termination of the driver
     */
    bool protocol_timeout();
    /**
     * Called by ProcessData() when an exception occurs.
     * The default does nothing and returns false.
     * I have yet to encounter and exceptional condition, so I don't know what to expect.
     * That may not be true: maybe if a socket gets closed or something?
     * @return true on an error requiring termination of the driver
     */
    bool protocol_except(int flag);

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
     */
    void consume(int nchars);
    /**
     * Report a protocol error. This system has automatic error
     * throttling to avoid cascading log messages.
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
    /** Number of qualified protocol errors. Decremented by report_ok() */
    int n_errors;
    /** Number of protocol error messages currently suppressed. */
    int n_suppressed;
    /** Total number of errors found. */
    int total_errors;
    int total_suppressed;
};

typedef std::vector<DAS_IO_Interface *> InterfaceVec;

/**
 * The class formerly known as Selector
 */
class DAS_IO_Loop {
  public:
    static const int Fl_Read = 1;
    static const int Fl_Write = 2;
    static const int Fl_Except = 4;
    static const int Fl_Timeout = 8;
    DAS_IO_Loop();
    ~DAS_IO_Loop();
    void add_child(DAS_IO_Interface *P);
    // void delete_child(int fd_in);
    // int update_flags(int fd_in, int flag);
    void set_gflag( unsigned gflag_index );
    /**
     * Method to map a global flag number to a bit mask to be
     * set in a Selectee's flags word.
     * @param gflag_index global flag bit number
     * @return bit mask selecting the specified global flag.
     */
    static inline int gflag(unsigned gflag_index) {
      return( 1 << (gflag_index+4) );
    }
    void event_loop();
  private:
    SelecteeVec S;
    SelecteeVec::iterator find_child_by_fd(int fd);
    bool children_changed;
    int gflags;
    virtual int ProcessTimeout();
    virtual Timeout *GetTimeout();
};
