/**
 * \file loop.h
 * Header for the Harvard Link Engineering Data Acquisition System I/O library
 */
#ifndef DAS_IO_LOOP_H_INCLUDED
#define DAS_IO_LOOP_H_INCLUDED
#include <string>
#include <list>
#include <atomic>
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
     * Removes the specified Interface from the list of active interfaces.
     * @return true if the specified interface was removed.
     */
    bool remove_child(Interface *P);
    
    /**
     * @param P the Interface to be deleted.
     * Removes the specified Interface from the list of active interfaces,
     * and marks it for deletion at a later time.
     */
    void delete_child(Interface *P);
    
    // I don't think these functions are used currently, but they may become
    // relevant in a server. In that case, though, I feel as though the interface
    // should have an opportunity to cleanup before the child is deleted.
    // I'll defer the definition until I come across the application.
    // void delete_child(int fd_in);
    // int update_flags(int fd_in, int flag);

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
};

}

#endif
