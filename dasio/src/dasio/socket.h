/** @file dasio/socket.h */
#ifndef DASIO_SOCKET_H_INCLUDED
#define DASIO_SOCKET_H_INCLUDED

#include "interface.h"

namespace DAS_IO {

class Authenticator;

/**
 * @brief Base class for TCP and Unix Domain sockets
 *
 * It is worth noting that currently the Socket class includes basic
 * mechanisms for a server socket--calling listen() and accept()
 * and creating a new Socket for the new client connection--but
 * this is essentially useless without creating a subclass that
 * will override new_client() to produce another subclass to
 * handle the client connection.
 *
 * For our negotiated client/server connection, the former
 * class is Server_socket, which overrides new_client to
 * create an Authenticator socket.
 *
 * Perhaps Socket::new_client(iname, fd) should always return 0,
 * since it really must be overridden to be useful. That said,
 * it is very short, so not much code is wasted.
 */
class Socket : public Interface {
  friend class Authenticator;
  public:
    typedef enum { Socket_disconnected, Socket_locking, Socket_connecting,
                              Socket_listening, Socket_connected }
                         socket_state_t;
    typedef enum { Socket_Unix, Socket_TCP, Socket_UDP, Socket_CAN }
                         socket_type_t;

                         // Socket(const char *iname, int bufsz);
    /**
     * Create to a Unix Domain socket client using the service name
     */
    Socket(const char *iname, int bufsz, const char *service);
    
    /**
     * Create a socket server
     */
    Socket(const char *iname, const char *service,
        socket_type_t socket_type);
    
    /**
     * Create a TCP client connection to the specified hostname and service/port.
     */
    Socket(const char *iname, int bufsz, const char *hostname, const char *service);
    
    /**
     * Initializes this Socket to match the original, making sure to
     * set is_server to false and propagating the is_server_client value.
     */
    Socket(Socket *original, const char *iname, int ibufsize, int fd);
    
    virtual ~Socket();
    /**
     * The flags bits consist of Fl_Read, Fl_Write, Fl_Except, Fl_Timeout and the gflag() values.
     * @param flag Bit-mapped list of events that triggered this call.
     * @return true to exit the event loop.
     */
    bool ProcessData(int flag);

    /**
     * Initiates connection to the server. The library
     * sets the timeout interval to 5 minutes, which should
     * be much longer than the network library's own
     * timeout. The client may alter the timeout interval
     * immediately after the call to connect() if a timeout
     * shorter than the network library's is desired.
     */
    void connect();

    /**
     * The default configuration is set_retries(-1,5,60);
     * @param max_retries Set to 0 for no retries, -1 for unlimited.
     * @param min_dly Seconds to wait before first retry
     * @param max_foldback_dly Maximum delay between retries, with delay doubling
     *   on each attempt.
     */
    void set_retries(int max_retries, int min_dly, int max_foldback_dly);

    /**
     * If the socket is a listener, then return true.
     * If the socket is a server client, just tear it down.
     * Otherwise tear it down and attempt to reconnect.
     * @param The errno value
     * @return true if event loop should exit
     */
    bool read_error(int my_errno);
    /**
     * If the socket is a listener, then return true. (but should not be writing!)
     * If the socket is a server client, just tear it down.
     * Otherwise tear it down and attempt to reconnect.
     * @param The errno value
     * @return true if event loop should exit
     */
    bool iwrite_error(int my_errno);
    /**
     * Check socket error to determine if there is a problem.
     * @return true it the event loop should exit
     */
    bool protocol_except();
    /**
     * Called when read returns zero, indicating normal EOF.
     * The default action for clients is to close() the connection and
     * return true. Hence clients that are handling multiple interfaces
     * may need to override this method to make a finer grained determination
     * of the appropriate action.
     * For server side client connections, the default is
     * to close() the connection and delete the interface. Listening
     * server interfaces should never be reading, so should never see
     * this condition, so the default is to report an error and return
     * true.
     * @return true it the event loop should exit
     */
    bool process_eof();
    
