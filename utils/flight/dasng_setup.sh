#! /bin/bash
# Script for initial setup of a system for DASng
# This script is part of the le-dasng installation onto the target system
# It should live in /usr/local/share/linkeng/setup
# Obviously, it should be run *after* the basic le-dasng installation

# Make sure we are running as root
if [ `id -u` -ne 0 ]; then
  exec sudo $0 $*
fi

# Check if flight user exists and add if necessary
if grep -q "^flight:" /etc/passwd; then
  echo "dasng_setup.sh: flight user already exists"
else
  adduser --disabled-password --gecos "flight user" --no-create-home flight
  echo "dasng_setup.sh: flight user created"
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
    echo "dasng_setup.sh: WARNING: authorized_keys file not found"
  fi
  chown -R flight:flight /home/flight
  chmod g+w /home/flight
  echo "dasng_setup.sh: /home/flight hierarchy created"
else
  echo "dasng_setup.sh: /home/flight already exists"
fi

service=/usr/local/share/linkeng/setup/dasng.service 
svcdest=/lib/systemd/system/dasng.service
if [ -f $service ]; then
  if [ -f $svcdest ]; then
    echo "dasng_setup.sh: Shutting down dasng service"
    systemctl stop dasng
    systemctl disable dasng
  fi
  echo "dasng_setup.sh: cp -f $service $svcdest"
  cp -f $service $svcdest
  echo "dasng_setup.sh: Copied dasng.service into /lib/systemd/system"
  echo "dasng_setup.sh: Reloading, Enabling and Starting dasng"
  systemctl daemon-reload &&
  systemctl enable dasng &&
  systemctl start dasng
  sleep 1
  systemctl status dasng
else
  echo "dasng_setup.sh: Skipping systemd configuration"
fi

