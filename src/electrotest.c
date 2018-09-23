#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "electrotest.h"
#include "lib/power/libpower.h"
#include "lib/component/libcomponent.h"

int main(void) {

	// First we create a variable that temorarily stores the users input
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
	int count = 0;
	if (conn == 'S' || conn == 'P') {
		fprintf(stdout, "Antal komponenter:");
		fgets (i, sizeof (i), stdin);
		count = atoi(i);
	}

	// and finally, the ohm values of each component
	float array[count];
	for (int r = 0; r < count; r++){
		fprintf(stdout, "Komponent %d i ohm:", (r+1));
		fgets (i, sizeof (i), stdin);
		array[r] = atoi(i);
		// Abort if user inputs negative value
		if (atoi(i) < 0) {
			r = count;
		}
	}


	// Calculate the resistance:
	float ohm = calc_resistance(count, conn, array);
	printf("Ersättningsresistans:\n%.1f ohm.\n", ohm);

	// Get the effect using the resistance:
	float watt = calc_power_r(volt, ohm);
	fprintf(stdout, "Effekt:\n%.2fW\n", watt);

        //Calculate E12 resistors
        float e12Resistors[LIBCOMPONENT_NUMBER_OF_RESISTORS] = {0, 0, 0};
        int numberofResistors = e_resistance(ohm, e12Resistors);

        if (numberofResistors < 0) {
            fprintf(stdout, "Something went wrong");
            return 0;   // Early return
        }

        fprintf(stdout, "Ersättningsreistanser i E12-serien kopplade i serie:\n");
        for (int i = 0; i < LIBCOMPONENT_NUMBER_OF_RESISTORS; i++) {
            if (e12Resistors[i] < 10) {
                fprintf(stdout, "%.1f\n", e12Resistors[i]);
            }
            else {
                fprintf(stdout, "%.0f\n", e12Resistors[i]);

            }
        }

	return 0;
}
