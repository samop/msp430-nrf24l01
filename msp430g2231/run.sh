
#msp430-gcc -mmcu=msp430g2231 -Os -o main.elf main.c bk2421_initialize.c  BK2421_TxRx.c spi.c protocol.c
msp430-gcc -mmcu=msp430g2231 -Os -c main.c 
msp430-gcc -mmcu=msp430g2231 -Os -c bk2421_initialize.c  
msp430-gcc -mmcu=msp430g2231 -Os -c BK2421_TxRx.c 
msp430-gcc -mmcu=msp430g2231 -Os -c spi.c 
msp430-gcc -mmcu=msp430g2231 -Os -c protocol.c
msp430-gcc -mmcu=msp430g2231 -Os -c interrupt.c
msp430-gcc -mmcu=msp430g2231 -Os -o main.elf main.o bk2421_initialize.o BK2421_TxRx.o spi.o protocol.o interrupt.o
sudo mspdebug rf2500 'prog main.elf'
