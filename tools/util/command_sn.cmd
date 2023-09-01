%{
  #include "dasio/command_sn.h"
%}

%INTERFACE <Command_SN:DG/data>

&command
  : Retransmit * { cmdif_tx::req_retransmit(); }
  ;
