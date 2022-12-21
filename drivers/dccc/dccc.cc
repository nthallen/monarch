/*
 * Discrete command card controller program.
 *
 * Originally developed in the late 1980s
 * Modified by Eil July 1991 for QNX 2.
 * Ported to QNX 4 by Eil 4/15/92.
 * Ported to QNX 6 by Nort 8/23/08.
 * Ported to Monarch by Nort 12/15/22.
 */

/* header files */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include "subbus_mig.h"
#include "subbus_ID.h"
#include "disc_cmd.h"
#include "nl.h"
#include "nl_assert.h"
#include "oui.h"
// #include "dasio/tm.h"

/* functions */
void init_cards(void);
void set_line(int port, int mask), reset_line(int port, int mask);
void sel_line(int port, int mask, int value);
void read_commands(void);
int get_type(char *buf, int *type), get_line(FILE *fp, char *buf);
// int DCCC_Done = 0;

/* global variables */
struct cfgcmd {
  unsigned int address;
  unsigned int data;
} *cfg_cmds;

struct port {
  int sub_addr;
  int defalt;
  int value;
} *ports;

struct cmd {
  int type;
  int port;
  int mask;
  int value;
} *cmds;

int init_fail = 0;
static int sb_syscon = 0;
static int use_cmdstrobe = 0;
static char cmdfile[FILENAME_MAX] = "dccc_cmd.txt";
static int n_cfgcmds = 0, n_ports = 0, n_cmds = 0;


void dccc_init_options( int argc, char **argv ) {
  int i;
  
  /* process args */
  opterr = 0;
  optind = OPTIND_RESET;
  do {
    i = getopt(argc,argv,opt_string);
    switch (i) {
      case 'f': strncpy(cmdfile, optarg, FILENAME_MAX-1); break;
      case 'i': init_fail = 1; break;
      case '?': msg(4,"Invalid option -%c",optopt);
      default:  break;
    }
  } while (i!=-1);
}

int main(int argc, char **argv) {
  oui_init_options( argc, argv );
  msg( 0, "Startup" );

  /* subbus */
  subbus_sf subfunc{subbus_sf(subbus_subfunction)};
  if (subfunc == subbus_sf::SYSCON || 
      subfunc == subbus_sf::SYSCON104 ||
      subfunc == subbus_sf::DACS) sb_syscon = 1;
  if (subbus_features & SBF_CMDSTROBE) use_cmdstrobe = 1;
  else if (sb_syscon) 
    msg(MSG_WARN,"Out of date resident subbus library: please upgrade");
  // Limitation imposed during Monarch port:
  nl_assert(sb_syscon && use_cmdstrobe);
  
  read_commands();
  init_cards();
  operate();
  msg( -1, "Shutdown" );
  return 0;
}

void process_pcmd(cmd_t *pcmd) {
  int dccc_cmd_type;

  dccc_cmd_type = cmds[pcmd->cmds[0].cmd].type;
  execute_pcmd( pcmd, 0 );
  if (dccc_cmd_type == STRB) {
    /* optionally add a delay here */
    usleep(10*1000);
    execute_pcmd( pcmd, 1 );
  }
}

void execute_pcmd( cmd_t *pcmd, int clr_strobe ) {
  uint16_t cmd_idx = pcmd->cmds[0].cmd;
  uint16_t value;
  int dccc_cmd_type = cmds[cmd_idx].type;
  int cmd_ok = 1;
  static uint16_t str_cmd;
  int i;
  
   /* reset the strobe if necessary or define str_cmd */
  if (dccc_cmd_type == STRB) {
    if (clr_strobe) {
      set_cmdstrobe(0);
      if (cmd_idx != str_cmd) msg(MSG_WARN, "Bad strobe sequence");
    } else str_cmd = cmd_idx;
  }

  for ( i = 0; cmd_ok && i < pcmd->n_cmds; i++ ) {
    cmd_idx = pcmd->cmds[i].cmd;
    value = pcmd->cmds[i].value;

    switch (dccc_cmd_type) {
    case STRB:
      if (clr_strobe) {
        msg(MSG_DEBUG, "STRB reset: PORT %03X mask %04X command index %d",
          ports[cmds[cmd_idx].port].sub_addr, cmds[cmd_idx].mask, cmd_idx);
        reset_line(cmds[cmd_idx].port, cmds[cmd_idx].mask);
      } else {
        msg(MSG_DEBUG,"STRB set: port %03X mask %04X command index %d",
          ports[cmds[cmd_idx].port].sub_addr, cmds[cmd_idx].mask,cmd_idx);
        set_line(cmds[cmd_idx].port, cmds[cmd_idx].mask);
      }
      break;
    case STEP:
      set_line(cmds[cmd_idx].port, cmds[cmd_idx].mask);
      reset_line(cmds[cmd_idx].port, cmds[cmd_idx].mask);
      break;
    case SET:
      msg(MSG_DEBUG,
        "SET: PORT %03X, mask %04X, value %04X, command index %d",
        ports[cmds[cmd_idx].port].sub_addr, cmds[cmd_idx].mask,
        value, cmd_idx);
      if (cmds[cmd_idx].mask)
        if (value) set_line(cmds[cmd_idx].port, cmds[cmd_idx].mask);
        else reset_line(cmds[cmd_idx].port, cmds[cmd_idx].mask);
      else set_line(cmds[cmd_idx].port, value);
      break;
    case SELECT:
      // For historical reasons, SELECT uses negative logic
      // in the value arg
      msg(MSG_DEBUG,
        "SELECT: PORT %03X, mask %04X, value %04X, command index %d",
        ports[cmds[cmd_idx].port].sub_addr, cmds[cmd_idx].mask,
        value, cmd_idx);
      sel_line(cmds[cmd_idx].port, cmds[cmd_idx].mask, ~value);
      break;
    case UNSTRB:
      value = cmds[cmd_idx].value;
      msg(MSG_DEBUG,
        "UNSTRB: PORT %03X, mask %04X, value %04X, command index %d",
        ports[cmds[cmd_idx].port].sub_addr, cmds[cmd_idx].mask,
        value, cmd_idx);
      sel_line(cmds[cmd_idx].port, cmds[cmd_idx].mask, value);
      break;
    case SPARE: cmd_ok = 0;
      msg(MSG_WARN,"command %d of type SPARE received", cmd_idx);
      break;
    default: cmd_ok = 0;
      msg(MSG_WARN, "command %d: unknown command type %d received",
        cmd_idx, cmds[cmd_idx].type);
    } /* switch */
  }

  if (dccc_cmd_type == STRB && !clr_strobe) {
    set_cmdstrobe(1);
  }
}	/*execute_pcmd */


