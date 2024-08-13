# Monarch Driver for Alicat Mass Flow Controllers

Alicat communication is specified in https://documents.alicat.com/manuals/ModbusRTU_Manual.pdf

Device Status bits are:
Bit Description
  -  0 Temperature Overflow (TOV)
  -  1 Temperature Underflow (TOV)
  -  2 Volumetric Overflow (VOV)
  -  3 Volumetric Underflow (VOV)
  -  4 Mass Overflow (MOV)
  -  5 Mass Underflow (MOV)
  -  6 Pressure Overflow (POV)
  -  7 Totalizer Overflow (OVR)
  -  8 PID Loop in Hold (HLD)
  -  9 ADC Error (ADC)
  - 10 PID Exhaust (EXH)
  - 11 Over pressure limit (OPL)
  - 12 Flow overflow during totalize (TMF)
  - 13 Measurement was aborted
