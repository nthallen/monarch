%INTERFACE <TMIPX>

&^command
  : TM_Export set UDP MTU %d * {
      if ($5 <= 20) {
        msg(MSG_ERROR, "Request MTU (%d) too small");
      } else {
        if_TMIPX.Turf("M%d\n", $5);
      }
    }
  ;
