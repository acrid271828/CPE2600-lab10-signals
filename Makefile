CFLAGS=-c -g -Wall -Werror
CC=gcc

all: recv_signal send_signal signal_alarm signal_hander signal_segfault signal_sigaction

send: send_signal.o
	$(CC) -o send_signal send_signal.o

recv: recv_signal.o
	$(CC) -o recv_signal recv_signal.o

segfault: signal_segfault.o
	$(CC) -o segfault signal_segfault.o

alarm: signal_alarm.o
	$(CC) -o alarm signal_alarm.o

handler: signal_hander.o
	$(CC) -o handler signal_hander.o

sigaction: signal_sigaction.o
	$(CC) -o sigaction signal_sigaction.o

clean:
	rm -f *.o info pinfo finfo pmod

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

