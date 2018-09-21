/**
 * @file libcomponent.c
 * @brief Source file for component choices
 *
 * @author Charlotte Hagborg
 * @date 21 Sep 2018
 */

#include "libcomponent.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>

#define NUMBER_OF_RESISTORS 3 // Note! If this is changed you need to also change in calculateBestFit

/**
 * Calculate resistors that can be used in serie to achieve a total resistance
 * @param wantedSum[in] The resistance in ohm that we should achieve
 * @param e12Array[in] An array with the all possible choices of resistors
 * @param numberOfE12Values[in] Number of resisstors to choose between
 * @param resultArray[out] An array of the choosen resistors
 */
void calculateBestFit(float wantedSum,
                      float *e12Array,
                      int numberOfE12Values,
                      float *resultArray) {

    float rest = wantedSum; //Used in iteration to save the currently lowest remaining value after having substracting
                            //the wanted sum with three resistor values
    float tmpRest = wantedSum;  //The rest reamaining after having selecting three resistor values

    int e12ValueIndexMax = numberOfE12Values - 1;   //The max index value in E12 array is one less than length of array

    //Loop over all possible values staring with higest value assuming that it is better to use less resistors with
    //higher resistance.
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


/**
 * Fills the array of possible resistor values based on the normalised values
 * @param e12NormValues[in] Array with the normalised values
 * @param e12NormArrayLength[in] Length of array with normalised values
 * @param maxE12Factor[in] How many multiples (*10) of the e12NormArray that is supported
 * @param fullE12Array[out] All possible resistor values base on E12 table and the maxE12Factor
 */
void fillAllResistanceValues(float *e12NormValues,
                             int e12NormArrayLength,
                             int maxE12Factor,
                             float *fullE12Array) {

    int tmpFactor = 1;  //Factor to use to multiply the E12 normailised  array values with, starting at 1
    int index = 1;  //Index in fullE12Array

    fullE12Array[0] = 0; //Include 0 in array to use that for checking if resistors are used at all or not
    for (int i = 0; i < maxE12Factor; i++) {
        for (int j = 0; j < e12NormArrayLength; j++) {
            fullE12Array[index] = e12NormValues[j] * tmpFactor;
            index++;
        }
        tmpFactor = tmpFactor * 10;
    }
}


/**
 * Validates if the orig_resistance is within expected range
 * @param orig_resistance[in} Value to validate
 * @param e12MaxFactorArray[in] Array with all possible values
 * @param e12UpTo1000ArrayLength[in] Length of array with all possible values
 * @return -1 if origResistance is NOT within expected values otherwise 1
 */
int checkValidOriginResistance(float orig_resistance,
                               float *e12MaxFactorArray,
                               int e12UpTo1000ArrayLength) {

    int invalidInput = -1;

    if (orig_resistance < 0) {
        return invalidInput; //Too small
    }

    if (orig_resistance > (e12MaxFactorArray[e12UpTo1000ArrayLength-1] * NUMBER_OF_RESISTORS)) {
        return invalidInput; //Too large
    }

    return 1;
}


/**
 * Calculates which three serial connected resistances that can be used for the "orig_resistance".
 * @param[in] orig_resistance The resistance that needs resistor values
 * @param[out] res_array The array of maximum three resistors. 0 should be used if not needed
 * @return Number of resistors needed
 */
int e_resistance(float orig_resistance,
                 float *res_array) {

    float e12NormValues[] = {1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2};
    int e12NormArrayLength = sizeof(e12NormValues) / sizeof(e12NormValues[0]);
    int numberOfUsedResistors = 0; // Initiated to 0 and only changed if needed
    float *e12MaxFactorArray = NULL;
    int maxE12Factor = 3;
    int validInput = 0;     //Validates if orig_resistance is valid or not

    //First memset res_array to 0 and only change if valid input
    memset(res_array, 0, sizeof(res_array));

    //Programme supports e12NormValues, 10*e12NormValues, 100 * e12NormValues. +1 to be able to have 0 in array as well
    int e12UpTo1000ArrayLength = e12NormArrayLength * maxE12Factor + 1;

    //Allocate memory for array with all possible E12 values
    e12MaxFactorArray = (float *) malloc(e12UpTo1000ArrayLength * sizeof(float));

    //Fill array with values
    fillAllResistanceValues(e12NormValues, e12NormArrayLength, maxE12Factor, e12MaxFactorArray);

    //Chaeck valid inparameter orig_Resistance
    validInput = checkValidOriginResistance(orig_resistance, e12MaxFactorArray, e12UpTo1000ArrayLength);

    //If not valid input return early wth zero resistors
    if (validInput < 0) {
        return -1;
    }

    //Calculate suggested resistors
    calculateBestFit(orig_resistance, e12MaxFactorArray, e12UpTo1000ArrayLength, res_array);

    //If resistor value is 0 no resistor is needed
    for (int i = 0; i < NUMBER_OF_RESISTORS; i++) {
        if (res_array[i] > 0) {
            numberOfUsedResistors++;
        }
    }

    free(e12MaxFactorArray);

    return numberOfUsedResistors;
}
