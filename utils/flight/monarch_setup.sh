#! /bin/bash
# Script for initial setup of a system for Monarch.
# This script is part of the Monarch installation onto the target system
# It should live in /usr/local/share/monarch/setup
# Obviously, it should be run *after* the basic monarch installation

# Make sure we are running as root
if [ `id -u` -ne 0 ]; then
  exec sudo $0 $*
fi

# Check if flight user exists and add if necessary
if grep -q "^flight:" /etc/passwd; then
  echo "monarch_setup.sh: flight user already exists"
else
  adduser --disabled-password --gecos "flight user" --no-create-home flight
  echo "monarch_setup.sh: flight user created"
fi
[ -n "$SUDO_USER" ] && adduser $SUDO_USER flight

# setup the /home/flight directory 
if [ ! -d /home/flight ]; then
  mkdir -p /home/flight/.ssh
  
  HOMEDIR=`eval echo ~$SUDO_USER`
  echo "HOMEDIR = $HOMEDIR"
  if [ -f $HOMEDIR/.ssh/authorized_keys ]; then
    echo "Copying ssh keys from ~$SUDO_USER/.ssh"
    cp $HOMEDIR/.ssh/authorized_keys /home/flight/.ssh/
  else
    echo "monarch_setup.sh: WARNING: authorized_keys file not found"
  fi
  chown -R flight:flight /home/flight
  echo "monarch_setup.sh: /home/flight hierarchy created"
else
  echo "monarch_setup.sh: /home/flight already exists"
fi

for obsfile in sbin/flight.sh bin/dasctl; do
  if [ -f /usr/local/$obsfile ]; then
    echo "monarch_setup.sh: removing obsolete file /usr/local/$obsfile"
    rm -f /usr/local/$obsfile
  fi
done

for obsdir in oui linkeng; do
  if [ -d /usr/local/share/$obsdir ]; then
    echo "monarch_setup.sh: removing obsolete directory /usr/local/share/$obsdir"
    rm -rv /usr/local/share/$obsdir
  fi
done

service=/usr/local/share/monarch/setup/monarch.service 
svcdest=/lib/systemd/system/monarch.service
if [ -f $service ]; then
  if [ -f $svcdest ]; then
    echo "monarch_setup.sh: Shutting down monarch service"
    systemctl stop monarch
    systemctl disable monarch
  fi
  echo "monarch_setup.sh: cp -f $service $svcdest"
  cp -f $service $svcdest
  echo "monarch_setup.sh: Copied monarch.service into /lib/systemd/system"
  echo "monarch_setup.sh: Reloading, Enabling and Starting monarch"
  systemctl daemon-reload &&
  systemctl enable monarch &&
  systemctl start monarch
  sleep 1
  systemctl status monarch
else
  echo "monarch_setup.sh: Skipping systemd configuration"
fi

