# usb_enum.ps1
$Ports = @(get-wmiobject -Query "Select * FROM Win32_PnPEntity WHERE Name LIKE '%COM[0-9]%' AND Present = 'True'")
foreach ($port in $Ports) {
  $parts = (($port.DeviceID `
      -replace '[VP]ID_', '0x' -replace 'A\\', '\\') `
      -split '\\')[1] -split '\+'
  $query = "%$($parts[2])%"
  $USBdev = get-wmiobject -Query "Select * FROM Win32_PnPEntity WHERE PnPClass = 'USB' and PnPDeviceID LIKE '$query'"
  if ($USBdev -eq $null) {
    "Failed to find USBdev like $query"
  } else {
    @($port.Name, $parts[2], "$($parts[0]):$($parts[1])", "$($USBdev.Manufacturer) $($USBdev.Name)") -join ' :: '
  }
}
