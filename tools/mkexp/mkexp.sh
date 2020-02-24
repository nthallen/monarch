#! @SHELL_EXE@

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
export SourceDir=/usr/local/share/linkeng/setup/src

# Copy all the files
cp SourceDir/services $ExpDir/services
cp SourceDir/base.tmc $ExpDir/base.tmc
cp SourceDir/Experiment.config $ExpDir/Experiment.config
cp SourceDir/interact $ExpDir/interact
cp SourceDir/Demo.doit $ExpDir/$Experiment.doit
cp SourceDir/Demo.tbl $ExpDir/$Experiment.tbl
cp SourceDir/Demo.spec $ExpDir/$Experiment.spec
cp SourceDir/Demo.pcm $ExpDir/$Experiment.pcm
cp SourceDir/freemem.tmc $ExpDir/freemem.tmc
cp SourceDir/TMbase.genui $ExpDir/TMbase.genui
cp SourceDir/TMbase.tbl $ExpDir/TMbase.tbl
cp SourceDir/VERSION $ExpDir/VERSION

# Change the names accordingly
sed -i 's/@NAME@/'$Experiment'/g' $ExpDir/*

exit 0