/* 
 * File:	adcToResist.c
 * Author:	Amir Farhadi
 * Description:	Gets resistance from ADC value
 */

#include <stdio.h>
#include <math.h>
#include "adcToResist.h"

float adcToResistance(float adc) {

        /* calculates the resistance of the NTC Thermistor when given
         * the ADC voltage reading */


        float resistor = 1000; // Put in value of resistor that connects to your NTC thermistor
        float ntc; // used for resistance of NTC thermistor

        ntc = resistor * ((1023/adc) - 1); // formula to find resistance of NTC

        return ntc;
}
