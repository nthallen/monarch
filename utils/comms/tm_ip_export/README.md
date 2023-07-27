# tm_ip_export

**tm_ip_export** is a utility that runs on a flight computer to transfer
commands up from and telemetry down to a relay node on the internet.
The anticipated environment is where the flight computer is connected to
the internet via a satellite modem, but this would also work for any
remote but connected system operating behind firewalls and/or NAT
barriers.

tm_ip_export establishes the initial connection via TCP to tm_ip_import
running on the relay node. Once the connection is established, tm_ip_import
uses the connection to forward commands to the flight computer.

In parallel, tm_ip_export sends telemetry data via UDP to the same relay
node using the same port number as the command link's TCP port.

Invocation:
```
tm_ip_export -HRelay:<relay_IP> -HUplink:<local_uplink_interface_ip>
```

It is still to be determined exactly how this will be orchestrated
in the case where we are down-sampling the telemetry frame for a
reduced-bandwidth connection. It probably involves running two
different Monarch services, one for the primary stream and one for
the down-sampled secondary stream.