    /**
     * Shut down the connection.
     */
    void close();

    /**
     * Close and then try to reconnect after longish delay using
     * parameters specified by set_retries().
     * @return true if all retries have been exhausted
     */
    bool reset();

    inline socket_state_t get_socket_state() { return socket_state; }
    inline socket_type_t get_socket_type() { return socket_type; }
    
    static const char *company;

    class unix_name_t {
      public:
        unix_name_t();
        /**
         * Releases any allocated names.
         */
        ~unix_name_t();
        /**
         * @param service single word (e.g. cmd, DG, TM, memo)
         * Populates exp_name and svc_name. May only be called
         * once.
         * @return true if generated svc_name is valid
         */
        bool set_service(const char *service);
        /**
         * @return The full path for the service socket.
         */
        const char *get_svc_name();
        /**
         * The lock applies to all names on this system for this Experiment.
         * If the lock is not obtained, caller can retry later.
         * If the /var/run/$company directory does not exist, a fatal error
         * will occur.
         * @return true if lock is obtained
         */
        bool lock();
        /**
         * Release lock on socket names.
         */
        void unlock();
        /**
         * @return true if we hold the lock on the Experiment name space.
         */
        bool is_locked();
        /**
         * Populates pid_name. Must call lock() prior to claim_server().
         * @return true if we have successfully staked a claim for the specified
         * server name. false means an active process owns the space.
         */
        bool claim_server();
        /**
         * @return true if claim_server() has been successfully called.
         */
        bool is_server();
        /**
         * Deletes socket and PID files.
         * Attempts to unlink the Experiment directory and deletes the
         * Experiment lock file. Only valid if we have successfully
         * called claim_server().
         */
        void release_server();
        static const char *run_dir;
      private:
        /**
         * Accepts [-\._a-zA-Z0-9]
         * @param w the string to test
         * @param context The name of the parameter being tested for use in
         * error messages.
         * @return true if w points to a string of acceptable characters
         */
        bool is_word(const char *w, const char *context);
        int lock_fd;
        const char *lock_name;
        const char *exp_name;
        const char *svc_name;
        const char *pid_name;
        bool locked;
        bool server_claimed;
    };
  protected:

    /**
     * Called upon successful connection. The library
     * will have already reported the connection.
     * The default method does nothing.
     *
     * @return true if the event loop should exit.
     */
    virtual bool connected();

    /**
     * Called when connection has failed. The library will
     * automatically retry indefinitely, extending the
     * retry interval. The failure will have been reported
     * on the first occurrence, and then not on failed
     * retries.
     *
     * This method can be used to adjust the retry interval
     * from the default, or to take some other application-
     * specific action. The default method does nothing.
     *
     * @return true if the event loop should exit.
     */
    virtual bool connect_failed();
    
    /**
     * Copy all parameters from this Socket except iname and fd,
     * set is_server false and set is_server_client true.
     * Adds the new client to ELoop if defined.
     */
    virtual Socket *new_client(const char *iname, int fd);
    
    /**
     * Invokes new_client(fd) to clone this object into one of a different
     * class after negotiation has completed. Will remove this socket
     * from ELoop if defined and possible preserve the object for reuse.
     */
    virtual Socket *new_client();

    unix_name_t *unix_name;
    const char *hostname;
    const char *service;
    /** True if this interface is a listening socket */
    bool is_server;
    /** True if this interface was established after accept() */
    bool is_server_client;
    bool conn_fail_reported;
    int reconn_seconds; /**< Current retry delay */
    int reconn_retries; /**< The current number of reconnects attempted */
    int reconn_max; /**< The maximum number of retries */
    int reconn_seconds_min; /**< Seconds delay for first retry */
    int reconn_seconds_max; /**< Max seconds delay after multiple retries */
    socket_state_t socket_state;
    socket_type_t socket_type;
  private:
    static const int MAXPENDING = 5;
    void common_init();

    /**
     * Use getsockopt to read socket error.
     * @return true if getsockopt succeeds.
     */
    bool readSockError(int *sock_err);
};

}
#endif
