/*
 * File:		steinhartHart.c
 * Author:		Amir Farhadi
 * Description:		Use the Steinhart-Hart equation to change the resistance to Celsius
 * 				when given an ADC value.
 */

#include <stdio.h>
#include <math.h> //remember to compile with option -lm
#include "calculateABC.h"

float adcToResistance(float adc) {

	/* calculates the resistance of the NTC Thermistor when given
	 * the ADC voltage reading 
	 */


	float resistor = 1000; // resistor that connects to NTC thermistor
	float ntc; // used for resistance of NTC thermistor
	
	ntc = resistor * ((1023/adc) - 1); // formula to find resistance of NTC

	return ntc;
}

/*float getC(float l1, float l2, float l3, float y2, float y3) {

	// Calculates the coefficient C in the Steinhart-Hart equation

	float coefficientC;

	coefficientC = ((y3 - y2)/(l3 - l2)) * (1 / (l1 + l2 + l3)); // formula for C
	
	return coefficientC;

}

float getB(float y2, float coefficientC, float l1, float l2) {

	// Calculates the coefficient B in the Steinhart-Hart equation

	float coefficientB;

	coefficientB = y2 - (coefficientC * ((l1*l1) + (l1*l2) + (l2*l2))); // formula for B

	return coefficientB;

}

float getA(float Y1, float coefficientB, float l1, float coefficientC) {

	float coefficientA;

	coefficientA = Y1 - ((coefficientB + ((l1*l1) * coefficientC)) * l1);

	return coefficientA;

}
*/

float getTemp(float coefficientA, float coefficientB, float coefficientC, float resistanceNTC) {

	float temperature, logNTC;

	logNTC = logf(resistanceNTC);

	temperature = 1 / (coefficientA + (coefficientB * log(resistanceNTC)) +
			(coefficientC * (logNTC * logNTC * logNTC))); //Steinhart-Hart

	return temperature - 273.15; 

}

int main () {

	// We need to use 3 values from the LUT to calculate the estimated curve fit
	// R1 = resistance at the lowest temperature (T1 = 1.4 degCelsius)
	// R2 = resistance at a middle temperature (T2 = 36.1 degCelsius)
	// R3 = resistance at the highes temperature (T3 = 139.5 degCelsius)
	// Then we get the coefficients and use them in the equation
	
	float adcList[32] = {250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500,
			   525, 550, 575, 600, 625, 650, 675, 700, 725, 750, 775,
			   784, 825, 850, 875, 900, 925, 937, 950, 975, 1000};
	
	float tempList[32];

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

	r1 = adcToResistance(adc1); //get resistance of NTC thermistor
	r2 = adcToResistance(adc2);
	r3 = adcToResistance(adc3);

	l1 = logf(r1);// get logs of resistances
	l2 = logf(r2);
	l3 = logf(r3);

	Y1 = 1 /(1.4 + 273.15); // lowest temp
	Y2 = 1 / (273.15 + 36.1); // middle temp
	Y3 = 1 / (273.15 + 139.5); // highest temp

	y2 = (Y2 - Y1) / (l2 - l1); // formula for y2
	y3 = (Y3 - Y1) / (l3 - l1); //formula for y3

	coefficientC = getC(l1, l2, l3, y2, y3); //calculate the coefficients
	coefficientB = getB(y2, coefficientC, l1, l2);
	coefficientA = getA(Y1, coefficientB, l1, coefficientC);	

	for (int i = 0; i < 32; i++) {

		resistanceNTC = adcToResistance(adcList[i]); // get resistance of NTC from adc value
		tempList[i] = getTemp(coefficientA, coefficientB, coefficientC, resistanceNTC);
		printf("\nADC %.2f = %.2f degrees", adcList[i], tempList[i]);

	}

	printf("\n\n");

	counter += 1;
	
	}
	while(counter < 1); //program only runs once

	return 0;
}
