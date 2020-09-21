#! /bin/bash
# This is a script to undo what we did in monarch_setup.sh
# This is mostly for development purposes, so that we can
# test the setup process repeatedly until it's right.

function nl_error {
  echo "monarch_reset.sh ERROR: $*" >&2
  exit 1
}

if [ "$(uname -o)" = "Cygwin" ]; then
  rundir=/var/run/monarch
  passwd=/etc/passwd
  nss=/etc/nsswitch.conf

  if [ -f $nss.monarch ]; then
    echo "Performing Monarch reset for Cygwin"
    rm -rf $rundir $passwd $nss
    mv $nss.monarch $nss
  else
    nl_error $nss.monarch not found
  fi
  exit 0
fi

[ `id -u` -ne 0 ] && nl_error "Must be run as root"

# Shutdown, disable and/or remove the monarch service(s)
if [ -f /lib/systemd/system/monarch.service ]; then
  echo "monarch_reset.sh: Removing monarch service"
  systemctl stop monarch
  systemctl disable monarch
  rm -f /lib/systemd/system/monarch.service
  systemctl daemon-reload # try to make it stick!
fi

# Remove the /home/flight directory
if [ -d /home/flight ]; then
  rm -rf /home/flight
  echo "monarch_reset.sh: deleted /home/flight"
else
  echo "monarch_reset.sh: /home/flight does not exist"
fi

[ -d /home/flight ] &&
  echo "monarch_reset.sh: [ERROR] failed to remove /home/flight directory"

# Delete the flight user
#  deluser flight will remove the flight group if there are no other
#    members.
if grep -q "^flight:" /etc/passwd; then
  deluser flight 2>&1 >/dev/null
  if grep -q "^flight:" /etc/group; then
    delgroup flight 2>&1 >/dev/null
    echo "monarch_reset.sh: deleted flight user and group (explicitly)"
  else
    echo "monarch_reset.sh: deleted flight user and group"
  fi
elif grep -q "^flight:" /etc/group; then
  delgroup flight 2>&1 >/dev/null
  echo "monarch_reset.sh: flight user did not exist, deleted flight group"
fi

if grep -q "^flight:" /etc/passwd /etc/group; then
  echo "monarch_reset.sh: [ERROR] failed to remove flight user or group:"
  grep "^flight:" /etc/passwd /etc/group
fi
