#include "header.h"
#include <intrins.h>

sbit SCL = P3^6;
sbit SDA = P3^7;

void I2C_Start (void) {
	//Ideal Condition
	SCL = SET;
	SDA = SET;
	
	//I2C Start
	SCL = SET; //Default status of SCL line
	SDA = SET; //Default status of SDA line
	SDA = CLEAR; //Change the state of SDA from High to Low to issue the start of events
}

void I2C_Stop (void) {
	SCL = CLEAR; //To change status, SCl and SDA are made Low  during communication
	SDA = CLEAR;
	SCL = SET; //SCL line is released
	SDA = SET; //SDA is raised from Low to Hiigh to issue stop condition
}

void I2C_Write (U8 Data) {
	S8 i;
	for (i = 7; i >= 0; i--) {
		SCL = CLEAR; //To allow change of Bit status across SDA line
		SDA = (Data >> i) & 1; //Serialize - out Data MSB to LSB changing SDA line accordingly
		SCL = SET; //Release SCL so that slave can check/read/monitor Bit received across
	}
}

bit I2C_Acknowledgement (void) {

	SCL = CLEAR; //Master make SCL = 0 to change SDA to High/Release SDA
	SDA = SET; //Master is releasing SDA, so that slave can pull down SDA for +Acknowledgement
	SCL = SET; //Master releases SCL too
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	if (SDA == CLEAR) {
		SCL = CLEAR;
		return CLEAR;  //means Acknowledgement from Slave
	}
	else {
		SCL = CLEAR;
		return SET; //means no Acknowledgement from Slave
	}
}

U8 I2C_Read (void) {
	S8 i;
	U8 Temp = 0;
	
	for (i = 7; i >= 0; i--) {
		SCL = CLEAR;
		SCL = SET;
		if (SDA == SET)
			Temp = Temp | (1 << i);
	}
	return Temp;
}

void I2C_No_Acknowledgement (void) {
	SCL = SET;
	SDA = SET;
}