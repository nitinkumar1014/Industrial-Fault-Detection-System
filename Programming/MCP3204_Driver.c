#include "header.h"

sbit CLK = P3^0;
sbit DIn = P3^1;
sbit DOut = P3^3;
sbit CS = P3^4;

U16 ADC_Read (void) {
	U16 Temp = 0;
	S8 i;
	
	CS = CLEAR; //Select the Slave for communication (or) ADC is ON
	
	CLK = CLEAR; DIn = SET; CLK = SET; //Start Bit
	CLK = CLEAR; DIn = SET; CLK = SET; //Single-ended Mode selected
	
	//Channel Selection
	CLK = CLEAR; DIn = SET; CLK = SET; // D2 is don't care for MCP3204
	CLK = CLEAR; DIn = CLEAR; CLK = SET; //D1
	CLK = CLEAR; DIn = CLEAR; CLK = SET; //D0 + Start Sampling
	
	CLK = CLEAR; DIn = SET; CLK = SET; //Stop Sampling
	CLK = CLEAR; DIn = SET; CLK = SET; //Null Bit
	
	//Reading 12 -Bit digital output from ADC
	for ( i = 11; i >= 0; i--) {
		CLK = CLEAR;
		if (DOut == SET) 
			Temp = Temp | (1 << i);
		CLK = SET;
	}
	
	CS = SET; //Slave is deselected from communication (or) ADC is OFF
	return Temp;
}