CC = gcc
CFLAGS = -Wall -g

all: getsignal sendsignal

getsignal: getsignal.c
    $(CC) $(CFLAGS) -o getsignal getsignal.c

sendsignal: sendsignal.c
    $(CC) $(CFLAGS) -o sendsignal sendsignal.c

clean:
    rm -f getsignal sendsignal