#include "recoursemodel.h"

/*
 * Create the lambda part of the robust contraint
 */ 
IloNumArray RecourseModel::createLambdaConstraint()
{
    IloNumArray lambdaExprVals{d_env, d_params.nbScenarios};

    IloNumArray phi = IloNumArray{d_env, 3 * d_params.nbSurgeries};
    for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
    {
        // First constraint is simply sum to 1
        for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
            phi[surgery] = 1;
        
        // Second constraint is the mean 
        for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
            phi[d_params.nbSurgeries + surgery] = d_durationSample[scen][surgery];
        
        // Third constraint is the second moment 
        for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
            phi[2 * d_params.nbSurgeries + surgery] = pow(d_durationSample[scen][surgery] - d_params.mu, 2);

        lambdaExprVals[scen] = IloScalProd(phi, d_lambdaVals);
    }

    return lambdaExprVals;
}