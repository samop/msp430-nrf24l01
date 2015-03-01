#ifndef _SPI_H
#define _SPI_H
#include "lpc214x.h"
#include "sysdefs.h"
U8 SPI_Write( U8 valueIn );
U8 SPI_Read_Reg( U8 reg );
void SPI_Read_Buf(U8 reg, U8 *pBuffer, U8 Length);
void SPI_Write_Reg(U8 reg, U8 value);
void SPI_Write_Buf(U8 reg, U8 *pBuffer, U8 Length);
U8 SPI_Verify_Buf(U8 reg, U8 *pBuffer, U8 Length);

void CLR_CSN(void);
void SET_CSN(void);



void CLR_CE(void);
void SET_CE(void);


#endif

