#include <stdio.h>

float calc_resistance(int count, char conn, float *array){
	float resistance = 0;
	if (count < 1 ){
		fprintf(stderr, "Inga resistorer. Ange minst en resistor.\n");
		return -1;
	} else if (conn == 'P') {
		for (int i = 0; i < count; i++) {
			if (array[i] < 0) {
				fprintf(stderr, "Ogiltigt värde på komponent %d. %f\n", i+1, array[i]);
				return -1;
			}
			resistance += 1/array[i];
		}
		return 1/resistance;
	} else if (conn == 'S'){
		for (int i = 0; i < count; i++){
			if (array[i] < 0) {
				fprintf(stderr, "Ogiltigt värde på komponent %d. %f\n", i+1, array[i]);
				return -1;
			}
			resistance += array[i];
		}
		return resistance;
	} else {
		fprintf(stderr, "Ogiltig koppling. Enbart värdena S (seriell) och P (parallell) godtas\n");
		return -1;
	}
}
