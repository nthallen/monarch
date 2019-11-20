#include "tm.h"
#include "tm_gen.h"
#include "tm_client.h"

using namespace DAS_IO {

class tm_relay : public tm_generator, public tm_client {
  public:
    tm_relay();
    ~tm_relay();
  protected:
    virtual void process_data();
    virtual void process_tstamp();
  private:
}

}
