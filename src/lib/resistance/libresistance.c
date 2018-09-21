#include <stdio.h>
#include "libresistance.h"

float calc_resistance(int count, char conn, float *array){

	// If conn = P and count are valid, calculate parallel resistance
	if (conn == 'P') {
		return parallel(count, array);
	}

	// If conn = S and count are valid, calculate serial resistance
	if (conn == 'S'){
		return serial(count, array);
	}

	// Give error if conn is unvalid
	if (conn != 'P' || conn != 'S') {
		fprintf(stderr, "Ogiltig koppling. Enbart värdena S (seriell) och P (parallell) godtas\n");
	}

	// Return -1 for all unvalid cases
	return -1;
}

// Function to calculate parallel resistance
float parallel(int count, float *array) {
	if (count < 1 ){
		fprintf(stderr, "Inga resistorer. Ange minst en resistor.\n");
		return -1;
	}
	float resistance = 0;
	for (int i = 0; i < count; i++) {
		if (array[i] < 0) {
			fprintf(stderr, "Ogiltigt värde på komponent %d: %.1f\n", i+1, array[i]);
			return -1;
		}
		resistance += 1/array[i];
	}
	return 1/resistance;

}

// Function to calculate serial resistance
float serial(int count, float *array) {
	if (count < 1 ){
		fprintf(stderr, "Inga resistorer. Ange minst en resistor.\n");
		return -1;
	}
	float resistance = 0;
	for (int i = 0; i < count; i++){
		if (array[i] < 0) {
			fprintf(stderr, "Ogiltigt värde på komponent %d: %.1f\n", i+1, array[i]);
			return -1;
		}
		resistance += array[i];
	}
	return resistance;
}
