/** @file cic_transmit.cc Defines cic_transmit() */
#include "dasio/cmd_writer.h"
// #include <stdlib.h>
#include "nl.h"
#include "cmdalgo.h"

typedef struct cmd_lev {
  struct cmd_lev *prev;
  short int pos; /* offset in buffer */
  cmd_state state;
} cmd_level;

static cmd_level *cur = NULL;
static short int curpos = 0;
static char cmdbuf[CMD_INTERP_MAX];

void cic_transmit(char *buf, int n_chars, int transmit) {
  int c;
  cmd_level *cl, *cl_save;

  for (; n_chars > 0; n_chars--) {
    c = *buf++;
    if (c == 0) {
      if (n_chars == 1) c = '\n';
      else c = ' ';
    }
    cmdbuf[curpos++] = c;
    if (curpos > CMD_INTERP_MAX)
      nl_error(3, "Maximum transmissable command length exceeded");
  }
  if (transmit) {
    cmdbuf[curpos] = '\0';
    ci_sendcmd(DAS_IO::Cmd_Send, cmdbuf);
  }
  for (cl = cur; cl != NULL && cmd_check(&cl->state); cl = cl->prev);
  if (cl == NULL) {
    cl = (cmd_level *)new_memory(sizeof(cmd_level));
    cl->prev = cur;
    cl->pos = curpos;
    cmd_report(&cl->state);
    cur = cl;
  } else while (cur != cl) {
    cl_save = cur;
    cur = cur->prev;
    free(cl_save);
  }
  curpos = cur->pos;
}
