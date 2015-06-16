#include "msp430g2533.h"
#include "protocol.h"
#include "bk2421.h"
#include "types.h"
#include "project.h"
#include "spi.h"
#include "softstartstop.h"
extern st_state state;
/* first function that receives code for on/off the light. Never exists! */
void legacy_receiver(){
	//requred vars:
	UINT8 sta;
	#define BUFFER_LENGTH 1
    	UINT8 g_RFSendBuff[BUFFER_LENGTH];
	volatile unsigned int i;
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

		if((char)g_RFSendBuff[0]=='a'){
			power_on();
		}
		if((char)g_RFSendBuff[0]=='b'){
			power_off();	
			
		}	
		if((char)g_RFSendBuff[0]=='c'){
			//if(state.power) power_off();
			//else power_on();
			P1OUT^=BIT0;
			
		}
		if((char)g_RFSendBuff[0]=='d'){
			state.softstart=TRUE;
		}
		if((char)g_RFSendBuff[0]=='e'){
			state.softstart=FALSE;
		}
		if((char)g_RFSendBuff[0]=='f'){
		if(state.speed<500)	state.speed+=10;
		}
		if((char)g_RFSendBuff[0]=='g'){
		if(state.speed>10)	state.speed-=10;
		}
		
		
		if((char)g_RFSendBuff[0]>'0' && (char)g_RFSendBuff[0]<'a'){
		//49 levels
			P1OUT^=BIT0;
			angle_change(154*((char)g_RFSendBuff[0]-'0')+100);
		}
	}

  	if( sta & STATUS_MAX_RT )  //Send fail?
        	{
            	RF_FLUSH_TX();  //Flush the TX FIFO 
        	}
        RF_CLR_IRQ( sta );  //Clear the IRQ flag
	}
}
