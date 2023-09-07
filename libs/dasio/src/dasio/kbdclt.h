#ifndef KBDCLT_H_INCLUDED
#define KBDCLT_H_INCLUDED

extern const char *kbdclt_cross_exp;
/**
 * Function called from nct_cmdclt_init() to setup sending commands.
 * There is currently no hook to override the default (srvr). For
 * cross-Experiment control, kbdclt.oui defines a command-line option
 * to specify the Experiment value to use when connecting to the
 * command server.
 *
 * @param func host_session function for accessing the cmd server (srvr)
 */
extern bool kbdclt_cic_init(const char *func = "srvr");

#endif
