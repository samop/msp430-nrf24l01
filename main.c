#include "msp430x20x3.h"

#include "spi.h"

volatile unsigned int i;
void SPI_Init(void);
void main(void)
{
	//Disable watchdog
	WDTCTL = WDTPW + WDTHOLD;
	//set the clock
	BCSCTL1=CALBC1_1MHZ;
	DCOCTL=CALDCO_1MHZ;
	BCSCTL3 |= LFXT1S_2;	
	
	//set spi
	P1DIR = 0x71;                                //P1.5 is SCLK, P1.6 = SDO, P1.7 = SDI, P1.6=CS, P1.0 = LED
	SPI_Init();
	BK2421_Initialize();

	//send byte!
	
	for (;;)
	{
		P1OUT ^= 0x01;
	//	SPI_Write(0x71);
		i = 71*500;
		do (i--);
		while (i != 0);

	}



}



void SPI_Init(void)
{
// USIMST=1  USIIFG=0 (Operate)  USIIFL=1 (Idle)
  USICTL0 = USIPE7+USIPE6+USIPE5+USIMST+USISWRST+USIOE;  // Port & USI mode setup; Hold at reset
  USICTL1 |= USIIE;                               // Counter interrupt, flag remains set
  USICKCTL = USIDIV_7 + USISSEL_2;          // Setup USI clocks: SCLK = SMCLK/2
  USICTL0 &= ~USISWRST;                     // Enable USI i.e release reset
  P1OUT &= ~0x10; //enable slave!
}




