
CC = gcc
CFLAGS = -Wall -O2

all: heapsort revstack tailcall

heapsort: heapsort.c
	$(CC) $(CFLAGS) $< -o $@

revstack: revstack.c
	$(CC) $(CFLAGS) $< -o $@

tailcall: tailcall.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f *.o
	@rm -f heapsort revstack tailcall
