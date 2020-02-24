#! @SHELL_EXE@

function nl_error {
  echo "interact: $*" >&2
  exit 1
}

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

[ -d /home/flight ] || nl_error "missing directory /home/flight"
[ -d /home/$Experiment ] || nl_error "missing directory /home/$Experiment"
[ -e /home/$Experiment/Experiment.config ] || nl_error "missing /home/$Experiment/Experiment.config"
[ -e /home/flight/Experiment/config ] || nl_error "missing /home/flight/Experiment.config"

ln -sf /home/$Experiment/Experiment.config /home/flight/Experiment.config
systemctl restart dasng

exit 0