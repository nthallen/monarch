#include "dasio/cmd_writer.h"
#include "dasio/kbdclt.h"

const char *kbdclt_cross_exp;

using namespace DAS_IO;

bool kbdclt_cic_init(const char *func) {
  Cmd_writer *CW = new Cmd_writer("Cmd", func);
  if (kbdclt_cross_exp)
    CW->set_cross_exp(kbdclt_cross_exp);
  return cic_init(CW);
}
