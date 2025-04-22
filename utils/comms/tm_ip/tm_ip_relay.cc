#include <cctype>
#include <cstring>
#include <stdio.h>
#include "dasio/appid.h"
#include "dasio/quit.h"
#include "dasio/loop.h"
#include "tm_ip_relay.h"
#include "nl.h"
#include "nl_assert.h"
#include "oui.h"

/****** tm_ip_relay ******/

const char *ip_import_cross_exp;

tm_ip_relay::tm_ip_relay()
    : Client("relay", "Relay", "ip_ex", "relay", IBUFSZ)
{
}

void tm_ip_relay::add_subrelay(serio_pkt_type spt, const char *svc,
  const char *prefix, const char*mlf_config)
{
  subrelay *SR = find_relay(spt);
  if (SR)
    msg(MSG_FATAL, "%s: illegal redefinition of relay type '%c'",
        iname, spt);
  SR = new subrelay(spt, svc, prefix, mlf_config);
  subrelay_list.push_back(SR);
}

tm_ip_relay *tm_ip_relay::get_instance()
{
  if (!instance)
    instance = new tm_ip_relay();
  return instance;
}

void tm_ip_relay::adopted()
{
  for (subrelayList::iterator pos = subrelay_list.begin();
       pos != subrelay_list.end();
       ++pos )
  {
    subrelay *SR = *pos;
    ELoop->add_child(SR);
    SR->connect();
  }
}

static int dup_option(const char *cfg, char **copy)
{
  int i, j;
  for (i = 0; cfg[i] != 0 && cfg[i] != ':'; ++i);
  int nc = i;
  char *lcl = (char*)new_memory(nc+1);
  for (i = 0; i < nc; )
  {
    if (i+4 <= nc && cfg[i] == '\\' && cfg[i+1] == 'x' &&
        isxdigit(cfg[i+2]) && isxdigit(cfg[i+3]))
    {
      lcl[j++] =
        (isxdigit(cfg[i+2]) ? cfg[i+2]-'0' : tolower(cfg[i+2])+10-'a') +
        ((isxdigit(cfg[i+3]) ? cfg[i+3]-'0' : tolower(cfg[i+3])+10-'a')<<4);
      i += 4;
    }
    else
    {
      lcl[j++] = cfg[i++];
    }
  }
  lcl[j] = '\0';
  *copy = lcl;
  return nc;
}

void tm_ip_relay::init_options(const char *cfg_file)
{
  char *optbuf;
  FILE *fp = fopen(cfg_file, "r");
  if (fp)
  {
    size_t sz = 80;
    size_t n = getline(&optbuf, &sz, fp);
    if (n > 0 && !isspace(optbuf[0]))
      init_option(optbuf);
  }
}

void tm_ip_relay::init_option(const char *cfg)
{
  nl_assert(cfg);
  int nc = strlen(cfg);
  nl_assert(nc >= 6);
  int cp = 0;
  int i;
  tm_ip_relay *relay = get_instance();
  char spt = cfg[cp++];
  if (cfg[cp++] != ':')
    msg(MSG_FATAL, "tm_ip_relay::init_option() expected ':' at col 1");
  char *svc;
  char *pfx;
  char *mlf_cfg;
  cp += dup_option(&cfg[cp], &svc);
  cp += dup_option(&cfg[cp], &pfx);
  cp += dup_option(&cfg[cp], &mlf_cfg);
  relay->add_subrelay((serio_pkt_type)spt, svc, pfx, mlf_cfg);
}

/* protected: */

bool tm_ip_relay::app_input()
{
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;

  while (cp < nc)
  {
    msg(MSG_DBG(2), "%s: app_input cp:%u nc:%u",
      iname, cp, nc);
    if (not_serio_pkt(have_hdr, type, length, payload))
      break;
    msg(MSG_DBG(2), "%s: serio_pkt('%c', %u)",
      iname, type, length);
    uint16_t pkt_len = serio::pkt_hdr_size + length;
    if (type == pkt_type_TM)
    { /* could forward to serin here */
    }
    else
    {
      subrelay *SR = find_relay(type);
      if (SR)
        // Strip off the serio_pkt_hdr now
        SR->forward(&buf[cp+serio::pkt_hdr_size], length);
      else
        report_err("%s: Unsupported pkt type '%c'", iname, type);
    }
    cp += pkt_len;
  }
  report_ok(cp);
  return false;
}

subrelay *tm_ip_relay::find_relay(serio_pkt_type spt)
{
  for (subrelayList::iterator pos = subrelay_list.begin();
       pos != subrelay_list.end();
       ++pos )
  {
    subrelay *SR = *pos;
    if (SR->get_type() == spt)
      return SR;
  }
  return 0;
}

tm_ip_relay *tm_ip_relay::instance;

/****** subrelay ******/

subrelay::subrelay(serio_pkt_type spt, const char *svc,
          const char *prefix, const char*mlf_config)
    : Socket(svc, svc, Socket_TCP),
      mlf_packet_logger(svc, svc, mlf_config)
{
}

void subrelay::forward(const uint8_t *hdr, uint16_t len)
{
  // Check whether this is the start of a packet. If not,
  // use cur_file
  log_mode lmode = log_default;
  {
    for (int i = 0; prefix[i]; ++i)
    {
      if (hdr[i] != (uint8_t)prefix[i])
      {
        lmode = log_curfile;
        break;
      }
    }
  }
  log_packet(hdr, len, lmode);
  for (subrelayClientList::iterator pos = client_list.begin();
       pos != client_list.end();
       ++pos )
  {
    subrelay_client *SRC = *pos;
    SRC->forward(hdr, len);
  }
}

Socket *subrelay::new_client(const char *iname, int fd)
{
  subrelay_client *rv = new subrelay_client(this, iname, fd);
  client_list.push_back(rv);
  if (ELoop) ELoop->add_child(rv);
  return rv;
}

/****** subrelay_client ******/

subrelay_client::subrelay_client(Socket *original, const char *iname, int fd)
    : Socket(original, iname, IBUFSIZE, fd)
{
}

void subrelay_client::forward(const uint8_t *hdr, uint16_t len)
{
  if (obuf_empty())
    iwrite((char*)hdr, len);
}

/****** main() ******/

int main(int argc, char **argv)
{
  oui_init_options(argc, argv);
  {
    Loop ELoop;
    
    AppID.report_startup();
    
    tm_ip_relay *relay = tm_ip_relay::get_instance();
    relay->set_cross_exp(ip_import_cross_exp);
    ELoop.add_child(relay);
    relay->connect();
    
    Quit *Q = new Quit();
    Q->connect();
    ELoop.add_child(Q);
    
    /* TM status to collection */
    ELoop.event_loop();
    AppID.report_shutdown();
  }
}
