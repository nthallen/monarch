/** @file tm_ip_export.cc
 */
#include <cstring>
#include "tm_ip_export.h"
#include "crc16modbus.h"
#include "dasio/cmd_writer.h"
#include "dasio/tm.h"
#include "dasio/appid.h"
#include "dasio/ascii_escape.h"
#include "nl.h"
#include "nl_assert.h"
#include "oui.h"

ipx_relay::ipx_relay(const char *iname, ipx_tm_out *udp, ipx_cmd_in *tcp)
      : Interface(iname, 0),
        udp(udp),
        tcp(tcp),
        msecs_queued(0)
{
}

bool ipx_relay::send_udp(const uint8_t *hdr, uint16_t len)
{
  // do the necessary bookkeeping, then forward to ipx_tm_out
  if (udp->CTS())
  if (len == 0) {
    serio_pkt_hdr *shdr = (serio_pkt_hdr*)hdr;
    len = sizeof(serio_pkt_hdr) + shdr->length;
  }
  record_nbytes(len + ipx_tm_out::IP_header_len
                + ipx_tm_out::UDP_header_len);
  udp->send_udp(hdr, len);
  return false;
}

bool ipx_relay::send_tcp_req(ipx_client *caller)
{
  // enqueue the request
  if (caller->tcp_txfr_requested) {
    if (tcp_queue.empty()) {
      msg(MSG_ERROR,
        "%s: tcp_txfr_requested not cleared on empty queue",
        iname);
    } else {
      // Is it already in the queue?
      msg(MSG_ERROR,
        "%s: tcp_txfr_requested not cleared on non-empty queue",
        iname);
    }
  }
  tcp_queue.push_back(caller);
  process_queue();
  return false;
}

void ipx_relay::process_queue()
{
  // check the status of the queue
  if (tcp_queue.empty()) return;
  ipx_client *rdyclt = tcp_queue.front();
  record_nbytes(0);
  if (msecs_queued > 500) {
    TO.Set(0, msecs_queued-500);
    flags |= Fl_Timeout;
  } else if (tcp->CTS()) {
    // we can send now:
    const uint8_t *pkt;
    serio_pkt_hdr *hdr;
    pkt = rdyclt->get_current_packet();
    hdr = (serio_pkt_hdr *)pkt;
    uint16_t len = hdr->length;
    record_nbytes(len + ipx_tm_out::IP_header_len + TCP_header_len);
    tcp->send_tcp(pkt, len);
    flags &= Fl_Timeout;
    return;
  } else {
    msg(MSG_ERROR, "%s: !CTS() with %d msecs_queued", iname, msecs_queued);
    record_nbytes(1000); // An arbitrary amount
    TO.Set(0, msecs_queued > 500 ? msecs_queued-500 : 250);
    flags |= Fl_Timeout;
  }
  return;
}

void ipx_relay::record_nbytes(int nbytes)
{
  struct timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  if (msecs_queued) {
    time_t secs_elapsed = now.tv_sec - when_queued.tv_sec;
    long nsecs_elapsed = now.tv_nsec - when_queued.tv_nsec;
    long msecs_elapsed = (secs_elapsed*1000) + (nsecs_elapsed/1000000);
    if (msecs_elapsed > msecs_queued)
      msecs_queued = 0;
    else
      msecs_queued -= msecs_elapsed;
  }
  int msecs = (nbytes*8)/21; // kbps
  msecs_queued += msecs;
  when_queued = now;
}

ipx_relay *ipx_relay::get_instance()
{
  if (!instance) {
    msg(MSG_FATAL, "ipx_relay: Instance not predefined");
  }
  return instance;
}

ipx_relay *ipx_relay::instance;

const char *ip_export_cross_exp;

ipx_type ipx_tcp(false);
ipx_type ipx_udp(true);

ipx_client::ipx_client(Authenticator *auth, const char *iname, ipx_type *xtype)
    : Serverside_client(auth, iname, 2048),
      is_UDP(xtype->is_UDP)
{
  relay = ipx_relay::get_instance();
  set_obufsize(2048);
}

