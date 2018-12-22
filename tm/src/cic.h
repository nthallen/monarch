/** @file cic.h */
#ifndef CIC_H_INCLUDED
#define CIC_H_INCLUDED

/** Command client options parser.
 */
void cic_options(int argc, char **argv, const char *def_prefix);
/** Establishes connection to cmd/server and cmd/Quit.
 * Called implicitly by ci_sendcmd().
 */
int cic_init(void);
/** Closes connections to the command server. */
void cic_reset(void);
/** Generated version of the command interpreter source */
extern char ci_version[];
/** Low-level command transmission function called from the
 * command parser in interactive clients for transmission to the
 * command server. Called by cmd_interact() via static cmd_exec().
 */
void cic_transmit(char *buf, int n_chars, int transmit);

/** Application-level method to send a command to the command server */
int ci_sendcmd(const char *cmdtext, int mode);
/** Application-level method to send a formatted command to the command
 * server
 */
int ci_sendfcmd(int mode, const char *fmt, ...);
/** Specifies time for message timestamps during replay
 */
void ci_settime( long int time );
extern int cic_cmd_quit_fd;
const char *ci_time_str( void );

#endif
