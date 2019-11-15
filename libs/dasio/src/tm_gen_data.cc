// Include tm_gen_data.h first here to make sure our definition of
// IOFUNC_ATTR_T gets used in this file
#include "dasio/tm_gen_data.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "nl.h"
#include "nl_assert.h"
#include "dasio/tm.h"

bool tm_gen_data::funcs_initialized = false;
bool tm_gen_data::quitting = false;

extern "C" {

}

tm_gen_data::tm_gen_data(const char *name_in, void *data,
	 int data_size, int synch)
    : DAS_IO::Serverside_client() {
  name = name_in;
  dptr = data;
  dsize = data_size;
  synched = synch;
  stale_count = 0;
}

tm_gen_data::~tm_gen_data() {}

// The semantics of write are a bit non-standard. I use blocking I/O
// purely as a synchronization technique. In all contexts, a write
// that gets here is immediately processed, but depending on
// the synchronization flag (set in the TMC source) and the nonblock
// value (set by the client), we may not reply immediately to the
// client.
bool tm_gen_data::protocol_input() {
  //data_attr.written = synched;
  
  if (nc != dsize) {
    msg(MSG_FATAL, "%s: received %d bytes, expected %d", iname, nc, dsize);
  }
  memcpy(dptr, buf, dsize);
  report_ok(nc);
  
  return false;
}

void tm_gen_data::synch() {
  data_attr.written = false;
  if (blocked) {
    MsgReply(blocked->rcvid, blocked->msgsize, 0, 0);
    blocked = 0;
  }
  if (IOFUNC_NOTIFY_OUTPUT_CHECK( data_attr.notify, 1 ) )
    iofunc_notify_trigger(data_attr.notify, 1, IOFUNC_NOTIFY_OUTPUT);
}

int tm_gen_data::stale(int max_stale) {
  int rv = stale_count;
  if ( stale_count < INT_MAX ) ++stale_count;
  if ( rv > max_stale ) rv = max_stale;
  return rv;
}

int tm_gen_data_io_write( resmgr_context_t *ctp,
         io_write_t *msg, IOFUNC_OCB_T *ocb ) {
  int status, nonblock;

  status = iofunc_write_verify(ctp, msg, (iofunc_ocb_t *)ocb, &nonblock);
  if ( status != EOK )
    return status;

  if ((msg->i.xtype &_IO_XTYPE_MASK) != _IO_XTYPE_NONE )
    return ENOSYS;

  return ocb->hdr.attr->tmgd->io_write(ctp, ocb, nonblock);
}

int tm_gen_data_io_notify( resmgr_context_t *ctp,
         io_notify_t *msg, IOFUNC_OCB_T *ocb ) {
  IOFUNC_ATTR_T *wr_attr = ocb->hdr.attr;
  int trig = 0;
  if (!wr_attr->written) trig |= _NOTIFY_COND_OUTPUT;
  return(iofunc_notify(ctp, msg, wr_attr->notify, trig, NULL, NULL ));
}

int tm_gen_data_io_close_ocb(resmgr_context_t *ctp, void *rsvd,
			  IOFUNC_OCB_T *ocb) {
  IOFUNC_ATTR_T *wr_attr = ocb->hdr.attr;
  iofunc_notify_remove(ctp, wr_attr->notify);
  return(iofunc_close_ocb_default(ctp, rsvd, &ocb->hdr));
}

/** tm_gen_data::ready_to_quit() returns true if we are ready to terminate. For tm_gen/data, that means all writers
  have closed their connections and we have detached the device.
*/
int tm_gen_data::ready_to_quit() {
  // unlink the name
  quitting = true;
  if ( dev_id != -1 ) {
    int rc = resmgr_detach( dispatch->dpp, dev_id, _RESMGR_DETACH_PATHNAME );
    if ( rc == -1 )
      report_err(/* 2, */"Error returned from resmgr_detach: %d", errno );
    dev_id = -1;
  }
  if ( data_attr.attr.count )
    msg( MSG_DEBUG, "Still waiting for tm_gen/data/%s", name );
  return data_attr.attr.count == 0;
}
