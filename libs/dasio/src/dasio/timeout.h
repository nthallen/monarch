/** @file dasio/timeout.h */

#ifndef DASIO_TIMEOUT_H_INCLUDED
#define DASIO_TIMEOUT_H_INCLUDED

#include "tm.h"
#include <time.h>
#include <sys/select.h>

namespace DAS_IO {

class Timeout {
  public:
    Timeout();
    /**
     * Specifies a desired timeout relative to the current time. The event loop
     * will subtract the then-current time to determine the correct relative
     * timeout value. Note that secs and msecs should meet the criteria for
     * the Add() method, i.e. msecs must be non-negative.
     * @param secs Seconds
     * @param msecs Milleseconds
     */
    void Set( le_time_t secs, long msecs );
    /**
     * Adds the specified delay to the current timeout value.
     * The msecs parameter must be non-negative, although negative offsets
     * can be accommodated by making appropriate adjustments to the secs
     * parameter, e.g. TO.Add(-1, 800) to achieve a -200 msecs offset.
     * @param secs Seconds
     * @param msecs Milleseconds
     */
    void Add( le_time_t secs, long msecs );
    /**
     * Clears any current timeout setting.
     */
    void Clear();
    /**
     * @return True if a timeout value is set, regardless of whether
     * the time has expired or not.
     */
    bool Set();
    /**
     * @return True if a timeout value is set and has expired.
     */
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
    struct timespec *timeout_val_ns();
  private:
    struct timespec when;
    struct timeval how_soon;
    struct timespec how_soon_ns;
};

}

#endif
