/*
 * File:		sHFormula.c
 * Author:		Amir Farhadi
 * Description:		The Steinhart-Hart Forumla is used here
 *
 */

#include <stdio.h>
#include <math.h>
#include "sHformula.h"

float getTemp(float coefficientA, float coefficientB, float coefficientC, float resistanceNTC) {
	
	/* This is where we input the resistance of the thermistor into the Steinhart-Hart
	 * equation */

	float temperature, logNTC;

	logNTC = logf(resistanceNTC);

	temperature = 1 / (coefficientA + (coefficientB * logNTC) +
			(coefficientC * (logNTC * logNTC * logNTC))); //Steinhart-Hart

	return temperature - 273.15; //return celsius

}

