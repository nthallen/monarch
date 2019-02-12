/* msg.c */
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "dasio/client.h"
#include "dasio/loop.h"
#include "dasio/appid.h"
#include "oui.h"
#include "nl.h"
#include "dasio/msg.h"
// #include "tm.h" was needed for tm_dev_name
// I hacked that out, but this needs to interface to C++ to provide proper IPC
// with memo.

  memo_client::memo_client() : DAS_IO::Client("memo", 1000, "memo", 0) {
    //do stuff
  }
  
  memo_client::~memo_client() {}
  
  bool memo_client::init() {
    ELoop.add_child(this);
    connect();
    ELoop.event_loop();
    return (fd >= 0);
  }
  
  void memo_client::send(const char* msg) {
    if ((msg != 0) && (msg[0] != '\0')) {
      if (iwrite(msg)) {
        nl_error(3, "memo failure");
      } else {
        ELoop.event_loop();
      }
    }
  }
  
  bool memo_client::app_connected() {
    return true;
  }
  
  bool memo_client::connect_failed() {
    return true;
  }
  
  bool memo_client::iwritten(int nb) {
    ocp += nb;
    return (is_negotiated() && ocp >= onc);
  }

static int write_to_memo = 1, write_to_stderr = 0, write_to_file = 0;
FILE *file_fp;
static memo_client *memo_client_instance;

/*
<opts> "vo:mV"

<sort>
  -v add a level of verbosity
  -o <error filename> Write to specified file
  -m write to memo [default]
  -V write to stderr
*/
void msg_init_options(int argc, char **argv) {
  int c;

  optind = OPTIND_RESET;
  opterr = 0;
  while ((c = getopt(argc, argv, opt_string)) != -1) {
    switch (c) {
      case 'v': --nl_debug_level; break;
      case 'o':
        file_fp = fopen( optarg, "a" );
        if ( file_fp == NULL ) {
          fprintf( stderr, "Unable to open output file: '%s'\n", optarg );
          exit(1);
        }
        write_to_file = 1;
        break;
      case 'm': write_to_memo = 2; break;
      case 'V': write_to_stderr = 1; break;
      case '?':
        fprintf( stderr, "Unrecognized option: '-%c'\n", optopt );
        exit(1);
      default: break; // could check for errors
    }
  }
  if ( ( write_to_file || write_to_stderr ) && write_to_memo == 1 )
    write_to_memo = 0;
  if ( write_to_memo ) {
    // memo_fp = fopen( tm_dev_name( "memo" ), "w" );
    // memo_fp = fopen( "memo.log", "w" );
    
    memo_client_instance = new memo_client();
    if (!memo_client_instance->init()) {
      fprintf( stderr, "Unable to contact memo\n" );
      write_to_stderr = 1;
      write_to_memo = 0;
    }
  }
  nl_error = msg;
  nl_verror = msgv;
}

static void write_msg( char *buf, int nb, FILE *fp, const char *dest ) {
  int rv = fwrite( buf, 1, nb, fp );
  if ( rv == -1 ) {
    fprintf( stderr, "Memo: error %s writing to %s\n",
       strerror(errno), dest );
  }
  fflush(fp);
}

/**
 * msg() supports the nl_error() interface, but provides
 * a considerable amount of additional functionality to
 * support logging of messages within an application with
 * multiple executables. Through command-line options, msg()
 * can be configured to log to stderr and/or to a log file
 * and/or to the memo application, and adds a timestamp
 * to each message. See nl_error() for definition of the
 * level options.
 * @return the level argument.
 */
int msg( int level, const char *fmt, ...) {
  va_list args;
  int rv;

  va_start(args, fmt);
  rv = msgv( level, fmt, args );
  va_end(args);
  return rv;
}

/**
 * msgv() is a version of the msg() function that
 * takes a va_list for format arguments, allowing
 * more complex reporting functions to built on
 * top of the msg() functionality. Internally
 * msg() calls msgv().
 * @return the level argument.
 */
#define MSG_MAX_INTERNAL 250
int msgv( int level, const char *fmt, va_list args ) {
  const char *lvlmsg;
  char msgbuf[MSG_MAX_INTERNAL+2];
  time_t now = time(NULL);
  struct tm *tm = gmtime(&now);
  char *tbuf = asctime(tm);
  int nb;

  switch ( level ) {
    case -1:
    case 0: lvlmsg = ""; break;
    case 1: lvlmsg = "[WARNING] "; break;
    case 2: lvlmsg = "[ERROR] "; break;
    case 3: lvlmsg = "[FATAL] "; break;
    default:
      if ( level >= 4 ) lvlmsg = "[INTERNAL] ";
      else if ( level < nl_debug_level ) return level;
      else lvlmsg = "[DEBUG] ";
      break;
  }
  strncpy(msgbuf, tbuf+11, 9); // index, length of time string
  strncpy( msgbuf+9, lvlmsg, MSG_MAX_INTERNAL-9 );
  nb = 9 + strlen(lvlmsg);
  nb += snprintf( msgbuf+nb, MSG_MAX_INTERNAL-nb, "%s: ", DAS_IO::AppID.name );
  // I am guaranteed that we have not yet overflowed the buffer
  nb += vsnprintf( msgbuf+nb, MSG_MAX_INTERNAL-nb, fmt, args );
  if ( nb > MSG_MAX_INTERNAL ) nb = MSG_MAX_INTERNAL;
  if ( msgbuf[nb-1] != '\n' ) msgbuf[nb++] = '\n';
  // msgbuf[nb] = '\0';
  // nb may be as big as MSG_MAX_INTERNAL+1
  // we don't need to transmit the trailing nul

  if ( write_to_memo && memo_client_instance ) {
    memo_client_instance->send(msgbuf);
  }
  if ( write_to_file ) write_msg( msgbuf, nb, file_fp, "file" );
  if ( write_to_stderr ) write_msg( msgbuf, nb, stderr, "stderr" );
  if ( level >= 4 ) abort();
  if ( level == 3 ) exit(1);
  if ( level == -1 ) exit(0);
  return level;
}
