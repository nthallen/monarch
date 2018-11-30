/** @file dasio_socket.cc */
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "dasio_socket.h"
#include "nl.h"
#include "nl_assert.h"

#ifndef UNIX_PATH_MAX
#define UNIX_PATH_MAX 108
#endif

namespace DAS_IO {

Socket::Socket(const char *iname, int bufsz, const char *service, bool server) :
    Interface(iname, bufsz),
    service(service),
    hostname(0),
    is_server(server),
    socket_state(Socket_disconnected),
    socket_type(Socket_Unix)  
{
  common_init();
  connect();
}
    /**
     * Called by server when creating client interfaces after accept().
     * @param iname The interface name
     * @param bufsz Size of the input buffer
     * @param stype The socket type (Socket_TCP or Socket_Unix)
     * @param service The service of the server
     * @param hostname When Socket_TCP, the client's address
     * @fd The socket
     */
Socket::Socket(const char *iname, int bufsz, int fd, socket_type_t stype, const char *service, const char *hostname) :
  Interface(iname, bufsz),
  service(service),
  hostname(hostname),
  is_server(false),
  socket_type(stype),
  socket_state(Socket_connected)
{
  common_init();
  switch(socket_type) {
    case Socket_Unix:
      unix_name = new unix_name_t();
      if (!unix_name->set_service(service)) {
        nl_error(3, "%s: Invalid service name", iname);
      }
      break;
    case Socket_TCP:
      // probably something required here
      break;
  }
}

Socket::~Socket() {
  if (fd >= 0) {
    close();
  }
}

const char *Socket::company = "linkeng";

void Socket::common_init() {
  unix_name = 0;
  set_retries(-1, 5, 60);
  conn_fail_reported = false;
}

void Socket::connect() {
  reconn_seconds = reconn_seconds_min;
  reconn_retries = 0;
  
  switch (socket_type) {
    case Socket_Unix:
      if (unix_name == 0) {
        unix_name = new unix_name_t();
        if (!unix_name->set_service(service)) {
          nl_error(3, "%s: Invalid service name", iname);
        }
      }
      if (is_server) {
        if (!unix_name->lock()) {
          socket_state = Socket_locking;
          TO.Set(0,200);
          flags |= Fl_Timeout;
          return;
        }
        if (!unix_name->claim_server()) {
          nl_error(3, "%s: Unable to create server socket %s",
            iname, unix_name->get_svc_name());
        }
      }
      { struct hostent *hostinfo = 0;
        struct sockaddr_un local;
        nl_assert(iname != 0 && service != 0);
       
        fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd < 0)
          nl_error(4, "socket() failure in DAS_IO::Socket(%s): %s", iname,
            std::strerror(errno));
            
        local.sun_family = AF_UNIX;
        strncpy(local.sun_path, unix_name->get_svc_name(), UNIX_PATH_MAX);
        if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) == -1) {
          nl_error(3, "fcntl() failure in DAS_IO::Socket(%s): %s", iname,
            std::strerror(errno));
        }

        if (is_server) {
          unlink(local.sun_path);
          if (bind(fd, (struct sockaddr *)&local, SUN_LEN(&local)) < 0) {
            nl_error(3, "bind() failure in DAS_IO::Socket(%s,%s): %s", iname,
              local.sun_path, std::strerror(errno));
          }

          if (listen(fd, MAXPENDING) < 0) {
            nl_error(3, "listen() failure in DAS_IO::Socket(%s): %s", iname,
              std::strerror(errno));
          }
          socket_state = Socket_listening;
        } else {
          /* Establish the connection to the server */
          if (::connect(fd, (struct sockaddr *)&local,
                SUN_LEN(&local)) < 0) {
            if (errno != EINPROGRESS) {
              nl_error(2, "connect() failure in DAS_IO::Socket(%s): %s", iname,
                std::strerror(errno));
              reset();
              return;
            }
          }
          socket_state = Socket_connecting;
        }
        flags = Fl_Read | Fl_Except;
      }
      break;
    default:
      nl_error(3, "DAS_IO_Socket::Socket::connect: not implemented for socket_type %d", socket_type);
  }
}

