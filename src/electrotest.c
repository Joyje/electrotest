#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "electrotest.h"
#include "lib/power/libpower.h"

int main(void) {

	//First we create a variable that temorarily stores the users input
	char i[8];

	// Then, we need to get the volt:
	fprintf(stdout, "Ange spänningskälla i volt:");
	fgets (i, sizeof (i), stdin);
	float volt = atof(i);

	// Then we need to get the connection:
	fprintf(stdout, "Ange koppling [S | P]:");
	char conn = toupper(getchar());
	getchar();

	// ... number of components:
	fprintf(stdout, "Antal komponenter:");
	fgets (i, sizeof (i), stdin);
	int count = atoi(i);

	// and finally, the ohm values of each component
	float array[count];
	for (int r = 0; r < count; r++){
		fprintf(stdout, "Komponent %d i ohm:", (r+1));
		fgets (i, sizeof (i), stdin);
		array[r] = atoi(i);
	}


	// Calculate the resistance:
	float ohm = calc_resistance(count, conn, array);
	printf("Ersättningsresistans:\n%.1f ohm.\n", ohm);

	// Get the effect using the resistance:
	float watt = calc_power_r(volt, ohm);
	fprintf(stdout, "Effekt:\n%.2fW\n", watt);

	return 0;
}
