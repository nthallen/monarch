/**
 sspdrv.cc Driver framework for
 Harvard Anderson Group Scalable Signal Processing board (SSP)

 Options:
  -specify board IP
  -specify command channel
  -specify logging hierarchy

 Strategy:
 - Open tcp connection to ssp
 - Open read from cmd/SSP (different channel for each board)
 - Open write to DG/data/SSP (different channel for each board)

 Accept commands and queue requests to the board.
 Open UDP connection on start and add to the select

 Channels:
   cmd_fd: cmd/SSPn: always reading: READ
   tm_data->fd: DG/data/SSPn: always writing: may be synchronized: WRITE
   tcp_socket: ssp TCP: alternately reading and writing: IDLE,WRITE,READ,CONNECT
   udp_socket: ssp UDP: open and closed, always reading: IDLE,READ
 */
#include <math.h>
#include "dasio/tm_data_sndr.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "dasio/ascii_escape.h"
#include "sspint.h"
#include "oui.h"
#include "nl.h"

static char *mlf_config = NULL;
int latency = 1;
static const char *ssp_name;
#define SSP_AMP_NAME_SIZE 20
static char *ssp_amp_name;
static int quit_received = 0;
static int trigger_count = 0;
ssp_config_t ssp_config;
noise_config_t noise_config;
ssp_data_t ssp_data;
ssp_amp_data_t ssp_amp_data;
static volatile int saw_sigpipe = 0;

void sspdrv_init(int argc, char * const *argv) {
  int c, board_id;

  optind = OPTIND_RESET; /* start from the beginning */
  opterr = 0; /* disable default error message */
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'N':
        mlf_config = optarg;
        break;
      case 'L':
        latency = atoi(optarg);
        break;
      case '?':
        msg(3, "Unrecognized Option -%c", optopt);
    }
  }
}

using namespace DAS_IO;

SSP_Cmd::SSP_Cmd(SSP_TCP *TCP, SSP_UDP *UDP)
    : Cmd_reader("cmd", 160, AppID.name),
      TCP(TCP),
      UDP(UDP) {};

bool SSP_Cmd::is_eocmd(unsigned char c) {
  return c == '\0' || c == ' ' || c == '\n';
}

bool SSP_Cmd::report_invalid() {
  report_err("Invalid command at column %u", cp);
  consume(nc);
  return false;
}

/**
 Driver will accept space-delimited combinations of the following:
 Commands:
   Allowed when not acquiring:
    -EN Enable
    NS:xxxx N_Samples
    NA:xxxx N_Average (Pre-Adder)
    NC:xxxx N_Coadd
    NF:xx      Frequency (translate to a divisor)
    NE:x 1-7 bit-mapped Specifies which channels are enabled

   Allowed anytime:
    -DA Disable
    TU:[-]xxxxx Level Trigger Rising
    TD:[-]xxxxx Level Trigger Falling
    TS:x (0-3) Specifies the trigger source
    AE Autotrig Enable
    AD Autotrig Disable
    LE Logging Enable
    LD Logging Disable
    nZ Number of samples with laser off at the start of scan
    nN Starting sample for noise calculations
    nM Ending sample for noise calculations
    XR Reset TCP and UDP connections
    XX Terminate the driver
    Q  Terminate the driver (to match the Monarch standard)

   Never allowed:
    EX Quit: don't do it!
    NP:xxxxx UDP Port Number (I specify this)

  As before, we will accept triggering commands anytime and
  other commands only when not acquiring.
 */
