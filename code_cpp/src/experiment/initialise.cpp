#include "experiment.ih"

/*
 * Initialise the SAAMethod class without bender decomposition.
 */

void Experiment::initialise() 
{
	d_runTime = 0;

	// Initialise the SAA method
	d_SAAMethod.initialise(IloFalse);
}