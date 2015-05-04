#include "msp430g2231.h"
#include "bk2421.h"
#include <msp430.h>
#include "spi.h"
#include "types.h"
#include "project.h"
#include "protocol.h"
#include "interrupt.h"

st_state state;

//extern volatile long int angle;

void SPI_Init(void);

void main(void)
{
volatile int i;
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
	P1DIR |=CE+CSN;                             //P1.5 is SCLK, P1.6 = SDO, P1.7 = SDI, P1.6=CS, P1.0 = LED
	SPI_Init();
/* Initialize RF module */
	BK2421_Initialize();

/* Triac control and zero crossing detection  */
	P2SEL &=~(TRIAC); //sets I/O function
	P2OUT &=~TRIAC;
	P2DIR |=TRIAC;

	P1SEL |=ZEROCROSS; //sets Capture function
	P1DIR &=~ZEROCROSS;

/*set initial state of the device */
	state.angle=6000; //dim lights
	state.target_angle=state.angle;
	state.preset_angle=state.angle;
	state.power=OFF; //powered off
	state.cap=TIMERCAP; //prepare for capture mode
	state.timer_mode=TIMERIDLE; //timer will be idle after capture happened
	state.speed=5; //soft start/stop speed.
	state.softstart=FALSE;
/* Will be using interrupts for switch */
	Interrupt_init();

	captureMode();

	legacy_receiver(); //never returns!

/* endless loop, just in case */
	while(1);
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


