/* tma.cc Defines TMA support services */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "dasio/tmctime.h"
#if HAVE_NL_CONS_H
#include "nl_cons.h"
#endif
#include "dasio/tma.h"
#include "dasio/tmctime.h"
#include "dasio/cmd_writer.h"
#include "oui.h"
#include "nl.h"

using namespace DAS_IO;

char rcsid_tma_c[] = 
  "$Header$";

tma_prtn *tma_partitions = NULL;
long int tma_runbasetime = 0L;
int tma_is_holding = 0;
static int playback = 0;

/*
>Command Text Goes Here
Initialize        Holding   Next: 00:00:00  State: 00:00:00  Run: 00:00:00
SNAME             HOLDING   NEXT  NEXTTIME  STATE  STATETIME RUN  RUNTIME
*/

void tma_time(tma_prtn *p, unsigned int col, long int t) {
  char ts[9];
  int hh, h;
  
  if (p->row >= 0) {
    #if HAVE_NL_CONS_H
	ts[8] = '\0';
	hh = t % 60;
	h = hh % 10;
	ts[7] = h+'0';
	ts[6] = hh/10 + '0';
	ts[5] = ':';
	t /= 60;
	hh = t % 60;
	h = hh % 10;
	ts[4] = h+'0';
	ts[3] = hh/10 + '0';
	ts[2] = ':';
	t /= 60;
	hh = t % 100;
	h = hh % 10;
	ts[1] = h+'0';
	ts[0] = hh/10 + '0';
	nlcon_display(p->console, p->row + 1, col, ts, TMA_ATTR);
    #endif
  }
}

static void update_holding(tma_prtn *p) {
  #if HAVE_NL_CONS_H
  if (p->row >= 0)
	nlcon_display(p->console, p->row + 1, HOLDING_COL,
	  tma_is_holding ? "Holding" : "       ", HOLDING_ATTR);
  #endif
}

/** Copied from arp-das/tmlib/src/cic.c, 2020-02-04 */
void ci_settime( int32_t time ) {
  Cmd_writer::Cmd->ci_time = time;
}

/** Copied from arp-das/tmlib/src/cic.c, 2020-02-04 */
const char *ci_time_str() {
  static char buf[11];
  int hour, min, sec;
  int32_t time = Cmd_writer::Cmd->ci_time;

  if ( ! playback || time == 0 ) return "";
  if ( time < 0 ) return "-1: ";
  time = time % ( 24 * 3600L );
  hour = time / 3600;
  time = time % 3600;
  min = time / 60;
  sec = time % 60;
  sprintf( buf, "%02d:%02d:%02d: ", hour, min, sec );
  return buf;
}

void tma_hold(int hold) {
  int i, update;

  update = 0;
  if (hold) {
	if (! tma_is_holding) {
	  tma_is_holding = 1;
	  update = 1;
	}
  } else {
	if (tma_is_holding) {
	  tma_is_holding = 0;
	  update = 1;
	}
  }
  #if HAVE_NL_CONS_H
  if (update)
	for (i = 0; i < tma_n_partitions; i++) update_holding(&tma_partitions[i]);
  #endif
}

void tma_new_state(unsigned int partition, const char *name) {
  tma_prtn *p;

  if (partition < tma_n_partitions) {
	int log_level = -2;
	if ( *name == '_' ) {
	  name++;
	  log_level--;
	}
	msg( log_level, "%sEntering State %s", ci_time_str(), name );
	p = &tma_partitions[partition];
	p->basetime = (tma_runbasetime == 0L) ? 0L : itime();
	p->lastcheck = p->basetime;
	p->nexttime = 0;
	#if HAVE_NL_CONS_H
	if (p->row >= 0) {
	  nlcon_display(p->console, p->row + 1, STATE_COL,
		"  State: ", TMA_ATTR);
	  nlcon_display(p->console, p->row + 1, RUN_COL,
		"  Run: ", TMA_ATTR);
	  nlcon_display(p->console, p->row + 1, SNAME_COL,
		"                            Next:         ", TMA_ATTR);
	  nlcon_display(p->console, p->row + 1, SNAME_COL,
		name, TMA_ATTR);
	  nlcon_display(p->console, p->row + 1, RUNTIME_COL,
		RUNTIME_STRING, TMA_ATTR);
	  update_holding(p);
	  tma_time(p, STATETIME_COL, 0);
	}
	#endif
  }
}

