#include <reg52.h>

//STATES
#define CLEAR 0
#define SET 1


//Typedefs
#ifndef __TYPES_H__
#define __TYPES_H__
typedef unsigned char U8;
typedef 	signed char S8;
typedef unsigned int  U16;
typedef 	signed int  S16;
typedef unsigned long U32;
typedef 	signed long S32;
typedef float 				F32;
typedef double 				F64;
#endif

//Delay Function
extern void Delay_ms (U16 ms);

//LEDs State
#define ON 0
#define OFF 1

//LED Functions
extern void Green_LED (U8 State);
extern void Red_LED (U8 State);

//LCD 8-Bit Drivwer Functions
extern void CMD_LCD (U8 Command);
extern void LCD_Init (void);
extern void Data_LCD (U8 Data);
extern void Write_Char_LCD (U8 Data);
extern void Write_Str_LCD (S8 *Ptr);
extern void Write_Int_LCD (S16 Number);

//Switch State
#define PRESSED 0
#define UNPRESSED 1

//Switch Functions
extern bit Switch (void);

//Keypad Function
extern U8 Key_Scan (void);

//I2C Fields
extern void I2C_Start (void);
extern void I2C_Stop (void);
extern void I2C_Write (U8 Data);
extern bit I2C_Acknowledgement (void);
extern U8 I2C_Read (void);
extern void I2C_No_Acknowledgement (void);

//I2c Frames
extern void I2C_Byte_Write_Frame (U8 Slave_Address, U8 Memory_Address, U8 Data);
extern U8 I2C_Byte_Read_Frame (U8 Slave_Address, U8 Memory_Address);

//ADC Functions
extern U16 ADC_Read (void);