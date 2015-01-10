msp430-gcc -mmcu=msp430g2211 -Os -o main.elf main.c
sudo mspdebug rf2500 'prog main.elf'
