#ifndef _SPI_H
#define _SPI_H

#include "types.h"

UINT8 SPI_Read_Reg( UINT8 reg );
void SPI_Read_Buf(UINT8 reg, UINT8 *pBuffer, UINT8 Length);
void SPI_Write_Reg(UINT8 reg, UINT8 value);
void SPI_Write_Buf(UINT8 reg, UINT8 *pBuffer, UINT8 Length);
UINT8 SPI_Verify_Buf(UINT8 reg, UINT8 *pBuffer, UINT8 Length);

void CLR_CSN();
void SET_CSN();



void CLR_CE();
void SET_CE();


#endif

