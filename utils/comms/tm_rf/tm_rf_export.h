/** \file tm_rf_export.h
 * tm_client sub class for telemetry
 */
#ifndef TM_RF_EXPORT_H_INCLUDED
#define TM_RF_EXPORT_H_INCLUDED

#include <stdint.h>
#include "dasio/serial.h"
#include "dasio/cmd_reader.h"
#include "dasio/tm_client.h"
#include "dasio/serio_pkt.h"
#include "mlf.h"

#define EXTRACTION_ROW send_row(MFCtr, (const uint8_t *)raw);
#define TM_CLIENT_CLASS tm_rf_tm_client
#define TM_CLIENT_FAST true

using namespace DAS_IO;

class tm_rf_if : public Serial {
  public:
    tm_rf_if();
    ~tm_rf_if();
    void enqueue_photo();
    void send_row(uint16_t MFCtr, const uint8_t *raw);
    static tm_rf_if *radio;
    static const int blocksize = 512;
    static const char *tm_port;
    static const char *base;
    static int baud;
    static int air_speed;
    static uint32_t cur_photo;
    static bool hwflow;
  protected:
    void process_data();
    void connect();
    void queue_retry();
    // bool not_serio_pkt_hdr();
    bool protocol_input();
    bool protocol_timeout();
    bool protocol_except();
    bool read_error(int my_errno);
    bool process_eof();
    // uint16_t crc_calc(uint8_t *buf, int len);
  private:
    // int ser_fd, scan_fd;
    // int32_t cur_scan;
    // int32_t next_scan;
    // uint32_t scan_file_size, scan_file_offset;
    // uint16_t scan_nb, scan_cp;
    // uint16_t scan_mfctr, scan_mfctr_offset;
    // mlf_def_t *mlf;
    // uint8_t scanbuf[scanbufsize];
    // serio_pkt *row_buf;
    // ssp_scan_hdr_t *ssp_hdr;
    uint16_t row_len;
    // uint16_t row_offset;
    uint16_t rows_per_row; //*< Scan rows transmitted per TM row
    uint16_t rows_this_row; //*< Scan rows transmitted so far this TM row
    bool connect_waiting;
    bool dropping_tx_rows;
    int n_tx_rows_dropped;
    int total_tx_rows_dropped;
    
    // void send_scan_data();
};

class tm_rf_tm_client : public tm_client {
  public:
    inline tm_rf_tm_client() :
      tm_client(4096, TM_CLIENT_FAST) {}
  protected:
    unsigned int process_data();
    void process_quit();
    void send_row(uint16_t MFCtr, const uint8_t *raw);
};

void set_cur_photo(uint32_t Photo_Num);

#endif /* TM_RF_EXPORT_H_INCLUDED */
