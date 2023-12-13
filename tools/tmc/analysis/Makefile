# Makefile for test_calibr.c
CFLAGS=-I ../ -g -Wall -std=c99
LDFLAGS=-L/usr/local/lib
LIBS=-lm -lnl
OBJ=test_calibr.o calibr_icvt.o
.PHONY : all clean

all : test_calibr check_type

calibr_icvt.o : ../calibr_icvt.c
	$(CC) $(CFLAGS) -o calibr_icvt.o -c ../calibr_icvt.c

test_calibr : $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o test_calibr $(OBJ) $(LIBS)

clean :
	rm *.o test_calibr check_type