bool Socket::ProcessData(int flag) {
  int sock_err;

  switch (socket_state) {
    case Socket_locking:
      connect();
      return false;
    case Socket_connecting:
      if (!readSockError(&sock_err))
        return false;
      if ((flag & Fl_Write) &&
          (sock_err == EISCONN || sock_err == 0)) {
        nl_error(0, "Connected");
        socket_state = Socket_connected;
        TO.Clear();
        flags &= ~(Fl_Write|Fl_Timeout);
        flags |= Fl_Read;
        reconn_retries = 0;
        conn_fail_reported = false;
        return connected();
      } else {
        if (!conn_fail_reported) {
          if (TO.Expired()) {
            nl_error(2, "connect error: Client Timeout");
          } else {
            nl_error(2, "connect error: %s",
              strerror(sock_err));
          }
        }
        reset();
        return connect_failed();
      }
    case Socket_listening:
      if (ELoop && flag & Fl_Read) {
        int new_fd = accept(fd, 0, 0);
        if (new_fd < 0) {
          nl_error(2, "%s: Error from accept(): %s", iname, strerror(errno));
          return false;
        } else {
          Socket *client = new_client("clientcon", bufsize, new_fd, socket_type, service);
          ELoop->add_child(client);
          // create a new Socket and add it to the Loop
          // probably mark it as negotiating
          return client->connected();
        }
      } else {
        nl_error(1, "Socket_listening: connection sensed, but no Loop");
      }
      break;
    case Socket_disconnected:
      // Handle timeout (i.e. attempt reconnection)
      if (TO.Expired()) {
        connect();
      }
      break;
    case Socket_connected:
      return Interface::ProcessData(flag);
    default:
      nl_error(4, "DAS_IO::Socket::ProcessData: Invalid socket_state: %d", socket_state);
  }
  return false;
}

void Socket::set_retries(int max_retries, int min_dly, int max_foldback_dly) {
  reconn_max = max_retries;
  reconn_seconds_min = min_dly;
  reconn_seconds_max = max_foldback_dly;
}

void Socket::close() {
  if (fd >= 0) {
    ::close(fd);
    fd = -1;
    socket_state = Socket_disconnected;
    TO.Clear();
    flags &= ~(Fl_Write|Fl_Read|Fl_Except|Fl_Timeout);
    if (unix_name) {
      if (unix_name->is_server()) {
        unix_name->release_server();
      }
      delete(unix_name);
      unix_name = 0;
    }
  }
}

void Socket::reset() {
  close();
  if (reconn_max == 0) {
    nl_error(3, "DAS_IO::Socket::reset(): No retries requested");
  } else if (reconn_retries++ >= reconn_max) {
    nl_error(3, "DAS_IO::Socket::reset(): Maximum connection retries exceeded");
  }
  int delay_secs = reconn_seconds;
  reconn_seconds *= 2;
  if (reconn_seconds > reconn_seconds_max)
    reconn_seconds = reconn_seconds_max;
  TO.Set(delay_secs,0);
  flags |= Fl_Timeout;
}

bool Socket::connected() { return false; }

bool Socket::connect_failed() { return false; }

Socket *Socket::new_client(const char *iname, int bufsz, int fd, socket_type_t stype, const char *service, const char *hostname) {
  return new Socket(iname, bufsz, fd, stype, service, hostname);
}

bool Socket::readSockError(int *sock_err) {
  socklen_t optlen = sizeof(*sock_err);

  if (getsockopt(fd, SOL_SOCKET, SO_ERROR,
        sock_err, &optlen) == -1) {
    nl_error(2, "Error %d from getsockopt", errno);
    reset();
    return false;
  }
  return true;
}

/**
 * Create a TCP connection to the specified hostname and service/port.
 */
//Socket::Socket(const char *iname, int bufsz, const char *hostname, const char *service);
/**
 * Called by server when creating client interfaces after accept().
 * @param iname The interface name
 * @param bufsz Size of the input buffer
 * @fd The socket
 */
//Socket::Socket(const char *iname, int bufsz, int fd);
//Socket::~Socket();

}
