/* dasio/rundir.h */
/* Created 2019 April 3 for RUNDIR variables */
#ifndef DAS_IO_RUNDIR_H_INCLUDED
#define DAS_IO_RUNDIR_H_INCLUDED

#include <sys/types.h>

#ifdef __cplusplus
  extern "C" {
#endif
  
//extern void mkfltdir(const char *dir, uid_t flt_uid, gid_t flt_gid);
//extern void setup_rundir(void);
//extern void delete_rundir(void);
#define RUNDIR_UNIX "/var/run/linkeng"
#define RUNDIR_TMC "/var/run/linkeng/run"

#ifdef __cplusplus
  };
#endif

#endif
