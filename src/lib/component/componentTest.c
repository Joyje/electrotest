
#include <stdio.h>
#include "component.h"

int calculate0Resistance(float* resistors) {

    int result = 0;

    result = e_resistance(5.0, resistors);
    printf("Number of resistors %d. Values %f, %f, %f\n", result, resistors[0],
           resistors[1], resistors[2]);

    return 0;
}


int main(int argc, char *argv[]) {

    float theThreeResistors[3] = {0, 0, 0};

    calculate0Resistance(theThreeResistors);
    return 0;
}
