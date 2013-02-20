#
# Author: Mahavir Jain <mahavirpj@gmail.com>
#
# This file has been put into the public domain.
# You can do whatever you want with this file.
#

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as

CFLAGS=-mcpu=cortex-m3 -g -Os -mthumb -Wall 
ASFLAGS=-mcpu=cortex-m3 --gdwarf-2 -mthumb-interwork

LDFLAGS=-T generic-m-hosted.ld

.c.o:
	$(CC) $(CFLAGS) $(EXTRACFLAGS) -c $<
.s.o:
	$(AS) $(ASFLAGS) -o $@ $<

build: semihello.axf

OBJS=hello.c reset.s

semihello.axf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

clean:
	rm -f *.o semihello.axf
