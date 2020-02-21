#! /bin/bash

if [ "$1" != "" ]; then
  export Experiment=$1
  echo "Experiment named captured as [$1]"
else
  echo "Fatal: no Experiment name"
  exit 1
fi

sudo mkexpdir $Experiment

export ExpDir=/home/$Experiment/src/TM

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

#sudo sed 's/Demo/'$Experiment'/g' $ExpDir/*
sudo sed -i 's/@NAME@/'$Experiment'/g' $ExpDir/*

exit 0