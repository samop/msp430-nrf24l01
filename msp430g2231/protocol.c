#include "msp430g2231.h"
#include "protocol.h"
#include "bk2421.h"
#include "types.h"
#include "project.h"
#include "spi.h"

volatile unsigned int i;
/* first function that receives code for on/off the light. Never exists! */
void legacy_receiver(){
	//requred vars:
	UINT8 sta;
#define BUFFER_LENGTH 1
    	UINT8 g_RFSendBuff[BUFFER_LENGTH];

	SwitchToRxMode();   //Set RF to TX mode
	UINT8 rlen;
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
 if(sta & STATUS_RX_DR){    //Receive OK?
  	rlen = RF_ReadRxPayload( (UINT8 *)&g_RFSendBuff, BUFFER_LENGTH );
	//	P2OUT ^=TRIAC;	
	if((char)g_RFSendBuff[0]=='a'){
		P2OUT |=TRIAC;
	}
	if((char)g_RFSendBuff[0]=='b'){
		P2OUT &=~TRIAC;
	}	
	if((char)g_RFSendBuff[0]=='c'){
		P2OUT ^=TRIAC;
	}	
	
}

  if( sta & STATUS_MAX_RT )  //Send fail?
        {
            RF_FLUSH_TX();  //Flush the TX FIFO 
        }
        RF_CLR_IRQ( sta );  //Clear the IRQ flag
	}




}

