/*
 * tControlPID.c
 *
 *  Created on: Nov 10, 2017
 *      Author: jzilly
 */
#include <stdio.h>
#include "tLowPass.h"

// IMPORTANT: Pick which task to execute
uint16_t uiTaskCase = -1; // Choose either 1, 2, or 3
						  // any other number will use default case

// Default parameters - tune the parameters further below in the dPID function
double kp = 1.0e-7;
double kI = 0;
double kd = 0;
double k_ARW = 0.0;

// setpoint weights, tune these for tasks 2/3
double a = 1.0;
double b = 1.0;
double c = 1.0;

double e_prev = 0.0;
double ef_prev = 0.0;
double u_prev = 0.0;
double ef_2prev = 0.0;

double u_max = 0.035; // Tune empirically

double above_thres_u = 0.0;
double ei = 0.0; // integral error
double e = 0.0; // error
double ef = 0.0; // low-pass-filtered error


double dPID(double r, double y, double dt) {

	double u;
	double delta_u;
	double delta_uP;
	double delta_uI;
	double delta_uD;

	switch (uiTaskCase) {
	// Task 1: Trajectory following
	// Tune the controller parameters
	case 1 : {
		kp = 1.0e-8;
		kI = 0.0;
		kd = 0.0;
		break;}
	// Task 2: Step response
	// Tune the controller parameters and implement setpoint weighting,
	// Tune a,b,c at the top of the file
	case 2 : {
		kp = 1.0e-7;
		kI = 0.0;
		kd = 0.0;
		break; }
	// Task 3: ARW
	// Tune the controller parameters, implement ARW scheme, tune k_ARW and u_max,
	// setpoint weighting, tune a,b,c
	case 3 : {
		kp = 1.0e-7;
		kI = 0.0;
		kd = 0.0;
		k_ARW = 0.0; // without ARW -> k_ARW = 0;
		break; }
	// Default is controller off - change the task variable above to select a different case
	default : {
		kp = 0.0;
		kI = 0.0;
		kd = 0.0;
		k_ARW = 0.0;
		break; }
	}

	// ERROR SIGNAL, Error calculation
	e = r - y;

	// Low-pass necessary for causal D-part
	ef = dLP(r - y, dt);

	// calculate PID parts
	// P - part
	delta_uP = kp * (e - e_prev);

	// I - part
	ei = e;
	ei = kI*ei;
	delta_uI = dt * ei;

	// D - part
	delta_uD = kd / dt * (ef - 2 * ef_prev + ef_2prev);

	// calculate PID output value
	delta_u = delta_uP + delta_uI + delta_uD;
	u = u_prev + delta_u;


	// update values
	ef_2prev = ef_prev;
	ef_prev = ef;
	e_prev = e;

	u_prev = u;

	//return
	return u;

}
