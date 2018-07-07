#include "subproblem.ih"

IloInt SubProblem::createLambdaConstraint()
{
    // phi
    IloNumArray phi{d_env, 3 * d_params.nbSurgeries};

    // First constraint is simply sum to 1
    for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
        phi[surgery] = 1;
    
    // Second constraint is the mean 
    for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
        phi[d_params.nbSurgeries + surgery] = d_durations[surgery];
    
    // Third constraint is the second moment 
    for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
        phi[2 * d_params.nbSurgeries + surgery] = pow(d_durations[surgery] - d_params.mu, 2);

    return (IloScalProd(phi, d_lambdaVals));
}