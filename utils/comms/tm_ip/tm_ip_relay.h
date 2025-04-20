#ifndef TM_IP_RELAY_H_INCLUDED
#define TM_IP_RELAY_H_INCLUDED
#include <list>
#include "dasio/mlf_packet_logger.h"
#include "dasio/client.h"

using namespace DAS_IO;

class subrelay;
typedef std::list<subrelay *> subrelayList;

class tm_ip_relay : public Client
{
  public:
    tm_ip_relay();
    /**
     * @param spt serio_pkt_type assigned to subrelay
     * @param svc The service name assigned to subrelay
     * @param prefix The start of embedded subpackets
     * @param mlf_config Configuration for MLF logging
     * The service name will double as the directory name
     * for mlf_packet_logger. Need to be able to determine
     * this configuration at runtime, so probably need a
     * non-trivial command-line parsing routine.
     */
    void add_subrelay(serio_pkt_type spt, const char *svc,
      const char *prefix, const char*mlf_config);
    static tm_ip_relay *get_instance();
    void adopted() override;
    /**
     * subrelay config: colon-separated list of:
     *   - serio_pkt_type code letter
     *   - service name
     *   - packet prefix (hex escapes OK, e.g. \xAA\xAA)
     *   - mlf configuration string
     */
    static void init_option(const char*subrelay_config);
  protected:
    bool app_input() override;
    subrelay *find_relay(serio_pkt_type spt);
    static tm_ip_relay *instance;
    subrelayList subrelay_list;
    static const int IBUFSZ = 4096;
};


class subrelay_client;
typedef std::list<subrelay_client *> subrelayClientList;

/**
 * subrelay is a server socket listening on the specified
 * service. It can accommodate multiple clients, so will need
 * a list of clients, like tm_ip_import.
 */
class subrelay : public Socket, mlf_packet_logger
{
  public:
    subrelay(serio_pkt_type spt, const char *svc,
          const char *prefix, const char*mlf_config);
    inline serio_pkt_type get_type() { return spt; }
    /**
     * @param hdr points to a serio_pkt_hdr.
     * @param len The total length of the packet.
     * len must be equal to the serio_pkt_hdr length plus
     * the size of the serio_pkt_hdr, i.e. must be one
     * complete packet.
     */
    void forward(const uint8_t *hdr, uint16_t len);
    Socket *new_client(const char *iname, int fd) override;
  protected:
    serio_pkt_type spt;
    const char *prefix;
    subrelayClientList client_list;
};

class subrelay_client : public Socket
{
  public:
    subrelay_client(Socket *original, const char *iname, int fd);
    /**
     * @param hdr points to a serio_pkt_hdr.
     * @param len The total length of the packet.
     * len must be equal to the serio_pkt_hdr length plus
     * the size of the serio_pkt_hdr, i.e. must be one
     * complete packet.
     */
    void forward(const uint8_t *hdr, uint16_t len);
  protected:
    static const int IBUFSIZE = 4000;
};

#endif
