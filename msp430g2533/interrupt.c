#include "msp430g2533.h"
#include "bk2421.h"
#include <msp430.h>
#include "spi.h"
#include "types.h"
#include "project.h"
#include "protocol.h"
#include "softstartstop.h"

extern st_state state;

void captureMode(void)
{
	state.cap=TIMERCAP;
	TACTL =TACLR; // Clear
	TACTL = TASSEL_2 + MC_2+TAIE; // SMCLK, contmode
	TACCTL0 = CM_1+CCIS_0+SCS+CAP+CCIE;
  //	_BIS_SR(GIE); // enable interrupt

}

void compareMode(void)
{
	state.cap=TIMERCOMP;
	//TACTL = TASSEL_2 + MC_2+TAIE;                  // SMCLK, contmode
	TACCTL0 = OUTMOD_4+CCIE;
  //	_BIS_SR(GIE);                 // enable interrupt
	

}





void Interrupt_init(void){
//P2REN |=BIT1; //pull up resistor on P2
	P2DIR &=~BIT7;
	P2IE  |=BIT7; // enable interrupt on P2
	P2IES &=~BIT7; // enable interrupt on falling edge
	do {
		P2IFG=0;
	} while(P2IFG!=0);

	__enable_interrupt();
}


#pragma vector = PORT2_VECTOR
__interrupt PORT2_ISR(void) {
	if(state.power) power_off();
	else power_on();
do {
	P2IFG=0;
} while(P2IFG!=0);


}

#pragma vector=TIMERA0_VECTOR
__interrupt timerA(void){
	volatile int i; // for for loop
	if(state.cap==TIMERCAP){
		if(state.power)	P2OUT&=~TRIAC;
		TACCR0+=state.angle;
		compareMode();  //switch to compare mode after zero cross has been captured
	} else {
		if(state.power)	P2OUT|=TRIAC;
		for(i=1;i<15;i++); // wait a bit for triac to open for sure
		if(state.power)	P2OUT&=~TRIAC;
		if(state.timer_mode==TIMERIDLE){
			state.timer_mode=TIMERWAIT; //wait for another half period
			TACCR0 += HALF_PERIOD;
		} else {
			state.timer_mode=TIMERIDLE; //ok, the other half period found return to idle state
			captureMode(); //go to capture mode
		} 
	}

//rewrite. Do a check if abs(state.angle-state.target_angle)<state.speed then....
	/* soft start code */
	if(state.angle!=state.target_angle){
		if(state.angle>(state.target_angle+state.speed)){
			state.angle-=state.speed;
		}
		else if(state.angle<(state.target_angle-state.speed)){
			state.angle+=state.speed;
		}
		if(state.angle>=MAX_ANGLE-state.speed && state.power==ON) state.power=OFF;
/*		if(state.angle<MAX_ANGLE-state.speed && state.power==OFF) state.power=ON; */
	}
/*
	if(P2IFG & BIT7){
		if(state.power) power_off();
		else power_on();
		P2IFG=0;
	}
*/
}
