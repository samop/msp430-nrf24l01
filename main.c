#include "msp430x20x3.h"
#include "bk2421.h"
#include <msp430.h>
#include "spi.h"
#include "types.h"
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
	//set spi
	P1OUT &=~0x01;
	P1DIR = 0x79;                                //P1.5 is SCLK, P1.6 = SDO, P1.7 = SDI, P1.6=CS, P1.0 = LED
	SPI_Init();
	BK2421_Initialize();
	Interrupt_init();
//requred vars:
    UINT8 sta;
#define BUFFER_LENGTH 1
    	UINT8 g_RFSendBuff[BUFFER_LENGTH];
    	g_RFSendBuff[0]='a';
		i=75;
		do(i--);
		while(i!=0);
//	SwitchToTxMode();   //Set RF to TX mode
	SwitchToRxMode();   //Set RF to TX mode
	
	UINT8 rlen;
	cnt=0;
	is_on=0;
	for (;;)
	{
/*		i = 71*100;
		do (i--);
		while (i != 0); */
//		P1OUT ^= 0x01;
		i = 75;
		do (i--);
		while (i != 0);

//receive code:
   sta = RF_GET_STATUS();      //Get the RF status
 if(sta & STATUS_RX_DR)    //Receive OK?
       {
  rlen = RF_ReadRxPayload( (UINT8 *)&g_RFSendBuff, BUFFER_LENGTH );
		P1OUT ^=0x01;	
	}

  if( sta & STATUS_MAX_RT )  //Send fail?
        {
            RF_FLUSH_TX();  //Flush the TX FIFO 
        }

        RF_CLR_IRQ( sta );  //Clear the IRQ flag
    /*
	cnt++;
	//turn off for approx 1 period
	if(cnt==20){
		if(P1OUT&0x01) {
			is_on=1;
			//turn off momentary
			P1OUT &=~0x01;
		}
		else {
			is_on=0;
			cnt=0;
		}
		
	}
	if(cnt==25 && is_on){
		is_on=0;
		P1OUT |=0x01;
		cnt=0;
	}
*/

//	sta=SPI_Read_Reg(CONFIG)&0x0f;
//  if(sta==0x0f)
//		P1OUT ^=0x01;	

//transmit code:
//		SPI_Write_Buf(WR_TX_PLOAD, g_RFSendBuff, 1); // Writes data to TX FIFO
//	   // 	sta = SPI_Read_Reg( STATUS );   // read register STATUS's value
//	    	
//	/*	    if( (sta & STATUS_TX_DS) || (sta & STATUS_MAX_RT) )    //TX IRQ?
//		    {
//			if( sta & STATUS_MAX_RT )   //if send fail
//			{
//			    RF_FLUSH_TX();
//			}  
//	  */  
//	//		RF_CLR_IRQ( sta );  // clear RX_DR or TX_DS or MAX_RT interrupt flag
//
//		    }
//    //	    SwitchToRxMode();    
//
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
