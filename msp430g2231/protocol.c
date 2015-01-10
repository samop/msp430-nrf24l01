#include "msp430g2231.h"
#include "protocol.h"
#include "bk2421.h"
#include "types.h"
#include "project.h"
#include "spi.h"

volatile unsigned int i;
volatile unsigned int cnt;

unsigned char is_on;

/* first function that receives code for on/off the light. Never exists! */
void legacy_receiver(){
	//requred vars:
	UINT8 sta;
#define BUFFER_LENGTH 1
    	UINT8 g_RFSendBuff[BUFFER_LENGTH];

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
		while (i != 0); /* Is this just a pause to settle down the receiver? */
//receive code:
   sta = RF_GET_STATUS();      //Get the RF status
 if(sta & STATUS_RX_DR)    //Receive OK?
       {
  rlen = RF_ReadRxPayload( (UINT8 *)&g_RFSendBuff, BUFFER_LENGTH );
		P2OUT ^=TRIAC;	
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

