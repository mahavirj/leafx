
CC = gcc
CFLAGS = -Wall -O2

all: mergesort heapsort revstack tailcall circular_arr_min

mergesort: mergesort.c
	$(CC) $(CFLAGS) $< -o $@

heapsort: heapsort.c
	$(CC) $(CFLAGS) $< -o $@

revstack: revstack.c
	$(CC) $(CFLAGS) $< -o $@

tailcall: tailcall.c
	$(CC) $(CFLAGS) $< -o $@

circular_arr_min: circular_arr_min.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f *.o
	@rm -f mergesort heapsort revstack tailcall circular_arr_min
