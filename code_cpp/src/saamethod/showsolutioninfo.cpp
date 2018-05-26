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

	IloBool integerModel = IloFalse;

	// Assign all values
	/*
 	- ORs open
 	- Surgery assignment
 	- First-stage costs
 	- Second-stage costs
 	- Cuts added
	*/
    IloNumArray xVals(d_env);
    d_cplex.getValues(xVals, d_x);
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
		oss << xVals[OR] << ' ';

	IloNumArray2 yVals(d_env, d_params.nbORs);
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
	{
		IloNumArray yValsTemp(d_env);
    	d_cplex.getValues(yValsTemp, d_y[OR]);
    	yVals[OR] = yValsTemp;
		for (IloInt surgery = 0; surgery < d_params.nbSurgeries; ++surgery)
			oss << yVals[OR][surgery] << ' ';
	}

	IloNum lVal = d_cplex.getValue(d_l);
	oss << lVal << ' ';

	// Second-stage costs
	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
	{
		IloNumArray oVals(d_env);
		d_cplex.getValues(oVals, d_o[scen]);
		IloNum uPlus = d_cplex.getValue(d_uPlus[scen]);
		IloNum uMinus = d_cplex.getValue(d_uMinus[scen]);

		for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
			oss << oVals[OR] << ' ';
		oss << uPlus << ' ' << uMinus << ' ';
	}

	// First-stage cost is just the sum of all the x vals.
	oss << IloSum(xVals) << ' ';

	// Second-stage costs can be found by solving the real MILP for many scenarios, e.g,
	RecourseModel recourseCosts(d_env, d_params, integerModel, 10);
	recourseCosts.initialise(xVals, yVals, lVal);
	recourseCosts.solve();
	recourseCosts.showMinMaxDuals();
	IloNum secondStageCosts = recourseCosts.getObjVal();
	oss << secondStageCosts << ' ';

	// Get cuts added
	oss << d_iter;

	outputLine = oss.str();

	return outputLine;
}