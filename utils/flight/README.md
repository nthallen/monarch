# Flight utilities
This directory holds scripts and configurations to tie
the Monarch architecture into the operating system's
boot up process. For Linux, this means creating one or
more systemd services. This will be handled differently
for other operating systems.

The following information will be moved into CMakeLists.txt
eventually, but these are notes for that development.

Installation:
- flight.sh => /usr/local/sbin
- add_auth_key.sh => /usr/local/sbin
- monarch.service => /lib/systemd/system
- monarch_setup.sh => /usr/local/share/monarch/setup
- monarch_reset.sh => /usr/local/share/monarch/setup

### Start monarch 
`sudo systemctl start monarch`

### Setup monarch to run at boot time (requires monarch-run)
`sudo systemctl enable monarch`

### Get status information
`systemctl status monarch`

