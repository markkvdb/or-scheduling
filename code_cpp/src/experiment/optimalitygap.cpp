#include "experiment.ih"

/* 
 * Calculate the optimality gap by means of the Multiple 
 * Replication Procedure. 
 */

void Experiment::optimalityGap()
{
	vector<IloNum> gapEstimates{};
	IloInt seed = 2513102;

	// Obtain the first-stage solution
    IloNumArray xVals = d_SAAMethod.getXVals();
    IloNumArray2 yVals = d_SAAMethod.getYVals();
    IloNumArray lambdaVals = d_SAAMethod.getLVals();

	for (IloInt rep = 0; rep < d_optGapReps; ++rep)
	{
        // Define model parameters using new seed
        ModelParameters paramsRep = d_params;
        paramsRep.seed = seed;
        paramsRep.nbScenarios = d_optGapSamples;

		// 2. Evaluate the recourse cost for the second-stage MILP
        RecourseModel recourseModel{d_env, paramsRep, IloTrue, d_optGapSamples, xVals, yVals, lambdaVals};
        recourseModel.solve();
        recourseModel.exportModel();
        IloNum actualMILP = IloSum(xVals) + recourseModel.getObjVal();

        // 1. Solve the MILP for sample size nbSamples (actual solve)
        SAAMethod milpModel{d_env, paramsRep, IloFalse};
        milpModel.exportModel();
        milpModel.solve();
        IloNum optimalMILP = milpModel.getObjectiveVal();

		// 3. Calculate the gap
        gapEstimates.push_back(optimalMILP - actualMILP);

        ++seed;
	}

	// Get mean and standard deviation of gap estimates
	d_optGapMean = accumulate(gapEstimates.begin(), gapEstimates.end(), 0.0)/gapEstimates.size(); 
	IloNum accum = 0.0;
	for_each(begin(gapEstimates), end(gapEstimates), [&](IloNum const d) {
    	accum += (d - d_optGapMean) * (d - d_optGapMean);
    });
	d_optGapVar = accum / (gapEstimates.size()-1);
}