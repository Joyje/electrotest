#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "electrotest.h"

int main(void){
	char i[8];

	char conn;
	fprintf(stdout, "Ange koppling [S | P]:");
	conn = getchar();
	getchar();

	int count;
	fprintf(stdout, "Antal komponenter:");
	fgets (i, sizeof (i), stdin);
	count = atoi(i);

	float array[count];
	for (int r = 0; r < count; r++){
		fprintf(stdout, "Komponent %d i ohm:", (r+1));
		fgets (i, sizeof (i), stdin);
		array[r] = atoi(i);
	}

	float ohm = 0;
	ohm = calc_resistance(count, conn, array);
	printf("Ersättningsresistans:\n%f ohm.\n", ohm);
	return 0;
}
