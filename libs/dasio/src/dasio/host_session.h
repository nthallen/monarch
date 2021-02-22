#ifndef HOST_SESSION_H_INCLUDED
#define HOST_SESSION_H_INCLUDED
#include <map>
#include <string>

namespace DAS_IO {

class hs_registry {
  public:
    static void add_session(const char *spec);
    static void add_host(const char *spec);
    /**
     * @param func The application specific socket function
     * @return hostname if found, NULL otherwise
     */
    static const char *query_host(const char *func);
    /**
     * @param func The application specific socket function
     * @return Unix Domain session if found, NULL otherwise
     */
    static const char *query_session(const char *func);
  private:
    inline hs_registry() {}
    void add_spec(bool host, const char *spec);
    const char *query(bool host, const char *func);
    static hs_registry *instance;
    static hs_registry *instantiate();
    /**
     * Splits arg into its two compnents, func_arg and hs_arg
     * @param arg a colon-separate pair of strings
     * @return true if the input string is valid
     */
    bool split_arg(const char *arg);
    static const int max_strlen = 64;
    char func_arg[max_strlen];
    char hs_arg[max_strlen];
    std::map<std::string,std::string> host_reg;
    std::map<std::string,std::string> socket_reg;
};

}

#endif
