#ifndef AGILENT_INT_H_INCLUDED
#define AGILENT_INT_H_INCLUDED

#include "dasio/socket.h"
#include "dasio/tm_data_sndr.h"
#include "agilent.h"

class agilent_ctrl : public DAS_IO::Socket {
  public:
    agilent_ctrl(DAS_IO::TM_data_sndr *TM);
    void Request(); //< sends the READ? command
    enum state_t {ctrl_idle, ctrl_info, ctrl_read};
  protected:
    bool connected();
    bool protocol_input();
    bool protocol_timeout();
    bool protocol_gflag(int flag);
    state_t state;
    DAS_IO::TM_data_sndr *TM;
  private:
    int saveCount;
    static const int devicePort;
    static const char *hostname;
    static const int BUFFER_SIZE;
};

#endif

