# Makefile for test_calibr.c
CFLAGS=-I ../ -g -Wall
LDFLAGS=-L/usr/local/lib
LIBS=-lnl

calibr_icvt.o : calibr_icvt.c

test_calibr : test_calibr.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test_calibr test_calibr.c $(LIBS)