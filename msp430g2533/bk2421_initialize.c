#include "bk2421.h"
#include "spi.h"
//#include <avr/pgmspace.h>
//#include "bsp.h"

#define BANK0_REG_LIST_CNT			21
#define BANK0_REGACT_LIST_CNT		2

/*Bank1 register initialization value*/
//Reg0 to Reg13
#ifdef BK2421
const UINT32 Bank1_Reg0_13[]={
0xE2014B40,
0x00004BC0,
0x028CFCD0,
0x41390099,
0x0B869ED9,     //Change REG4[29:27] from 00 to 11
//0x21869ED9,   //For single carrier mode
0xA67F0624,     //Disable RSSI measurement
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00127300,
0x36B48000,
};
//Reg14,    Ramp curve
const UINT8 Bank1_Reg14[]=
{
0x41,0x20,0x08,0x04,0x81,0x20,0xCF,0xF7,0xFE,0xFF,0xFF
};
#endif

/*Bank0 register initialization value*/
const UINT8 Bank0_Reg[BANK0_REG_LIST_CNT][2]={
	{CONFIG,	0x0F},	//Power up, PRX
	{EN_AA,		0x01},	//Enable pipe0 auto ACK
	{EN_RXADDR,	0x01},	//Enable data pipe 0
	{SETUP_AW,	0x03},	//Address width = 5Bytes
	{SETUP_RETR,0x25},	//Retransmit, ARD = 750us, ARC = 5
	{RF_CH,		0x20},	//channel = 60
	{RF_SETUP,	0x15},	//1Mbps data rate, output power=0dBm 
	{STATUS,	0x70},	
	{OBSERVE_TX,0x00},	
	{CD,		0x00},
	{RX_ADDR_P2,0xc3},
	{RX_ADDR_P3,0xc4},
	{RX_ADDR_P4,0xc5},
	{RX_ADDR_P5,0xc6},
	{RX_PW_P0,	0x20},	//RX Payload Length = 32
	{RX_PW_P1,	0x20},
	{RX_PW_P2,	0x20},
	{RX_PW_P3,	0x20},
	{RX_PW_P4,	0x20},
	{RX_PW_P5,	0x20},
	{FIFO_STATUS,0x11} 
};

const UINT8 Bank0_RegAct[BANK0_REGACT_LIST_CNT][2] = {
	{DYNPD,		0x01},	//Enable pipe 0, Dynamic payload length
	{FEATURE,	0x04}	//EN_DPL= 1, EN_ACK_PAY = 0, EN_DYN_ACK = 0
};

/*The Rx Address 5 bytes*/
const UINT8 RX_Address[5] = { 0x3a, 0x3b, 0x3c, 0x3d, 0x01 };

/*The Tx Address 5 bytes*/
const UINT8 TX_Address[5] = { 0x3a, 0x3b, 0x3c, 0x3d, 0x01 };

extern volatile UINT8 g_TimeDelay;

/*****************************************************************************************
Function:       void DelayMs( UINT8 dlycnt )
Parameter: 
                dlycnt  [IN]    delay period, unit: ms 
Return: 
                None 
Description:
                To delay the program for dlycnt(ms) time
                It is recommended to use a 1ms timer for this delay work 
*****************************************************************************************/
void DelayMs( UINT8 dlycnt )
{
	volatile int cnt;
		cnt = 71*dlycnt; //checked with osciloscope
		do (cnt--);
		while (cnt != 0);

}

/*****************************************************************************************
Function:       void SwitchToRxMode( void )
Parameter: 
                None 
Return: 
                None 
Description:
	            switch to Rx mode
*****************************************************************************************/
void SwitchToRxMode( void )
{
	UINT8 value;

	SPI_Write_Reg( FLUSH_RX, 0 );	//flush Rx

	value = SPI_Read_Reg( STATUS );	// read register STATUS's value
	SPI_Write_Reg( WRITE_REG | STATUS, value );// clear RX_DR or TX_DS or MAX_RT interrupt flag

	CLR_CE();

	value = SPI_Read_Reg( CONFIG );	// read register CONFIG's value

    //PRX
	value = value | 0x01;//set bit 1
  	SPI_Write_Reg( WRITE_REG | CONFIG, value ); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled..

	SET_CE();
}

/*****************************************************************************************
Function:       void SwitchToTxMode( void )
Parameter: 
                None
Return: 
                None
Description:
	            switch to Tx mode
*****************************************************************************************/
void SwitchToTxMode( void )
{
	UINT8 value;
	SPI_Write_Reg( FLUSH_TX, 0 );               //flush Tx

	CLR_CE();
	value = SPI_Read_Reg( CONFIG );	            // read register CONFIG's value

    //PTX
	value = value & 0xfe;                       //set bit 1
  	SPI_Write_Reg( WRITE_REG | CONFIG, value ); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled.

	SET_CE();
}


