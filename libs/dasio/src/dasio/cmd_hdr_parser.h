#ifndef CMD_HDR_PARSER_H_INCLUDED
#define CMD_HDR_PARSER_H_INCLUDED

#include "cmd_server.h"

namespace DAS_IO {

class cmd_hdr_parser {
  public:
    cmd_hdr_parser();
    ~cmd_hdr_parser();
    /**
     * @param ibuf Pointer to command string
     * The string at ibuf must remain unchanged until the
     * command has been fully processed.
     * Checks the command string for header data and sets
     * hdrID_buf, SN, mode and cmd values accordingly.
     * If no header is present, hdrID_buf[0], SN and mode
     * will all be set to zero.
     * @return true if a syntax error is found.
     */
    bool parse(const char *ibuf);
    /**
     * Formats the previously parsed command into fmtcmd.
     * @return The number of characters in fmtcmd or zero
     * on overflow.
     */
    int format();
    char *hdrID_default; // Initialized from AppID.name
    char *hdrID_buf; // allocated and extended as necessary
    int SN;
    char mode;
    const char *cmd; // points into ibuf, assumed to remain constant
    char fmtcmd[Cmd_Server::MAX_COMMAND_IN];
  private:
    int hdrID_len;
    /**
     * @param ibuf The source string
     * @param suffix The required suffix string
     * @return true if ibuf ends with the suffix string
     */
    bool chk_trailing(const char *ibuf, const char *suffix);
    int inline remaining(int nc) {
      return nc < Cmd_Server::MAX_COMMAND_IN ?
        Cmd_Server::MAX_COMMAND_IN-nc : 0;
    }
    int inline retcode(int nc) {
      return nc < Cmd_Server::MAX_COMMAND_IN ? nc : 0;
    }
};

}

#endif
