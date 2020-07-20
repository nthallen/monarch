%{
  /* I have to do this so cmdgen doesn't get confused */
  #define FF_CODE "TM}\n"
%}
&tm_cmd
	: Stop * { if_tm_gen.Turf( "TMe\n" ); }
	: Play * { if_tm_gen.Turf( "TM>\n" ); }
	: Faster * { if_tm_gen.Turf( "TM+\n" ); }
	: Slower * { if_tm_gen.Turf( "TM-\n" ); }
	: FF * { if_tm_gen.Turf( FF_CODE ); }
	;
&command
	: Telemetry * &tm_cmds *
	;
&tm_cmds
	:
	: &tm_cmds &tm_cmd
	;
