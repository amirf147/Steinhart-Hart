/*
 * File:		steinhartHart.c
 * Author:		Amir Farhadi
 * Description:		Use the Steinhart-Hart equation to change the resistance to Celsius 
 *                      when given an ADC value.
 */

#include <stdio.h>
#include <math.h>
#include "./calculations/calculateABC.h"
#include "./calculations/adcToResist.h"
#include "./calculations/sHformula.h"

int main () {

	// We need to use 3 values from the LUT to calculate the estimated curve fit
	// r1 = resistance at the lowest temperature (T1 = 1.4 degCelsius)
	// r2 = resistance at a middle temperature (T2 = 36.1 degCelsius)
	// r3 = resistance at the highes temperature (T3 = 139.5 degCelsius)
	// Then we get the coefficients and use them in the equation
	
	float adcList[32] = {250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500,
			   525, 550, 575, 600, 625, 650, 675, 700, 725, 750, 775,
			   784, 825, 850, 875, 900, 925, 937, 950, 975, 1000};
	
	float tempList[32]; // will hold the corresponding temperatures for the adc values

	float adc1 = 250; // ADC value for a temperature of 1.4 degrees celsius
	float adc2 = 625; // ADC value for a temperature of 36.1 degrees celsius
	float adc3 = 1000; // ADC value for a temperature of 139.5 degrees celsius

	float r1, r2, r3; // placeholders for the NTC resistance equivalent of the ADC values

	float l1, l2, l3; //placeholders for log of resistances

	float Y1, Y2, Y3; //holder for inverse of temperatures

	float y2, y3; // variables used in B and C coefficient formula

	float coefficientA, coefficientB, coefficientC; // coefficients A, B and C

	float resistanceNTC; // used to hold resistance of NTC calculated from adci

	int counter = 0;

	do {

	//Get resistances of three key values 
	r1 = adcToResistance(adc1); 
	r2 = adcToResistance(adc2);
	r3 = adcToResistance(adc3);

	// get logs of resistances
	l1 = logf(r1);
	l2 = logf(r2);
	l3 = logf(r3);

	// inverse of temperatures after converting to Kelvin
	Y1 = 1 /(1.4 + 273.15); // lowest temp
	Y2 = 1 / (273.15 + 36.1); // middle temp
	Y3 = 1 / (273.15 + 139.5); // highest temp

	y2 = (Y2 - Y1) / (l2 - l1); // formula for y2
	y3 = (Y3 - Y1) / (l3 - l1); //formula for y3

	//calculate the coefficients
	coefficientC = getC(l1, l2, l3, y2, y3);
	coefficientB = getB(y2, coefficientC, l1, l2);
	coefficientA = getA(Y1, coefficientB, l1, coefficientC);	

	for (int i = 0; i < 32; i++) {

		resistanceNTC = adcToResistance(adcList[i]); // get resistance of NTC from adc value

		// put temperatures into list
		tempList[i] = getTemp(coefficientA, coefficientB, coefficientC, resistanceNTC);
		
		printf("\nADC %.2f = %.2f degrees", adcList[i], tempList[i]);

	}

	printf("\n\n");

	counter += 1;
	
	}
	while(counter < 1); //program only runs once

	return 0;
}
