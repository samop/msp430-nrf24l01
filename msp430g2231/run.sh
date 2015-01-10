msp430-gcc -mmcu=msp430g2231 -Os -o main.elf main.c bk2421_initialize.c  BK2421_TxRx.c spi.c protocol.c
sudo mspdebug rf2500 'prog main.elf'
