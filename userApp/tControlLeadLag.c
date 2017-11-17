/*
 * tControlLeadLag.c
 *
 *  Created on: Nov 16, 2017
 *      Author: clruch
 */

#include <math.h>

double kLL = 0.00001;
double pLL = -6.0;
double zLL = -1.7;

double xLLold = 0.0;
double eold = 0.0;

double dLeadLag(double e, double dt) {

	double xLL = (pLL*xLLold + eold)*dt;
	double uLL = (kLL*(pLL-zLL))*xLL + kLL*e;

	xLLold = xLL;
	eold = e;

	return uLL;

}

