#include <stdio.h>

float calc_resistance(int count, char conn, float *array){
	float resistance = 0;
	if (count > 0 ){
		if (conn == 'P') {
			fprintf(stdout, "Du har angett parallellkoppling\n");
			for (int i = 0; i < count; i++) {
				resistance += 1/array[i];
			}
			if (resistance > 0){
				resistance = 1/resistance;
			}
			return resistance;

		} else if (conn == 'S'){
			fprintf(stdout, "Du har angett seriekoppling\n");
			for (int i = 0; i < count; i++){
				resistance += array[i];
			}
			return resistance;
		} else {
			fprintf(stderr, "Ogiltig koppling. Enbart värdena S (seriell) och P (parallell) godtas\n");
			return -1;
		}
	} else {
		fprintf(stderr, "Inga resistorer. Ange minst en resistor.\n");
		return -1;
	}
}
