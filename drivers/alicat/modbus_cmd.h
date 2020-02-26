#ifndef MODBUS_CMD_H_INCLUDED
#define MODBUS_CMD_H_INCLUDED
#include "dasio/modbus_rtu.h"
#include "dasio/cmd_reader.h"

namespace DAS_IO { namespace Modbus {

  class modbus_cmd : public DAS_IO::Cmd_reader {
    public:
      modbus_cmd(const char *channel, DAS_IO::Modbus::RTU *MB);
      bool app_input();
    protected:
      DAS_IO::Modbus::RTU *MB;
  };

} }

#endif
