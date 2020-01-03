#! /bin/bash
# Script to run on bootup as root
[ -d /var/run/linkeng ] || mkdir /var/run/linkeng
chown flight:flight /var/run/linkeng
chmod g+sw /var/run/linkeng