/*****************************************************************************************
Function:       void SwitchCFG( char _cfg )
Parameter: 
                _cfg    [IN]
                            1:register bank1
            	            0:register bank0 
Return: 
                None 
Description:
	            access switch between Bank1 and Bank0 
*****************************************************************************************/
void SwitchCFG( UINT8 _cfg )//1:Bank1 0:Bank0
{
    UINT8 Tmp = 0;

    Tmp = SPI_Read_Reg( 7 );
    Tmp = Tmp & 0x80;
    
    if( (_cfg && (!Tmp)) ||((!_cfg) && Tmp) )
    {
        SPI_Write_Reg( ACTIVATE_CMD, 0x53 );
    }

    SPI_Read_Reg( 7 );
}



/*****************************************************************************************
Function:       void RF_SetPowerMode( UINT8 powerdown ) 
 
Parameter: 
                powerdown   [IN]
                                    TRUE    Set to Powerdown mode
                                    FALSE   Set to Powerup mode
Return: 
                None 
Description:
	            Power mode switch between powerdown and powerup
*****************************************************************************************/
void RF_SetPowerMode( UINT8 powerdown )
{
	UINT8 rd;

	rd = SPI_Read_Reg( CONFIG );
	if( powerdown )
	{
		rd &= ~(1 << 1);
	}
	else
	{
		rd |= (1 << 1);
	}

	SPI_Write_Reg( CONFIG, rd );
}

///////////////////////////////////////////////////////////////////////////////
//                  BK2421 initialization                                    //
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************
Function:       void BK2421_Initialize()
 
Parameter: 
                None
Return: 
                None 
Description:
	            Initialization the Bk2421's register
*****************************************************************************************/
void BK2421_Initialize()
{
    signed char i,j;
    UINT8 rData;
    UINT8 WriteArr[4];
    //UINT8 addr,value;

    DelayMs(100);   //delay more than 50ms.

    SwitchCFG(0);

//********************Write Bank0 register******************
    for( i = (BANK0_REG_LIST_CNT - 1); i >= 0; i-- )
    {
        SPI_Write_Reg( (WRITE_REG | Bank0_Reg[i][0]), Bank0_Reg[i][1] );
        rData = SPI_Read_Reg( Bank0_Reg[i][0] );
    }

    //reg 10 - Rx0 addr
    RF_SET_RX_ADDR( (UINT8 *)RX_Address );

    //REG 16 - TX addr
    RF_SET_TX_ADDR( (UINT8 *)TX_Address );

    i = SPI_Read_Reg( 29 );

    if( i == 0 ) // i!=0 showed that chip has been actived.so do not active again.
    {
        SPI_Write_Reg( ACTIVATE_CMD, 0x73 );// Active
    }



    for( i = (BANK0_REGACT_LIST_CNT - 1); i >= 0; i-- )
    {
        SPI_Write_Reg( (WRITE_REG | Bank0_RegAct[i][0]), Bank0_RegAct[i][1] );

        SPI_Read_Reg( (Bank0_RegAct[i][0]) );
    }

#ifdef BK2421
//********************Write Bank1 register******************
    SwitchCFG(1);

    for( i = 0; i <= 8; i++ )//reverse
    {
        for( j = 0; j < 4; j++ )
        {
            WriteArr[ j ] = ( Bank1_Reg0_13[i] >> ( 8 * (j) ) ) & 0xff;
        }

        SPI_Write_Buf( (WRITE_REG|i), &(WriteArr[0]), 4 );
    }

    for( i = 9; i <= 13; i++ )
    {
        for( j = 0; j < 4; j++ )
        {
            WriteArr[j] = ( Bank1_Reg0_13[i] >> ( 8 * ( 3 - j ) ) ) & 0xff;
        }

        SPI_Write_Buf( ( WRITE_REG|i), &(WriteArr[0]), 4 );
    }

    SPI_Write_Buf( ( WRITE_REG|14), (UINT8 *)&(Bank1_Reg14[0]), 11 );

    //toggle REG4<25,26>
    for( j = 0; j < 4; j++ )
    {
        WriteArr[j] = ( Bank1_Reg0_13[4] >> ( 8 * (j) ) ) & 0xff;
    }

    WriteArr[0] = WriteArr[0] | 0x06;
    SPI_Write_Buf( (WRITE_REG | 4), &(WriteArr[0]), 4 );

    WriteArr[0] = WriteArr[0] & 0xf9;
    SPI_Write_Buf( (WRITE_REG | 4 ), &(WriteArr[0] ), 4 );

    DelayMs( 10 );

//********************switch back to Bank0 register access******************
    SwitchCFG( 0 );
#endif

    SwitchToRxMode();//switch to RX mode

    RF_FLUSH_RX();
    RF_FLUSH_TX();
}





