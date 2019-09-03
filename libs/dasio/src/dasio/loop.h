/**
 * \file loop.h
 * Header for the Harvard Link Engineering Data Acquisition System I/O library
 */
#ifndef DAS_IO_LOOP_H_INCLUDED
#define DAS_IO_LOOP_H_INCLUDED
#include <string>
#include <list>
#include <atomic>
#include <signal.h>
#include "interface.h"
#include "timeout.h"

namespace DAS_IO {

typedef std::list<Interface *> InterfaceList;

/**
 * The class formerly known as Selector
 */
class Loop {
  public:
    Loop();
    virtual ~Loop();
    
    /**
     * Adds the interface as a child of the loop. This adds the interface's fd
     * to the list of fds in the loop's select() call, depending on the
     * interface's flags. Also ensures that all non-negative interface fds are
     * unique.
     */
    void add_child(Interface *P);
    
    /**
     * @param P the Interface to be removed.
     * @param deref dereference the interface P if removed
     * Removes the specified Interface from the list of active interfaces.
     * If deref is asserted, the interface will be dereferenced after
     * being removed. This allows delete_child() to delay the dereference
     * until the PendingDeletion queue is emptied.
     * @return true if the specified interface was removed.
     */
    bool remove_child(Interface *P, bool deref = true);
    
    /**
     * @param P the Interface to be deleted.
     * Removes the specified Interface from the list of active interfaces,
     * and marks it for deletion at a later time.
     */
    void delete_child(Interface *P);
    
    /**
     * Move all children onto PendingDeletion queue.
     */
    void delete_children();
    
    /**
     * dereference() all Interfaces on the PendingDeletion queue.
     * @param final If asserted, will report an error if any queued
     * Interface has a non-zero reference count.
     */
    void clear_delete_queue(bool final=false);
    
    /**
     * Sets a bit in the global flags word. Selectees can set
     * a corresponding bit in their flags word to request
     * notification when the bit gets set. The function
     * Selector::gflag(gflag_index) returns the bit that
     * corresponds to set_gflag(gflag_index). gflag_index
     * can take on values from 0 to 8*sizeof(int)-4.
     * @param gflag_index non-negative gflag index.
     */
    void set_gflag( unsigned gflag_index );
    /**
     * Loops waiting on select(), using the fds and flags of
     * each Interface registered via add_child(). When select()
     * indicates that an fd is ready, the corresponding Interface's
     * ProcessData() method is invoked with the flag value indicating
     * what action is ready.
     */
    void event_loop();
    /**
     * Causes event_loop() to exit on each iteration
     */
    void set_loop_exit();
    /**
     * Setup to process signals during pselect().
     * @param sig The signal number
     * @param func The function handler
     */
    void signal(int sig, void (*func)(int sig));
    /**
     * @return A pointer to the sigset_t struct defining the
     * signals that should be blocked outside of pselect.
     * If application is multi-threaded, threads that are not
     * running the event_loop() should block these signals to
     * ensure that they are handled by the event_loop() thread.
     */
    inline sigset_t *get_blockset() { return &blockset; }
    
    /** 
     * A bitmapped register indicating which signals have been 
     * seen by asynchronous signal-handlers. event_loop uses
     * this field to determine which interfaces to route the
     * serialized signal to.
     */
    static uint32_t signals_seen;
    
  private:
    /** The list of child interfaces */
    InterfaceList S;
    /** List of interfaces pending deletion */
    InterfaceList PendingDeletion;
    
    /**
     * Locates the position in list S of the Interface with the matching fd.
     * Will not match anything if fd < 0.
     * @param fd The fd we are searching for
     * @return The position in S of the Interface with the matching fd.
     */
    InterfaceList::iterator find_child_by_fd(int fd);
    bool children_changed;
    std::atomic<int> gflags;
    /**
     * Virtual method called whenever select() returns 0. The default does nothing,
     * but it can be overridden.
     * @return non-zero if the event loop should terminate.
     */
    virtual int ProcessTimeout();
    /**
     * Virtual method to allow Selector to bid on the select() timeout
     * along with the Selectee children. The minimum timeout value is used.
     * @return a Timeout * indicating the requested timeout value or 0.
     */
    virtual Timeout *GetTimeout();
    bool loop_exit;
    sigset_t blockset;
    sigset_t runset;
};

}

extern "C" {
  void loop_signal_handler(int sig);
}

#endif
