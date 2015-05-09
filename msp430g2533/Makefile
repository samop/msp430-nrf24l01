

CC=msp430-gcc
MCU=msp430g2533
CFLAGS=-Os -mmcu=$(MCU) -I.
PROG=mspdebug

all: main.o interrupt.o protocol.o spi.o BK2421_TxRx.o bk2421_initialize.o softstartstop.o
	$(CC) $(CFLAGS) main.o interrupt.o protocol.o spi.o BK2421_TxRx.o bk2421_initialize.o softstartstop.o -o main.elf

#main.o:
#	$(CC) $(CFLAGS) main.c


program: all
	sudo $(PROG) rf2500 'prog main.elf'

clean:
	rm -rf *.o main.elf

