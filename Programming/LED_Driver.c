#include "header.h"

sbit G_LED = P2^3;
sbit R_LED = P2^4;

void Green_LED (U8 State) {
	G_LED = State;
}

void Red_LED (U8 State) {
	R_LED = State;
}