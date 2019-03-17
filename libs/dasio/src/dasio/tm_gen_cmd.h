#ifndef TM_GEN_CMD_H
#define TM_GEN_CMD_H

#include <signal.h>
#include "tm_gen.h"

class tm_generator;

class tm_gen_cmd : public DAS_IO::Serverside_client() {
  private:
    int dev_id;
    tm_generator *tmg;
    static iofunc_attr_t cmd_attr;
        static resmgr_connect_funcs_t connect_funcs;
        static resmgr_io_funcs_t io_funcs;
  public:
    tm_gen_cmd(tm_generator *tm_gen);
    ~tm_gen_cmd();
    void attach(); // add to dispatch list
    int execute(char *buf);
    int ready_to_quit(); // virtual function of tm_gen_dispatch_client
    static int const tm_gen_CMD_BUFSIZE = 80;
};

extern "C" {
    int tm_gen_cmd_io_write(
        resmgr_context_t *ctp,
	io_write_t *msg,
	RESMGR_OCB_T *ocb );
}

#endif

