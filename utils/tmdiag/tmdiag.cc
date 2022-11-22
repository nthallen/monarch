/** @file tmdiag.cc
 */
#include <errno.h>
#include <string.h>
#include <unistd.h> // for optind, opterr
#include "tmdiag.h"
#include "dasio/msg.h"
#include "dasio/tm.h"
#include "oui.h"

tmdiag tmd;

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  load_tmdac(".");
  tmd.process_args(argc, argv);
}

tmdiag::tmdiag() :
    curfile(0),
    curfp(0),
    bufsize(20000),
    buf(0) {
  buf = (char*)new_memory(bufsize);
}

void tmdiag::process_args(int argc, char **argv) {
  int optltr;

  optind = OPTIND_RESET;
  opterr = 0;
  while ((optltr = getopt(argc, argv, opt_string)) != -1) {
    switch (optltr) {
      case '?':
        msg(3, "Unrecognized Option -%c", optopt);
      default:
        break;
    }
  }
  for (; optind < argc; optind++) {
    optarg = argv[optind];
    tmd.process_file(optarg);
  }
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
    if (process_record(&buf[offset]))
      break;
  }
  cleanup_error();
}

void tmdiag::cleanup_error() {
  // If additional error logic is added here, create a non-error
  // cleanup function that can be called from process_file().
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
    if (where) msg(MSG_ERROR, "%s: %s", curfile, where);
    cleanup_error();
  }
  return val;
}

bool tmdiag::process_record(const char *rawrec) {
  if (check_logic_error(fsize-offset < sizeof(tm_hdr_t), "Short record at EOF"))
    return true;
  struct tm_msg *rec = (struct tm_msg *)rawrec;
  if (check_logic_error(rec->hdr.tm_id != TMHDR_WORD, 0)) {
    msg(MSG_ERROR, "%s: Invalid message header at offset %d",
          curfile, offset);
    return true;
  }
  switch (rec->hdr.tm_type) {
    case TMTYPE_INIT: // 0x0100
      return (process_init(rec));
    case TMTYPE_TSTAMP: // 0x0200
      return (process_tstamp(rec));
    case TMTYPE_DATA_T3: // 0x0303
      return (process_data_t3(rec));
    case TMTYPE_QUIT: // 0x0400
      return (process_quit(rec));
    case TMTYPE_DATA_T1: // 0x0301
    case TMTYPE_DATA_T2: // 0x0302
    case TMTYPE_DATA_T4: // 0x0304
    case TMTYPE_ACK_T3: // 0x0503: Never referenced or documented
    default:
      msg(MSG_ERROR, "%s: Unsupported record type 0x%04X at offset %d",
        curfile, rec->hdr.tm_type, offset);
      cleanup_error();
      return true;
  }
}

bool tmdiag::process_init(struct tm_msg *rec) {
  tm_info_t *tmi = &rec->body.init;
  tm_dac_t *tmdac = &tmi->tm;
  // Compare tmdac to tm_info.tm
  //   Compare tmdac->tmid.version
  //   Compare tmdac->tmid.md5
  //   Compare tmdac->nbminf
  if (check_file_error(offset+sizeof(tm_hdr_t)+sizeof(tm_info_t) > fsize,
      "Incomplete TM_INIT record"))
    return true;
  return false;
}

bool tmdiag::process_tstamp(struct tm_msg *rec) {
  return true;
}

bool tmdiag::process_data_t3(struct tm_msg *rec) {
  return true;
}

bool tmdiag::process_quit(struct tm_msg *rec) {
  return true;
}
