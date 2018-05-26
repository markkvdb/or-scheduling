#include "modelparameters.ih"

/*
 * Model parameters of the problem.
 */

ModelParameters::ModelParameters()
{
	// Parameters for the problem
	nbORs 			= 10;
	nbSurgeries 	= nbORs;

	// Costs
	cf 				= 1;
	cv 				= 0.3;
	nbHours 		= 8;

	// Uncertainty
	meanDuration 	= 200;
	stdDuration 	= pow(12.12, 2);

	mu 				= log(pow(meanDuration, 2) / sqrt(stdDuration + pow(meanDuration, 2)));
	sig 			= sqrt(log(stdDuration / pow(meanDuration, 2) + 1));

	eps1 			= 3;
	eps2 			= 0.1;

	// Number of scenarios for the problem
	nbScenarios 	= 200;
	seed 			= 1;
}