void ipx_client::xfer_confirmed(uint16_t nbytes)
{
  // verify the length of the current header, then
  // consume it and set the read flag (in case it
  // has been cleared).
  serio_pkt_hdr *shdr = (serio_pkt_hdr *)buf;
  uint16_t len = shdr->length;
  nl_assert(nbytes == len);
  nl_assert(nbytes <= nc);
  report_ok(nbytes);
  flags |= Fl_Read;
}

bool ipx_client::protocol_input()
{
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;
  msg(MSG_DBG(1), "%s: Incoming %d bytes", iname, nc);
  if (not_serio_pkt(have_hdr, type, length, payload))
  { /* We do not expect partial packets unless the input buffer
     * has filled (nc == bufsize)
     */
    if (nc - cp < sizeof(serio_pkt_hdr)) {
      if (nc == bufsize) {
        if (cp) consume(cp);
        else flags &= ~Fl_Read;
        return false;
      }
    } else if (have_hdr && cp + sizeof(serio_pkt_hdr)+length + 1 > nc) {
      if (nc == bufsize) {
        if (cp) consume(cp);
        else flags &= ~Fl_Read;
        return false;
      }
      /* We could reach here if the buffer filled on the 2nd or 3rd
       * packet, and we subsequently consumed the first. */
    } else {
      report_err("%s: Internal: cp:%d length:%d nc:%d bufsize:%d",
        iname, cp, length, nc, bufsize);
      consume(cp);
    }
  }
  // Now we have a valid packet. Since this interface is for side-channel
  // data, it should not be of a type used for internal data
  switch (type) {
    case pkt_type_NULL:
    case pkt_type_TM:
    case pkt_type_CMD:
      report_err(isgraph(type)
          ? "%s: Invalid packet type '%c' in side channel"
          : "%s: Invalid packet type %u in side channel",
          iname, type);
      cp += sizeof(serio_pkt_hdr) + length;
      report_ok(cp);
      return false;
  }

  if (is_UDP)
  {
    relay->send_udp(buf);
    cp += sizeof(serio_pkt_hdr) + length;
    report_ok(cp);
    flags |= Fl_Read;
  } else {
    // Need variable and check that we don't have an outstanding request
    flags &= ~Fl_Read;
    report_ok(cp); // make sure buf points to packet header
    relay->send_tcp_req(this);
  }
  return false;
}

void ipx_client::attach(Server *S, ipx_type *xtype)
{
  S->add_subservice(
    new SubService(xtype->is_UDP ? "ipx/udp" : "ipx/tcp",
                    new_ipx_client, (void*)xtype));
}

Serverside_client *ipx_client::new_ipx_client(
        Authenticator *auth, SubService *SS)
{
  return new ipx_client(auth, auth->get_client_app(), (ipx_type*)(SS->svc_data));
}


/**
 * Establishes connection to the Relay node and receives
 * commands.
 */
ipx_cmd_in::ipx_cmd_in(const char *iname)
    : Client(iname, "Relay", "ip_ex", 0, serio::min_buffer_size)
{
  set_obufsize(3000);
  set_retries(-1, 10, 10, false); // Never stop trying
}

bool ipx_cmd_in::app_input() {
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;

  while (cp < nc) {
    if (not_serio_pkt(have_hdr, type, length, payload)) {
      if (have_hdr && type != pkt_type_CMD) {
        report_err("%s: Invalid command type: '%c'", iname, type);
        ++cp; // skip over this packet header
        continue;
      }
      return false;
    }
    if (type != pkt_type_CMD) {
      report_err("%s: Invalid command type: '%c'", iname, type);
      ++cp;
      continue;
    }
    char save_char = buf[cp + serio::pkt_hdr_size + length];
    buf[cp + serio::pkt_hdr_size + length] = '\0';
    ci_sendcmd(Cmd_Send, (char *)&buf[cp + serio::pkt_hdr_size]);
    buf[cp + serio::pkt_hdr_size + length] = save_char;
    cp += serio::pkt_hdr_size + length;
  }
  report_ok(cp);
  return false;
}

