/** @file dasio/timeout.h */

#ifndef DASIO_TIMEOUT_H_INCLUDED
#define DASIO_TIMEOUT_H_INCLUDED

#include <time.h>
#include <sys/select.h>

namespace DAS_IO {

class Timeout {
  public:
    Timeout();
    // Timeout( time_t secs, long msecs );
    void Set( time_t secs, long msecs );
    void Clear();
  /**
   * Specifies a desired timeout relative to the current time. The event loop
   * will subtract the then-current time to determine the correct relative
   * timeout value.
   * @param secs Seconds
   * @param msecs Milleseconds
   */
    bool Set();
    bool Expired();
    struct timespec when;
};

class TimeoutAccumulator {
  public:
    TimeoutAccumulator();
    bool Set();
    void Set( Timeout * );
    void Set_Min( Timeout * );
    struct timeval *timeout_val();
  private:
    struct timespec when;
    struct timeval how_soon;
};

}

#endif
