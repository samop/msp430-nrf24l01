#include "msp430g2231.h"
#include "protocol.h"
#include "bk2421.h"
#include "types.h"
#include "project.h"
#include "spi.h"
extern volatile char on;
extern volatile long int angle;
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
		i = 75;
		do (i--);
		while (i != 0); /* Is this just a pause to settle down the receiver? */

//receive code:
   		sta = RF_GET_STATUS();      //Get the RF status
		if(sta & STATUS_RX_DR){    //Receive OK?
  		rlen = RF_ReadRxPayload( (UINT8 *)&g_RFSendBuff, BUFFER_LENGTH );
		//	P2OUT ^=TRIAC;	
		if((char)g_RFSendBuff[0]=='a'){
			//P2OUT |=TRIAC;
			on=1;
		}
		if((char)g_RFSendBuff[0]=='b'){
			//P2OUT &=~TRIAC;
			on=0;
		}	
		if((char)g_RFSendBuff[0]=='c'){
			//P2OUT ^=TRIAC;
			on=!on;
		}
		if((char)g_RFSendBuff[0]=='1'){
			angle=500;
			on=!on;
		}
		if((char)g_RFSendBuff[0]=='5'){
			angle=4000;
			on=!on;
		}
			
		if((char)g_RFSendBuff[0]=='9'){
			angle=8000;
			on=!on;
		}
	
	}

  	if( sta & STATUS_MAX_RT )  //Send fail?
        	{
            	RF_FLUSH_TX();  //Flush the TX FIFO 
        	}
        RF_CLR_IRQ( sta );  //Clear the IRQ flag
	}
}
