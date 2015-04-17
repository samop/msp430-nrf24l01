#include "project.h"

int cap=0;
int timer_mode=0;
volatile long int angle;
void captureMode(void)
{
	cap=1;
	TACTL =TACLR; // Clear
	TACTL = TASSEL_2 + MC_2+TAIE;                  // SMCLK, contmode
	TACCTL0 = CM_1+CCIS_0+SCS+CAP+CCIE;
  	_BIS_SR(GIE);                 // enable interrupt

}

void compareMode(void)
{
	cap=0;
	//TACTL = TASSEL_2 + MC_2+TAIE;                  // SMCLK, contmode
	TACCTL0 = OUTMOD_4+CCIE;
  	_BIS_SR(GIE);                 // enable interrupt
	

}

#pragma vector=TIMERA0_VECTOR
__interrupt timerA(void){
	volatile int i;
	//P1OUT ^=LED;
	if(cap){
		P1OUT&=~LED;
		TACCR0+=angle;
		compareMode(); 
	} else {
		if(angle!=0) {
			P1OUT|=LED;
			for(i=1;i<15;i++);
			P1OUT&=~LED;
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
