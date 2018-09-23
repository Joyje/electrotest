/**
 * @file componentTest.h
 * @brief Unit tests for libcomponent
 *
 * @author Charlotte Hagborg
 * @date 21 Sep 2018
 */

#include <stdio.h>
#include "libcomponent.h"

#define OK "OK"
#define FAILED "FAILED"

int calculate0Resistance(float* resistors) {

    int result = 0;
    const float expectedResistance1 = 0;
    const float expectedResistance2 = 0;
    const float expectedResistance3 = 0;

    result = e_resistance(0, resistors);
    if (result == 0 && resistors[0] == expectedResistance1 && resistors[1] == expectedResistance2 && resistors[2] == expectedResistance3) {
        printf("%s: %s\n", __func__, OK);
    }
    else {
        printf("%s: %s. Number of resistors=%d(0), ResistorValue=%f(%f), %f(%f), %f(%f)\n", __func__, FAILED, result,
               resistors[0], expectedResistance1, resistors[1], expectedResistance2, resistors[2], expectedResistance3);
    }
    return 0;
}


int calculateMaxResistance(float* resistors) {

    int result = 0;
    const float expectedResistance1 = 820;
    const float expectedResistance2 = 820;
    const float expectedResistance3 = 820;

    result = e_resistance((expectedResistance1 * 3), resistors);
    if (result == 3 && resistors[0] == expectedResistance1 && resistors[1] == expectedResistance2 && resistors[2] == expectedResistance3) {
        printf("%s: %s\n", __func__, OK);
    }
    else {
        printf("%s: %s. Number of resistors=%d(3), ResistorValue=%f(%f), %f(%f), %f(%f)\n", __func__, FAILED, result,
               resistors[0], expectedResistance1, resistors[1], expectedResistance2, resistors[2], expectedResistance3);
    }
    return 0;
}

int calculate2MaxResistance(float *resistors) {

    int result = 0;
    const float expectedResistance1 = 820;
    const float expectedResistance2 = 820;
    const float expectedResistance3 = 0;

    result = e_resistance((expectedResistance1 * 2), resistors);
    if (result == 2 && resistors[0] == expectedResistance1 && resistors[1] == expectedResistance2 && resistors[2] == expectedResistance3) {
        printf("%s: %s\n", __func__, OK);
    }
    else {
        printf("%s: %s. Number of resistors=%d(2), ResistorValue=%f(%f), %f(%f), %f(%f)\n", __func__, FAILED, result,
               resistors[0], expectedResistance1, resistors[1], expectedResistance2, resistors[2], expectedResistance3);
    }
    return 0;
}

int calculateMinResistance(float *resistors) {

    int result = 0;
    const float expectedResistance1 = 1.2;
    const float expectedResistance2 = 0;
    const float expectedResistance3 = 0;

    result = e_resistance((expectedResistance1), resistors);
    if (result == 1 && resistors[0] == expectedResistance1 && resistors[1] == expectedResistance2 && resistors[2] == expectedResistance3) {
        printf("%s: %s\n", __func__, OK);
    }
    else {
        printf("%s: %s. Number of resistors=%d(1), ResistorValue=%f(%f), %f(%f), %f(%f)\n", __func__, FAILED, result,
               resistors[0], expectedResistance1, resistors[1], expectedResistance2, resistors[2], expectedResistance3);
    }
    return 0;
}

int calculateNegativeInvalidResistance(float *resistors) {

    int result = 0;
    const float expectedResistance1 = 0;
    const float expectedResistance2 = 0;
    const float expectedResistance3 = 0;

    result = e_resistance(-75, resistors);
    if (result == -1 && resistors[0] == expectedResistance1 && resistors[1] == expectedResistance2 && resistors[2] == expectedResistance3) {
        printf("%s: %s\n", __func__, OK);
    }
    else {
        printf("%s: %s. Number of resistors=%d(0), ResistorValue=%f(%f), %f(%f), %f(%f)\n", __func__, FAILED, result,
               resistors[0], expectedResistance1, resistors[1], expectedResistance2, resistors[2], expectedResistance3);
    }
    return 0;
}

int calculateTooHighResistance(float *resistors) {

    int result = 0;
    const float expectedResistance1 = 0;
    const float expectedResistance2 = 0;
    const float expectedResistance3 = 0;

    result = e_resistance((820 * 3 + 1), resistors);
    if (result == -1 && resistors[0] == expectedResistance1 && resistors[1] == expectedResistance2 && resistors[2] == expectedResistance3) {
        printf("%s: %s\n", __func__, OK);
    }
    else {
        printf("%s: %s. Number of resistors=%d(0), ResistorValue=%f(%f), %f(%f), %f(%f)\n", __func__, FAILED, result,
               resistors[0], expectedResistance1, resistors[1], expectedResistance2, resistors[2], expectedResistance3);
    }
    return 0;
}

int main(int argc, char *argv[]) {

    float theThreeResistors[LIBCOMPONENT_NUMBER_OF_RESISTORS] = {0, 0, 0};

    calculate0Resistance(theThreeResistors);
    calculateMaxResistance(theThreeResistors);
    calculate2MaxResistance(theThreeResistors);
    calculateMinResistance(theThreeResistors);
    calculateNegativeInvalidResistance(theThreeResistors);
    calculateTooHighResistance(theThreeResistors);
    return 0;
}
