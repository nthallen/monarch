/* cmdalgo.h defines entry points into the cmdgen-based algorithms
 * Part of the cmdgen distribution
 */
#ifndef CMDALGO_H_INCLUDED
#define CMDALGO_H_INCLUDED

#ifdef __cplusplus

#ifdef __QNXNTO__
  // required for cmdif_dgdata
  #include "collect.h"
#else
  // the monarch version
  #include "dasio/config.h"
#endif

extern "C" {
#endif // __cplusplus

void cmd_init(void); // cmdgen.skel, called from library
void cmd_interact(void); // cmdgen.skel if CMD_INTERACT_MODE. called from library
int cmd_batch(char *cmd, int test); // cmdgen.skel if !CMD_CLIENT. called from library
typedef struct {
  unsigned short state;
  unsigned short value;
} cmd_state;
void cmd_report(cmd_state *s); // cmdgen.skel called from cic_transmit()
int cmd_check(cmd_state *s); // cmdgen.skel called from cic_transmit()

void cis_initialize(void); // cmdgen.skel
void cis_terminate(void); // cmdgen.skel
void cis_interfaces(void); /* generated */
void cis_interfaces_close(void); /* generated */
#define CMDREP_OK 0
#define CMDREP_QUIT 1000
#define CMDREP_SYNERR 2000
#define CMDREP_EXECERR 3000
#define CMDREP_NOREPLY 4000
#define CMDREP_TYPE(x) ((x)/1000)

#ifdef __QNXNTO__
  struct ioattr_s;
  #define IOFUNC_ATTR_T struct ioattr_s
  extern IOFUNC_ATTR_T *cis_setup_rdr( char *node );
  extern void cis_turf( IOFUNC_ATTR_T *handle, char *format, ... );
  void ci_server(void); /* in tmpplib/cis.cc */
  #define CMD_VERSION_MAX 80
#endif
#define CMDSRVR_NAME "cmd/server"
#define CMD_INTERP_MAX 256

#ifdef __cplusplus
};

#ifdef __QNXNTO__

class cmdif_rd {
  public:
    cmdif_rd( const char *name );
    void Setup();
    void Turf(const char *fmt, ...);
    void Shutdown();
  private:
    const char *name;
    IOFUNC_ATTR_T *handle;
};

class cmdif_wr {
  public:
    cmdif_wr(const char *name, const char *path);
    void Setup();
    void Turf(const char *fmt, ...);
    void Shutdown();
  private:
    const char *name;
    const char *path;
    int ofd;
};

class cmdif_dgdata {
  public:
    cmdif_dgdata(const char *name, void *data, int dsize);
    // void Setup(); // does nothing.
    void Turf();
    void Shutdown();
  private:
    const char *name;
    void *data;
    int dsize;
    send_id id;
};

#endif // __QNXNTO__

#endif

#endif
