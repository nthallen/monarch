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
#include "sspint.h"

static char board_hostname[40] = "10.0.0.200";
static char *mlf_config = NULL;
static const char *ssp_name, *interface, *portspec = "0";
#define SSP_AMP_NAME_SIZE 20
static const char *ssp_amp_name;
static int quit_received = 0;
static int trigger_count = 0;
static int latency = 1;
ssp_config_t ssp_config;
noise_config_t noise_config;
ssp_data_t ssp_data;
ssp_amp_data_t ssp_amp_data;
static volatile int saw_sigpipe = 0;

using namespace DAS_IO;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  AppID.report_startup();
  ssp_config.LE = 1; // Logging enabled by default
  mlf_def_t *mlf = mlf_init( 3, 60, 1, ssp_name, "dat", mlf_config );

  Loop ELoop;

  ssp_data.index = mlf->index;
  ssp_data.ScanNum = 0;
  ssp_data.Flags = 0;
  ssp_data.Total_Skip = 0;
  TM_data_sndr *tm_data = TM_data_sndr("TM", 0,
    ssp_name, &ssp_data, sizeof(ssp_data));
  tm_data->connect();
  ELoop.add_child(tm_data);

  { int nc = snprintf(0, 0, "%s_amp", ssp_name);
    ssp_amp_name = (const char *)new_memory(nc+1);
    TM_data_sndr *tm_amp_data = TM_data_sndr("TMn", 0,
      ssp_amp_name, &ssp_amp_data, sizeof(ssp_amp_data));
    tm_amp_data->connect();
    ELoop.add_child(tm_amp_data);
  }
  
  CMD setup
  UDP setup
  TCP setup
  signal setup

  AppID.report_shutdown();
}
