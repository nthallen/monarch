#! /bin/bash

if [ "$1" != "" ]; then
  export Experiment=$1
  echo "Experiment named captured as [$1]"
else
  echo "Fatal: no Experiment name"
  exit 1
fi

sudo mkdir /home/$Experiment
sudo chmod g+w /home/$Experiment
sudo chown $USERNAME /home/$Experiment

sudo mkdir /home/$Experiment/src
sudo chmod g+w /home/$Experiment/src
sudo chown $USERNAME /home/$Experiment/src

sudo mkdir /home/$Experiment/src/TM
sudo chmod g+w /home/$Experiment/src/TM
sudo chown $USERNAME /home/$Experiment/src/TM

exit 0