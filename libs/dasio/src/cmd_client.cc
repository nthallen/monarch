#include "dasio/cmd_client.h"

const char *DAS_IO::CmdServerNode;

void cic_set_server_node(const char *node) {
  DAS_IO::CmdServerNode = node;
}
