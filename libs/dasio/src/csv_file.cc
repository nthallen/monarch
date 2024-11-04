/**
 * \file csv_file.cc
 * These classes definee the runtime for extraction to CSV output
 */
#include <malloc.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include "dasio/csv_file.h"
#include "nl.h"
#include "nl_assert.h"

csv_col::csv_col(const char *colname, const char *fmt) {
  cname = colname;
  format = fmt;
  dsval = 0;
  dsval_size = 0;
  warned = false;
  length = 1;
  is_col = false;
}

csv_col::~csv_col() {
  if (dsval) free(dsval);
}

void csv_col::init_array(unsigned int length, bool is_col)
{
  this->length = length;
  this->is_col = is_col;
}

const char *csv_col::output() {
  return dsval ? dsval : "";
}

const char *csv_col::header() {
  return cname ? cname : "";
}

const char *csv_col::get_format() {
  return format;
}

void csv_col::dsval_resize(int newsize) {
  char *newbuf;
  dsval_size = newsize;
  newbuf = (char *)realloc(dsval, dsval_size);
  if (newbuf == NULL) {
    msg(MSG_FATAL, "Memory allocation failure in csv_col::set(double)");
  }
  dsval = newbuf;
}

void csv_col::set(double dval) {
  nl_assert(format);
  int sz = snprintf(dsval, dsval_size, format, dval);
  if (sz >= dsval_size) {
    dsval_resize(sz+5);
    sz = snprintf(dsval, dsval_size, format, dval);
    nl_assert(sz < dsval_size);
  }
}

void csv_col::set(const char *tval) {
  int sz;
  const char *s = tval;
  bool is_num = true;
  // Check tval for numeric. If non, warn once, and replace text with nan
  int n_whitespace = 0;
  while ( isspace(*s) ) { ++s; ++n_whitespace; }
  if ( *s == '-' || *s == '+') ++s;
  if ( isdigit(*s) ) {
    while (isdigit(*s)) ++s;
    if ( *s == '.' ) {
      ++s;
      while (isdigit(*s)) ++s;
    }
  } else if (*s == '.') {
    ++s;
    if (isdigit(*s)) {
      while (isdigit(*s)) ++s;
    } else {
      is_num = false;
    }
  }
  if (is_num && tolower(*s) == 'e') {
    ++s;
    if ( *s == '-' || *s == '+') ++s;
    if (isdigit(*s)) {
      while (isdigit(*s)) ++s;
    } else is_num = false;
  }
  if (is_num && *s != '\0')
    is_num = false;
  if (!is_num) {
    if (!warned) {
      msg(MSG_WARN,"Column '%s' reported at least one non-numeric value: '%s'",
        cname, tval);
      warned = true;
    }
    tval = csv_file::nan;
  }
  sz = snprintf(dsval, dsval_size, "%s", &tval[n_whitespace]);
  if (sz >= dsval_size) {
    dsval_resize(sz+5);
    sz = snprintf(dsval, dsval_size, "%s", &tval[n_whitespace]);
    nl_assert(sz < dsval_size);
  }
}

void csv_col::reset() {
  if (dsval) dsval[0] = '\0';
}


csv_file::csv_file(const char *name, unsigned int n_cols,
      const char *nan_text, int json_fmt) {
  filename = name;
  cols.resize(n_cols);
  time_set = false;
  if (nan_text)
    nan = nan_text;
  json = json_fmt ? true : false;
  fp = 0;
  jbufsize = 0;
  jbuf = 0;
  jcb = 0;
}

csv_file::~csv_file() {
  if (time_set) {
    flush_row();
  }
  if (fp) {
    fclose(fp);
    fp = 0;
  }
  for (unsigned int i = 0; i < cols.size(); ++i) {
    if ( cols[i] ) {
      delete cols[i];
      cols[i] = 0;
    }
  }
  if (jbuf) {
    nl_free_memory(jbuf);
    jbuf = 0;
  }
}

void csv_file::init() {
  signal(SIGPIPE, &terminate_on_write_err);
  if (json) {
    // fp = stdout;
  } else {
    fp = fopen( filename, "w" );
    if (fp == NULL)
      msg(MSG_FATAL, "Cannot open output file %s", filename);
  }
}

void csv_file::terminate_on_write_err(int sig) {
  msg(0, "Received signal %d: Terminating", sig);
  exit(0);
}

const char *csv_file::nan = "";

void csv_file::init_col(unsigned int col_num, const char *colname,
          const char *fmt) {
  if (time_set)
    msg(MSG_FATAL, "csv_file::init_col() after time_set");
  if (col_num >= cols.size())
    msg(MSG_FATAL, "col_num %d out of range in csv_file::init_col", col_num);
  if (cols[col_num])
    msg(MSG_FATAL, "Illegal redefinition of column %d in csv_file::init_col",
      col_num);
  if (col_num == 0 && fmt == 0) fmt = "%.0lf";
  cols[col_num] = new csv_col(colname, fmt);
}

