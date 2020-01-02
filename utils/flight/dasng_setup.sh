#! /bin/bash
# Script for initial setup of a system for DASng
# This script is part of the le-dasng installation onto the target system
# It should live in /usr/local/share/linkeng/setup
# Obviously, it should be run *after* the basic le-dasng installation


# Check if flight user exists and add if necessary
if grep -q "^flight:" /etc/passwd; then
  echo "dasng_setup.sh: flight user already exists"
else
  adduser --disabled-password --gecos "flight user" --no-create-home flight
  echo "dasng_setup.sh: flight user created"
fi

# setup the /home/flight directory 
if [ ! -d /home/flight ]; then
  mkdir -p /home/flight/.ssh
  mkdir -p /home/flight/.config/systemd/user
  
  cp /usr/local/share/linkeng/setup/dasng.service /home/flight/.config/systemd/user/
  if [ -f ~/.ssh/authorized_keys ]; then
    cp ~/.ssh/authorized_keys /home/flight/.ssh/
  else
    echo "dasng_setup.sh: WARNING: authorized_keys file not found"
  fi
  chown -R flight:flight /home/flight
  chmod g+w /home/flight
  echo "dasng_setup.sh: /home/flight hierarchy created"
else
  echo "dasng_setup.sh: /home/flight already exists"
fi
