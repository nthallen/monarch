#! /bin/bash

# Make sure we are running as root
if [ `id -u` -ne 0 ]; then
  exec sudo $0 $*
fi

# Make sure we have an experiment name
if [ "$1" != "" ]; then
  export Experiment=$1
  echo "Experiment named captured as [$1]"
else
  echo "Fatal: no Experiment name"
  exit 1
fi

# Uncertain about invocation?
# Create the proper directories
mkexpdir $Experiment
export ExpDir=/home/$Experiment

# Copy all the files
cp src/services $ExpDir/services
cp src/base.tmc $ExpDir/base.tmc
cp src/Experiment.config $ExpDir/Experiment.config
cp src/interact $ExpDir/interact
cp src/Demo.doit $ExpDir/$Experiment.doit
cp src/Demo.tbl $ExpDir/$Experiment.tbl
cp src/Demo.spec $ExpDir/$Experiment.spec
cp src/Demo.pcm $ExpDir/$Experiment.pcm
cp src/freemem.tmc $ExpDir/freemem.tmc
cp src/TMbase.genui $ExpDir/TMbase.genui
cp src/TMbase.tbl $ExpDir/TMbase.tbl
cp src/VERSION $ExpDir/VERSION

# Change the names accordingly
sed -i 's/@NAME@/'$Experiment'/g' $ExpDir/*

exit 0