#include "saamethod.ih"

/*
 * Output the values of the first- and second-stage variables.
 * Calculate the real recourse cost by solving the RecourseModel
 * with many scenarios.
 */

string SAAMethod::showSolutionInfo()
{
	string outputLine;
	ostringstream oss;

	// Assign all values
	/*
 	- ORs open
 	- Surgery assignment
 	- First-stage costs
 	- Second-stage costs
 	- Cuts added
	*/
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
		oss << d_xVals[OR] << ' ';

	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
		for (IloInt surgery = 0; surgery < d_params.nbSurgeries; ++surgery)
			oss << d_yVals[OR][surgery] << ' ';

	for (IloInt surgery = 0; surgery != (3 * d_params.nbSurgeries); ++surgery)
		oss << d_lambdaVals[surgery] << ' ';

	// Second-stage costs
	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
	{
		for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
			oss << d_oVals[scen][OR] << ' ';
		oss << d_uPlus[scen] << ' ' << d_uMinus[scen] << ' ';
	}

	// First-stage cost is just the sum of all the x vals.
	oss << IloSum(d_xVals) << ' ';

	// Second-stage costs can be found by solving the real MILP for many scenarios, e.g,
	RecourseModel recourseCosts(d_env, d_params, IloTrue, 1000, d_xVals, d_yVals, d_lambdaVals);
	recourseCosts.solve();
	IloNum secondStageCosts = recourseCosts.getObjVal();
	oss << secondStageCosts << ' ';

	// Get cuts added
	oss << d_iter;

	outputLine = oss.str();

	return outputLine;
}