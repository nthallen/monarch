#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "dasio/tm.h"
#include "dasio/msg.h"

static FILE *open_path( const char *path, const char *fname ) {
  char filename[PATH_MAX];
  FILE *tmd;
  if ( snprintf( filename, PATH_MAX, "%s/%s", path, fname )
          >= PATH_MAX )
    msg( 3, "Pathname overflow for file '%s'", fname );
  tmd = fopen( filename, "r" );
  return tmd;
}

void load_tmdac( const char *path ) {
  FILE *dacfile;
  if ( path == NULL || path[0] == '\0' ) path = ".";
  dacfile = open_path( path, "tm.dac" );
  if ( dacfile == NULL ) {
    char version[40];
    char dacpath[80];
    FILE *ver;

    version[0] = '\0';
    ver = open_path( path, "VERSION" );
    if ( ver != NULL ) {
      int len;
      if ( fgets( version, 40, ver ) == NULL )
        msg(3,"Error reading VERSION: %s",
          strerror(errno));
      len = strlen(version);
      while ( len > 0 && isspace(version[len-1]) )
        version[--len] = '\0';
      if ( len == 0 )
        msg( 1, "VERSION was empty: assuming 1.0" );
    } else {
      msg( 1, "VERSION not found: assuming 1.0" );
    }
    if ( version[0] == '\0' ) strcpy( version, "1.0" );
    snprintf( dacpath, 80, "bin/%s/tm.dac", version );
    dacfile = open_path( path, dacpath );
  }
  if ( dacfile == NULL ) msg( 3, "Unable to locate tm.dac" );
  if ( fread(&tm_info.tm, sizeof(tm_dac_t), 1, dacfile) != 1 )
    msg( 3, "Error reading tm.dac" );
  fclose(dacfile);
  tm_info.nrowminf = tmi(nbminf)/tmi(nbrow);
}
