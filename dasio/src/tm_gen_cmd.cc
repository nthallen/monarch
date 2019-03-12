#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "dasio/tm_gen_Resmgr.h"
#include "dasio/tm_gen_cmd.h"
#include "nl.h"
#include "nl_assert.h"
#include "dasio/tm.h"

static tm_gen_cmd *Cmd;
resmgr_connect_funcs_t tm_gen_cmd::connect_funcs;
resmgr_io_funcs_t tm_gen_cmd::io_funcs;
iofunc_attr_t tm_gen_cmd::cmd_attr;

/**
 * buf is guaranteed to be nul-terminated
 * We will strip any trailing newlines before forwarding to tmg->execute()
 */
int tm_gen_cmd::execute(char *buf) {
  assert(buf != 0);
  int len = strlen(buf);
  while ( len > 0 && isspace(buf[len-1]) )
    buf[--len] = '\0';
  return tmg->execute(buf);
}

tm_gen_cmd::tm_gen_cmd(tm_generator *tm_gen) : tm_gen_dispatch_client() {
  tmg = tm_gen;
}

void tm_gen_cmd::attach() {
  dispatch_t *dpp = tmg->dispatch->dpp;
  if (Cmd != NULL)
      msg(3, "Only one tm_gen_cmd instance allowed");
 
  // This is our write-only command interface
  resmgr_attr_t resmgr_attr;
  memset(&resmgr_attr, 0, sizeof(resmgr_attr));
  resmgr_attr.nparts_max = 1;
  resmgr_attr.msg_max_size = tm_gen_CMD_BUFSIZE+1;

  iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs,
      _RESMGR_IO_NFUNCS, &io_funcs );
  io_funcs.write = tm_gen_cmd_io_write;
  
  iofunc_attr_init( &tm_gen_cmd::cmd_attr, S_IFNAM | 0222, 0, 0 ); // write-only
  const char *wr_devname = tm_dev_name( "tm_gen/cmd" );
  dev_id = resmgr_attach( dpp, &resmgr_attr, wr_devname, _FTYPE_ANY, 0,
                    &tm_gen_cmd::connect_funcs, &tm_gen_cmd::io_funcs, &tm_gen_cmd::cmd_attr );
  if ( dev_id == -1 )
    report_err( /*3, */"Unable to attach name %s: errno %d", wr_devname, errno );
 
  Cmd = this;
  tm_gen_dispatch_client::attach(tmg->dispatch); // Now get in on the quit loop
}

tm_gen_cmd::~tm_gen_cmd() { }

int tm_gen_cmd_io_write( resmgr_context_t *ctp,
         io_write_t *msg, RESMGR_OCB_T *ocb ) {
  int status, msgsize;
  char buf[tm_gen_cmd::TM_GEN_CMD_BUFSIZE+1];

  status = iofunc_write_verify(ctp, msg, (iofunc_ocb_t *)ocb, NULL);
  if ( status != EOK )
    return status;

  if ((msg->i.xtype &_IO_XTYPE_MASK) != _IO_XTYPE_NONE )
    return ENOSYS;

  msgsize = msg->i.nbytes;
  if ( msgsize > tm_gen_cmd::TM_GEN_CMD_BUFSIZE )
    return E2BIG;


  resmgr_msgread( ctp, buf, msgsize, sizeof(msg->i) );
  buf[msgsize] = '\0';

  // Handle the message
  // Reply to sender before handling the command to
  // reduce possibility of deadlock.
  MsgReply(ctp->rcvid, msg->i.nbytes, NULL, 0);
  Cmd->execute(buf);
  return _RESMGR_NOREPLY;

  //_IO_SET_WRITE_NBYTES( ctp, msg->i.nbytes );
  // return EOK;
}

/** tm_gen_cmd::ready_to_quit() returns true if we are ready to terminate. For tm_gen/cmd, that means all writers
  have closed their connections and we have detached the device.
*/
int tm_gen_cmd::ready_to_quit() {
  // unlink the name
  if ( dev_id != -1 ) {
    int rc = resmgr_detach( dispatch->dpp, dev_id, _RESMGR_DETACH_PATHNAME );
    if ( rc == -1 )
      report_err( 2, "Error returned from resmgr_detach: %d", errno );
    dev_id = -1;
  }
  // ### Need to make sure my tm_generator knows it's time to quit
  return cmd_attr.count == 0;
}
