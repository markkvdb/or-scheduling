#include "experiment.ih"

/*
 * Specify the header of the output of the experiment. 
 * 
 * TODO add MRP functionality
 */

string Experiment::createExperimentHeader()
{
	ostringstream oss;

	oss << "id nbORs cf cv meanDuration stdDuration eps1 eps2 nbScenarios seed ";

	// Add first-stage variable names
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
		oss << "x_" << to_string(OR+1) << ' ';

	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
		for (IloInt surgery = 0; surgery < d_params.nbSurgeries; ++surgery)
			oss << "y_" << to_string(surgery+1) << "_" << to_string(OR+1) << ' ';

	oss << "lambda ";

		// Second-stage costs
	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
	{
		for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
			oss << "o_" << to_string(OR+1) << '_' << to_string(scen+1) << ' ';
		oss << "u+_" << to_string(scen+1) << " u-_" << to_string(scen+1) << ' ';
	}

	// Other info
	oss << "FSC SSC iterations ";

	// Time data
	oss << "runTimeSaa";

	// MRP data
	oss << "optGapMean optGapVar optGapReps";

	return oss.str();
}
