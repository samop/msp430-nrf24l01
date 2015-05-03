
/* Standard includes. */
//#include <stdlib.h>
//#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "usb2wireless.h"
#include "usbser.h"
#include "spi.h"
#include "bk2421.h"
//#include "queue.h"

//#include "usbapi.h"

void vUsb2WirelessTask( void )
{
    int i;

	for(;;)
	{
		vTaskDelay( 50 ); 
    U8 sta;
    U8 rlen;
#define BUFFER_LENGTH 255
    unsigned char buffer[BUFFER_LENGTH];
    char message[255];
signed portBASE_TYPE retval;
    	buffer[0]='0';
	retval=usbserGetChar(buffer, 10);
//	if(retval==pdTRUE) usbserPutChar(buffer[0], 1);
	if(retval==pdTRUE//&& (buffer[0]=='a' || buffer[0]=='b' || buffer[0]=='c')
		){	
			SwitchToTxMode();
			CLR_CE();
			SPI_Write_Buf(WR_TX_PLOAD, (U8 *)&buffer, 1); // Writes data to TX FIFO
			SET_CE();
			vTaskDelay(10);
			CLR_CE();
	   while(1){	
	    	sta = SPI_Read_Reg( STATUS );   // read register STATUS's value
		    if( (sta & STATUS_TX_DS) || (sta & STATUS_MAX_RT) )    //TX IRQ?
		    {
			if( sta & STATUS_MAX_RT )   //if send fail
			{
			    RF_FLUSH_TX();
			}  
		usbserPutChar(sta, 1);
	//	usbserPutChar(buffer[0],1);
		
	    
			RF_CLR_IRQ( sta );  // clear RX_DR or TX_DS or MAX_RT interrupt flag
			break;
		    }
		}
	}
    //	    SwitchToRxMode();    

	

/*     sta = RF_GET_STATUS();      //Get the RF status
//	usbserPutChar(sta,1);

        if( sta & STATUS_RX_DR )    //Receive OK?
       {
            //Readout the received data from RX FIFO
            rlen = RF_ReadRxPayload( (U8 *)&buffer, BUFFER_LENGTH );
//	sprintf(message, "Received: %d, message: %s\n", rlen, buffer);
	usbserPutChar(buffer[0], 1);
	usbserPutChar(0xff,1);
	//usbserPutString(message,1);
        }
	sta=SPI_Read_Reg(CONFIG);
	usbserPutChar(sta, 1);
    //    if( sta & STATUS_MAX_RT )  //Send fail?
    //    {
    //        RF_FLUSH_TX();  //Flush the TX FIFO 
    //    }

      //  RF_CLR_IRQ( sta );  //Clear the IRQ flag
    
*/

	}
}

