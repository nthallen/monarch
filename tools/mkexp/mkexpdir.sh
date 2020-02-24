#! @SHELL_EXE@

# Make sure we are running as root
if [ `id -u` -ne 0 ]; then
  exec sudo $0 $*
fi

# Make sure we have an Experiment name
if [ "$1" != "" ]; then
  export Experiment=$1
  echo "Experiment named captured as [$1]"
else
  echo "Fatal: no Experiment name"
  exit 1
fi

# Create the Experiment directory
mkdir /home/$Experiment
chmod g+w /home/$Experiment
chown $USERNAME /home/$Experiment

# Create the corresponding bin directory
mkdir /home/$Experiment/bin
chmod g+w /home/$Experiment/bin
chown $USERNAME /home/$Experiment/bin

exit 0