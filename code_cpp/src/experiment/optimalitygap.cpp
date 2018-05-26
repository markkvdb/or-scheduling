#include "experiment.ih"

/* 
 * Calculate the optimality gap by means of the Multiple 
 * Replication Procedure. 
 * 
 * TODO Save as data member: mean, standard deviation and number of reps
 */

void Experiment::optimalityGap(IloNum alpha, IloInt nbSamples, IloInt nbReps)
{
	array<IloNum, nbReps> gapEstimates{};
	IloInt seed = 2513102;

	// Obtain the first-stage solution
    xVals;
    yVals;
    lVal;

	for (IloInt rep = 0; rep < nbReps; ++rep)
	{
        // Define model parameters using new seed
        ModelParameters paramsRep = d_params;
        paramsRep.seed = seed;

		// 1. Solve the MILP for sample size nbSamples (actual solve)
        SAAMethod milpModel{d_env, paramsRep, IloTrue};
        milpModel.solve();
        IloNum optimalMILP = milpModel.getObjectiveVal();

		// 2. Evaluate the recourse cost for the second-stage MILP
        RecourseModel recourseModel{d_env, paramsRep, IloTrue, nbSamples, xVals, yVals, lVal};
        IloNum actualMILP = IloSum(xVals) + recourseModel.getObjVal();

		// 3. Calculate the gap
        gapEstimates[rep] = optimalMILP - actualMILP;

        ++seedBase;
	}

	// Get mean and standard deviation of gap estimates
	d_optGapMean = accumulate(gapEstimates.begin(), gapEstimates.end(), 0.0)/gapEstimates.size(); 
	IloNum accum = 0.0;
	for_each(begin(gapEstimates), end(gapEstimates), [&](IloNum const d) {
    	accum += (d - meanGap) * (d - meanGap);
    });
	d_optGapVar = accum / (gapEstimates.size()-1);
}