bool ipx_cmd_in::send_tcp(const uint8_t *pkt, uint16_t len)
{
  return iwrite((const char *)pkt, len);
}

bool ipx_cmd_in::process_eof() {
  msg(MSG_ERROR, "%s: Connection dropped", iname);
  return reset();
}

ipx_tm_out::ipx_tm_out(const char *iname)
    : Socket(iname, "Relay", "ip_ex", 0, UDP_WRITE),
      dropping_tx_rows(false),
      n_tx_rows_dropped(0),
      total_tx_rows_dropped(0),
      MTU(max_MTU),
      pyld_nc(0),
      relay(0)
{
  max_udp_payload = max_MTU - IP_header_len - UDP_header_len;
  payload = (uint8_t *)new_memory(max_udp_payload);
  set_obufsize(max_udp_payload);
}

ipx_tm_out::~ipx_tm_out() {
  msg(MSG, "%s: Destructing", iname);
  if (dropping_tx_rows) {
    msg(MSG, "%s: dropping %d rows", iname, n_tx_rows_dropped);
  }
  if (total_tx_rows_dropped || n_tx_rows_dropped) {
    msg(MSG, "%s: total rows dropped: %d", iname,
      n_tx_rows_dropped + total_tx_rows_dropped);
  }
}

void ipx_tm_out::update_MTU(int new_MTU) {
  if (new_MTU > max_MTU) {
    msg(MSG_ERROR, "%s: Requested MTU %d exceeds max %d",
      iname, new_MTU, max_MTU);
    new_MTU = max_MTU;
  }
  MTU = new_MTU;
  max_udp_payload = new_MTU - IP_header_len - UDP_header_len;
}

/**
 * @param MFCtr
 * @param raw The raw homerow data without the leading MFCtr or
 *    trailing Synch
 */
void ipx_tm_out::send_row(uint16_t MFCtr, const uint8_t *raw) {
  if (obuf_empty()) {
    if (dropping_tx_rows) {
      msg(MSG_DEBUG, "%s: Tx resumed after dropping %d rows",
        iname, n_tx_rows_dropped);
      dropping_tx_rows = false;
      total_tx_rows_dropped += n_tx_rows_dropped;
      dropping_tx_rows = false;
      n_tx_rows_dropped = 0;
    }
    int rowsize = sizeof(serio_pkt_hdr) + sizeof(MFCtr) + tm_info.tm.nbminf - 4;
    if (pyld_nc + rowsize >= max_udp_payload)
      flush();

    // We have allocated an obuf, so we can use auto vars for
    // io and hdr
    serio_pkt_hdr hdr;
    hdr.LRC = 0;
    hdr.type = pkt_type_TM;
    hdr.length = tm_info.tm.nbminf-2;

    int hdr_offset = pyld_nc;
    pyld_nc += sizeof(serio_pkt_hdr);
    int mfc_offset = pyld_nc;
    memcpy(&payload[pyld_nc], &MFCtr, sizeof(MFCtr));
    pyld_nc += sizeof(MFCtr);
    memcpy(&payload[pyld_nc], (void*)raw, tm_info.tm.nbminf - 4);
    pyld_nc += tm_info.tm.nbminf - 4;
    
    // Calculate the CRC of io[1] and io[2]
    { unsigned CRC = crc16modbus_word(0,0,0);
      CRC = crc16modbus_word(CRC, &payload[mfc_offset], pyld_nc-mfc_offset);
      hdr.CRC = CRC;
      uint8_t *hdrp = (uint8_t *)&hdr;
      for (int i = 1; i < sizeof(serio_pkt_hdr); ++i) {
        hdr.LRC += hdrp[i];
      }
      hdr.LRC = -hdr.LRC;
    }
    memcpy(&payload[hdr_offset],&hdr,sizeof(serio_pkt_hdr));
    if (pyld_nc + rowsize >= max_udp_payload)
      flush();
    rows_this_row = 0;
  } else {
    if (!dropping_tx_rows) {
      msg(MSG_DEBUG, "%s: dropping MFCtr %u", iname, MFCtr);
      dropping_tx_rows = true;
    }
    ++n_tx_rows_dropped;
  }
}

