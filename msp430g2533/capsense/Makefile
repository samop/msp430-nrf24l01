

CC=msp430-gcc
MCU=msp430g2533
CFLAGS=-Os -mmcu=$(MCU) -I.
PROG=mspdebug

all: main.o structure.o CTS_HAL.o CTS_Layer.o
	$(CC) $(CFLAGS) main.o structure.o CTS_HAL.o CTS_Layer.o -o main.elf

#main.o:
#	$(CC) $(CFLAGS) main.c


program: all
	sudo $(PROG) rf2500 'prog main.elf'

clean:
	rm -rf *.o main.elf

