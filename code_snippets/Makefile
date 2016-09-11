
CC := gcc
CFLAGS := -Wall -O2 -I./include/

all: mergesort mergesort-list heapsort revstack tailcall \
	 circular_arr_min hashtable stack_mid merge-sorted-array

mergesort: mergesort.c
	$(CC) $(CFLAGS) $< -o $@

mergesort-list: mergesort-list.c
	$(CC) $(CFLAGS) $< -o $@

heapsort: heapsort.c
	$(CC) $(CFLAGS) $< -o $@

revstack: revstack.c
	$(CC) $(CFLAGS) $< -o $@

tailcall: tailcall.c
	$(CC) $(CFLAGS) $< -o $@

circular_arr_min: circular_arr_min.c
	$(CC) $(CFLAGS) $< -o $@

hashtable: hashtable.c
	$(CC) $(CFLAGS) $< -o $@

stack_mid: stack_mid.c
	$(CC) $(CFLAGS) $< -o $@

merge-sorted-array: merge-sorted-array.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f *.o
	@rm -f mergesort mergesort-list heapsort revstack \
		tailcall circular_arr_min hashtable stack_mid \
		merge-sorted-array

