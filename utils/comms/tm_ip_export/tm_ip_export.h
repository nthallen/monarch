/** @file tm_ip_export.h
 * tm_client sub class for telemetry export
 */
#ifndef TM_IP_EXPORT_H_INCLUDED
#define TM_IP_EXPORT_H_INCLUDED
#include "dasio/tm_client.h"

using namespace DAS_IO;

/**
 * Establishes connection to the remote tm_ip_import server.
 * Maintains the Client TCP connection to receive commands and
 * uses UDP to transmit telemetry.
 */
class tm_ip_remote : public Client {
  public:
    tm_ip_remote();
    void send_row(uint16_t MFCtr, const uint8_t *raw);
  protected:
    ~tm_ip_remote();
};

class tm_ip_export : public tm_client {
  public:
    tm_ip_export(tm_ip_remote *rmt);
  protected:
    ~tm_ip_export();
    unsigned int process_data();
    tm_ip_remote *rmt;
};

#endif
