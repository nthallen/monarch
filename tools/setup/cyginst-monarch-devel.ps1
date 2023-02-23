#
# cyginst-monarch-devel.ps1
#
# Setup script to install Cygwin and/or all the packages necessary to
# build the Monarch architecture under Cygwin on Windows.
#
# ----------
# Invocation:
# ----------
#
# The recommended way to run this script is to:
#  - bring up Windows File Explorer (nee Windows Explorer)
#  - navigate to $monarch_source_root\utils\flight
#    - Pro Tip: You can cut and paste into the address bar!
#  - right-click on this file and select "Run with PowerShell"
#
# --------------------
# Alternate Invocation:
# --------------------
# 
# This script can also be run from a Windows Cmd shell as:
# > cd $monarch_source_root\utils\flight
# > PowerShell -ExecutionPolicy Bypass .\monarch-win-setup.ps1

$curloc = Get-Location
Set-Location $env:USERPROFILE\Downloads
if (-not (Test-Path -Path setup-x86_64.exe -PathType Leaf))
{ # need to download the program
  $url = "https://cygwin.com/setup-x86_64.exe"
  [Net.ServicePointManager]::SecurityProtocol = "tls12, tls11, tls"
  write-host "Need to download cygwin setup from $url"
  $dest = "setup-x86_64.exe"
  $start_time = Get-Date
  Invoke-WebRequest -Uri $url -OutFile $dest
  Write-Output "Time taken: $((Get-Date).Subtract($start_time).Seconds) second(s)"
}

if (Test-Path -Path setup-x86_64.exe -PathType Leaf)
{
  start-process setup-x86_64.exe  -Wait -argumentlist "--packages bzip2,cygwin-doc,file,less,openssh,git,chere,cmake,doxygen,graphviz,gcc-core,gcc-g++,gdb,make,bison,flex,perl,libncurses-devel,screen"
}
else
{
  Write-Output "Download must have failed"
}
Set-Location $curloc.Path
