/* dasio/rundir.h */
/* Created 2019 April 3 for RUNDIR variables */
#ifndef DAS_IO_RUNDIR_H_INCLUDED
#define DAS_IO_RUNDIR_H_INCLUDED

#include <sys/types.h>

#ifdef __cplusplus
  extern "C" {
#endif
  
#define RUNDIR_UNIX "/var/run/monarch"
#define RUNDIR_TMC "/var/run/monarch/run"

#ifdef __cplusplus
  };
#endif

#endif
