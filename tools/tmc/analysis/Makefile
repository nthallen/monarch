# Makefile for test_calibr.c
CFLAGS=-I ../ -g -Wall
LDFLAGS=-L/usr/local/lib
LIBS=-lnl
OBJ=test_calibr.o calibr_icvt.o
.PHONY : all

all : test_calibr

calibr_icvt.o : ../calibr_icvt.c
	$(CC) $(CFLAGS) -o calibr_icvt.o -c ../calibr_icvt.c

test_calibr : $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o test_calibr $(OBJ) $(LIBS)
