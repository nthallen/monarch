#ifndef GETCON_H_INCLUDED
#define GETCON_H_INCLUDED
/** @file getcon.h
 */
#include "dasio/cmd_reader.h"
#include "dasio/cmd_writer.h"

/**
 * @param arg a positional parameter from the getcon command line
 * oui_init_options() will call getcon_args() once for each (non-option)
 * positional parameter on the command line. The first positional
 * parameter, the window name, is mandatory. The second, specifying
 * the session ID, is optional but commonly used.
 */
extern void getcon_init_options(int argc, char **argv);
extern bool opt_end_session;

class getcon_cmd : public DAS_IO::Cmd_reader {
  public:
    getcon_cmd();
    bool connect_failed();
    bool app_process_eof();
    bool app_input();
    bool app_negotiation_failed();
    bool app_connected();
  private:
    bool tried_quit;
};

#endif
