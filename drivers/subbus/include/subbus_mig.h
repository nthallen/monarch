#ifndef SUBBUS_MIG_H_INCLUDED
#define SUBBUS_MIG_H_INCLUDED
#include "subbuspp.h"

class subbus_mig : public subbuspp {
  public:
    subbus_mig();
    ~subbus_mig();
    static int load_subbus();
    static subbus_mig *sb;

    /**
     * Issues the low-level subbus SBC_SETCMDENBL command.
     * Some subbus devices do not support the failure function.
     * @return non-zero on success. Zero if unsupported
     */
    inline int set_cmdenbl(int value) {
      return send_CSF(SBC_SETCMDENBL, value);
    }

    /**
     * Issues the low-level subbus SBC_SETCMDSTRB command.
     * Some subbus devices do not support the cmdstrobe function.
     * @return non-zero on success. Zero if unsupported
     */
    inline int set_cmdstrobe(int value) {
      return send_CSF(SBC_SETCMDSTRB, value);
    }

    /**
     * Issues the low-level subbus SBC_SETFAIL command.
     * Some subbus devices do not support the fail function.
     * @return non-zero on success. Zero if unsupported
     */
    inline int set_failure(int value) {
      return send_CSF(SBC_SETFAIL, value);
    }
    
    inline uint16_t read_switches() {
      return read_special(SBC_READSW);
    }
    
    uint16_t read_failure() {
      return read_special( SBC_READFAIL );
    }
    
    uint16_t sbrb(uint16_t addr);
    uint16_t sbrba(uint16_t addr);
    uint16_t sbrwa(uint16_t addr);
};

inline int load_subbus(void) {
  return subbus_mig::load_subbus();
}

extern uint16_t subbus_subfunction;
extern uint16_t subbus_features;
extern uint16_t subbus_version;

// subbus_version subbus_mig::sb->subbus_version
// subbus_features subbus_mig::sb->subbus_features
// subbus_subfunction subbus_mig::sb->subbus_subfunction

inline uint16_t read_subbus(uint16_t addr) {
  return subbus_mig::sb->read_subbus(addr);
}

inline int write_ack(uint16_t addr, uint16_t data) {
  return subbus_mig::sb->write_ack(addr, data);
}

inline int read_ack(uint16_t addr, uint16_t *data) {
  return subbus_mig::sb->read_ack(addr, data);
}

inline int write_subbus(uint16_t x, uint16_t y) {
  return write_ack(x,y);
}

inline subbus_mread_req *pack_mread_request(int n_reads, const char *req) {
  return subbus_mig::sb->pack_mread_request(n_reads, req);
}

/* There is no simple way to do this without messing with stdarg
 * stuff. Much easier to require manual mods in the migrating
 * application.
 */
// pack_mread_requests subbus_mig::sb->pack_mread_requests

inline int mread_subbus(subbus_mread_req *req, uint16_t *data) {
  return subbus_mig::sb->mread_subbus(req, data);
}

inline int mread_subbus_nw(subbus_mread_req *req, uint16_t *data,
                        uint16_t *nwords) {
  return subbus_mig::sb->mread_subbus_nw(req, data, nwords);
}

inline int set_cmdenbl(int value) {
  return subbus_mig::sb->set_cmdenbl(value);
}

inline int set_cmdstrobe(int value) {
  return subbus_mig::sb->set_cmdstrobe(value);
}

inline int set_failure(int value) {
  return subbus_mig::sb->set_failure(value);
}

inline uint16_t read_switches() {
  return subbus_mig::sb->read_switches();
}

inline uint16_t read_failure() {
  return subbus_mig::sb->read_failure();
}

inline const char *get_subbus_name() {
  return subbus_mig::sb->get_subbus_name();
}

//extern int cache_write(uint16_t addr, uint16_t data);
//extern uint16_t cache_read(uint16_t addr);

inline uint16_t sbrb(uint16_t addr) {
  return subbus_mig::sb->sbrb(addr);
}

inline uint16_t sbrba(uint16_t addr) {
  return subbus_mig::sb->sbrba(addr);
}

inline uint16_t sbrw(uint16_t addr) {
  return read_subbus(addr);
}

inline uint16_t sbrwa(uint16_t addr) {
  return subbus_mig::sb->sbrwa(addr);
}

inline int sbwr(uint16_t x,uint16_t y) {
  return write_ack(x,y);
}

// extern int subbus_int_attach( char *cardID, uint16_t address,
      // uint16_t region, struct sigevent *event );
// extern int subbus_int_detach( char *cardID );
// extern int subbus_quit(void);

#endif
