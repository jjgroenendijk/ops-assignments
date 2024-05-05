CC=gcc
CFLAGS=-I.

all: getsignal_sendpid sendsignal_getpid

getsignal_sendpid: getsignal_sendpid.c
    $(CC) -o getsignal_sendpid getsignal_sendpid.c $(CFLAGS)

sendsignal_getpid: sendsignal_getpid.c
    $(CC) -o sendsignal_getpid sendsignal_getpid.c $(CFLAGS)

clean:
    rm -f getsignal_sendpid sendsignal_getpid