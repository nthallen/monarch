#ifndef JSON_SRVR_H_INCLUDED
#define JSON_SRVR_H_INCLUDED
#include <list>
#include "dasio/socket.h"
#include "dasio/loop.h"

namespace DAS_IO {

class json_server;

class json_listener : public DAS_IO::Socket {
  public:
    json_listener(const char *hostname, json_server *jsrvr);
    /**
     * Creates a new json_client Socket using iname and fd.
     * Set is_server false and set is_server_client true.
     * Adds the new client to ELoop if defined.
     */
    virtual Socket *new_client(const char *iname, int fd);
  protected:
    inline ~json_listener() {}
    json_server *jsrvr;
};

class json_client : public DAS_IO::Socket {
  public:
    json_client(Socket *orig, const char *iname,
          int ibufsize, int fd, json_server *jsrvr);
    void jwrite(const char *buf, int nc);
  protected:
    inline ~json_client() {}
    bool protocol_input();
    bool process_eof();
    json_server *jsrvr;
};

class json_server {
  public:
    json_server(const char *hostname);
    void add_client(json_client *clt);
    void rm_client(json_client *clt);
    void rm_clients();
    /**
     * @param buf Data to be written to clients.
     * @param nc Size of data in buf
     * Writes data to each client.
     */
    void jcallback(const char *buf, int nc);
    static void jcb(const char *buf, int nc);
    static json_server *jserver;
    Loop ELoop;
  protected:
    std::list<json_client *> clients;
    std::list<json_client *> rmclts;
    bool writing;
};

}

#ifndef TMC_SERVER_CLASS
#define TMC_SERVER_CLASS json_server
#endif
#ifndef TMC_SERVER_HOSTNAME
#define TMC_SERVER_HOSTNAME "127.0.0.1"
#endif

#endif
