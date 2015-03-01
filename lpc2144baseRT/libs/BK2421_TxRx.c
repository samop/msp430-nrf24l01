#include "bk2421.h"
#include "spi.h"

/*****************************************************************************************
Function:       void RF_WriteTxPayload( U8* pbuf, U8 len )
Parameter: 
                pbuf    [IN]    data buffer
                len     [IN]    data buffer length
Return: 
                None 
Description:
	            Write data to TX FIFO
*****************************************************************************************/
void RF_WriteTxPayload( U8* pbuf, U8 len )
{
    SPI_Write_Buf( WR_TX_PLOAD, pbuf, len ); // Writes data to TX FIFO
}

/*****************************************************************************************
Function:       void RF_WriteAckPayload( U8* pbuf, U8 len )
Parameter: 
                pbuf    [IN]    data buffer
                len     [IN]    data buffer length
Return: 
                None 
Description:
	            Write data to ACK FIFO
*****************************************************************************************/
void RF_WriteAckPayload( U8* pbuf, U8 len )
{
    SPI_Write_Buf( W_ACK_PAYLOAD_CMD, pbuf, len ); // Writes data to ACK FIFO
}


/*****************************************************************************************
Function:       U8 RF_ReadRxPayload( U8 *pbuf, U8 maxlen )
Parameter: 
                pbuf    [OUT]    receive data buffer
                len     [IN]    data buffer max length
Return: 
                The count wrote to buffer 
Description:
	            Read received data from RX FIFO
*****************************************************************************************/
U8 RF_ReadRxPayload( U8 *pbuf, U8 maxlen )
{
    U8 i = 0;
	U8 len = RF_GET_RX_PL_LEN();	        //Get Top of fifo packet length

	if( len > maxlen )
	{
		len = maxlen;
	}

    for ( i = 0; i < maxlen; i++ )          //Clear buffer
    {
        pbuf[ i ] = 0;
    }

	SPI_Read_Buf(RD_RX_PLOAD, pbuf, len);   // read receive payload from RX_FIFO buffer
	
	return len;
}