/* specify the next significant time for a partition */
void tma_next_cmd(unsigned int partn, const char *next_cmd) {
  #if HAVE_NL_CONS_H
  tma_prtn *p;
  const char *txt;
  int len;
  
  if (partn < tma_n_partitions) {
	p = &tma_partitions[partn];
	if (p->row >= 0) {
	  nlcon_display(p->console, p->row, 0, ">", TMA_ATTR);
	  nlcon_display(p->console, p->row, 1,
		"                                        "
		"                                       ", CMD_ATTR);
	  len = strlen(next_cmd);
	  if (len > 79) txt = next_cmd + (len - 79);
	  else txt = next_cmd;
	  nlcon_display(p->console, p->row, 1, txt, CMD_ATTR);
	}
  }
  #endif
}

void tma_init_options(int argc, char **argv) {
  int c, con_index, part_index;

  // tma_partitions = malloc(sizeof(tma_prtn) * tma_n_partitions);
  tma_partitions = (tma_prtn *) new_memory(sizeof(tma_prtn) * tma_n_partitions);
  if (tma_partitions == NULL)
	msg(3, "No memory for partitions table");
  for (c = 0; c < tma_n_partitions; c++) {
	tma_partitions[c].row = -1;
	tma_partitions[c].cmds = NULL;
	tma_partitions[c].next_cmd = -1;
	tma_partitions[c].waiting = 0;
	tma_partitions[c].next_str = NULL;
  }

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  con_index = 0;
  part_index = 0;
  while ((c = getopt(argc, argv, opt_string)) != -1) {
	switch (c) {
	  #if HAVE_NL_CONS_H
	  case 'a': /* move on to the next console */
		con_index++;
		break;
	  case 'r':
		if (part_index < tma_n_partitions) {
		  tma_partitions[part_index].row = atoi(optarg);
		  tma_partitions[part_index].console = con_index;
		  part_index++;
		}
		break;
	  #endif
	  case '?':
		msg(3, "Unrecognized Option -%c", optopt);
	}
  }
}

void tma_init_state( int partno, tma_state *cmds, const char *name ) {
  tma_prtn *p;

  if ( partno < tma_n_partitions ) {
    /* tma_new_state() sets part basetime, outputs STATETIME
       Does *not* set RUNTIME or NEXTTIME or next command area
       basetime is set only if tma_basetime is non-zero (set
       in tma_process first time after TM starts). lastcheck is 
       set to basetime. partno, name );
     */
    tma_new_state( partno, name );
    p = &tma_partitions[partno];
    p->cmds = cmds;
    p->next_cmd = 0;
    p->waiting = 0;
    p->lastcheck = p->basetime - 1;
    if ( p->basetime == 0L && p->cmds != 0 ) {
      /* Issue start-up commands (T==0, ">") */
      for (;;) {
        cmds = &p->cmds[p->next_cmd];
        if ( cmds->dt != 0 || cmds->cmd[0] != '>' )
          break;
        p->next_cmd++;
        if ( cmds->cmd[1] == '_' ) ci_sendcmd(Cmd_Send_Quiet, cmds->cmd+2);
        else ci_sendcmd(Cmd_Send, cmds->cmd+1);
      }
    }
  }
}

/* tma_process returns 0 when no more action is required for any
   partition at the present time (now). Otherwise it returns
   a positive integer which is an index into case statement
   generated by tmcalgo for validating states. */
