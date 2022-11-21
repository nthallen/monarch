/** @file tmdiag.h
 * @brief Telemetry Diagnostic Utility
 * This program reads raw log files written by lgr and read by rdr.
 * It may have various options, but initially, it will report each
 * record and file
 */
#ifndef TMDIAG_H_INCLUDED
#define TMDIAG_H_INCLUDED
#include <stdio.h>

extern void process_file(const char *filename);

class tmdiag {
  public:
    tmdiag();
    void process_file(const char *filename);
    /**
     * @return record size in bytes or -1 on error
     * If any error occurs, the file will be closed and a
     * message reported before returning.
     */
    int process_record(const char *rec);
  protected:
    bool check_file_error(bool val, const char *where);
    bool check_logic_error(bool val, const char *where);
    void cleanup_error();
    const char *curfile;
    FILE *curfp;
    int bufsize;
    char *buf;
    size_t fsize;
    int offset;
};

extern tmdiag tmd;

#endif
