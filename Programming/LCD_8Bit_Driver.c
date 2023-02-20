#include "header.h"

#define LCD_PORT P0\

sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;

//Function to give command to the LCD Display
void CMD_LCD (U8 Command) {
	LCD_PORT = Command;
	RS = CLEAR;
	RW = CLEAR;
	EN = SET;
		Delay_ms(2);
	EN = CLEAR;
}

//Function to Initialise the LCD Display
void LCD_Init (void) {
	CMD_LCD(0x02);
	CMD_LCD(0x38);
	CMD_LCD(0x0E);
	CMD_LCD(0x01);
}

//Function to print Data on the LCD Display
void Data_LCD (U8 Data) {
	LCD_PORT = Data;
	RS = SET;
	RW = CLEAR;
	EN = SET;
		Delay_ms(2);
	EN = CLEAR;
}

//Function to print a character on the LCD Display
void Write_Char_LCD (U8 Ch) {
	LCD_PORT = Ch;
	RS = SET;
	RW = CLEAR;
	EN = SET;
		Delay_ms(2);
	EN = CLEAR;
}

//Function to print the String on the LCD Display
void Write_Str_LCD (S8 *Ptr) {
	while (*Ptr != 0) {
		Data_LCD(*Ptr);
		Ptr++;
	}
}

//Function to print the integer on the LCD Display
void Write_Int_LCD (S16 Number) {
	S8 A[10], i = 0;
	
	if (Number < 0) {
		Data_LCD('-');
		Number = -Number;
	}
	
	do {
		A[i] = (Number % 10) + 48;
		i++;
		Number = Number / 10;
	} while (Number != 0);
	
	for (i; i > 0; i--)
		Data_LCD(A[i - 1]);
}