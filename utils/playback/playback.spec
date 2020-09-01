cmdbase = /usr/local/share/monarch/modules/root.cmd
cmdbase = /usr/local/share/monarch/modules/getcon.cmd
cmdbase = $(SRCDIR)/playback.cmd
TGTDIR = $(PWD)
prefix = playback
%%
binPrograms = playbacksrvr playbackcltnc
install : $(binPrograms)
	cp -puv $(binPrograms) $(TGTNODE)/usr/local/bin
