# Setup script for the Monarch architecture when run under Cygwin
# on Windows.
#
# ----------
# Invocation:
# ----------
#
# The recommended way to run this script is to:
#  - bring up Windows File Explorer (nee Windows Explorer)
#  - navigate to c:\cygwin64\usr\local\share\monarch\setup
#    - Pro Tip: You can cut and paste into the address bar!
#  - right-click on this file and select "Run with PowerShell"
# After successfully running this script, you should start
# a Cygwin shell and run the command:
#
#   $ /usr/local/share/monarch/setup/monarch_setup.sh
#
# You may need to reboot before monarch_setup.sh completes.
#
# --------------------
# Alternate Invocation:
# --------------------
# 
# This script can also be run from a Windows Cmd shell as:
# > PowerShell -ExecutionPolicy Bypass ./monarch-win-setup.ps1
#
# ---------
# Uninstall:
# ---------
#
# If you would like to reverse the actions of this script
# (i.e. delete the flight group), you can issue the command:
# > PowerShell -ExecutionPolicy Bypass ./monarch-win-setup.ps1 -uninstall
#
# Note that you should also run the following from a Cygwin shell:
# $ /usr/local/share/monarch/setup/monarch_reset.sh

param (
  [switch]$uninstall = $false
)

# Script to:
#   Make sure the flight group exists or create it
#   Make sure the current user is in the flight group

# Check here to figure out whether we have to do anything
#   Does the $fltgrp exist
#   Is the current user a member?
$fltgrp = 'flight'
$fulluser = "$Env:USERDOMAIN\$Env:USERNAME"
if ( $uninstall) {
  if (-NOT ((Get-LocalGroup).Name -contains $fltgrp)) {
    Write-Output "Group $fltgrp does not exist, so no changes required for uninstall."
    $cont = Read-Host -Prompt "Finish?"
    Break
  }
} else {
  if ((Get-LocalGroup).Name -contains $fltgrp -and
           (Get-LocalGroupMember $fltgrp).Name -contains $fulluser ) {
    Write-Output "Group $fltgrp already exists and $fulluser is a member"
    $cont = Read-Host -Prompt "Finish?"
    Break
  }
}

# This is the elevation check and elevation
$is_admin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole(
    [Security.Principal.WindowsBuiltInRole] "Administrator")
if (-NOT $is_admin) {
  # $myinvocation | Format-List | Write-Output
  # $myinvocation.mycommand | Format-List | Write-Output
  $cmdline = $myinvocation.Line.Replace($myinvocation.InvocationName, $myinvocation.mycommand.definition)
  Write-Verbose "Invocation: $cmdline"
  Write-Warning "You do not have Administrator rights"
  Write-Warning "Will attempt to RunAs Administrator"
  $cont = Read-Host -Prompt "Continue? [N/y]"
  if ( $cont -match 'y(es)?' ) {
    Write-Output "Restarting script as Administrator"
    $cmdline = "-ExecutionPolicy Bypass $cmdline"
    Start-Process -FilePath PowerShell.exe -ArgumentList "$cmdline" -Verb RunAs # -Wait
    Write-Verbose "Back from RunAs"
    Write-Verbose "Could conceivably run the bash script now"
    # $cont = Read-Host -Prompt "Finish?"
  }
  Break # So we don't try to do the privileged stuff
}

Write-Verbose "Now we can do admin stuff!"
if ($uninstall) {
  Write-Output "Uninstalling ..."
  if ((Get-LocalGroupMember $fltgrp).Name -contains $fulluser ) {
    Write-Output "Removing $fulluser from local group $fltgrp"
    Remove-LocalGroupMember -Name $fltgrp -Member $fulluser
  }
  if ((Get-LocalGroupMember $fltgrp).Name.count -eq 0) {
    Write-Output "Removing local group $fltgrp"
    Remove-LocalGroup -Name $fltgrp
  } else {
    Write-Output "Holding off on removing non-empty local group $fltgrp"
  }
} else {
  Write-Output "Installing ..."
  if (-NOT ((Get-LocalGroup).Name -contains $fltgrp) ) {
    Write-Output "Creating Local Group $fltgrp"
    $grp = New-LocalGroup -Name "$fltgrp" -Description 'Monarch flight group'
  }
  Write-Output "Adding $fulluser to local group $fltgrp"
  Add-LocalGroupMember -Name $fltgrp -Member $fulluser
}
$cont = Read-Host -Prompt "Finish?"
