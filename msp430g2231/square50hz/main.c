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
/* input (hiZ) on P1.1 */
	P1DIR &=~BIT1; 
/* endless loop */
	while(1){
		for(i=1;i<30;i++);

		P1OUT ^=BIT0;	
		//start timer
	}
}


#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
	//stop timer
	//count number of pulses
do {
	P2IFG=0;
} while(P2IFG!=0);



