/* commands.c Handles interface to command interpreters.
 */
#include <string.h>
#include "nl.h"
#include "compiler.h"
#include "cmdalgo.h"
#include "yytype.h"
#ifdef __QNXNTO__
  /* For ci_sendcmd() definition */
  #include "tm.h"
#else
  #include "dasio/cmd_writer.h"
#endif

char ci_version[CMD_VERSION_MAX] = "";

static int cswarn = 0;

void check_command(const char *command) {
  if (!cswarn) {
	int rv;

	{ int old_response = set_response(0);
	  if ( command == 0 ) rv = ci_sendcmd(1, command);
	  else {
		char *cmdnl;
		if ( *command == '_' ) command++;
		cmdnl = new_memory( strlen( command ) + 2 );
		sprintf( cmdnl, "%s\n", command );
		rv = ci_sendcmd(1, cmdnl);
		free_memory( cmdnl );
	  }
	  set_response(old_response);
	}
	switch (CMDREP_TYPE(rv)) {
	  case 0:
		if ( rv != 0 ) {
		  compile_error(1, "Command Server not found: commands untested");
		  cswarn = 1;
		}
		break;
	  case CMDREP_TYPE(CMDREP_QUIT):
		break;
	  case CMDREP_TYPE(CMDREP_EXECERR):
		compile_error(4, "Unexpected Execution Error %d from CIS", rv);
	  case CMDREP_TYPE(CMDREP_SYNERR):
		compile_error(2, "Text Command Syntax Error:");
		compile_error(2, "%s", command);
		compile_error(2, "%*s", rv - CMDREP_SYNERR, "^");
		break;
	}
  }
}

void set_version(char *ver) {
  strncpy(ci_version, ver, CMD_VERSION_MAX);
  ci_version[CMD_VERSION_MAX-1] = '\0';
}

void get_version(FILE *ofp) {
  #ifdef __QNXNTO__NOT_USED
    int old_response, rv;

    old_response = set_response(0);
    rv = cic_query(ci_version);
    set_response(old_response);
    if (rv) {
	  compile_error(1, "Command Server not found: %s",
	    ci_version[0] ? "Using specified version." :
	    "No version info.");
    }
  #endif
  fprintf(ofp, "%%{\n"
	"  #include \"nl.h\"\n"
	"  #include \"dasio/tma.h\"\n"
	"  char ci_version[] = \"%s\";\n"
	"%%}\n", ci_version);
}
