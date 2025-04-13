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
  if (udp->CTS()) {
    if (len == 0) {
      serio_pkt_hdr *shdr = (serio_pkt_hdr*)hdr;
      len = sizeof(serio_pkt_hdr) + shdr->length;
    }
    msg(MSG_DBG(2), "%s: send_udp(hdr, %u)", iname, len);
    record_nbytes(len + ipx_tm_out::IP_header_len
                  + ipx_tm_out::UDP_header_len);
    udp->send_udp(hdr, len);
  }
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
  caller->tcp_txfr_requested = true;
  tcp_queue.push_back(caller);
  process_queue();
  return false;
}

void ipx_relay::process_queue()
{
  // check the status of the queue
  if (tcp_queue.empty()) return;
  record_nbytes(0); // Update mseqs_queued based on current time
  if (msecs_queued > 500) {
    TO.Set(0, msecs_queued-500);
    flags |= Fl_Timeout;
  } else if (tcp->CTS()) {
    // we can send now:
    TO.Clear();
    flags &= Fl_Timeout;
    ipx_client *rdyclt = tcp_queue.front();
    const uint8_t *pkt;
    serio_pkt_hdr *hdr;
    pkt = rdyclt->get_current_packet();
    hdr = (serio_pkt_hdr *)pkt;
    uint16_t len = hdr->length + serio::pkt_hdr_size;
    record_nbytes(len + ipx_tm_out::IP_header_len + TCP_header_len);
    tcp->send_tcp(pkt, len);
    tcp_queue.pop_front();
    rdyclt->tcp_txfr_confirmed(len);
    return;
  } else {
    msg(MSG_ERROR, "%s: !CTS() with %d msecs_queued",
      iname, msecs_queued);
    record_nbytes(1000); // An arbitrary amount
    TO.Set(0, msecs_queued > 500 ? msecs_queued-500 : 250);
    flags |= Fl_Timeout;
  }
  return;
}

bool ipx_relay::protocol_timeout()
{
  TO.Clear();
  flags &= ~Fl_Timeout;
  process_queue();
  return false;
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
  msg(MSG_DBG(1), "%s: nbytes: %d msecs_queued: %d", iname, nbytes, msecs_queued);
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
      is_UDP(xtype->is_UDP),
      outstanding_bytes(0),
      ack_bytes_pending(0)
{
  relay = ipx_relay::get_instance();
  set_obufsize(2048);
}

void ipx_client::tcp_txfr_confirmed(uint16_t nbytes)
{
  // verify the length of the current header, then
  // consume it and set the read flag (in case it
  // has been cleared).
  tcp_txfr_requested = false;
  serio_pkt_hdr *shdr = (serio_pkt_hdr *)buf;
  uint16_t len = shdr->length;
  nl_assert(nbytes == len+serio::pkt_hdr_size);
  nl_assert(nbytes <= nc);
  ack_bytes_pending += nbytes;
  if (outstanding_bytes >= 2000) // HARD_CODED PROTOCOL VALUE
  {
    send_ACK(ack_bytes_pending);
    if (ack_bytes_pending > outstanding_bytes)
    {
      msg(MSG_ERROR,
        "%s: ack_bytes_pending exceeds outstanding_bytes: %u:%u",
        iname, ack_bytes_pending, outstanding_bytes);
      outstanding_bytes = 0;
    } else
      outstanding_bytes -= ack_bytes_pending;
    ack_bytes_pending = 0;
  }
  report_ok(nbytes);
  msg(MSG_DBG(1), "%s: txfr'd: %u nc: %u", iname, nbytes, nc);
  flags |= Fl_Read;
  if (nc)
  {
    TO.Set(0, 0);
    flags |= Fl_Timeout;
  }
}

bool ipx_client::protocol_input()
{
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;
  
  // Using timeout to trigger another pass through protocol_input()
  TO.Clear();
  flags &= ~Fl_Timeout;
  while (cp < nc)
  {
    msg(MSG_DBG(1), "%s: Incoming %s %d/%d bytes",
      iname, is_UDP ? "UDP" : "TCP",  cp, nc);
    if (not_serio_pkt(have_hdr, type, length, payload))
    { // Any true return should leave the buffer almost empty
      // or with a partial packet (have_hdr)
      // Any CRC errors or oversized packets have been
      // skipped
      return false;
    }
    msg(MSG_DBG(1), "%s: serio_pkt(%u)", iname, length);
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
        cp += serio::pkt_hdr_size + length;
        report_ok(cp);
        // if (!is_UDP) iwrite("NACK\n");
        return false;
    }

    if (is_UDP)
    {
      relay->send_udp(buf);
      cp += serio::pkt_hdr_size + length;
      report_ok(cp);
      flags |= Fl_Read;
      iwrite("OK\n");
    } else {
      // Need variable and check that we don't have an outstanding request
      flags &= ~Fl_Read;
      if (!tcp_txfr_requested) {
        report_ok(cp); // make sure buf points to packet header
        outstanding_bytes += serio::pkt_hdr_size + length;
        msg(MSG_DBG(1), "%s: outstanding_bytes: %u", iname, outstanding_bytes);
        relay->send_tcp_req(this);
        break;
      }
      else
      {
        flags &= Fl_Read;
        break;
      }
    }
  }
  return false;
}

