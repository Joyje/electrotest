#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "electrotest.h"
#include "lib/power/libpower.h"

int main(void) {

	// First, we need to get the volt:
	fprintf(stdout, "Ange spänningskälla i volt:");

	char voltInput[8];
	fgets (voltInput, sizeof (voltInput), stdin);
	float volt = atof(voltInput);

	// Then we need to get the connection:
	char i[8];

	char conn;
	fprintf(stdout, "Ange koppling [S | P]:");
	conn = toupper(getchar());
	getchar();

	// We need the connection value to be in correct format; if we don't get it we may as well terminate
	if (conn != 'S' && conn != 'P') {
		fprintf(stderr, "Fel input, du måste ange S eller P!\n");
		return -1;
	}

	// ... number of components:
	int count;
	fprintf(stdout, "Antal komponenter:");
	fgets (i, sizeof (i), stdin);
	count = atoi(i);

	// and finally, the ohm values of each component
	float array[count];
	for (int r = 0; r < count; r++){
		fprintf(stdout, "Komponent %d i ohm:", (r+1));
		fgets (i, sizeof (i), stdin);
		array[r] = atoi(i);
	}


	// Calculate the resistance:
	float ohm = 0;
	ohm = calc_resistance(count, conn, array);
	printf("Ersättningsresistans:\n%.1f ohm.\n", ohm);

	// Get the effect using the resistance:
	float watt = calc_power_r(volt, ohm);
	fprintf(stdout, "Effekt:\n%.2fW\n", watt);

	return 0;
}
