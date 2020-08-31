#! /bin/bash
# This is a script to undo what we did in dasng_setup.sh
# This is mostly for development purposes, so that we can
# test the setup process repeatedly until it's right.

function nl_error {
  echo "dasng_reset.sh ERROR: $*" >&2
  exit 1
}

[ `id -u` -ne 0 ] && nl_error "Must be run as root"

# Shutdown, disable and/or remove the dasng service(s)
if [ -f /lib/systemd/system/dasng.service ]; then
  echo "dasng_reset.sh: Removing dasng service"
  systemctl stop dasng
  systemctl disable dasng
  rm -f /lib/systemd/system/dasng.service
  systemctl daemon-reload # try to make it stick!
fi

# Remove the /home/flight directory
if [ -d /home/flight ]; then
  rm -rf /home/flight
  echo "dasng_reset.sh: deleted /home/flight"
else
  echo "dasng_reset.sh: /home/flight does not exist"
fi

[ -d /home/flight ] &&
  echo "dasng_reset.sh: [ERROR] failed to remove /home/flight directory"

# Delete the flight user
#  deluser flight will remove the flight group if there are no other
#    members.
if grep -q "^flight:" /etc/passwd; then
  deluser flight 2>&1 >/dev/null
  if grep -q "^flight:" /etc/group; then
    delgroup flight 2>&1 >/dev/null
    echo "dasng_reset.sh: deleted flight user and group (explicitly)"
  else
    echo "dasng_reset.sh: deleted flight user and group"
  fi
elif grep -q "^flight:" /etc/group; then
  delgroup flight 2>&1 >/dev/null
  echo "dasng_reset.sh: flight user did not exist, deleted flight group"
fi

if grep -q "^flight:" /etc/passwd /etc/group; then
  echo "dasng_reset.sh: [ERROR] failed to remove flight user or group:"
  grep "^flight:" /etc/passwd /etc/group
fi
