/** @file loop.cc */
#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include "dasio/loop.h"
#include "nl.h"
#include "dasio/msg.h"
#include "nl_assert.h"

namespace DAS_IO {
  
Loop::Loop(bool is_memo) : is_memo_loop(is_memo) {
  // children_changed = false;
  gflags = 0;
  loop_exit = false;
  LI = S.begin();
  list_element_deleted = false;
  pthread_sigmask(SIG_SETMASK, 0, &blockset);
  pthread_sigmask(SIG_SETMASK, 0, &runset);
}

Loop::~Loop() {
  delete_children();
  clear_delete_queue(true);
}

void Loop::add_child(Interface *P) {
  if (find_child_by_fd(P->fd) == S.end() ) {
    S.push_back(P);
    P->ELoop = this;
    P->reference();
    P->adopted();
    // children_changed = true;
  } else {
    msg( MSG_EXIT_ABNORM, "fd %d already inserted in DAS_IO::Loop::add_child", P->fd );
  }
}

bool Loop::remove_child(Interface *P, bool deref) {
  for (InterfaceList::iterator pos = S.begin(); pos != S.end(); ++pos ) {
    if (P == *pos) {
      if (pos == LI) {
        list_element_deleted = true;
      } else {
        S.erase(pos);
      }
      // children_changed = true;
      P->ELoop = 0;
      if (deref) Interface::dereference(P);
      return true;
    }
  }
  if (P->ELoop)
    msg(MSG_ERROR, "remove_child(%s,%d) failed, but ELoop != 0", P->get_iname(), P->fd);
  else
    msg(MSG_WARN, "remove_child Interface(%s,%d) not found", P->get_iname(), P->fd);
  return false;
}

void Loop::delete_child(Interface *P) {
  if (P->ref_check(2))
    msg(MSG_WARN, "%s: ref_count >= 2 in delete_child", P->get_iname());
  if (remove_child(P, false))
    PendingDeletion.push_back(P);
}

void Loop::delete_children() {
  while (!S.empty()) {
    Interface *P = S.front();
    delete_child(P);
  }
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

void Loop::clear_delete_queue(bool final) {
  while (!PendingDeletion.empty()) {
    Interface *P = PendingDeletion.front();
    if (P->ref_check(2))
      msg(MSG_ERROR,"%s: ref_count > 1 in clear_delete_queue(final)", P->get_iname());
    Interface::dereference(P); // delete(P);
    PendingDeletion.pop_front();
  }
}

void Loop::event_loop() {
  int keep_going = 1;
  int width = 0;
  int rc;
  fd_set readfds, writefds, exceptfds;
  
  do {
    TimeoutAccumulator TA;
    InterfaceList::const_iterator Sp;
    
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);
    TA.Set(GetTimeout());
    // children_changed = false;
    if (S.empty() && ! TA.Set()) break;
    for (loop_init(); loop_active(); loop_iterate()) {
      Interface *P = *LI;
      int flag = gflags.fetch_and(~P->flags) & P->flags;
      if (flag) {
        P->ProcessData(flag);
      }
    }
    for (loop_init(); loop_active(); loop_iterate()) {
      Interface *P = *LI;
      // msg(0, "%s fd %d flags %d", P->get_iname(), P->fd, P->flags);
      if (P->fd >= 0) {
        if (P->flags & P->Fl_Read) FD_SET(P->fd, &readfds);
        if (P->flags & P->Fl_Write) FD_SET(P->fd, &writefds);
        if (P->flags & P->Fl_Except) FD_SET(P->fd, &exceptfds);
        if (width <= P->fd) width = P->fd+1;
      }
      if (P->flags & P->Fl_Timeout) TA.Set_Min( P->GetTimeout() );
    }
    // rc = select(width, &readfds, &writefds, &exceptfds, TA.timeout_val());
    rc = pselect(width, &readfds, &writefds, &exceptfds,
                 TA.timeout_val_ns(), &runset);
    if ( rc == 0 ) {
      if ( ProcessTimeout() ) {
        if (!is_memo_loop) {
          msg(MSG_DBG(1), "Loop.ProcessTimeout() requested termination");
        }
        keep_going = 0;
      }
      for (loop_init(); loop_active(); loop_iterate()) {
        Interface *P = *LI;
        if ((P->flags & P->Fl_Timeout) && P->ProcessData(P->Fl_Timeout)) {
          if (!is_memo_loop) {
            msg(MSG_DBG(1), "%s: requested termination after P->Fl_Timeout", P->get_iname());
          }
          keep_going = 0;
        }
      }
    } else if ( rc < 0 ) {
      if ( errno == EINTR ) {
        //keep_going = 0;
        for (loop_init(); loop_active(); loop_iterate()) {
          Interface *P = *LI;
          if (signals_seen && P->signals) {
            if (P->serialized_signal_handler(signals_seen)) {
              if (!is_memo_loop) {
                msg(MSG_DBG(1), "%s: requested termination after if (errno==EINTR)", P->get_iname());
              }
              keep_going = 0;
            }
            signals_seen &= ~(P->signals);
          }
        }
        if (signals_seen != 0) {
          msg(MSG_ERROR, "unhandled signal in Loop: %08X", signals_seen);
          signals_seen = 0;
          keep_going = 0;
        }
      } else {
        // We have received an error likely related to one of
        // the fds we are monitoring, but have no clue to which.
        // This occurs under Cygwin, for example, when a USB
        // serial device is unplugged. This might also occur
        // with a TCP socket if the remote host dropped off
        // the network.
        bool any_handled = false;
        int saw_errno = errno;
        for (loop_init(); loop_active(); loop_iterate()) {
          Interface *P = *LI;
          bool handled = false;
          if (P->protocol_unknown(handled)) {
            msg(MSG_DBG(1),
              "%s: requested termination after"
              " pselect() error %d: (%s)",
              P->get_iname(), saw_errno, strerror(saw_errno));
            keep_going = 0;
          }
          if (handled)
            any_handled = true;
        }
        if (!any_handled) {
          msg(MSG_FATAL, "Unhandled error %d from pselect(): %s",
            saw_errno, strerror(saw_errno));
        }
      }
    } else {
      for (loop_init(); loop_active(); loop_iterate()) {
        Interface *P = *LI;
        int flags = 0;
        if (P->fd >= 0) {
          if ( (P->flags & P->Fl_Read) && FD_ISSET(P->fd, &readfds) )
            flags |= P->Fl_Read;
          if ( (P->flags & P->Fl_Write) && FD_ISSET(P->fd, &writefds) )
            flags |= P->Fl_Write;
          if ( (P->flags & P->Fl_Except) && FD_ISSET(P->fd, &exceptfds) )
            flags |= P->Fl_Except;
          if ( flags ) {
            if ( P->ProcessData(flags) ) {
              if (!is_memo_loop) {
                msg(MSG_DBG(1), "%s: requested termination after P->ProcessData(flags)", P->get_iname());
              }
              keep_going = 0;
            }
            // if (children_changed) break;
          }
        }
      }
    }
    clear_delete_queue();
  } while (keep_going && !loop_exit);
  clear_delete_queue();
}

void Loop::set_loop_exit() {
  loop_exit = true;
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

void Loop::signal(int sig, void (*handler)(int)) {
  sigaddset(&blockset, sig);
  pthread_sigmask(SIG_SETMASK, &blockset, 0);
  sigdelset(&runset, sig);
  
  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  
  if (sigaction(sig, &sa, 0) < 0)
    msg(MSG_ERROR, "sigaction(%d) error %d: %s", sig, errno, strerror(errno));
}

void Loop::loop_init() {
  LI = S.begin();
  list_element_deleted = false;
}

bool Loop::loop_active() {
  return(LI != S.end());
}

void Loop::loop_iterate() {
  if (list_element_deleted) {
    LI = S.erase(LI);
    list_element_deleted = false;
  } else {
    ++LI;
  }
}

} // End of namespace DAS_IO

uint32_t DAS_IO::Loop::signals_seen = 0;

void loop_signal_handler(int sig) {
  DAS_IO::Loop::signals_seen |= 1 << (sig - 1);
}
