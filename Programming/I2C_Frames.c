#include "header.h"

void I2C_Byte_Write_Frame (U8 Slave_Address, U8 Memory_Address, U8 Data) {
	bit R;
	I2C_Start();
	I2C_Write(Slave_Address); //Write Slave Address SA + W
	R = I2C_Acknowledgement();
	if (R == SET) 
		goto Exit;
	
	I2C_Write(Memory_Address); //Write Memory Address
	R = I2C_Acknowledgement();
	if (R == SET) 
		goto Exit;
	
	I2C_Write(Data); //Write Data
	R = I2C_Acknowledgement();
	if (R == SET) 
		goto Exit;
	
	Exit:
		I2C_Stop();
}

U8 I2C_Byte_Read_Frame (U8 Slave_Address, U8 Memory_Address) {
	U8 Temp = 0;
	bit R;
	
	I2C_Start();
	I2C_Write(Slave_Address); //Write Slave Address SA + W
	R = I2C_Acknowledgement();
	if (R == SET) 
		goto Exit;
	
	I2C_Write(Memory_Address); //Write Memory Address
	R = I2C_Acknowledgement();
	if (R == SET) 
		goto Exit;
	
	I2C_Start();
	I2C_Write(Slave_Address | 1); //Write Slave Address SA + R
	R = I2C_Acknowledgement();
	if (R == SET) 
		goto Exit;
	
	Temp = I2C_Read(); //Get Data from Slave
	I2C_No_Acknowledgement();
	
	Exit:
		I2C_Stop();
	
	return Temp;
}