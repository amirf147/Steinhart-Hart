/* 
 * File:	calculateABC.h
 * Author:	Amir Farhadi
 * Description: Contains the function prototypes of calculateABC.c
 */

#ifndef CALCULATEABC_H
#define CALCULATEABC_H

// function prototypes

float getA(float Y1, float coefficientB, float l1, float coefficientC);
float getB(float y2, float coefficientC, float l1, float l2);
float getC(float l1, float l2, float l3, float y2, float y3);

#endif /* CALCULATEABC_H */

