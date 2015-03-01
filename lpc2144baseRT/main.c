// Simple blinking led program for the LPC-H2148 board

/* *********************************************************
               Function declarations
  ********************************************************* */

void Initialize(void);
void feed(void);
void spiInit (void);
void IRQ_Routine (void)   __attribute__ ((interrupt("IRQ")));
void FIQ_Routine (void)   __attribute__ ((interrupt("FIQ")));
void SWI_Routine (void)   __attribute__ ((interrupt("SWI")));
void UNDEF_Routine (void) __attribute__ ((interrupt("UNDEF")));

/**********************************************************
                  Header files
 **********************************************************/
/* Standard includes. */
#include <stdlib.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "sysdefs.h"
/* Hardware includes. */
#include "bk2421.h"

/* Task includes. */
#include "ledblink.h"
#include "usbser.h"
#include "usb2wireless.h"
xTaskHandle adctaskhandle;

#define mainLED_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define SPI_SEL      (1 << 11) 



/**********************************************************
                       MAIN
**********************************************************/
int	main (void) {
	
	// Initialize the system
	Initialize();
//	IO0DIR |= (1<<3);	// P0.02 output
	IO0DIR |=(1<<14);	// debug led on P1.14 between
	IO0DIR |=(1<<13);	// /CS for SPI P1.13


   xTaskCreate(vLEDTask, ( signed char * ) "LED", configMINIMAL_STACK_SIZE,NULL, tskIDLE_PRIORITY, NULL );
   xTaskCreate(vUsb2WirelessTask, ( signed char * ) "USB2WIR", configMINIMAL_STACK_SIZE,NULL, tskIDLE_PRIORITY+2, NULL );
//   xTaskCreate (vLCDTask, ( signed char * ) "LCD", configMINIMAL_STACK_SIZE,
//NULL, (tskIDLE_PRIORITY+1), NULL);
//   xTaskCreate (refreshLCD, ( signed char * ) "LCDDR", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY), NULL);
//   xTaskCreate (vKEYTask, ( signed char * ) "KEY", configMINIMAL_STACK_SIZE,
//NULL, (tskIDLE_PRIORITY+1), NULL);
//   xTaskCreate (vADCTask, ( signed char * ) "ADC", configMINIMAL_STACK_SIZE,
//NULL, (tskIDLE_PRIORITY + 2), &adctaskhandle);
  // xTaskCreate (vPRIMETask, ( signed char * ) "PRIMES", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY), NULL);

    usbserInit();
    spiInit();
    BK2421_Initialize();
	SwitchToTxMode();

    //putStringXY("Prototype 1",4,0);
    //putStringXY(">=MENU",12,3);
	
    vTaskStartScheduler();

 //   IO0CLR=(1<<10);	
    IO0CLR=1<<14;
    IO0CLR=1<<13;
    while(1);
}



/**********************************************************
                      Initialize
**********************************************************/

#define PLOCK 0x400

void Initialize(void)  {
    //SET P0.22 Pin as PWR sustain output
    //Not required, because we are not in battery mode!
/*    IO0DIR=0x00; 
    IO0DIR |= GPIO_IO_P22;
    //IO0CLR = (1<<22);
    IO0SET = (1<<22); // PWR sustain
*/
   
	// Setting Multiplier and Divider values
//23 za 48MHz 24 za 60MHz
  	PLLCFG=0x23; //dela tudi z 21 (24MHz)
  	feed();
  
	// Enabling the PLL */	
	PLLCON=0x1;
	feed();
  
	// Wait for the PLL to lock to set frequency
	while(!(PLLSTAT & PLOCK)) ;
  
	// Connect the PLL as the clock source
	PLLCON=0x3;
	feed();
  
	// Enabling MAM and setting number of clocks used for Flash memory fetch (4 cclks in this case)
	MAMCR=0x2;
	MAMTIM=0x4;
  
	// Setting peripheral Clock (pclk) to System Clock (cclk)
	VPBDIV=0x1;


    PINSEL0=0x00;
    //SET P0.22 Pin as PWR sustain output
    //IO0DIR=0x00; 
    //IO0DIR |= GPIO_IO_P22;
    //IO0CLR = (1<<22);
    //Set P1.28 Pin as output for ADC frequency output
/*    IO1DIR=0x00;
   	IO1DIR |= GPIO_IO_P28;	// P1.28 output
    IO1DIR |= GPIO_IO_P19; // Fast charge
    IO1SET = (1<<19); // Fast charge ON!
*/

    // Initialize Serial port on UART0

 //   uartInit(115200);


}
void spiInit (void)
{
  unsigned int spsr;
  //
  //  Setup SCK0, MISO0 and MOSI0.  SSEL0 (P0.7) is GPIO
  //
  PCB_PINSEL0 = (PCB_PINSEL0 & ~(PCB_PINSEL0_P04_MASK | PCB_PINSEL0_P05_MASK | PCB_PINSEL0_P06_MASK | PCB_PINSEL0_P07_MASK)) | (PCB_PINSEL0_P04_SCK0 | PCB_PINSEL0_P05_MISO0 | PCB_PINSEL0_P06_MOSI0 | PCB_PINSEL0_P07_GPIO);

  //
  //  Set P0.7 as output, deselect by driving high
  //
  IO0DIR |= GPIO_IO_P7;
  IO0SET  = GPIO_IO_P7;

  //
  //  Turn on SPI module power
  //
  SCB_PCONP |= SCB_PCONP_PCSPI0;

  //
  //  SPI configuration:
  //    Master mode
  //    Sample on 1st edge of SCK
  //    SCK is active high
  //    MSB out first
  //    No interrupts
  //
  SPI_SPCR = SPI_SPCR_MSTR | SPI_SPCR_CPHA1ST | SPI_SPCR_CPOLACTHIGH | SPI_SPCR_MSBF;
  
  //
  //  Reading the status register clears it
  //
  spsr = SPI_SPSR;

  //
  //  SCK0 = (PCLK = (CCLK/APB)) / 8 will be 6Mhz (putt putt putt...)
  //
  SPI_SPCCR = 0xF0;
}



void feed(void)
{
  PLLFEED=0xAA;
  PLLFEED=0x55;
}
/*
unsigned long ul;
void vApplicationTickHook( void )
{
 ul++;
 if(ul%2)
    IO0SET =1<<10;
 else
    IO0CLR= 1<<10;
}
*/

/*  Stubs for various interrupts (may be replaced later)  */
/*  ----------------------------------------------------  */

void IRQ_Routine (void) {
	while (1) ;	
}

void FIQ_Routine (void)  {
	while (1) ;	
}


void SWI_Routine (void)  {
	while (1) ;	
}


void UNDEF_Routine (void) {
	while (1) ;	
}
