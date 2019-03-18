#ifndef RESMGR_H_
#define RESMGR_H_

//#include <sys/iofunc.h> //QNX
//#include <sys/dispatch.h> //QNX
//#include <sys/resmgr.h> //QNX
#include <list>
#include "dasio/server.h"

/**
  tm_gen_client is a virtual base class for clients of tm_gen_dispatch. The main service provided is quit coordination.
  ready_to_quit() virtual function should return true if client is ready to quit. This will remove the client from the
  tm_gen_dispatch's list, so a subsequent detach() is unnecessary. Hence ready_to_quit() should set the dispatch member to
  NULL before returning a non-zero value.
  As a rule, clients should shut down all of their functions prior to returning. For devices, that means resmgr_detach()
  
  As written, this is probably a bad design, since tm_gen_dispatch::client_add is called with a partially constructed client.
  In a multi-threaded environment, there is a potential for harm.
*/
class tm_gen_client : public DAS_IO::Serverside_client {
  public:
    tm_gen_client();
    virtual ~tm_gen_client(); // calls detach() if necessary
    //void attach(tm_gen_dispatch *disp); // add to dispatch list
    //void detach(); // remove from dispatch list
    virtual int ready_to_quit()= 0;
    //tm_gen_dispatch *dispatch;
};

/* class tm_gen_dispatch {
  public:
    dispatch_t *dpp;
    tm_gen_dispatch();
    ~tm_gen_dispatch();
    void client_add(tm_gen_client *clt);
    void client_rm(tm_gen_client *clt);
    void Loop();
    void ready_to_quit();
  private:
    int quit_received;
    int all_closed();
    dispatch_context_t *single_ctp;
    std::list<tm_gen_client *> clients;
}; */

#endif /*RESMGR_H_*/
