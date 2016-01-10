# makefile for simplefs

# compiler:
CC=gcc
CFLAGS=-c -Wall
INCLUDES=-I ./include
BINDIR=./bin
SRCDIR=./src
TESTDIR=./tests

dev_test: device.o dev_test.o
	$(CC) $(INCLUDES) device.o device_test.o -o $(BINDIR)/dev_test

device.o: 
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCDIR)/device.c

dev_test.o: 
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTDIR)/device_test.c

clean:
	rm *.o