#! /bin/bash
project=$1

function errmsg {
  echo "gitscript.sh: $*" >&1
  exit 1
}

if [ $(id -un) = git ]; then
  echo "Running as git:"
  cd /srv/git
  mkdir .ssh && chmod 700 .ssh
  touch .ssh/authorized_keys && chmod 600 .ssh/authorized_keys
  if [ -n "$project" ]; then
    mkdir ${project}.git
    cd ${project}.git
    git init --bare
  fi
elif [ $(id -un) = root ]; then
  echo "Running as root:"
  echo "Duplicating authorized keys"
  cat /home/flight/.ssh/authorized_keys > /srv/git/.ssh/authorized_keys
else
  echo "Running as $(id -un):"
  grep -q "^git:" /etc/passwd || {
    echo Creating user git
    sudo adduser --disabled-password --gecos "Git Server" --home /srv/git \
            --shell /bin/bash git
  }
  [ -d /home/flight ] || errmsg "/home/flight does not exist"
  [ -d /srv/git ] || errmsg "/srv/git does not exist"
  sudo -u git $0 $1
  sudo $0 $1
fi