bool SSP_Cmd::app_input() {
  unsigned char *head, *tail;
  uint16_t newval16;
  int32_t newval32;
  uint32_t newvalu32;

  msg(MSG_DBG(1), "%s: Rec'd cmd '%s'", iname, ascii_esc((char *)buf));
  while (cp < nc) {
    while (cp < nc && isspace(buf[cp])) ++cp;
    if (cp < nc && buf[cp] == 'Q')
      return true;
    if (cp+3 > nc) break; // incomplete command
    head = tail = &buf[cp];
    /* In the following switch statement, if we break out, the command code
       will be directly transmitted to the SSP. If instead we continue, the
       code will not be transmitted.  Hence any codes that are handled
       entirely in the driver must update cp and use continue.
       This applies to LD, LE, XR, XX, nZ, nN and nM as well as any command
       that is incorrectly formatted or inappropriate due to the current
       operating mode.
     */
    switch (*head) {
      case 'E':
        if ( *++tail != 'N' || !is_eocmd(*++tail) ) {
          return report_invalid();
        }
        cp += 3;
        if ( UDP->state != FD_IDLE ) {
          msg( 2, "EN not valid: Already enabled" );
          continue;
        }
        if ( TCP->state == FD_CONNECT ) {
          msg( 2, "EN suppressed: not connected" );
          continue;
        }
        if ( ssp_config.NS == 0 ) {
          ssp_config.NS = 1024;
          TCP->enqueue((const unsigned char*)"NS:1024");
        }
        if ( ssp_config.NE == 0 ) {
          ssp_config.NE = 1;
          TCP->enqueue((const unsigned char*)"NE:1");
        }
        msg(MSG_DBG(1), "%s: Processing EN", iname);
        ssp_config.NP = 0;
        { ssp_config.NP = UDP->connect();
          if (ssp_config.NP == 0) {
            msg(2, "UDP->connect() returned error");
            continue; // suppress EN
          }
          unsigned char udp_buf[20];
          snprintf((char *)udp_buf, 20, "NP:%d", ssp_config.NP);
          TCP->enqueue(udp_buf);
        }
        ssp_data.Status = SSP_STATUS_ARMED;
        break; // transmit EN
      case 'D':
        if ( *++tail != 'A' || !is_eocmd(*++tail) ) {
          return report_invalid();
        }
        cp += 3;
        UDP->disconnect();
        if ( TCP->state != FD_CONNECT )
          ssp_data.Status = SSP_STATUS_READY;
        break;
      case 'A':
        switch (*++tail) {
          case 'E':
          case 'D':
            if ( is_eocmd(*++tail) ) break;
            // else fall through
          default:
            return report_invalid();
        }
        cp += 3;
        break;
      case 'L':
        switch (*++tail) {
          case 'E':
            if ( is_eocmd(*++tail) ) {
              ssp_config.LE = 1;
              cp += 3;
              continue;
            } else {
              return report_invalid();
            }
          case 'D':
            if ( is_eocmd(*++tail) ) {
              ssp_config.LE = 0;
              cp += 3;
              continue;
            } else {
              return report_invalid();
            }
          default:
            return report_invalid();
        }
        break;
      case 'X':
        switch (*++tail) {
          case 'R':
            UDP->disconnect();
            TCP->reset();
            cp += 3;
            continue;
          case 'X':
            UDP->disconnect();
            cp += 3;
            // quit_received = 1;
            report_ok(cp);
            return true;
          default:
            return report_invalid();
        }
        break;
      case 'N':
        ++cp;
        if ( is_eocmd(buf[cp++]) ||
             buf[cp++] != ':' ||
             ( head[1] == 'F' ?
               not_uint32(newvalu32) :
               not_uint16(newval16))) {
          return report_invalid();
        }
        tail = &buf[cp++];
        if ( UDP->state != FD_IDLE ) {
          *tail = '\0';
          msg( 2, "Command invalid while SSP is enabled: '%s'", head );
          // Abort the entire command line
          report_ok(nc);
          return false;
        }
        switch (head[1]) {
          case 'S': ssp_config.NS = newval16; noise_config.modified = 1; break;
          case 'A': ssp_config.NA = newval16; break;
          case 'C': ssp_config.NC = newval16; break;
          case 'F':
            { unsigned char div_buf[80];
              ssp_config.NF = 100000000/newvalu32;
              snprintf((char*)div_buf, 80, "NF:%d", ssp_config.NF );
              TCP->enqueue(div_buf);
            }
            continue;
          case 'E': ssp_config.NE = newval16; break;
          default:
            return report_invalid();
        }
        break;
      case 'n':
        ++cp;
        if ( is_eocmd(buf[cp++]) ||
             buf[cp++] != ':' ||
             not_uint16(newval16)) {
          return report_invalid();
        }
        tail = &buf[cp++];
        switch (head[1]) {
          case 'Z':
            noise_config.NZ = newval16;
            noise_config.modified = 1;
            continue;
          case 'N':
            noise_config.NN = newval32;
            noise_config.modified = 1;
            continue;
          case 'M':
            noise_config.NM = newval32;
            noise_config.modified = 1;
            continue;
          default:
            return report_invalid();
        }
        break;
      case 'T': // Trigger commands
        ++cp;
        if ( is_eocmd(buf[cp++]) ||
             buf[cp++] != ':' ||
             not_int32(newval32)) {
          return report_invalid();
        }
        tail = &buf[cp++];
        switch (head[1]) {
          case 'U':
          case 'D':
          case 'S':
            break;
          default:
            return report_invalid();
        }
        break;
      default:
        return report_invalid();
    }
    { *tail = '\0';
      TCP->enqueue(head);
    }
  }
  report_ok(cp);
  if (noise_config.modified) {
    if (noise_config.NN == 0 || noise_config.NM == 0) {
      noise_config.NZ = 0;
    }
    if (noise_config.NN > noise_config.NM ||
        noise_config.NZ >= noise_config.NN ||
        noise_config.NM > ssp_config.NS) {
      noise_config.NZ = 0;
    }
    if (noise_config.NZ == 0) {
      int i;
      noise_config.NN = 0;
      noise_config.NM = 0;
      for (i = 0; i < 3; ++i) {
        ssp_amp_data.noise[i] = 0;
        ssp_amp_data.noise_percent[i] = 0;
      }
    } else {
      noise_config.NSamp = noise_config.NM - noise_config.NN + 1;
      noise_config.meanX = (noise_config.NSamp+1)/2.0;
      noise_config.sumX2  = powf(noise_config.NSamp,3)/12. -
        noise_config.NSamp/12.;
    }
    noise_config.modified = 0;
  }
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  AppID.report_startup();
  ssp_config.LE = 1; // Logging enabled by default
  ssp_name = AppID.name;
  mlf_def_t *mlf = mlf_init( 3, 60, 1, ssp_name, "dat", mlf_config );

  { Loop ELoop;

    ssp_data.index = mlf->index;
    ssp_data.ScanNum = 0;
    ssp_data.Flags = 0;
    ssp_data.Total_Skip = 0;
    TM_data_sndr *tm_data = new TM_data_sndr("TM", 0,
      ssp_name, &ssp_data, sizeof(ssp_data));
    tm_data->connect();
    ELoop.add_child(tm_data);

    TM_data_sndr *tm_amp_data;
    { int nc = snprintf(0, 0, "%s_amp", ssp_name);
      ssp_amp_name = (char *)new_memory(nc+1);
      snprintf(ssp_amp_name, nc+1, "%s_amp", ssp_name);
      tm_amp_data = new TM_data_sndr("TMn", 0,
        ssp_amp_name, &ssp_amp_data, sizeof(ssp_amp_data));
      tm_amp_data->set_gflag_no(1); // to avoid colliding with tm_data
      tm_amp_data->set_retries(0, 0, 0, false);
      tm_amp_data->connect();
      ELoop.add_child(tm_amp_data);
    }

    SSP_UDP *UDP = new SSP_UDP(mlf, tm_amp_data);
    ELoop.add_child(UDP);

    SSP_TCP *TCP = new SSP_TCP();
    ELoop.add_child(TCP);
    TCP->connect();

    SSP_Cmd *Cmd = new SSP_Cmd(TCP, UDP);
    ELoop.add_child(Cmd);
    Cmd->connect();

    // signal setup, if needed
    
    ELoop.event_loop();
    ssp_data.Status = SSP_STATUS_GONE;
    tm_data->Send();
    ELoop.delete_children();
    ELoop.clear_delete_queue();
  }

  AppID.report_shutdown();
  return 0;
}
