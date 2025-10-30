#include "OLACommon.h"

unsigned long long OLA::myrand_seed = 1;
int OLA::myrand(void)
{
	// Use our own implementation of rand, stolen from PS2
	myrand_seed = 0x5851F42D4C957F2D * myrand_seed + 1;
	return ((myrand_seed >> 32) & 0x7FFFFFFF);
}