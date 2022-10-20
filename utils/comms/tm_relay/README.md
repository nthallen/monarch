# tm_relay

**tm_relay** is a TM generator that obtains its telemetry data from a remote node.

Specify the remote host from which you will receive telemetry as:
```
tm_relay -H bfr:$remote_host
```
There is another bfr function, `bfr-input`, that specifies where to send the
telemetry data.
