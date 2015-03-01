
/* Standard includes. */
//#include <stdlib.h>
//#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "ledblink.h"
#include "usbser.h"
#include "spi.h"
#include "bk2421.h"
void vLEDTask( void )
{
    int i;

	for(;;)
	{
        /* Delay for half the flash period then turn the LED on. */
        IO0CLR = 1<<14;
        
/* Now and then we send calibration data in unsigned big endian u16
 * enclosed in frame starting with 0xFCFF and ending with 0xF0FF
 */

		vTaskDelay( 5000 ); 
//	SPI_Write(0x71);
        IO0SET = 1<<14;
		vTaskDelay( 5000 );
	//Test usbSerial
//	usbserPutString("Hello!",1);
	
 /*   U8 sta;
    U8 rlen;
#define BUFFER_LENGTH 1
    unsigned char buffer[BUFFER_LENGTH];
    char message[255];
    buffer[0]='a';
			SwitchToTxMode();
			CLR_CE();
		SPI_Write_Buf(WR_TX_PLOAD, (U8 *)&buffer, 32); // Writes data to TX FIFO
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
	    
			RF_CLR_IRQ( sta );  // clear RX_DR or TX_DS or MAX_RT interrupt flag
			break;
		    }
		}
    //	    SwitchToRxMode();    

*/	

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