void csv_file::init_array(unsigned int col_num, unsigned int length, bool is_col)
{
  if (col_num >= cols.size())
    msg(MSG_FATAL, "col_num %d out of range in csv_file::init_col", col_num);
  if (! cols[col_num])
    msg(MSG_FATAL, "Column %d uninitialized in csv_file::init_array",
      col_num);
  cols[col_num]->init_array(length, is_col);
  for (int i = 1; i < length; ++i) {
    init_col(col_num+i, cols[col_num]->header(), cols[col_num]->get_format());
  }
}

void csv_file::set_time(double T) {
  if (cols[0] == 0)
    cols[0] = new csv_col("Time", "%.0lf");
  if (time_set) {
    if (T != cur_time) flush_row();
  } else {
    flush_headers();
  }
  time_set = true;
  cur_time = T;
  cols[0]->set(T);
}

/**
 * This interface is not for column zero (Time)
 */
void csv_file::set_col(unsigned int col_num, double dval) {
  if (col_num < 1 || col_num >= cols.size()) {
    msg(MSG_FATAL, "col_num %u out of range in csv_file::set_col", col_num);
  } else if (cols[col_num] == NULL) {
    msg(MSG_FATAL, "column %u undefined in csv_file::set_col", col_num);
  } else cols[col_num]->set(dval);
}

void csv_file::set_col(unsigned int col_num, const char *sval) {
  if (col_num < 1 || col_num >= cols.size()) {
    msg(MSG_FATAL, "col_num %u out of range in csv_file::set_col", col_num);
  } else if (cols[col_num] == NULL) {
    msg(MSG_FATAL, "column %u undefined in csv_file::set_col", col_num);
  } else cols[col_num]->set(sval);
}

void csv_file::set_jcb(void (*jcb)(const char *buf, int nc)) {
  this->jcb = jcb;
}

void csv_file::flush_headers() {
  unsigned int i;
  nl_assert(cols[0]);
  if (!json) {
    fprintf(fp, "%s", cols[0]->header());
    for (i = 1; i < cols.size(); ++i) {
      fprintf(fp, ",%s", cols[i] ? cols[i]->header() : "");
    }
    fprintf(fp, "\n");
  }
}

void csv_file::process_nc(int nc, char *&jb, int &jspace, int &jneeded) {
  jspace -= nc;
  if (jspace > 0) {
    jb += nc;
  } else {
    jspace = 0;
  }
  jneeded += nc;
}

void csv_file::flush_row() {
  if (json) {
    while (jcb) {
      char *jb = jbuf;
      int jspace = jbufsize;
      int jneeded = 0;
      int nc =
        snprintf(jb, jspace, "{\r\n  \"Record\": \"%s\",\r\n  \"%s\": %s",
          filename, cols[0]->header(), cols[0]->output() );
      process_nc(nc, jb, jspace, jneeded);
      int i = 1;
      while (i < cols.size()) {
        if (cols[i]) {
          unsigned int len = cols[i]->get_length();
          if (len <= 1) {
            nc = snprintf(jb, jspace, ",\r\n  \"%s\": %s",
              cols[i]->header(), cols[i]->output() );
            process_nc(nc, jb, jspace, jneeded);
            ++i;
          } else {
            nc = snprintf(jb, jspace, ",\r\n  \"%s\": [%s",
              cols[i]->header(), cols[i]->output() );
            process_nc(nc, jb, jspace, jneeded);
            for (int j = 1; j < len; ++j) {
              nc = snprintf(jb, jspace, ",%s", cols[i+j]->output() );
              process_nc(nc, jb, jspace, jneeded);
            }
            nc = snprintf(jb, jspace, "]");
            process_nc(nc, jb, jspace, jneeded);
            i += len;
          }
        } else ++i;
      }
      nc = snprintf(jb, jspace, "\r\n}\r\n");
      process_nc(nc+1, jb, jspace, jneeded);
      if (jneeded > jbufsize) {
        // reallocate jbuf at jneeded + 100, say
        if (jbuf) nl_free_memory(jbuf);
        jbufsize = jneeded+100;
        jbuf = (char *)new_memory(jbufsize);
      } else {
        jcb(jbuf, jneeded-1);
        return;
      }
    }
  } else {
    fprintf(fp, "%s", cols[0]->output() );
    for (unsigned int i = 1; i < cols.size(); ++i) {
      fprintf(fp, ",");
      if (cols[i]) {
        fprintf(fp, "%s", cols[i]->output() );
        cols[i]->reset();
      }
    }
    fprintf(fp, "\n");
  }
}
