#include "msp430x20x3.h"
#include "bk2421.h"
#include <msp430.h>
#include "spi.h"
#include "types.h"
#define TRIAC 1<<6 //P2.6
#define ZEROCROSS 1<<7 //P2.7

volatile unsigned int i;
volatile unsigned int cnt;
volatile unsigned int output;
unsigned char is_on;
void SPI_Init(void);
void Interrupt_init(void);
void main(void)
{
	//Disable watchdog
	WDTCTL = WDTPW + WDTHOLD;
	//set the clock
	BCSCTL1=CALBC1_1MHZ;
	DCOCTL=CALDCO_1MHZ;
	BCSCTL3 |= LFXT1S_2;	
/* Initializing SPI interface for communication with RF module */
/* P1.5 : SCK */
/* P1.6 : MOSI */
/* P1.6 : MISO */
/* Additionaly two more I/O pins are required for CSN and CE on*/
/* the module. These are connected as follows: */
/* P1.3 : CE  */
/* P1.4 : CSN */
	P1OUT &=~0x01;
	P1DIR = 0x79;                                //P1.5 is SCLK, P1.6 = SDO, P1.7 = SDI, P1.6=CS, P1.0 = LED
//DIS	SPI_Init();
/* Initialize RF module */
//DIS	BK2421_Initialize();

/* Triac control and zero crossing detection is on port 2 */
/* P2.6 : Triac control output */
/* P2.7 : Zero crossing detector */
	//port 2 requires selecting right functionality
	P2SEL &=~ (TRIAC+ZEROCROSS) ; //sets I/O function to P2.6 and P2.7

	P2OUT |=TRIAC;
	P2DIR |=TRIAC;
	P2DIR &=~ZEROCROSS;



/* Will be using interrupts. Here we initialize them */
//DIS	Interrupt_init();



/* endless loop, just in case */
	volatile int i;
	while(1){
		for(i=1;i<1000;i++);
		P2OUT ^=TRIAC;	
	}
}

void SPI_Init(void)
{
// USIMST=1  USIIFG=0 (Operate)  USIIFL=1 (Idle)
  USICTL0 = USIPE7+USIPE6+USIPE5+USIMST+USISWRST+USIOE;  // Port & USI mode setup; Hold at reset
  USICTL1 |= USICKPH;                               // Counter interrupt, flag remains set
  USICKCTL = USIDIV_4 + USISSEL_2;// + USICKPL;          // Setup USI clocks: SCLK = SMCLK/2
  USICTL0 &= ~USISWRST;                     // Enable USI i.e release reset
  P1OUT &= ~0x10; //enable slave!
  P1OUT &= ~0x08; // /CE  to power on chip
}

void Interrupt_init(void){
output=0;
P1OUT |= BIT1;
P1REN |= BIT1;
 // P1.4 pullup
P1IE |= BIT1; 
 // P1.4 IRQ enabled
P1IES |= BIT1;
P1IFG &= ~BIT1; 
__enable_interrupt();
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {

//	P1OUT |= 0x01;
	P1IES ^= BIT1 ; // make interrupt also on other edge
	//set timer
 	TACTL   = 0x0212; // Use SMCLK, Up mode (count to TACCR0), Interrupts Enabled
 	TACCTL0 = CCIE; // Interrupts Enabled, Compare Mode
 	TACCR0  = 4000;  // 8MHz/1000Hz = 8000 gives the number of system clocks required for a 1ms timer
      
	P1IFG &= ~BIT1; // clear interrupt flag.

}

   
#pragma vector = TIMERA0_VECTOR
__interrupt void TimerIsr(void)
{
	if(TAIV){
		if(output==0){
			P1OUT |= 0x01;
			TACTL=0;
			output=1;
			TACTL   = 0x0212; // Use SMCLK, Up mode (count to TACCR0), Interrupts Enabled
		 	TACCTL0 = CCIE; // Interrupts Enabled, Compare Mode
 			TACCR0  = 2000;  // 8MHz/1000Hz = 8000 gives the number of system clocks required for a 1ms timer
		}
		else {
			P1OUT &= ~0x01;
			TACTL=0;
			TACCTL0=0;
			output=0;
		}
	}	
}
