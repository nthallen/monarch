/** @file dasio/cmd_writer.h */
#ifndef DAS_IO_CMD_WRITER_H_INCLUDED
#define DAS_IO_CMD_WRITER_H_INCLUDED


typedef enum { Cmd_Send, Cmd_Test, Cmd_Send_Quiet } CI_Cmd_Mode;

#ifdef __cplusplus

#include "cmd_client.h"
#include "client.h"
#include "loop.h"
#include "cmdalgo.h"

namespace DAS_IO {

/**
 * @brief Class for command server clients
 */
class Cmd_writer : public Client {
  public:
    Cmd_writer(const char *iname, const char *hostname);
    bool app_input();
    bool app_connected();

    /**
     * Runs the event loop.
     */
    void wait();
    
    /**
     * @brief Sends a command to the command server.
     *
     * Returns zero on success. If the command server cannot be
     * located (and =nl_response= is set below 3) returns 1.
     * Otherwise, the return value is the sum of a type code and a
     * value. The possible types are CMDREP_QUIT, CMDREP_SYNERR and
     * CMDREP_EXECERR. CMDREP_QUIT indicates that the command you sent
     * was a quit request, which probably means the client should shut
     * down also. CMDREP_SYNERR indicates there was a syntax error in
     * the command you sent. The value portion of the return code is
     * the offset within the command where the error occurred.
     * CMDREP_EXECERR indicates that an error occurred when the server
     * was executing the instructions associated with the command. The
     * value portion of the return code is the error code.
     *
     * @param mode Indicates how command is to be processed
     * @param cmdtext The ASCIIZ text of the command, including
     * any required terminating newline character
     * @return CMDREP_* error codes
     */
    int sendcmd(CI_Cmd_Mode mode, const char *cmdtext);
    
    /**
     * @return A string which is appropriate for
     * output of algorithm time when in playback mode.
     * If not in playback mode, or if settime() has not
     * yet been called, an empty string is returned.
     */
    const char *time_str();
    
    /**
     * Internal function used to update a command
     * client's time. This is used during playback
     * of algorithms to allow outbound commands to
     * be logged with their TM time instead
     * of the current time.
     */
    void settime(int32_t time);
    
    static Cmd_writer *Cmd;
    static bool playback;
    static const int CMD_PREFIX_MAX = 10;
    static const int CMD_VERSION_MAX = 80;
    
  protected:
    ~Cmd_writer();
    bool version_verified;
    bool sent_quit;
    bool recd_quit;
    int ret_code;
    int32_t ci_time;
    Loop PvtLoop;
};

}

extern "C" {

#else // __cplusplus

  #include <stdbool.h>
  #define CMD_VERSION_MAX 80

#endif // __cplusplus

/**
 * @param playback Indicates if this is a playback session. Defaults to false.
 */
void cic_set_playback(bool playback);

/**
 * If not in playback mode,
 * Locates the command server using either the default node
 * information or the information set by cic_options -C <node>.
 * Once located, if ci_version is
 * non-empty, the version is queried.
 *
 * This version does not connect to cmd/Quit, since that needs
 * to happen at a different level.
 * @return true on error.
 */
bool cic_init();

/**
 * @brief Sends a command to the command server.
 * @param mode Indicates how command is to be processed
 * @param cmdtext The ASCIIZ text of the command, including
 * any required terminating newline character
 * @return CMDREP_* error codes
 */
int ci_sendcmd(CI_Cmd_Mode mode, const char *cmdtext);

/**
 * @brief Application-level method to send a formatted command
 * to the command server
 * @param mode Indicates how command is to be processed
 * @param fmt Format for printf-style command.
 * @return CMDREP_* error codes
 */
int ci_sendfcmd(CI_Cmd_Mode mode, const char *fmt, ...);

/** cic_transmit receives commands from the interactive command
   parser and transmits them as required to the command server
   using the nortlib routine ci_sendcmd(). Commands are only
   actually transmitted if the transmit argument is non-zero.
   Since the client and server share source code, it is easy
   for cmdgen to determine whether a particular command will
   result in an action at the far end.
   
   cic_transmit also keeps track of the command parser states,
   recording the commands required to get to a particular
   state. For example, in the HOX command configuration,
   entering "OH\r" will cause the parser to change to a new
   state (submemu) which expects OH commands. This does
   not require transmission, but it does need to be recorded
   because of the new state. Subsequent commands will be
   transmitted prefixed by the "OH\r" until a "\r" is
   entered, returning the parser to the base state.
   
   The command in buf is not ASCIIZ. Spaces may be represented
   by NULs and the terminating newline should be universally
   represented by a NUL. These must be translated back to
   their original representation before actual transmission.
*/
void cic_transmit(char *buf, int n_chars, int transmit);

#ifdef __cplusplus
  };
#endif

#endif