/* functions */

/* return 1 on success, 0 on error */
void init_cards(void) {
  int i;
  for (i = 0; i < n_cfgcmds; i++)
    if (!write_ack(cfg_cmds[i].address, cfg_cmds[i].data))
      msg(init_fail ? MSG_EXIT_ABNORM : MSG_WARN,"No ack for configuration command at address %#X",cfg_cmds[i].address);
  for (i = 0; i < n_ports; i++)
    if (!write_ack(ports[i].sub_addr, ports[i].defalt))
      msg(init_fail ? MSG_EXIT_ABNORM : MSG_WARN,"No ack at port address %#X",ports[i].sub_addr);
  /* Set Command Strobe Inactive */
  set_cmdstrobe(0);
  /* Enable Commands */
  set_cmdenbl(1);
}

void set_line(int port, int mask) {
  ports[port].value |= mask;
  write_subbus(ports[port].sub_addr, ports[port].value);
}

void old_line(int port) {
  ports[port].value = read_subbus(ports[port].sub_addr);
}

void sel_line(int port, int mask, int value) {
  ports[port].value &= ~mask;
  ports[port].value |= (mask & value);
  write_subbus(ports[port].sub_addr, ports[port].value);
}

void reset_line(int port, int mask) {
  ports[port].value &= ~mask;
  write_subbus(ports[port].sub_addr, ports[port].value);
}

/* No special commands for the time being */

void read_commands(void) {
  FILE *fp;
  char buf[128], *p;
  int i;

  if ((fp = fopen(cmdfile, "r")) == NULL)
    msg(MSG_EXIT_ABNORM,"error opening %s",cmdfile);

  if (get_line(fp, buf) || (sscanf(buf, "%d", &n_cfgcmds) != 1))
    msg(MSG_EXIT_ABNORM,"error getting number of config commands");

  cfg_cmds = (struct cfgcmd *) malloc(n_cfgcmds * sizeof(struct cfgcmd));

  /* Configuration commands */
  for (i = 0; i < n_cfgcmds; i++)
    if (get_line(fp, buf) ||
        (sscanf(buf, "%x,%x", &cfg_cmds[i].address, &cfg_cmds[i].data) != 2))
      msg(MSG_EXIT_ABNORM, "error getting configuration command %d",i);

  if (get_line(fp, buf) || (sscanf(buf, "%d", &n_ports) != 1))
    msg(MSG_EXIT_ABNORM, "error getting number of ports");

  ports = (struct port *) malloc(n_ports * sizeof(struct port));

  /* Port information */
  for (i = 0; i < n_ports; i++) {
    if ((get_line(fp, buf))) 
      msg(MSG_EXIT_ABNORM, "error getting port %d info",i);
    switch(sscanf(buf, "%x,%x", &ports[i].sub_addr, &ports[i].defalt)) {
    case 2: ports[i].value = 0; break;
    /*** if a defalt value is not scanned, set it and value to hardware ***/
    case 1: old_line(i); ports[i].defalt = ports[i].value; break;
    case 0:
    case EOF: msg(MSG_EXIT_ABNORM, "error getting port %d info",i);
    }
  }

  if (get_line(fp, buf) || (sscanf(buf, "%d", &n_cmds) != 1))
    msg(MSG_EXIT_ABNORM, "error getting number of commands");

  cmds = (struct cmd *) malloc(n_cmds * sizeof(struct cmd));

  /* Commands */
  for (i = 0; i < n_cmds; i++) {
    int n_args;
    if (get_line(fp,buf) || get_type(buf, &cmds[i].type))
      msg(MSG_EXIT_ABNORM, "error getting command %d type", i);
    for (p = &buf[0]; *p != ','; p++);
    n_args = sscanf(p, ",%d,%x,%x", &cmds[i].port, &cmds[i].mask,
      &cmds[i].value);
    if (n_args == 3) {
      if (cmds[i].type != UNSTRB)
        msg(MSG_EXIT_ABNORM, "Too many arguments for command %d");
    } else if (n_args == 2) {
      if (cmds[i].type == UNSTRB)
        msg(MSG_EXIT_ABNORM, "Missing value for command %d");
    } else {
      msg(MSG_EXIT_ABNORM, "error getting command %d info");
    }
  }

  /* dont read special commands */

  fclose(fp);
}
