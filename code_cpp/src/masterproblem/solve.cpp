#include "masterproblem.ih"

/*
 * Solve the MasterProblem using the CPLEX algorithms and 
 * update the numeric values of the first-stage solution.
 */

void MasterProblem::solve()
{
    // Add the model to the algorithm and solve it
    d_cplex.solve();

    // Update values of variables and objective 
    updateVals();
}