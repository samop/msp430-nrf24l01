#include "msp430g2231.h"
#include "bk2421.h"
#include <msp430.h>
#include "spi.h"
#include "types.h"
#include "project.h"
#include "protocol.h"

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
	P2OUT ^=TRIAC;
do { //debouncing ;)
	P2IFG=0;
} while(P2IFG!=0);


}

