/*
 * tLowPass.c
 *
 *  Created on: Nov 10, 2017
 *      Author: root
 */

/* Includes ------------------------------------------------------------------*/
#include "tLowPass.h"

double y0 = 0.0;
double k = 0.4;


double dLP(double e, double h){
	double y1 = y0 + k*h*(e -y0);
	y0 = y1;
	return y1;
}

