

CC=msp430-gcc
MCU=msp430g2211
CFLAGS=-Os -mmcu=$(MCU) -I.
PROG=mspdebug

all: main.o interrupt.o
	$(CC) $(CFLAGS) main.o interrupt.o -o main.elf

#main.o:
#	$(CC) $(CFLAGS) main.c


program: all
	sudo $(PROG) rf2500 'prog main.elf'

clean:
	rm *.o main.elf

