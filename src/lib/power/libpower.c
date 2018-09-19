#include "libpower.h"
#include <stdio.h>
#include <math.h>

/**
 * Calculates power from volt and resistance
 */
float calc_power_r(float volt, float resistance) {
	// The formula is P = U^2 / R, so first we need to raise volt to the power
	// of 2. After that, we just divide the result with the resistance argument
	return powf(volt, 2) / resistance;
}

/**
 * Calculates power from volt and current
 */
float calc_power_i(float volt, float current) {
	// The formula is P = U*I. We already have both those values (volt and
	// current), so we can just multiply and return the product
	return volt * current;
}
