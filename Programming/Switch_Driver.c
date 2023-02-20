#include "header.h"

sbit SW = P3^2;

bit Switch (void) {
	return SW;
}