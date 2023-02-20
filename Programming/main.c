#include "header.h"

#define Set_Point 45
#define Password 06

void Ext_Int (void) interrupt 0 {
	U8 Entered_Password, Saved_Password, New_Temp;
	U8 Count = 0;
	
	//Storing Password
	I2C_Byte_Write_Frame(0xA0, 0x50, Password);
	
	Start:	
		LCD_Init();
		CMD_LCD(0x80);
		Write_Str_LCD("ENTER PASSWORD: ");
		Entered_Password = Key_Scan();
		Saved_Password = I2C_Byte_Read_Frame(0xA0, 0x50);
		Write_Char_LCD(Entered_Password);
		Delay_ms(100);
		CMD_LCD(0x01);
		Delay_ms(100);
		if (Entered_Password == Saved_Password) {
			CMD_LCD(0x80);
			Write_Str_LCD("SET NEW TEMP: ");
			CMD_LCD(0xC0);
			New_Temp = Key_Scan();
			Write_Char_LCD(New_Temp);
			I2C_Byte_Write_Frame(0xA0, 0x80, New_Temp);
			Count = 0;
			Delay_ms(100);
			CMD_LCD(0x01);
			CMD_LCD(0x80);
			Write_Str_LCD("TEMP UPDATED! ");
			CMD_LCD(0xC0);
		}
		else if (Count < 3){
			Count++;
			CMD_LCD(0x80);
			Write_Str_LCD("WRONG PASSWORD");
			Delay_ms(500);
			CMD_LCD(0x01);
			CMD_LCD(0x80);
			Write_Str_LCD("TRY AGAIN !!");
			Delay_ms(500);
			CMD_LCD(0x01);
			goto Start;
		}
		else if (Count == 3) {
			Delay_ms(500);
			CMD_LCD(0x80);
			Write_Str_LCD("3 TRIALS OVER");
			Delay_ms(10);
			CMD_LCD(0xC0);
			Write_Str_LCD("WAIT FOR 30 SEC");
			Delay_ms(30000);
			CMD_LCD(0x01);
			Count = 0;
			goto Start;
		}
}

void main () {
	F32 Analog_R;
	U8 Temp, Check_Temp;
	
	IE = 0x81;
	IT0 = 0;
	
	LCD_Init();
	//Storing Temperature
	I2C_Byte_Write_Frame(0xA0, 0x80, Set_Point);
	
	while (1) {
		Check_Temp = I2C_Byte_Read_Frame(0xA0, 0x80);
		CMD_LCD(0x01);
		Delay_ms(20);
		CMD_LCD(0x80);
		Write_Str_LCD("CURRENT TEMP: ");
		Delay_ms(150);
		CMD_LCD(0x0C);
		Delay_ms(150);
		
		
		Analog_R = ADC_Read(); //Hexa-decimal
		Temp = Analog_R / 8.3; // Decimal
		CMD_LCD(0xC5);
		Write_Int_LCD(Temp);
		Data_LCD(223);
		Write_Str_LCD("C");
		CMD_LCD(0x0C);
		
		if (Temp <= Check_Temp)
			Green_LED(ON);
		else
			Red_LED(ON);
		Delay_ms(500);
		Green_LED(OFF);
		Red_LED(OFF);
		Delay_ms(500);
	}
}