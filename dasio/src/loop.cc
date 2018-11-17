/** @file loop.cc */
#include <errno.h>
#include <sys/select.h>
#include "dasio.h"
#include "nl.h"
#include "nl_assert.h"

DAS_IO_Loop::DAS_IO_Loop() {
  children_changed = false;
  gflags = 0;
}

/**
 * Destructor should not delete children, since it does not know
 * how they were allocated
 */
DAS_IO_Loop::~DAS_IO_Loop() {
}

void DAS_IO_Loop::add_child(DAS_IO_Interface *P) {
  if (find_child_by_fd(P->fd) == S.end() ) {
    S.push_back(P);
    P->Loop = this;
    children_changed = true;
  } else {
    nl_error( 4, "fd %d already inserted in DAS_IO_Loop::add_child", P->fd );
  }
}

InterfaceVec::iterator DAS_IO_Loop::find_child_by_fd(int fd) {
  InterfaceVec::iterator pos;
  for ( pos = S.begin(); pos != S.end(); ++pos ) {
    DAS_IO_Interface *P;
    P = *pos;
    if (P->fd == fd) return pos;
  }
  return S.end();
}

void DAS_IO_Loop::set_gflag( unsigned gflag_index ) {
  nl_assert(gflag_index+4 < sizeof(int)*8 );
  // gflags |= gflag(gflag_index);
  // atomic_set((unsigned *)&gflags, gflag(gflag_index));
  gflags |= DAS_IO_Interface::gflag(gflag_index);
}

void DAS_IO_Loop::event_loop() {
  int keep_going = 1;
  int width = 0;
  int rc;
  fd_set readfds, writefds, exceptfds;
  
  while (keep_going) {
    TimeoutAccumulator to;
    InterfaceVec::const_iterator Sp;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);
    to.Set_Min(GetTimeout());
    children_changed = false;
    for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
      DAS_IO_Interface *P = *Sp;
      int flag = gflags.fetch_and(~P->flags) & P->flags;
      if (flag) {
        P->ProcessData(flag);
      }
      // if (P->flags & gflags) {
        // int flag = P->flags & gflags;
        // atomic_clr((unsigned *)&gflags, flag);
        // P->ProcessData(flag);
      // }
    }
    for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
      DAS_IO_Interface *P = *Sp;
      if (P->flags & P->Fl_Read) FD_SET(P->fd, &readfds);
      if (P->flags & P->Fl_Write) FD_SET(P->fd, &writefds);
      if (P->flags & P->Fl_Except) FD_SET(P->fd, &exceptfds);
      if (P->flags & P->Fl_Timeout) to.Set_Min( P->GetTimeout() );
      if (width <= P->fd) width = P->fd+1;
    }
    rc = select(width, &readfds, &writefds, &exceptfds, to.timeout_val());
    if ( rc == 0 ) {
      if ( ProcessTimeout() )
        keep_going = 0;
      for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
        DAS_IO_Interface *P = *Sp;
        if ((P->flags & P->Fl_Timeout) && P->ProcessData(P->Fl_Timeout))
          keep_going = 0;
      }
    } else if ( rc < 0 ) {
      if ( errno == EINTR ) keep_going = 0;
      else if (errno == EBADF || errno == EHOSTDOWN) {
        bool handled = false;
        for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
          DAS_IO_Interface *P = *Sp;
          int flags = 0;
          if (P->flags & P->Fl_Except) {
            if ( P->ProcessData(P->Fl_Except) )
              keep_going = 0;
            if (children_changed) break; // Changes can occur during ProcessData
            handled = true;
          }
        }
        if (!handled) {
          nl_error(3, "DAS_IO_Loop::event_loop(): Unhandled EBADF or EHOSTDOWN");
        }
      } else {
        nl_error(3,
          "DAS_IO_Loop::event_loop(): Unexpected error from select: %d", errno);
      }
    } else {
      for ( Sp = S.begin(); Sp != S.end(); ++Sp ) {
        DAS_IO_Interface *P = *Sp;
        int flags = 0;
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

int DAS_IO_Loop::ProcessTimeout() { return 0; }
Timeout *DAS_IO_Loop::GetTimeout() { return 0; }
