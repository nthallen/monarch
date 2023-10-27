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
