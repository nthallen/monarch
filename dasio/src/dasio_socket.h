/** @file dasio_socket.h */
#ifndef DASIO_SOCKET_H_INCLUDED
#define DASIO_SOCKET_H_INCLUDED

#include "dasio.h"

namespace DAS_IO {
  
class Socket : public Interface {
  public:
    // Socket(const char *iname, int bufsz);
    /**
     * Connect to a Unix Domain socket using the service name
     */
    Socket(const char *iname, int bufsz, const char *service, bool server = false);
    /**
     * Create a TCP connection to the specified hostname and service/port.
     */
    Socket(const char *iname, int bufsz, const char *hostname, const char *service);
    /**
     * Called by server when creating client interfaces after accept().
     * @param iname The interface name
     * @param bufsz Size of the input buffer
     * @fd The socket
     */
    Socket(const char *iname, int bufsz, int fd);
    virtual ~Socket();
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
     * Shut down the connection.
     */
    void close();

    /**
     * Close and then try to reconnect after longish delay using
     * parameters specified by set_retries().
     */
    void reset();

    typedef enum { Socket_disconnected, Socket_locking, Socket_connecting,
                              Socket_listening, Socket_connected }
                         socket_state_t;
    typedef enum { Socket_Unix, Socket_TCP, Socket_UDP, Socket_CAN }
                         socket_type_t;

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
     */
    virtual void connected() = 0;

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
     */
    virtual void connect_failed();

    unix_name_t *unix_name;
    const char *hostname;
    const char *service;
    bool is_server;
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
     * Use getsockopt to read socket error. reset()s the
     * socket and returns false if getsockopt fails,
     * otherwise sets sock_err and returns true
     */
    bool readSockError(int *sock_err);
};

class Socket_Server : public Interface { // or DAS_IO_Socket?
  public:
    Socket_Server(const char *iname, const char *service, int opt);
    virtual ~Socket_Server();
  protected:
};

}
#endif