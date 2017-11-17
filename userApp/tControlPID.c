/*
 * tControlPID.c
 *
 *  Created on: Nov 10, 2017
 *      Author: root
 */


double kp = 0.00001;
double Ti = 1000;
double Td = 0.0;

double e_prev = 0.0;
double ef_prev = 0.0;
double u_prev = 0.0;
double ef_2prev = 0.0;

double dPID(double e, double ef, double dt) {

	double u;
	double delta_u;
	double delta_uP;
	double delta_uI;
	double delta_uD;


	// calculate PID parts
	delta_uP = kp * (e - e_prev);
	delta_uI = kp * dt / Ti * e;
	delta_uD = kp * Td / dt * (ef - 2 * ef_prev + ef_2prev);

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
