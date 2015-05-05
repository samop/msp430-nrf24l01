
#include "CTS_Layer.h"
#define LED BIT0

#define NUM_SEN	14

struct Element* keypressed;

// Main Function
void main(void)
{ 
  uint8_t i;
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

  BCSCTL3 |= LFXT1S_2;                  // LFXT1 = VLO
 	P1DIR|=LED; 
/*
BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 |= DIVS_2;
*/
  TI_CAPT_Init_Baseline(&keypad);
  TI_CAPT_Update_Baseline(&keypad,5);

  // Main loop starts here
  while (1)
  {
    keypressed = (struct Element *)TI_CAPT_Buttons(&keypad);
	if(keypressed)
	{
 	P1OUT |=LED;  
	} else{
 	P1OUT &=~LED;  
	}
  }
} // End Main

