/*
 * File:	calculateABC.c
 * Author: 	Amir Farhadi
 * Description:	Contains the formulas for coefficients A, B and C
 */

#include <math.h>
#include <stdio.h>
#include "calculateABC.h"

float getA(float Y1, float coefficientB, float l1, float coefficientC) {

        float coefficientA;

        coefficientA = Y1 - ((coefficientB + ((l1*l1) * coefficientC)) * l1);

        return coefficientA;

}

float getB(float y2, float coefficientC, float l1, float l2) {

        // Calculates the coefficient B in the Steinhart-Hart equation

        float coefficientB;

        coefficientB = y2 - (coefficientC * ((l1*l1) + (l1*l2) + (l2*l2))); // formula for B

        return coefficientB;

}

float getC(float l1, float l2, float l3, float y2, float y3) {

        // Calculates the coefficient C in the Steinhart-Hart equation

        float coefficientC;

        coefficientC = ((y3 - y2)/(l3 - l2)) * (1 / (l1 + l2 + l3)); // formula for C

        return coefficientC;

}