bool ipx_client::protocol_timeout()
{
  if (nc)
    return protocol_input();
  return false;
}

void ipx_client::serio_pkt_package(
    serio_pkt_hdr *hdr,
    serio_pkt_type type,
    uint8_t *payload,
    uint16_t payload_length)
{
  hdr->LRC = 0;
  hdr->type = type;
  hdr->length = payload_length;
  { unsigned CRC = crc16modbus_word(0,0,0);
    hdr->CRC = crc16modbus_word(CRC, payload, payload_length);
    uint8_t *hdrp = (uint8_t *)hdr;
    for (uint32_t i = 1; i < serio::pkt_hdr_size; ++i) {
      hdr->LRC += hdrp[i];
    }
    hdr->LRC = -hdr->LRC;
  }
}

void ipx_client::send_ACK(uint16_t nbytes)
{
  if (obuf_empty())
  {
    serio_ctrl_packet pkt;
    pkt.ctrl.subtype = ctrl_subtype_ACK;
    pkt.ctrl.reserved = 0;
    pkt.ctrl.length = nbytes;
    serio_pkt_package(&pkt.hdr, pkt_type_CTRL,
      (uint8_t*)&pkt.ctrl, sizeof(pkt.ctrl));
    iwrite((char*)&pkt, sizeof(pkt));
  } else {
    msg(MSG_ERROR, "%s: !obuf_empty() in send_ACK", iname);
  }
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
    : Client(iname, "Relay", "ip_ex", 0, serio::min_buffer_size),
      bytes_written(0),
      bytes_acknowledged(0),
      bytes_unacknowledged(0)
{
  set_obufsize(3000);
  set_retries(-1, 10, 10, false); // Never stop trying
  flags |= Fl_Read;
}

bool ipx_cmd_in::app_input() {
  bool have_hdr;
  serio_pkt_type type;
  uint16_t length;
  uint8_t *payload;
  char save_char;

  msg(MSG_DBG(1), "%s: Incoming nc: %u", iname, nc);
  while (cp < nc) {
    if (not_serio_pkt(have_hdr, type, length, payload)) {
      if (have_hdr && type != pkt_type_CMD) {
        report_err("%s: Invalid command type: '%c'", iname, type);
        ++cp; // skip over this packet header
        continue;
      }
      return false;
    }
    switch (type)
    {
      case pkt_type_CMD:
        save_char = buf[cp + serio::pkt_hdr_size + length];
        buf[cp + serio::pkt_hdr_size + length] = '\0';
        ci_sendcmd(Cmd_Send, (char *)&buf[cp + serio::pkt_hdr_size]);
        buf[cp + serio::pkt_hdr_size + length] = save_char;
        cp += serio::pkt_hdr_size + length;
        break;
      case pkt_type_CTRL:
        process_ack(payload);
        cp += serio::pkt_hdr_size + length;
        break;
      default:
        report_err("%s: Invalid command type: '%c'", iname, type);
        ++cp;
        continue;
    }
  }
  report_ok(cp);
  return false;
}

bool ipx_cmd_in::app_process_eof() {
  msg(MSG_ERROR, "%s: Connection dropped", iname);
  return reset();
}

bool ipx_cmd_in::send_tcp(const uint8_t *pkt, uint16_t len)
{
  bytes_written += len;
  bytes_unacknowledged = bytes_written - bytes_acknowledged;
  msg(MSG_DBG(1), "%s: writing %u, total written: %u unack'd: %u",
    iname, len, bytes_written, bytes_unacknowledged);
  return iwrite((const char *)pkt, len);
}

ipx_cmd_in::~ipx_cmd_in()
{
  report_bytes();
}

bool ipx_cmd_in::app_connected()
{
  report_bytes();
  bytes_written = 0;
  bytes_acknowledged = 0;
  bytes_unacknowledged = 0;
  return false;
}

void ipx_cmd_in::report_bytes()
{
  if (bytes_written || bytes_acknowledged || bytes_unacknowledged)
  {
    msg(MSG, "%s: Reconnected bytes_written: %u ack'd: %u unack'd: %u",
      bytes_written, bytes_acknowledged, bytes_unacknowledged);
  }
}

void ipx_cmd_in::process_ack(uint8_t *payload)
{
  serio_ctrl_payload *ctrl = (serio_ctrl_payload*)payload;
  if (ctrl->subtype == ctrl_subtype_ACK)
  {
    bytes_acknowledged += ctrl->length;
    bytes_unacknowledged = bytes_written - bytes_acknowledged;
    msg(MSG_DBG(1), "%s: rec'd ACK(%u) total written: %u unACK'd: %u",
      iname, ctrl->length, bytes_written, bytes_unacknowledged);
  } else
    msg(MSG_ERROR, "%s: Invalid control packet", iname);
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
  if (nl_debug_level <= MSG_DBG(1)) {
    msg(MSG_DBG(2), "%s: Send packet %d bytes", iname, pyld_nc);
    if (nl_debug_level <= MSG_DBG(2))
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
