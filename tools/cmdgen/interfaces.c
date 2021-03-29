#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "cmdgen.h"
#include "compiler.h"
#include "nl.h"

typedef struct if_list_s {
  struct if_list_s *next;
  int if_type;
  int if_usage;
  char *if_name;
  char *if_path;
} if_list_t;
static if_list_t *if_list, *if_last;
const char *transmitting_if;

#define IFT_READ 1
#define IFT_WRITE 2
#define IFT_DGDATA 3
#define IFT_SUBBUS 4

void new_interface(char *if_name, int usage) {
  const char *cmd_class = 0;
  char *s;

  if_list_t *new_if;
  new_if = (if_list_t *)new_memory(sizeof(if_list_t));
  if (if_last == NULL ) {
    if_list = new_if;
  } else {
    if_last->next = new_if;
  }
  if_last = new_if;
  new_if->next = NULL;
  new_if->if_name = if_name;
  new_if->if_usage = usage;
  new_if->if_path = NULL;
  for ( s = if_name; *s; ++s ) {
    if ( *s == ':' ) {
      *s++ = '\0';
      new_if->if_path = s;
      break;
    }
  }
  if ( new_if->if_path ) {
    if ( strcmp( new_if->if_path, "DG/data" ) == 0 ) {
      cmd_class = "cmdif_dgdata";
      new_if->if_type = IFT_DGDATA;
    } else {
      cmd_class = "cmdif_wr";
      new_if->if_type = IFT_WRITE;
    }
  } else if ( strcasecmp( new_if->if_name, "subbus" ) == 0 ||
          strcasecmp( new_if->if_name, "subbusd" ) == 0 ) {
    new_if->if_type = IFT_SUBBUS;
    fprintf( ofile, "#include \"subbus.h\"\n" );
  } else {
    cmd_class = "cmdif_rd";
    new_if->if_type = IFT_READ;
  }
  if (cmd_class) {
    const char *condition;
    switch (usage) {
      case IF_USE_TX:
        condition = "defined(SERVER) && defined(TRANSMITTING)";
        if (transmitting_if)
          msg(1,
            "Ignoring redefinition of transmitting interface if_%s with if_%s",
            transmitting_if, if_name);
        else transmitting_if = if_name;
        break;
      case IF_USE_FLIGHT:
        condition = "defined(SERVER) && !defined(TRANSMITTING)";
        break;
      case IF_USE_COORD:
        condition = "defined(SERVER)";
        break;
      default:
        msg(4, "Invalid usage code %d for interface %s", new_if->if_usage, if_name);
    }
    fprintf( ofile, "#if %s\n", condition);
    switch (new_if->if_type) {
      case IFT_WRITE:
        fprintf( ofile, "  %s if_%s(\"%s\", \"%s\");\n",
              cmd_class, if_name, if_name, new_if->if_path );
        break;
      case IFT_DGDATA:
        fprintf( ofile, "  %s if_%s(\"%s\", &%s, sizeof(%s));\n",
          cmd_class, if_name, if_name, if_name, if_name );
        break;
      case IFT_READ:
        fprintf( ofile, "  %s if_%s(\"%s\");\n",
          cmd_class, if_name, if_name );
        break;
      default:
        msg(4,"Invalid if_type %d", new_if->if_type);
    }
    fprintf( ofile, "#endif\n" );
  }
}

void output_interfaces(void) {
  if_list_t *cur_if;
  const char *condition;
  bool conditioned = false;
  fprintf( ofile, "\n#ifdef SERVER\n" );
  fprintf( ofile, "  void cis_interfaces(void) {\n" );
  for (int usage = IF_USE_COORD; usage >= IF_USE_FLIGHT; --usage) {
    // That's COORD, TX and FLIGHT, in that order
    switch (usage) {
      case IF_USE_COORD:
        condition = 0;
        break;
      case IF_USE_TX:
        condition = "#ifdef TRANSMITTING";
        break;
      case IF_USE_FLIGHT:
        condition = conditioned ?
          "#else" : "#ifndef TRANSMITTING";
        break;
    }
    for ( cur_if = if_list; cur_if; cur_if = cur_if->next ) {
      if (cur_if->if_usage == usage) {
        if (condition) {
          fprintf(ofile, "  %s\n", condition);
          condition = 0;
          conditioned = true;
        }
        switch (cur_if->if_type) {
          case IFT_READ:
          case IFT_WRITE:
          case IFT_DGDATA:
            fprintf( ofile, "    if_%s.Setup();\n", cur_if->if_name );
            break;
          case IFT_SUBBUS:
            break; // initialization is handled by subbus.oui
          default:
            msg(4, "Unexpected interface type: %d", cur_if->if_type );
        }
      }
    }
  }
  if (conditioned)
    fprintf(ofile, "  #endif\n");
  conditioned = false;
  fprintf( ofile, "  };\n\n" );
  fprintf( ofile, "  void cis_interfaces_close(void) {\n" );
  for (int usage = IF_USE_COORD; usage >= IF_USE_FLIGHT; --usage) {
    // That's COORD, TX and FLIGHT, in that order
    switch (usage) {
      case IF_USE_COORD:
        condition = 0;
        break;
      case IF_USE_TX:
        condition = "#ifdef TRANSMITTING";
        break;
      case IF_USE_FLIGHT:
        condition = conditioned ?
          "#else" : "#ifndef TRANSMITTING";
        break;
    }
    for ( cur_if = if_list; cur_if; cur_if = cur_if->next ) {
      if (cur_if->if_usage == usage) {
        if (condition) {
          fprintf(ofile, "  %s\n", condition);
          condition = 0;
          conditioned = true;
        }
        switch (cur_if->if_type) {
          case IFT_READ:
          case IFT_WRITE:
          case IFT_DGDATA:
            fprintf( ofile, "    if_%s.Shutdown();\n", cur_if->if_name );
            break;
          case IFT_SUBBUS:
            fprintf( ofile, "    subbus_quit();\n" );
            break;
          default:
            msg(4, "Unexpected interface type: %d", cur_if->if_type );
        }
      }
    }
  }
  if (conditioned)
    fprintf(ofile, "  #endif\n");
  fprintf( ofile, "  }\n#endif\n\n" );
}
