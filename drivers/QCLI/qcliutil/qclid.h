#ifndef QCLID_H_INCLUDED
#define QCLID_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  int qcli_wave;
  unsigned short status;
} qcli_data_t;

extern qcli_data_t qcli_data;

#endif
