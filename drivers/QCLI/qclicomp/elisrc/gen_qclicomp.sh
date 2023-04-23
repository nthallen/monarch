#! /bin/bash
# Script called from CMakeLists.txt to run eli to gneerate nctable
eli=$1
specs=$2
output=$3
rm -f $output
$eli "$specs :exe >$output"
