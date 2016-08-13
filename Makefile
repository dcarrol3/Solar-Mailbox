# Makefile for MailBox project
# Doug Carroll
# CST-486 Spring 2016

CC = gcc
CFLAGS = -lwiringPi -std=gnu99 -lrt -pthread
TARGET = MailBox

all: main

main: main.o mailhandler.o mail.o motor.o uv.o
	$(CC) -o $(TARGET) main.o mailhandler.o mail.o motor.o uv.o $(CFLAGS)

main.o: main.c mailhandler.h motor.h uv.h
	$(CC) -c main.c $(CFLAGS)

mailhandler.o: mailhandler.c mailhandler.h mail.h
	$(CC) -c mailhandler.c $(CFLAGS)

mail.o: mail.c mail.h
	$(CC) -c mail.c $(CFLAGS)

motor.o: motor.c motor.h
	$(CC) -c motor.c $(CFLAGS)

uv.o: uv.c uv.h
	$(CC) -c uv.c $(CFLAGS)

clean:
	$(RM) $(TARGET) *.o *.~
