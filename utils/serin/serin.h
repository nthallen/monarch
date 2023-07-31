#ifndef SERIN_H_INCLUDED
#define SERIN_H_INCLUDED
#include "dasio/tm_gen.h"
#include "dasio/server.h"
#include "dasio/serio_pkt.h"

using namespace DAS_IO;

class serin : public tm_generator {
  public:
    serin();
    void start();
    void service_row_timer();
    void process_tm(serio_pkt_hdr *hdr);
  protected:
    void commit_tstamp(mfc_t MFCtr, le_time_t time);
    bool have_tstamp;
    uint16_t next_minor_frame;
    static const uint16_t TS_MFC_LIMIT = 32767;
    static const uint32_t NAN32 = 0xFFC00000U;
    uint16_t ROLLOVER_MFC;
};

class serin_serin : public Serverside_client {
  public:
    serin_serin(Authenticator *auth, const char *iname, serin *tm);
    /** Adds serin subservice to the server */
    static void attach(serin *srvr);
    static Serverside_client *new_serin_serin(
              Authenticator *auth, SubService *SS);
    static const int serin_serin_bufsize = 4096;
  protected:
    bool protocol_input();
    serin *srvr;
};

#endif
