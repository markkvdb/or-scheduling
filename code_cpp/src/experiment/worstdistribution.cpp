#include "experiment.ih"

/*
 * Return the worst-case distribution for our problem
 * 
 * TODO consider individual surgeries. Not the sum.
 */
void Experiment::worstDistribution(IloNumArray2 durationSample)
{
    // Obtain first-stage variable values
    IloNumArray xVals = d_SAAMethod.getXVals();
    IloNumArray2 yVals = d_SAAMethod.getYVals();
    IloNumArray lambdaVals = d_SAAMethod.getLVals();

    // Solve each subproblem and store objective value
    IloNumArray objValues_MILP{d_env, d_params.nbScenarios};
    IloNumArray objValues_approx{d_env, d_params.nbScenarios};

    for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
    {
        // Obtain value of MILP
        SubProblem subProblem{d_env, durationSample[scen], d_params, IloTrue, xVals, yVals, lambdaVals};
        subProblem.solve();
        objValues_MILP[scen] = subProblem.getObjectiveVal();

        // Obtain value of convex approximation
        SubProblem subProblem2{d_env, durationSample[scen], d_params, IloFalse, xVals, yVals, lambdaVals};
        subProblem2.solve();
        objValues_approx[scen] = subProblem2.getObjectiveVal();
    }

    // Find the worst-case distribution
    worstDistributionLP(objValues_MILP, "MILP");
    worstDistributionLP(objValues_approx, "Approx");
}