/** @file dasio/appid.h */
#ifndef DAS_IO_APPID_H_INCLUDED
#define DAS_IO_APPID_H_INCLUDED
#include "nl.h"

namespace DAS_IO {

class AppID_t {
  public:
    AppID_t(const char *name, const char *fullname, const char *rev);
    ~AppID_t();
    void report_startup();
    void report_shutdown();
    inline void new_name(const char *name) { this->name = name; }
    const char *name;
    const char *fullname;
    const char *rev;
    const char *Experiment;
};

extern AppID_t AppID;

}

#endif
