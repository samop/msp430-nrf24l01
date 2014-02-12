msp430-gcc -mmcu=msp430f2013 -o main.elf main.c bk2421_initialize.c  BK2421_TxRx.c spi.c
sudo mspdebug uif 'prog main.elf'
