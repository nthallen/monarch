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

    typedef enum { Socket_disconnected, Socket_connecting,
                              Socket_listening, Socket_connected }
                         socket_state_t;
    typedef enum { Socket_Unix, Socket_TCP, Socket_UDP, Socket_CAN }
                         socket_type_t;

    inline socket_state_t get_socket_state() { return socket_state; }
    inline socket_type_t get_socket_type() { return socket_type; }
    
    static const char *company;

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

    const char *hostname;
    const char *service;
    const char *exp_path;
    const char *unix_path;
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