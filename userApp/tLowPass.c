/*
 * tLowPass.c
 *
 *  Created on: Nov 10, 2017
 *      Author: root
 */
// Low pass filter to smooth the error signal e
/* Includes ------------------------------------------------------------------*/
#include "tLowPass.h"

double y0 = 0.0;
double k = 4e0;
// h is the time step of the forward - Euler approximation
// Tf = 1/k
// P_lowpass = 1/(Tf*s+1)

double dLP(double e, double dt){
	double y1 = y0 + k*dt*(e -y0);
	y0 = y1;
	return y1;
}

