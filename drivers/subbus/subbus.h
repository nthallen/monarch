#ifndef SUBBUS_H_INCLUDED
#define SUBBUS_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  unsigned short req_len;
  unsigned short n_reads;
  char multread_cmd[256];
} subbus_mread_req;

#endif
