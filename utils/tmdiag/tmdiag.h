/** @file tmdiag.h
 * @brief Telemetry Diagnostic Utility
 * This program reads raw log files written by lgr and read by rdr.
 * It may have various options, but initially, it will report each
 * record and file
 */
#ifndef TMDIAG_H_INCLUDED
#define TMDIAG_H_INCLUDED
#include <stdio.h>
#include "dasio/tm.h"

extern void process_file(const char *filename);

class tmdiag {
  public:
    tmdiag();
    void process_file(const char *filename);
    void process_args(int argc, char **argv);
    /**
     * @param rec pointer to the current record in buf
     * @return true if there was an error
     * On success, offset will be updated to the next
     * record. On error, the file will be closed and
     * a message reported before returning.
     */
    bool process_record(const char *rec);
    /**
     * @param msg pointer to the current tm_msg
     * @return true if there was an error
     * On success, offset will be updated to the next
     * record. On error, the file will be closed and
     * a message reported before returning.
     */
    bool process_init(struct tm_msg *msg);
    bool process_tstamp(struct tm_msg *msg);
    bool process_data_t3(struct tm_msg *msg);
    bool process_quit(struct tm_msg *msg);
  protected:
    bool check_file_error(bool val, const char *where);
    /**
     * @param val If true, invoke cleanup_error()
     * @param where If non-zero, display error message when val is true
     * @return val for convenience
     */
    bool check_logic_error(bool val, const char *where);
    /**
     * Currently just closes the file.
     */
    void cleanup_error();
    const char *curfile;
    FILE *curfp;
    int bufsize;
    char *buf;
    size_t fsize;
    int offset;
    mfc_t next_mfctr;
};

extern tmdiag tmd;

#endif
