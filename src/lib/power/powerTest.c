#include <stdio.h>
#include "libpower.h"

int main(int argc, char *argv[]) {
	printf("***** Running test for libpower *****\n\n");

	// Using the values provided in the assignment description for this test
	// (50volt and 1398 ohm)
	float power_r = calc_power_r(50.0, 1398);

	// For this function, we take the current (ampere) as input.
	// Current = volt/resistance = 50/1398 = 0.0358
	float power_i = calc_power_i(50.0, 0.0358);

	printf("50 volts and 1398 ohm (resistance) should give us 1.79w in return.\n");
	printf("power_r: %.2f \n\n", power_r);
	printf("50 volts and 0.0358A should give us 1.79w in return\n");
	printf("power_i: %.2f \n", power_i);
	
	return 0;
}
