#ifndef CSV_FILE_H_INCLUDED
#define CSV_FILE_H_INCLUDED
#include <vector>
#include <stdio.h>

class csv_col {
  public:
    csv_col(const char *colname, const char *fmt = NULL);
    ~csv_col();
    void init_array(unsigned int length, bool is_col);
    const char *output();
    const char *header();
    const char *get_format();
    inline unsigned int get_length() { return length; }
    /**
     * @return true for high-rate data
     */
    inline bool get_rate() { return is_col; }
    void set(double dval);
    void set(const char *tval);
    void reset();
  protected:
    void dsval_resize(int newsize);
    const char *cname;
    char *dsval;
    int dsval_size;
    const char *format;
    unsigned int length;
    bool is_col;
    bool warned;
};

class csv_file {
  public:
    csv_file(const char *name, unsigned int n_cols,
        const char *nan_text = NULL, int json = 0);
    ~csv_file();
    void init();
    void init_col(unsigned int col_num, const char *colname,
                  const char *fmt = NULL);
    /**
     * @param col_num Column index
     * @param length Number of elements in the array
     * @param is_col true if array contains multiple readings of a single
     *   sensor
     *
     * Sets the dimensions of the specified column and initializes the
     * following length-1 columns with the same column name and format.
     * There are two bassic types of arrays within this framework.
     * The first is an aggregation of related data, usually from
     * different sensors, e.g. an array of multiple temperature sensors.
     * The second kind is a convenient way of reporting data at a higher
     * rate than the telemetry format, e.g. reporting multiple readings
     * from a single sensor.
     */
    void init_array(unsigned int col_num, unsigned int length, bool is_col = false);
    void set_time(double T);
    void set_col(unsigned int col_num, double dval);
    void set_col(unsigned int col_num, const char *sval);
    /**
     * @param jcb callback function to send out JSON text.
     * This should be a static method of the JSON web server
     * class.
     */
    void set_jcb(void (*jcb)(const char *buf, int nc));
    static void terminate_on_write_err(int sig);
    static const char *nan;
  protected:
    void flush_headers();
    void flush_row();
    void process_nc(int nc, char *&jb, int &jspace, int &jneeded);
    std::vector<csv_col*> cols;
    double cur_time;
    bool time_set;
    bool json;
    const char *filename;
    FILE *fp;
    char *jbuf;
    int jbufsize;
    void (*jcb)(const char *buf, int nc);
};

#endif
