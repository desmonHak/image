CC=gcc
CFLAGS=-O0 -Wall -g -o 
TARGET=example
init: 
	$(CC)  $(TARGET)1.c $(CFLAGS) $(TARGET)1.exe
	$(CC) $(TARGET)2.c $(CFLAGS) $(TARGET)2.exe