#include "dasio/tm.h"
#include "dasio/tm_gen.h"
#include "dasio/tm_client.h"

using namespace DAS_IO;

class tm_relay;

class tm_relay : public tm_generator, public tm_client {
  public:
    tm_relay();
    ~tm_relay();
  protected:
    void process_data(mfc_t MFCtr, int mfrow, int nrows);
    void process_data();
    void process_tstamp(mfc_t MFCtr, time_t time);
    void service_row_timer();
  private:
};
