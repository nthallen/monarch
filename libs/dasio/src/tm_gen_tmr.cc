/**
 * tm_gen_tmr Object definitions
 */
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/timerfd.h>
#include "dasio/tm.h"
#include "dasio/tm_gen_cmd.h"
#include "dasio/tm_gen_tmr.h"
#include "nl.h"
#include "nl_assert.h"

namespace DAS_IO {

tm_gen_tmr::tm_gen_tmr(tm_generator *tm_gen)
    : tm_tmr(), tmg(tm_gen) {
  nl_assert(tmg);
  tmg->ELoop.add_child(this);
}

bool tm_gen_tmr::protocol_input() {
  report_ok(nc);
  tmg->service_row_timer();
  return false;
}

}
