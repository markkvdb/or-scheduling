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
    IloNum lVal = d_SAAMethod.getLVal();

    // Solve each subproblem and store objective value
    vector<IloNum> objValues;

    for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
    {
        SubProblem subProblem{d_env, durationSample[scen], d_params, IloTrue, xVals, yVals, lVal};
        subProblem.solve();
        objValues.push_back(subProblem.getObjectiveVal());
    }

    // Solve the 
}