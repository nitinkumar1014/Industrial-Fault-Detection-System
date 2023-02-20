#include "header.h"

void IO_Bit_Write (U8 PORT_Num, U8 PIN_Num, U8 State) {
	switch (PORT_Num) {
		
		#ifdef PORT0
		case PORT0:
						if (State == SET)
							P0 |=(1 << PIN_Num);
						else
							P0 &= ~(1 << PIN_Num);
						break;
		#endif
		
		#ifdef PORT1
		case PORT1:
						if (State == SET)
							P1 |=(1 << PIN_Num);
						else
							P1 &= ~(1 << PIN_Num);
						break;
		#endif
		
		#ifdef PORT2
		case PORT2:
						if (State == SET)
							P2 |=(1 << PIN_Num);
						else
							P2 &= ~(1 << PIN_Num);
						break;
		#endif
						
		#ifdef PORT3
		case PORT3:
						if (State == SET)
							P3 |=(1 << PIN_Num);
						else
							P3 &= ~(1 << PIN_Num);
						break;
		#endif
	}
}

/*This function is used to read live 
	status of given IO pin*/
bit IO_Bit_Read (U8 PORT_Num, U8 PIN_Num) {
	U8 Status;
	switch (PORT_Num) {
		case PORT0:
			Status = ((P0 >> PIN_Num) & 1) ? 1 : 0;
			break;
		case PORT1:
			Status = ((P1 >> PIN_Num) & 1) ? 1 : 0;
			break;
		case PORT2:
			Status = ((P2 >> PIN_Num) & 1) ? 1 : 0;
			break;
		case PORT3:
			Status = ((P3 >> PIN_Num) & 1) ? 1 : 0;
			break;
	}
	return Status;
}