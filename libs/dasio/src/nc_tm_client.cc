#include "dasio/nc_tm_client.h"

void DAS_IO::nc_tm_client::adopted() {
  signal(SIGWINCH, true);
}
