#include "msp430g2211.h"
#include <msp430.h>

void main(void)
{
	volatile int i;
	//Disable watchdog
	WDTCTL = WDTPW + WDTHOLD;
	//set the clock
	BCSCTL1=CALBC1_1MHZ;
	DCOCTL=CALDCO_1MHZ;
	BCSCTL3 |= LFXT1S_2;	
/* 50hz output on P1.0 */
	P1DIR |=BIT0;
/* endless loop */
	while(1){
		for(i=1;i<979;i++);
		P1OUT ^=BIT0;	
	}
}

