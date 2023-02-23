# This can be copied to /etc/profile.d/ssh_agent.sh to be run on
# the first invocation of the shell after reboot.
SSH_ENV="$HOME/.ssh/environment"

function start_agent {
     echo "Initialising new SSH agent..."
     rm -rf /tmp/ssh-* 2> /dev/null
     /usr/bin/ssh-agent | sed 's/^echo/#echo/' > "${SSH_ENV}"
     echo succeeded
     chmod 600 "${SSH_ENV}"
     . "${SSH_ENV}" > /dev/null
     /usr/bin/ssh-add;
}

# Source SSH settings, if applicable

[ -d ~/.ssh ] || mkdir ~/.ssh

if [ -f "${SSH_ENV}" ]; then
  . "${SSH_ENV}" > /dev/null
  if [ -z "${SSH_AGENT_PID}" ] || ! kill -0 ${SSH_AGENT_PID} 2>/dev/null; then
    start_agent
  fi
else
  start_agent
fi
