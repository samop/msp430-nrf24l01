#include "spi.h"
#include "sysdefs.h"
/*****************************************************************************************
Function:       U8 SPI_Write( U8 reg )
Parameter: 
                reg     [IN]    register address 
Return: 
                The register value 
Description:
                SPI write byte operation
*****************************************************************************************/
U8 SPI_Write( U8 valueIn )
{

 SPI_SPDR = valueIn;
  while (!(SPI_SPSR & SPI_SPSR_SPIF));
  return SPI_SPDR;
}

/*****************************************************************************************
Function:       U8 SPI_Read_Reg( U8 reg )
Parameter: 
                reg     [IN]    register address 
Return: 
                The register value 
Description:
                Read from BK2421's register
*****************************************************************************************/
U8 SPI_Read_Reg( U8 reg )
{
    U8 res;

    CLR_CSN();

    SPI_Write( reg );
    res = SPI_Write( 0xff );

    SET_CSN();
    
    return res;
}


/*****************************************************************************************
Function:       void SPI_Read_Buf(U8 reg, U8 *pBuffer, U8 Length)
Parameter: 
                reg     [IN]    register address
                pBuffer [OUT]   read data buffer
                Length  [IN]    buffer length
Return: 
                None
Description:
                Read multiple bytes from BK2421's register
*****************************************************************************************/
void SPI_Read_Buf(U8 reg, U8 *pBuffer, U8 Length)
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
Function:       void SPI_Write_Reg(U8 reg, U8 value)
Parameter: 
                reg     [IN]    register address
                value   [IN]    value's for register
Return: 
                None 
Description:
                Write to BK2421's register
*****************************************************************************************/
void SPI_Write_Reg(U8 reg, U8 value)
{
    CLR_CSN();

    SPI_Write( reg );
    SPI_Write( value );

    SET_CSN();
}


/*****************************************************************************************
Function:       void SPI_Write_Buf(U8 reg, U8 *pBuffer, U8 Length)
Parameter: 
                reg     [IN]    register address
                pBuffer [IN]   write data buffer
                Length  [IN]    buffer length
Return: 
                None
Description:
                Write multiple bytes to BK2421's register
*****************************************************************************************/
void SPI_Write_Buf(U8 reg, U8 *pBuffer, U8 Length)
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
  IO0CLR  = GPIO_IO_P7;

}

void SET_CSN(){
  IO0SET  = GPIO_IO_P7;
}

void CLR_CE(){
	IO0CLR = 1<<13;
}

void SET_CE(){
	IO0SET = 1<<13;
}
