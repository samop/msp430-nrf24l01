#include "msp430g2231.h"
#include "bk2421.h"
#include <msp430.h>
#include "spi.h"
#include "types.h"
#include "project.h"
#include "protocol.h"


int cap=0;
int timer_mode=0;
volatile char on=0;
volatile long int angle;
void captureMode(void)
{
	cap=1;
	TACTL =TACLR; // Clear
	TACTL = TASSEL_2 + MC_2+TAIE; // SMCLK, contmode
	TACCTL0 = CM_1+CCIS_0+SCS+CAP+CCIE;
  	_BIS_SR(GIE); // enable interrupt

}

void compareMode(void)
{
	cap=0;
	//TACTL = TASSEL_2 + MC_2+TAIE;                  // SMCLK, contmode
	TACCTL0 = OUTMOD_4+CCIE;
  	_BIS_SR(GIE);                 // enable interrupt
	

}





void Interrupt_init(void){
//P2REN |=BIT1; //pull up resistor on P2
	P2IE  |=BIT7; // enable interrupt on P2
	P2IES &=~BIT7; // enable interrupt on falling edge
	do {
		P2IFG=0;
	} while(P2IFG!=0);

	__enable_interrupt();
}


#pragma vector = PORT2_VECTOR
__interrupt void PORT2_ISR(void) {
//	P2OUT ^=TRIAC;
	if(on) on=0;
	else on=1;
do { //debouncing ;)
	P2IFG=0;
} while(P2IFG!=0);


}

#pragma vector=TIMERA0_VECTOR
__interrupt timerA(void){
	volatile int i;
	//P1OUT ^=LED;
	if(cap){
		if(on)	P2OUT&=~TRIAC;
		TACCR0+=angle;
		compareMode(); 
	} else {
		if(angle!=0) {
			if(on)	P2OUT|=TRIAC;
			for(i=1;i<15;i++);
			if(on)	P2OUT&=~TRIAC;
			if(timer_mode==0){
				timer_mode=1;
				TACCR0 += HALF_PERIOD;
			} else {
				timer_mode=0;
				captureMode();
			} 
		}
		else
		{
			timer_mode=0; // reset timer mode.
			captureMode(); //go back to edge detect.
		}
	}

}
