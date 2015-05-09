#include "structure.h"

//PinOsc P1.0

const struct Element elementB = {

              .inputPxselRegister = (uint8_t *)&P2SEL,  
              .inputPxsel2Register = (uint8_t *)&P2SEL2,  
              .inputBits = BIT5,
              .maxResponse = 121+655, 
              .threshold = 121 

};  


const struct Sensor keypad =
               { 
                  .halDefinition = RO_PINOSC_TA0,
                  .numElements = 1,
                  .baseOffset = 0,
                  // Pointers to elements
                  .arrayPtr[0] = &elementB,  
 

                  // Timer Information
                  .accumulationCycles= 100   //number of ACLK cycles              
               };


/*
//PinOsc Wheel: middle button P2.5
const struct Element elementB = {

              .inputPxselRegister = (uint8_t *)&P2SEL,  
              .inputPxsel2Register = (uint8_t *)&P2SEL2,  
              .inputBits = BIT5,
              // When using an abstracted function to measure the element
              // the 100*(maxResponse - threshold) < 0xFFFF
              // ie maxResponse - threshold < 655
              .maxResponse = 427+655,	// used for RO_PINOSC_TA1_xxx
              .threshold = 427
}; 

const struct Sensor keypad =
               { 
                  .halDefinition = RO_PINOSC_TA1_WDTp,
                  .numElements = 1,
                  .baseOffset = 4,
                  // Pointer to elements
                  .arrayPtr[0] = &elementB,  // point to first element
                  // Timer Information
                  .measGateSource= GATE_WDT_SMCLK,     //  0->SMCLK, 1-> ACLK
//                  .accumulationCycles= WDTp_GATE_32768             //32768
                  .accumulationCycles= WDTp_GATE_8192               // 8192
                  //.accumulationCycles= WDTp_GATE_512             //512
                  //.accumulationCycles= WDTp_GATE_64             //64                  
               };
*/

