#include "component.h"

/**
 * Calculates which three serial connected resistances that can be used for the "orig_resistance".
 * @param[in] orig_resistance The resistance that needs resistors
 * @param[out] res_array The array of maximum three resistors. 0 should be used if not needed
 * @return Number of resistors needed
 */
int e_resistance(float orig_resistance,
                 float* res_array) {

    float e12Values[] = {1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2};
    float remainingResistance = orig_resistance;
    int e12ArrayLength = sizeof(e12Values) / sizeof(e12Values[0]);

    return 1;
}
