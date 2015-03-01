/*--------------------------------------------------------------------------------------
*This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
*****************
*MCU: STC89LE58RD+
Compiler:uVision2 2.40
*****************
* website: http://www.bekencorp.com
---------------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "sysdefs.h"

#define sBitCE   (1<<3)
#define BitCE_bit   (3)	

#define MAX_PACKET_LEN  32// max value is 32


//************************FSK COMMAND and REGISTER****************************************//
// SPI(BK2421) commands
#define READ_REG        0x00  // Define read command to register
#define WRITE_REG       0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define W_TX_PAYLOAD_NOACK_CMD	0xb0
#define W_ACK_PAYLOAD_CMD	0xa8
#define ACTIVATE_CMD		0x50
#define R_RX_PL_WID_CMD		0x60
//#define NOP             0xFF  // Define No Operation, might be used to read status register

// SPI(BK2421) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address
#define PAYLOAD_WIDTH   0x1f  // 'payload length of 256 bytes modes register address
#define DYNPD           0x1c
#define FEATURE         0x1d

//interrupt status
#define STATUS_RX_DR    0x40
#define STATUS_TX_DS    0x20
#define STATUS_MAX_RT   0x10

#define STATUS_TX_FULL 0x01

//FIFO_STATUS
#define FIFO_STATUS_TX_REUSE 0x40
#define FIFO_STATUS_TX_FULL 0x20
#define FIFO_STATUS_TX_EMPTY 0x10

#define FIFO_STATUS_RX_FULL 0x02
#define FIFO_STATUS_RX_EMPTY 0x01


//EXTERN MACROS=====================================================================
//Set RX address
#define RF_SET_RX_ADDR(addr) { SPI_Write_Buf((WRITE_REG|RX_ADDR_P0), addr, 5); }   
//TX address
#define RF_SET_TX_ADDR(addr) { SPI_Write_Buf((WRITE_REG|TX_ADDR), addr, 5); }    
//Set ACK
#define RF_SET_AUTO_ACK(enable) { SPI_Write_Reg((WRITE_REG|EN_AA), enable); } 
//choice pipe
#define RF_SET_CHN(ch) { SPI_Write_Reg((WRITE_REG|RF_CH), ch); }
//Read status register
#define RF_GET_STATUS() ( SPI_Read_Reg(STATUS) )
//Clear IRQ
#define RF_CLR_IRQ(x) { SPI_Write_Reg(WRITE_REG|STATUS, x); }
//Read receiver data length
#define RF_GET_RX_PL_LEN() ( SPI_Read_Reg(R_RX_PL_WID_CMD) )
//Read result of carry detection
#define RF_GET_CD() ( SPI_Read_Reg(CD) )
//Clear RX FIFO
#define RF_FLUSH_RX() { SPI_Write_Reg(FLUSH_RX,0); }
//Clear TX FIFO
#define RF_FLUSH_TX() { SPI_Write_Reg(FLUSH_TX,0); }


//EXTERN FUNCTIONS==================================================================
void DelayMs( U8 dlycnt );
void SwitchToRxMode( void );
void SwitchToTxMode( void );
void SwitchCFG( U8 _cfg );
void RF_SetPowerMode( U8 powerdown );
void BK2421_Initialize(void);
void RF_WriteTxPayload( U8* pbuf, U8 len );
void RF_WriteAckPayload( U8* pbuf, U8 len );
U8 RF_ReadRxPayload( U8 *pbuf, U8 maxlen );


