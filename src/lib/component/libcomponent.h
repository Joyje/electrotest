/**
 * @file libcomponent.h
 * @brief Header file for component choices
 *
 * @author Charlotte Hagborg
 * @date 17 Sep 2018
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#define LIBCOMPONENT_NUMBER_OF_RESISTORS 3 // Note! If this is changed you need to also change in calculateBestFit in the c-file

int e_resistance(float orig_resistance,
                 float* res_array);
#endif //COMPONENT_H
