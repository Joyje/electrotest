#include "component.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void calculateBestFit(float wantedSum,
                      float *e12Array,
                      int numberOfE12Values,
                      float* resultArray) {

    float rest = wantedSum;
    float tmpRest = wantedSum;
    int e12ValueIndexMax = numberOfE12Values - 1;
    for(int i = e12ValueIndexMax; i>=0; i--) {
        for (int j = e12ValueIndexMax; j>=0; j--) {
            for (int k = e12ValueIndexMax; k>=0; k--) {
               tmpRest = wantedSum - e12Array[i] - e12Array[j] - e12Array[k];
               if (fabsf(tmpRest) < fabsf(rest)) {
                   rest = tmpRest;
                   resultArray[0] = e12Array[i];
                   resultArray[1] = e12Array[j];
                   resultArray[2] = e12Array[k];
               }
               if (tmpRest == 0) {
                   //No reason to continue, best value already achieved, return early
                   return;
               }
            }
        }
    }
}

void fillAllResistanceValues(float *e12NormValues,
                             int e12NormArrayLength,
                             float *e12UpTo1000Array,
                             int totalArrayLength) {
    int tmpFactor = 1;

    for (int i = 0; i < totalArrayLength; i++) {
        for (int j = 0; j < e12NormArrayLength; j++) {
            e12UpTo1000Array[i] = e12NormValues[j] * tmpFactor;
            printf("%f\n", e12UpTo1000Array[i]);
        }
        if ((i > 0) && (i % e12NormArrayLength == 0)) {
            tmpFactor = tmpFactor * 10;
        }
    }


}

/**
 * Calculates which three serial connected resistances that can be used for the "orig_resistance".
 * @param[in] orig_resistance The resistance that needs resistors
 * @param[out] res_array The array of maximum three resistors. 0 should be used if not needed
 * @return Number of resistors needed
 */
int e_resistance(float orig_resistance,
                 float* res_array) {

    float e12NormValues[] = {0, 1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2};
    float remainingResistance = orig_resistance;
    int e12NormArrayLength = sizeof(e12NormValues) / sizeof(e12NormValues[0]);
    int sizeOfAllocatedResistorArray = sizeof(res_array) / sizeof(res_array[0]);
    int numberOfUsedResistors = 0; // Initiated to 0 and only changed if needed
    float *e12UpTo1000Array = NULL;
    int e12UpTo1000ArrayLength = e12NormArrayLength * 3;

    //Allocate memory for array with all values
    e12UpTo1000Array = (float *) malloc(e12UpTo1000ArrayLength * sizeof(float));

    //Fill array with values
    fillAllResistanceValues(e12NormValues, e12NormArrayLength, e12UpTo1000Array, e12UpTo1000ArrayLength);

    calculateBestFit(orig_resistance, e12UpTo1000Array, e12UpTo1000ArrayLength, res_array);

    free(e12UpTo1000Array);

    for (int i = 0; i <= sizeOfAllocatedResistorArray; i++) {
        if (res_array[i] > 0) {
            numberOfUsedResistors++;
        }
    }

    return numberOfUsedResistors;
}