int tma_process( long int now ) {
  int partno, success, state_case, Rpartno;
  tma_prtn *p;
  long int dt, pdt, timeout, lastcheck;
  const char *cmd;
  
  if (tma_runbasetime == 0L) {
    unsigned int i;

    tma_runbasetime = now;
    for (i = 0; i < tma_n_partitions; i++) {
      tma_partitions[i].basetime = now;
      tma_partitions[i].lastcheck = now-1;
    }
  }
  for ( partno = 0; partno < tma_n_partitions; partno++ ) {
    p = &tma_partitions[ partno ];
    if ( now != p->lastcheck ) {
      lastcheck = p->lastcheck;
      if ( lastcheck < p->basetime )
        lastcheck = p->basetime;
      if ( p->waiting > 0 ) {
        dt = now - lastcheck;
        if ( dt >= p->waiting ) {
          p->waiting = 0;
          p->next_cmd++;
        }
      }
      if ( p->waiting == 0 && tma_is_holding == 0 ) {
        dt = now - p->basetime;
        if ( p->cmds != 0 && p->next_cmd >= 0 ) {
          while ( p->waiting == 0 ) {
            pdt = p->cmds[p->next_cmd].dt;
            cmd = p->cmds[p->next_cmd].cmd;
            if ( pdt == -1 ) {
              p->next_cmd = -1;
              p->nexttime = 0;
              break;
            } else if ( pdt > dt ) {
              if ( p->nexttime != pdt ) {
                p->nexttime = pdt;
                if ( ( p->next_str == 0 || *p->next_str == '\0' )
                      && *cmd == '>' )
                  p->next_str = cmd+1;
              }
              break;
            } else {
              p->next_cmd++;
              switch( *cmd ) {
                case '>':
                  if ( cmd[1] == '_' )
                    ci_sendcmd(Cmd_Send_Quiet, cmd+2);
                  else
                    ci_sendcmd(Cmd_Send, cmd+1);
                  p->next_str = "";
                  break;
                case '"':
                  p->next_str = cmd;
                  break;
                case '#':
                  return atoi( cmd+1 );
                case '?':
                  if ( sscanf( cmd+1, "%d,%ld,%d",
                    &success, &timeout, &state_case ) != 3 )
                    msg( 4, "Error reading hold command\n" );
                  if ( timeout > 0 )
                    timeout += pdt + p->basetime - lastcheck;
                  p->waiting = timeout;
                  p->next_cmd--;
                  if ( state_case > 0 ) return state_case;
                  break;
                case 'R':
                  if ( sscanf( cmd+1, "%d,%d", &Rpartno,
                        &state_case ) != 2 )
                    msg( 4, "Error reading Resume command\n" );
                  tma_succeed( Rpartno, -state_case );
                  if ( Rpartno < partno ) return -1;
                  break;
                default:
                  msg( 1, "Unknown cmd char %c in tma_process", *cmd );
              }
            }
          }
        }
      }
    }
  }
  for ( partno = 0; partno < tma_n_partitions; partno++ ) {
    p = &tma_partitions[ partno ];
    lastcheck = p->lastcheck;
    if ( lastcheck < p->basetime )
      lastcheck = p->basetime;
    dt = now - lastcheck;
    if ( dt != 0 ) {
      if ( p->waiting != 0 || tma_is_holding != 0 ) {
        p->basetime += dt;
        if ( p->waiting > dt ) {
          p->waiting -= dt;
        } else if ( p->waiting > 0 )
          p->waiting = 0;
      }
    }
    if ( now != p->lastcheck ) {
      p->lastcheck = now;
      if ( p->row >= 0 ) {
        if ( p->next_str != 0 ) {
          tma_next_cmd( partno, p->next_str );
          p->next_str = NULL;
        }
        tma_time( p, RUNTIME_COL, now - tma_runbasetime );
        tma_time( p, STATETIME_COL, now - p->basetime );
        pdt = p->nexttime;
        switch ( pdt ) {
          case -1: continue;
          case 0:
            pdt = 0;
            p->nexttime = -1;
            break;
          default:
            pdt += p->basetime - now;
            break;
        }
        tma_time( p, NEXTTIME_COL, pdt );
      }
    }
  }
  return 0; /* Nothing left to do */
}

void tma_succeed( int partno, int statecase ) {
  tma_prtn *p;
  int success, state_case, res_case;
  long int timeout;
  const char *cmd;

  if ( partno < 0 || partno >= tma_n_partitions )
    msg( 4, "Invalid partno in tma_succeed" );
  p = &tma_partitions[ partno ];
  if ( p->cmds != 0 && p->next_cmd >= 0 ) {
    cmd = p->cmds[p->next_cmd].cmd;
    if ( cmd != 0 && *cmd == '?' ) {
      int n_args = sscanf( cmd+1, "%d,%ld,%d,%d",
          &success, &timeout, &state_case, &res_case );
      if ( n_args < 3 ) msg( 4, "Error re-reading hold command\n" );
      if ( statecase > 0 && state_case != statecase )
        msg( 1, "Different statecase active in tma_succeed" );
      else if ( statecase < 0 &&
                ( n_args < 4 || -statecase != res_case) ) {
        if ( n_args < 4 )
          msg( 1, "Resume not compatible with this version" );
        else
          msg( -3, "Resume(%d,%d): other state is holding", partno,
                      -statecase );
      } else {
        p->waiting = 0;
        p->next_cmd += success;
      }
      return;
    }
  }
  if ( statecase < 0 )
    msg( -3, "Resume(%d,%d): Specified state not holding",
        partno, -statecase );
  else msg( -3, "Hold(%d,%d) not active in tma_succeed",
        partno, statecase );
}
