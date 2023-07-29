# tm_ip_import

**tm_ip_import** is a utility that is designed to run on a relay
node on the internet to transfer commands up to and telemetry
down from a flight instrument on the internet. Like tm_ip_export,
the anticipated environment is where the flight computer is
connected to the internet via a satellite modem, but this would
also work for any remote but connected system operating behind
firewalls and/or NAT barriers.

tm_ip_export establishes the initial connection via TCP to
tm_ip_import running on the relay node. Once the connection
is established, tm_ip_import uses the connection to forward
commands to the flight computer.

Ordinarily, I would have tm_ip_export acknowledge commands back
to tm_ip_import, but that would steal bandwidth from telemetry.
I might consider sending responses in specific cases or on
request.

In parallel, tm_ip_export sends telemetry data via UDP to the
tm_ip_import using the same port number as the command link's
TCP port.
