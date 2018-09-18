#include "libpower.h"
#include <stdio.h>
/**
 * Calculates power from volt and resistance
 */
float calc_power_r(float volt, float resistance) {
	// The formula is P = U*I, where U is equal to R*I.
	// First we need to find I, which is ampere. So we convert Ohm to ampere by taking volt/ohm:
	float i = volt / resistance;

	// Since u == volt, we can just return volt * I
	return volt * i;
}

/**
 * Calculates power from volt and current
 */
float calc_power_i(float volt, float current) {
	// The formula is P = U*I. We already have both those values (volt and
	// current), so we can just multiply and return the product
	return volt * current;
}
