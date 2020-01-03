# Flight utilities
This directory holds scripts and configurations to tie
the DASng architecture into the operating system's
boot up process. For Linux, this means creating one or
more systemd services. This will be handled differently
for other operating systems.

The following information will be moved into CMakeLists.txt
eventually, but these are notes for that development.

Installation:
- flight.sh => /usr/local/sbin
- add_auth_key.sh => /usr/local/sbin
- dasng.service => /lib/systemd/system
- dasng_setup.sh => /usr/local/share/linkeng/setup
- dasng_reset.sh => /usr/local/share/linkeng/setup

### Start dasng 
`sudo systemctl start dasng`

### Setup dasng to run at boot time (requires dasng-run)
`sudo systemctl enable dasng`

### Get status information
`systemctl status dasng`

