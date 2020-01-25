#ifndef DAS_IO_CMD_CLIENT_H_INCLUDED
#define DAS_IO_CMD_CLIENT_H_INCLUDED

#ifdef __cplusplus

namespace DAS_IO {
  extern const char *CmdServerNode;
}

extern "C" {

#endif

void cic_set_server_node(const char *node);

#ifdef __cplusplus
}
#endif

#endif
