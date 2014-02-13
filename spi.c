#include "spi.h"
#include "msp430x20x3.h"

/*****************************************************************************************
Function:       UINT8 SPI_Write( UINT8 reg )
Parameter: 
                reg     [IN]    register address 
Return: 
                The register value 
Description:
                SPI write byte operation
*****************************************************************************************/
UINT8 SPI_Write( UINT8 wData )
{
  UINT8 ret;
//write to SPI
	USISRL=wData;
	USICNT=8;
	while((~USICTL1)&USIIFG);
	ret=USISRL;
//return read byte
    return ret;
}

/*****************************************************************************************
Function:       UINT8 SPI_Read_Reg( UINT8 reg )
Parameter: 
                reg     [IN]    register address 
Return: 
                The register value 
Description:
                Read from BK2421's register
*****************************************************************************************/
UINT8 SPI_Read_Reg( UINT8 reg )
{
    UINT8 res;

    CLR_CSN();

    SPI_Write( reg );
    res = SPI_Write( 0xff );

    SET_CSN();
    
    return res;
}


/*****************************************************************************************
Function:       void SPI_Read_Buf(UINT8 reg, UINT8 *pBuffer, UINT8 Length)
Parameter: 
                reg     [IN]    register address
                pBuffer [OUT]   read data buffer
                Length  [IN]    buffer length
Return: 
                None
Description:
                Read multiple bytes from BK2421's register
*****************************************************************************************/
void SPI_Read_Buf(UINT8 reg, UINT8 *pBuffer, UINT8 Length)
{
    CLR_CSN();

    SPI_Write( reg );

    while( Length -- )
    {
        *pBuffer++ = SPI_Write( 0xff );
    }

    SET_CSN();
}


/*****************************************************************************************
Function:       void SPI_Write_Reg(UINT8 reg, UINT8 value)
Parameter: 
                reg     [IN]    register address
                value   [IN]    value's for register
Return: 
                None 
Description:
                Write to BK2421's register
*****************************************************************************************/
void SPI_Write_Reg(UINT8 reg, UINT8 value)
{
    CLR_CSN();

    SPI_Write( reg );
    SPI_Write( value );

    SET_CSN();
}


/*****************************************************************************************
Function:       void SPI_Write_Buf(UINT8 reg, UINT8 *pBuffer, UINT8 Length)
Parameter: 
                reg     [IN]    register address
                pBuffer [IN]   write data buffer
                Length  [IN]    buffer length
Return: 
                None
Description:
                Write multiple bytes to BK2421's register
*****************************************************************************************/
void SPI_Write_Buf(UINT8 reg, UINT8 *pBuffer, UINT8 Length)
{
    CLR_CSN();

    SPI_Write( reg );

    while( Length-- )
    {
        SPI_Write( *pBuffer++ );
    }

   SET_CSN();
}

void CLR_CSN(){
P1OUT &= ~0x10; //enable slave by clearing!

}

void SET_CSN(){
P1OUT |= 0x10;
}

void CLR_CE(){
P1OUT &=~0x08;
}

void SET_CE(){
P1OUT |=0x08;
}
