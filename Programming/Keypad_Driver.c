#include "header.h"

sbit ROW0 = P1^0;
sbit ROW1 = P1^1;
sbit ROW2 = P1^2;
sbit ROW3 = P1^3;
sbit COL0 = P1^4;
sbit COL1 = P1^5;
sbit COL2 = P1^6;
sbit COL3 = P1^7;

//4x4 Keypad Matrix Lookup Table
code U8 Keypad_Table[][4] = {{7, 8, 9, 'A'}, 
														 {4, 5, 6, 'F'}, 
														 {1, 2, 3, 'K'}, 
														 {0, 0, '=', 'P'}};


void Keypad_Init() {
	ROW0 = CLEAR;
	ROW1 = CLEAR;
	ROW2 = CLEAR;
	ROW3 = CLEAR;
	COL0 = SET;
	COL1 = SET;
	COL2 = SET;
	COL3 = SET;
}

//Getting the Key Pressed
U8 Key_Scan (void) {
	U8 ROW, COL;
	
	Keypad_Init();
	while ((COL0 & COL1 & COL2 & COL3) == SET); //Waiting for switch pressing
	
	//Checking ROW 0
	ROW0 = CLEAR;
	ROW1 = SET;
	ROW2 = SET;
	ROW3 = SET;
	if ((COL0 & COL1 & COL2 & COL3) == CLEAR) {
		ROW = 0;
		goto COL_Check;
	}
	
	//Checking ROW 1
	ROW0 = SET;
	ROW1 = CLEAR;
	ROW2 = SET;
	ROW3 = SET;
	if ((COL0 & COL1 & COL2 & COL3) == CLEAR) {
		ROW = 1;
		goto COL_Check;
	}
	
	//Checking ROW 2
	ROW0 = SET;
	ROW1 = SET;
	ROW2 = CLEAR;
	ROW3 = SET;
	if ((COL0 & COL1 & COL2 & COL3) == CLEAR) {
		ROW = 2;
		goto COL_Check;
	}
	
	//Checking ROW 3
	ROW0 = SET;
	ROW1 = SET;
	ROW2 = SET;
	ROW3 = CLEAR;
	if ((COL0 & COL1 & COL2 & COL3) == CLEAR) {
		ROW = 3;
		goto COL_Check;
	}
	
	//Checking Columns
	COL_Check:
		if (COL0 == CLEAR)
			COL = 0;
		else if (COL1 == CLEAR)
			COL = 1;
		else if (COL2 == CLEAR)
			COL = 2;
		else if (COL3 == CLEAR)
			COL = 3;
		
	return Keypad_Table[ROW][COL];
}