# sspdrv: Scalable Signal Processor Monarch Driver

This SSP driver is ported from the original
[QNX driver](https://github.com/nthallen/arp-das/tree/master/drivers/ssp_driver).
The interface to the SSP board is defined in the
[SSP Manual](https://www.arp.harvard.edu/eng/elec/SSP_Manual_v1.0.pdf).
The syntax of commands to this driver is very similar to the command syntax
for the board with a few exceptions.

 - The driver accepts multiple space-separated commands
 - Additional commands have been added:
   - LD Logging Disable
   - LE Logging Enable
   - nZ:xxxx Number of samples with laser off at the start of scan (0 to nZ-1)
   - nN:xxxx Starting sample for noise calculations
   - nM:xxxx Ending sample for noise calculations
   - XR Reset TCP and UDP connections
   - XX Terminate the driver
   - Q  Terminate the driver (to match Monarch standard)
 - The trigger level commands N[UD] have been rewritten as T[UD] to make
   parsing a little easier. This is true on the board as well, but has
   not been documented.

The full driver command syntax is specified in sspdrv.cc at SSP_Cmd::app_input().

The TCP connection is derived from DAS_IO::Socket and uses the function 'SSP' and
the service 'SSP'.

The function is used to specify the SSP's IP address on the command line using the
-H option: -H SSP:10.0.0.200

The service is used specify the port number for the TCP connection. This must be
defined in the project's services file. The following line must be present:

  SSP 1500

