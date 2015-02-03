#include "msp430g2231.h"
#include "bk2421.h"
#include <msp430.h>
#include "spi.h"
#include "types.h"
#include "project.h"
#include "protocol.h"



extern unsigned int angle;
volatile unsigned int output;
 int next_transition;
void Interrupt_init(void){
	output=0;
	next_transition=0;
//P2REN |=BIT1; //pull up resistor on P2
	P2IE  |=BIT7; // enable interrupt on P2
	P2IES &=~BIT7; // enable interrupt on falling edge
	do {
		P2IFG=0;
	} while(P2IFG!=0);

/* init free running counter A */
	TACCTL0 = CCIE; // Interrupts disabled, Compare Mode
//	TACCTL1 = CCIE|OUTMOD_4; // Interrupts disabled, Compare Mode
//	TACTL   = TASSEL_2|ID_0|MC_1|TACLR|TAIE; // Use SMCLK, Divider 1, Cont mode,Clear counter, Interrupts Enabled
	__enable_interrupt();
}


#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void) {
//	TACCTL0 &= ~CCIE; //disable timer interrupt
//	P2OUT &=~TRIAC; // we close triac
	P2OUT &=~TRIAC;
	output=0;

	if(angle<=MIN_ANGLE){
		P2OUT |=TRIAC;
	} else if(angle<MAX_ANGLE){
	next_transition=9500-angle; // in 10ms next transition will occur, but we will not detect it.
	TACTL   = TASSEL_2|ID_0|MC_1|TACLR|TAIE; // Use SMCLK, Divider 1, Cont mode,Clear counter, Interrupts Enabled
 	TACCR0  = angle;  
	TACCTL0 = CCIE;
 	}
//	P2IES ^=BIT7; 
do {
	P2IFG=0;
} while(P2IFG!=0);


}


   
#pragma vector = TIMERA0_VECTOR
__interrupt void TimerIsr(void){
TACCTL0 &= ~CCIE; 
		if(next_transition){
			//	TACCTL0 = CCIE;
				P2OUT |=TRIAC;
				output=1;
				TACCR0=next_transition;
				next_transition=0;
				TACTL   = TASSEL_2|ID_0|MC_1|TACLR|TAIE;
				TACCTL0 = CCIE;
		} else {
			 if(output==1){
				P2OUT &=~TRIAC;
				output=0;
				TACCR0=angle;
				TACTL   = TASSEL_2|ID_0|MC_1|TACLR|TAIE;
				TACCTL0 = CCIE;


			} else {	
				P2OUT |=TRIAC;
				output=0;	
				TACTL=0;
			}

		}
//TACCTL0 = CCIE;
}




