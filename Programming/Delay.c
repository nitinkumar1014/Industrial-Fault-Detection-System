#include "header.h"

void Delay_ms (U16 ms) {
	U8 i;
	
	for ( ; ms > 0; ms--) {
		for (i = 50; i > 0; i--);
		for (i = 48; i > 0; i--);
	}
}