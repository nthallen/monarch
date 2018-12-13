/** @file loop.cc */
#include <errno.h>
#include <sys/select.h>
#include "dasio/loop.h"
#include "nl.h"
#include "nl_assert.h"

namespace DAS_IO {
  
Loop::Loop() {
  children_changed = false;
  gflags = 0;
}

/**
 * Destructor should not delete children, since it does not know
 * how they were allocated
 */
Loop::~Loop() {
}

void Loop::add_child(Interface *P) {
  if (find_child_by_fd(P->fd) == S.end() ) {
    S.push_back(P);
    P->ELoop = this;
    children_changed = true;
  } else {
    nl_error( 4, "fd %d already inserted in DAS_IO::Loop::add_child", P->fd );
  }
}

void Loop::remove_child(Interface *P) {
  for (InterfaceList::iterator pos = S.begin(); pos != S.end(); ++pos ) {
    if (P == *pos) {
      S.erase(pos);
      children_changed = true;
      return;
    }
  }
  nl_error(1, "remove_child Interface(%s,%d) not found", P->get_iname(), P->fd);
}

void Loop::delete_child(Interface *P) {
  remove_child(P);
  PendingDeletion.push_back(P);
}

InterfaceList::iterator Loop::find_child_by_fd(int fd) {
  if (fd >= 0) {
    for (InterfaceList::iterator pos = S.begin(); pos != S.end(); ++pos ) {
      Interface *P;
      P = *pos;
      if (P->fd == fd) return pos;
    }
  }
  return S.end();
}

void Loop::set_gflag( unsigned gflag_index ) {
  nl_assert(gflag_index+4 < sizeof(int)*8 );
  // gflags |= gflag(gflag_index);
  // atomic_set((unsigned *)&gflags, gflag(gflag_index));
  gflags |= Interface::gflag(gflag_index);
}

void Loop::event_loop() {
  int keep_going = 1;
  int width = 0;
  int rc;
  fd_set readfds, writefds, exceptfds;
  
  while (keep_going) {
    TimeoutAccumulator TA;
    InterfaceList::const_iterator Sp;

    // nl_error(0, "Loop: %sempty, %d children", S.empty() ? "" : "not ", S.size());
    while (!PendingDeletion.empty()) {
      Interface *P = PendingDeletion.front();
      // nl_error(0, "Deleting Interface %d", P->get_iname());
      delete(P);
      PendingDeletion.pop_front();
    }
    
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);
    TA.Set(GetTimeout());
    children_changed = false;
    for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
      Interface *P = *Sp;
      int flag = gflags.fetch_and(~P->flags) & P->flags;
      if (flag) {
        P->ProcessData(flag);
      }
    }
    for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
      Interface *P = *Sp;
      // nl_error(0, "%s fd %d flags %d", P->get_iname(), P->fd, P->flags);
      if (P->fd >= 0) {
        if (P->flags & P->Fl_Read) FD_SET(P->fd, &readfds);
        if (P->flags & P->Fl_Write) FD_SET(P->fd, &writefds);
        if (P->flags & P->Fl_Except) FD_SET(P->fd, &exceptfds);
        if (P->flags & P->Fl_Timeout) TA.Set_Min( P->GetTimeout() );
        if (width <= P->fd) width = P->fd+1;
      }
    }
    rc = select(width, &readfds, &writefds, &exceptfds, TA.timeout_val());
    if ( rc == 0 ) {
      if ( ProcessTimeout() )
        keep_going = 0;
      for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
        Interface *P = *Sp;
        if ((P->flags & P->Fl_Timeout) && P->ProcessData(P->Fl_Timeout))
          keep_going = 0;
      }
    } else if ( rc < 0 ) {
      if ( errno == EINTR ) keep_going = 0;
      else if (errno == EBADF || errno == EHOSTDOWN) {
        bool handled = false;
        for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
          Interface *P = *Sp;
          int flags = 0;
          if (P->flags & P->Fl_Except) {
            if ( P->ProcessData(P->Fl_Except) )
              keep_going = 0;
            if (children_changed) break; // Changes can occur during ProcessData
            handled = true;
          }
        }
        if (!handled) {
          nl_error(3, "DAS_IO::Loop::event_loop(): Unhandled EBADF or EHOSTDOWN");
        }
      } else {
        nl_error(3,
          "DAS_IO::Loop::event_loop(): Unexpected error from select: %d", errno);
      }
    } else {
      for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
        Interface *P = *Sp;
        int flags = 0;
        if (P->fd >= 0) {
          if ( (P->flags & P->Fl_Read) && FD_ISSET(P->fd, &readfds) )
            flags |= P->Fl_Read;
          if ( (P->flags & P->Fl_Write) && FD_ISSET(P->fd, &writefds) )
            flags |= P->Fl_Write;
          if ( (P->flags & P->Fl_Except) && FD_ISSET(P->fd, &exceptfds) )
            flags |= P->Fl_Except;
          if ( flags ) {
            if ( P->ProcessData(flags) )
              keep_going = 0;
            if (children_changed) break; // Changes can occur during ProcessData
          }
        }
      }
    }
  }
}

/*
 * Regarding children_changed, the most likely change during P->ProcessData() is
 * the removal of the child pointing to P. Given the properties of lists,
 * it is possible to restructure the loop so that even if the current element
 * gets removed, we can continue processing the list. This would involve
 * incrementing the iterator before calling ProcessData(). That's fine until
 * we come to a corner case where some action on one interface causes another
 * interface to shut down. Simply restarting the loop is probably the safest
 * policy.
 */

int Loop::ProcessTimeout() { return 0; }
Timeout *Loop::GetTimeout() { return 0; }

}
