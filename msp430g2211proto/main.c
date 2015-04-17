#include "project.h"


void systemInit(void)
{
	//Disable watchdog
	WDTCTL = WDTPW + WDTHOLD;
	//set the clock
	BCSCTL1=CALBC1_1MHZ;
	DCOCTL=CALDCO_1MHZ;
	BCSCTL3 |= LFXT1S_2;	

	

}	



extern volatile long int angle;
void main(void)
{
volatile long int i;

	systemInit();

	P1OUT &=~LED;
	P1SEL &=~LED;
	P1DIR |=LED;

	P1SEL |=ZEROCROSS;
	P1DIR &=~ZEROCROSS;

	TACTL=TACLR;
	captureMode();
	angle=8000;
	while(1){
		for(i=1;i<2000;i++);
		angle=angle-50;
		if(angle<=5500) angle=8000;
	}
}