void ipx_tm_out::flush() {
  if (nl_debug_level <= MSG_DEBUG) {
    msg(MSG_DEBUG, "%s: Send packet %d bytes", iname, pyld_nc);
    dump_hex(MSG, iname, payload, pyld_nc);
  }
  if (!relay) relay = ipx_relay::get_instance();
  relay->send_udp((uint8_t *)payload, pyld_nc);
  pyld_nc = 0;
}

void ipx_tm_out::send_udp(const uint8_t *data, int length)
{
  iwrite((char*)data, length);
}

ipx_tm_in::ipx_tm_in(ipx_tm_out *tm_out)
    : tm_client(1024),
      tm_out(tm_out)
{}

ipx_tm_in::~ipx_tm_in() {
}

// Extracted and adapted from extmain.skel
unsigned int ipx_tm_in::process_data() {
  const uint8_t *raw;
  int n_rows = rows_in_buf;
  uint16_t MFCtr = buf_mfctr;
  majf_row = (((uint16_t)MFCtr) % tmi(nrowmajf));

  for ( raw = data_row; n_rows > 0; --n_rows, raw += nbQrow ) {
    tm_out->send_row(MFCtr, raw);
    majf_row = (majf_row == tmi(nrowmajf)-1) ? 0 : (majf_row+1);
    ++MFCtr;
  }
  next_minor_frame = MFCtr;
  return rows_in_buf;
}

void ipx_tm_in::process_init() {
  memcpy(&tm_info, &tm_msg->body.init.tm, sizeof(tm_dac_t));
  tm_rcvr::process_init();
}

void ipx_tm_in::process_quit() {
  msg(MSG, "%s: process_quit()", iname);
  ELoop->set_loop_exit();
}

ipx_ctrl::ipx_ctrl(const char *iname, const char *cmdchannel,
                    ipx_tm_out *tm_out)
    : Cmd_reader(iname, 80, cmdchannel),
      tm_out(tm_out) {}

bool ipx_ctrl::app_input() {
  uint16_t new_MTU;
  if (buf[cp] == 'Q') {
    msg(MSG, "%s: process_quit()", iname);
    ELoop->set_loop_exit();
  } else if (not_str("M") || not_uint16(new_MTU)) {
    msg(MSG_ERROR, "%s: Invalid command: '%s'",
      iname, ascii_escape());
  } else {
    msg(MSG, "%s: Updating MTU to %u", iname, new_MTU);
    tm_out->update_MTU(new_MTU);
  }
  consume(nc);
  return false;
}

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  AppID.report_startup();
  { Server S("ipx");

    ipx_client::attach(&S, &ipx_udp);
    ipx_client::attach(&S, &ipx_tcp);
  
    ipx_cmd_in *cmd_in = new ipx_cmd_in("cmd_in");
    cmd_in->set_cross_exp(ip_export_cross_exp);
    S.ELoop.add_child(cmd_in);
    cmd_in->connect();
    
    ipx_tm_out *tm_out = new ipx_tm_out("tm_out");
    S.ELoop.add_child(tm_out);
    tm_out->connect();

    ipx_relay::set_instance(new ipx_relay("relay", tm_out, cmd_in));
    S.ELoop.add_child(ipx_relay::get_instance());

    // tm_client iname is hard-coded to tm_client
    ipx_tm_in *tm_in = new ipx_tm_in(tm_out);
    S.ELoop.add_child(tm_in);
    tm_in->connect();
    
    ipx_ctrl *ctrl = new ipx_ctrl("ctrl", "TMIPX", tm_out);
    S.ELoop.add_child(ctrl);
    ctrl->connect();

    msg(MSG_DEBUG, "Entering Server Start");    
    S.Start(Server::Srv_Unix);
  }
  AppID.report_shutdown();
  return 0;
}
