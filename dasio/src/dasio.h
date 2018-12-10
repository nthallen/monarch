/**
 * \file dasio.h
 * Header for the Harvard Link Engineering Data Acquisition System I/O library
 */
#ifndef DAS_IO_H_INCLUDED
#define DAS_IO_H_INCLUDED
#include <string>
#include <list>
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
     * The default implementation returns a pointer to the TO member.
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
    /** The event loop we belong to */
    Loop *ELoop;
    /** getter for interface name. */
    inline const char *get_iname() { return iname; }
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
     * 
     * If an error occurs during writing, iwrite_error(errno) is called,
     * and it's return value is returned.
     * @param str Pointer to the output buffer
     * @param nc The total number of bytes in the output buffer
     * @param cp The starting offset within the output buffer
     * @return true if event loop should terminate.
     */
    bool iwrite(const char *str, unsigned int nc, unsigned int cp = 0);
    /**
     * Sets up a write of the string s by invoking iwrite(str, nc, 0).
     * There are risks associated with this invocation if the resulting
     * string is not transmitted immediately. The string argument must
     * remain unmodified until entirely transmitted.
     * @param s The string to output
     * @return true if event loop should terminate.
     */
    bool iwrite(const std::string &s);
    /**
     * Sets up a write of the string s by invoking iwrite(str, strlen(str), 0).
     * The string must remain unmodified until the data has been entirely
     * transmitted.
     * @param str The string to output
     * @return true if event loop should terminate.
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
     * Called from fillbuf() when read() returns an error. If read() returns zero,
     * read_error() is called with EOK, which higher-level processors can use
     * to investigate.
     * @param my_errno The errno value or EOK
     * @return true if the error is fatal, false if it has been handled
     */
    virtual bool read_error(int my_errno);
    
    /**
     * Called by ProcessData() when new data is available to the protocol level.
     *
     * protocol_input() and the parsing functions use the Interface's buf, cp and nc
     * members to define the current input text. nc is the total number
     * of characters in buf, and cp defines the current offset into
     * buf. Hence the next input character to consider is always buf[cp],
     * and we can only advance while cp < nc.
     *
     * The not_*() parsing functions
     * will advance cp as a side effect. nc is updated by fillbuf()
     * when input is received and by consume() when protocol_input()
     * is finished with input characters. cp is set to zero before
     * protocol_input() is called, so it is important that protocol_input()
     * take care to clear out any characters that have already been fully
     * processed.
     *
     * @return true on an error requiring termination of the driver
     */
    virtual bool protocol_input();
    /**
     * Called by ProcessData() when timeout is reported by select() and
     * this interface has a timeout set, and this interface's timeout
     * has expired. If the interface is also waiting for input, protocol_input()
     * will be called before protocol_timeout(). If the protocol_input()
     * clears the timeout, then protocol_timeout() will not be called.
     *
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
     * Called when 0 bytes are read from the interface. The default
     * returns true, but this is not appropriate in all situations.
     * @return true if the event loop should terminate.
     */
    virtual bool closed();

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
     * @param nchars Optionally call consume(nchars)
     */
    void report_ok(int nchars = 0);
    /**
     * Parsing utility function that searches forward in the buffer for the
     * specified framing character. On success, cp is updated to point just
     * past the location of the framing character and the function returns
     * false. If the character is not found, the buffer is emptied and the
     * function returns true.
     *
     * See not_hex() for a more detailed description of these parsing
     * functions.
     *
     * @param c A framing character
     * @return false if the character is found.
     */
    bool not_found(unsigned char c);
    /**
     * Parsing utility function to read in a hex integer starting
     * at the current position. Integer may be proceeded by optional
     * whitespace.
     *
     * Read the description of protocol_input() to understand how
     * we use buf, cp and nc.
     *
     * These parsing utility functions advance cp, looking for a
     * specific syntactic element (in this case, a hex integer
     * optionally preceded by whitespace). If the element is
     * found, the converted value is stored in the referenced
     * variable (hexval here) and the function will return false.
     *
     * If the function encounters an invalid character or reaches
     * the end of the input text (cp == nc) before the semantic
     * element has been found, the function will return true.
     * If the error occurs before the end of the input buffer,
     * an error will also be reported via report_err().
     *
     * The idea is that a protocol_input() implementation should be
     * able to string together a string of these functions, such as:
     *
     * ```
     * if (not_int(val1) || not_str(",") || not_int(val2) ||
     *     not_str(",") || not_float(flt1)) {
     *   if (cp < nc) {
     *     // input error
     *   }
     *   return false;
     * } else {
     *   // valid input, can reference val1, val2, flt1 
     * }
     * ```
     *
     * Note that failure of a parsing function is only a real error
     * if cp < nc. Otherwise, it probably just means that we are 
     * awaiting more input. How exactly to recover from real input
     * errors is very much dependent on the nature of the input
     * source. If this is a socket connection from another program,
     * it is probably appropriate to consume() all the characters in
     * the input buffer. If the input is coming from a serial device
     * and there is some sort of framing character in the input protocol,
     * it may be reasonable to consume() only up to cp and then search
     * for the framing character using not_found().
     *
     * @param[out] hexval The integer value
     * @return false if a hexadecimal integer was found and converted,
     * true if the current char is not a digit.
     */
    bool not_hex(unsigned short &hexval);
    /**
     * Parsing utility function to read in a decimal integer starting
     * at the current position. Integer may be proceeded by optional
     * whitespace and an optional sign.
     *
     * See not_hex() for a more detailed description of these parsing
     * functions.
     *
     * @param[out] val The integer value
     * @return zero if an integer was converted, non-zero if the current char is not a digit.
     */
    bool not_int(int &val );
    /**
     * Parsing utility function to check that the specified string matches the
     * input at the current position. On success, advances cp to just
     * after the matched string. On failure, cp points to the first
     * character that does not match, which may be the end of the
     * input buffer.
     *
     * Since both str and len are specified, the specified string may
     * include NUL characters.
     *
     * See not_hex() for a more detailed description of these parsing
     * functions.
     *
     * @param str The comparison string
     * @param len The length of the string
     * @return zero if the string matches the input buffer.
     */
    bool not_str(const char *str, unsigned int len);
    /**
     * Parsing utility function to check that the specified string matches the
     * input at the current position. On success, advances cp to just
     * after the matched string. On failure, cp points to the first
     * character that does not match, which may be the end of the
     * input buffer.
     *
     * See not_hex() for a more detailed description of these parsing
     * functions.
     *
     * @param s The comparison string
     * @return zero if the string matches the input buffer.
     */
    bool not_str(const std::string &s);
    /**
     * Parsing utility function to check that the specified string matches the
     * input at the current position. On success, advances cp to just
     * after the matched string. On failure, cp points to the first
     * character that does not match, which may be the end of the
     * input buffer.
     *
     * See not_hex() for a more detailed description of these parsing
     * functions.
     *
     * @param str The comparison ASCIIZ string.
     * @return zero if the string matches the input buffer.
     */
    bool not_str(const char *str);
    /**
     * Parsing utility function to convert a string in the input
     * buffer to a float value. Updates cp to point just after the
     * converted string on success.
     *
     * See not_hex() for a more detailed description of these parsing
     * functions.
     *
     * @param val[out] The converted value
     * @return false if the conversion succeeded.
     */
    bool not_float( float &val );
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

typedef std::list<Interface *> InterfaceList;

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
     * interface's flags. Also ensures that all non-negative interface fds are
     * unique.
     */
    void add_child(Interface *P);
    
    /**
     * @param P the Interface to be removed.
     * Removes the specified Interface from the list of active interfaces.
     */
    void remove_child(Interface *P);
    
    /**
     * @param P the Interface to be deleted.
     * Removes the specified Interface from the list of active interfaces,
     * and marks it for deletion at a later time.
     */
    void delete_child(Interface *P);
    
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
    /** The list of child interfaces */
    InterfaceList S;
    /** List of interfaces pending deletion */
    InterfaceList PendingDeletion;
    
    /**
     * Locates the position in list S of the Interface with the matching fd.
     * Will not match anything if fd < 0.
     * @param fd The fd we are searching for
     * @return The position in S of the Interface with the matching fd.
     */
    InterfaceList::iterator find_child_by_fd(int fd);
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
