/** @file socket.cc
 * Tests of the DAS_IO::Interface::Socket classes
 */
#include "dasio_socket.h"
#include "gmock/gmock.h"

class MockSocket : public DAS_IO::Socket {
  public:
    inline MockSocket(const char *iname, int bufsz, const char *service, bool server = false) :
      DAS_IO::Socket(iname, bufsz, service, server) {}
    inline ~MockSocket() {};
    MOCK_METHOD0(connected, void());
    MOCK_METHOD0(connect_failed, void());
};
