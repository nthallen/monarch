/** @file cic.h */
#ifndef CIC_H_INCLUDED
#define CIC_H_INCLUDED

/* Command Interpreter Client (CIC) and Server (CIS) Utilities
   Message-level definition is in cmdalgo.h
 */
void cic_options(int argc, char **argv, const char *def_prefix);
int cic_init(void);
void cic_reset(void);
extern char ci_version[];
void cic_transmit(char *buf, int n_chars, int transmit);
int ci_sendcmd(const char *cmdtext, int mode);
int ci_sendfcmd(int mode, const char *fmt, ...);
void ci_settime( long int time );
extern int cic_cmd_quit_fd;
const char *ci_time_str( void );

#endif
