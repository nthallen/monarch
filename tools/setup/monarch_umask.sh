# monarch_umask.sh
# Sets umask to 02 in order to enable group write permissions in
# experiment directories shared among members of the 'flight'
# group.
# This can be copied to /etc/profile.d/monarch_umask.sh to be run
# on login.
umask 02
