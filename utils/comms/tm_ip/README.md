# tm_ip

**tm_ip_export** and **tm_ip_import** together provide basic
command and telemetry communication between two systems over
the internet. Telemetry is transmitted from tm_ip_export to
tm_ip_import over UDP. tm_ip_export also opens a TCP connection
to tm_ip_import, which then sends commands back.

The anticipated environment is where the flight computer running
tm_ip_export is connected to the internet via a satellite modem,
but this would also work for any remote but connected system
operating behind firewalls and/or NAT barriers. The system
running tm_ip_import must have one port accessible from the
internet on both TCP and UDP.

Ordinarily, I would have tm_ip_export acknowledge commands back
to tm_ip_import, but that would steal bandwidth from telemetry.
I might consider sending responses in specific cases or on
request.

3/28/2025
Adding support for side channel data.

Senders will connect with a Client connection to the 'ip_ex/tcp' or
'ip_ex/udp' service, and then can begin sending packets.

Incoming data should be pre-packetized in serio_pkt format using
an appropriate packet type for side channel data.

Packets should be small enough to be transmitted in less than a
second. Packets will not be forwarded until the entire packet is
received. tm_ip_export will need to be aware of bandwidth
limitations.

After sending a packet, sender must wait for a positive
acknowlegement "OK\n" before sending additional data.

tm_ip_export will forward the side channel data to tm_ip_import
over either the TCP connection or via UDP, depending on the
service. The TCP connection will also need positive acknowledgement
to continue sending. As of 3/28/2025, the TCP connection has only
been used for uplink packetized commands. I suggest:

Downlink tm_ip_export can forward up to 2 seconds of data before
requiring an acknowledgement. pkt_type_CTRL will be defined to
support the following functions:
  - Keep Alive (nop)
  - Acknowledge
    Identifying the last block? not enough info in the hdr for that
    Identifying the number of bytes received since last ack