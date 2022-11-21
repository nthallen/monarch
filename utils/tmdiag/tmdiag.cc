/** @file tmdiag.cc
 */
#include <errno.h>
#include <string.h>
#include "tmdiag.h"
#include "dasio/msg.h"
#include "oui.h"

tmdiag tmd;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
}

tmdiag::tmdiag() :
    curfile(0),
    curfp(0),
    bufsize(20000),
    buf(0) {
  buf = (char*)new_memory(bufsize);
}

void tmdiag::process_file(const char *filename) {
  curfile = filename;
  curfp = fopen(filename,"r");
  if (check_file_error(curfp == 0, "in fopen()")) return;
  if (check_file_error(fseek(curfp, 0, SEEK_END) != 0, "in fseek()"))
    return;
  fsize = ftell(curfp);
  if (check_file_error(fsize<0, "in ftell()")) return;
  if (check_file_error(fseek(curfp, 0, SEEK_SET) != 0, "seeking start"))
    return;
  // Make sure the buffer size is large enough
  // Resize as necessary
  if (fsize > bufsize) {
    msg(MSG_ERROR, "File '%s' exceeds bufsize", filename);
    fclose(curfp);
    curfp = 0;
    return;
  }
  // Read in the file
  size_t rc = fread(buf, fsize, 1, curfp);
  // This error will be confusing
  if (check_logic_error(rc != fsize, "wrong read length from fread()"))
    return;
  for (offset = 0; offset < fsize;) {
    int rc = process_record(&buf[offset]);
    if (rc < 0) return; // error already processed
    offset += rc;
  }
  fclose(curfp);
  curfp = 0;
}

void tmdiag::cleanup_error() {
  if (curfp) {
    fclose(curfp);
    curfp = 0;
  }
}

bool tmdiag::check_file_error(bool val, const char *where) {
  if (val) {
    msg(MSG_ERROR, "%s: Error %d %s on file '%s' (%s)",
      curfile, errno, where, strerror(errno));
    cleanup_error();
  }
  return val;
}

bool tmdiag::check_logic_error(bool val, const char *where) {
  if (val) {
    msg(MSG_ERROR, "%s: %s", curfile, where);
    cleanup_error();
  }
  return val;
}

int tmdiag::process_record(const char *rec) {
  if (check_logic_error(fsize-offset < sizeof(tm_hdr_t), "Short record at EOF"))
    return -1;
  struct tm_msg *tms = (struct tm_msg *)rec;
  return -1;
}
