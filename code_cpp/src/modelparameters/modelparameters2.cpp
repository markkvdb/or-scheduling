#include "modelparameters.ih"

/*
 * Set model parameters using a file.
 */

ModelParameters::ModelParameters(string parametersInput)
{
	istringstream iss(parametersInput);
    string subs;

    // Parameters for the problem
    iss >> subs;
	nbORs 			= stoi(subs);
	iss >> subs;
	nbSurgeries 	= stoi(subs);

	// Costs
	iss >> subs;
	cf 				= stof(subs);
	iss >> subs;
	cv 				= stof(subs);
	iss >> subs;
	nbHours 		= stof(subs);

	// Uncertainty
	iss >> subs;
	meanDuration 	= stof(subs);
	iss >> subs;
	stdDuration 	= stof(subs);

	iss >> subs;
	mu 				= stof(subs);
	iss >> subs;
	sig 			= stof(subs);

	iss >> subs;
	eps1 			= stof(subs);
	iss >> subs;
	eps2 			= stof(subs);

	// Number of scenarios for the problem
	iss >> subs;
	nbScenarios 	= stoi(subs);
	iss >> subs;
	seed 			= stoi(subs);

	cout << parametersInput << '\n';
	cout << nbORs << ' ' << nbSurgeries << ' ' << cf << ' ' << cv << ' ' << nbHours << ' ' << meanDuration << ' ' << stdDuration << ' ' << eps1 << ' ' << eps2 << ' ' << nbScenarios << ' ' << seed << '\n';
}