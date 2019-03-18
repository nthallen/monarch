/** @file dasio/cmd_version.h */
#ifndef DAS_IO_CMD_VERSION_H_INCLUDED
#define DAS_IO_CMD_VERSION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void ci_report_version();
/** Generated version of the command interpreter source */
extern char ci_version[];

#ifdef __cplusplus
};
#endif

#endif
