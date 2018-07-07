#include "saamethod.ih"

/*
 * Second-stage constraints. First one is related to the overtime 
 * constraints. Second set of constraints correspond to the robust
 * part. 
 * 
 * TODO Add support for multi-dimensional lambda vector.
 */

void SAAMethod::createConstraints()
{
    IloArray<IloExpr> lambdaExprs = createLambdaConstraint();
    for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
    {
        // Add constraints related to the minimum overtime
        for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
        {
            if (d_integer) 
                d_completeModel.add(60 * d_o[scen][OR] >= IloScalProd(d_durationSample[scen], d_y[OR]) - (60 * d_params.nbHours * d_x[OR]));
            else 
                d_completeModel.add(60 * d_o[scen][OR] >= IloScalProd(d_durationSample[scen], d_y[OR]) - (60 * d_params.nbHours * d_x[OR]) + 30);
        }
        d_completeModel.add(d_uPlus[scen] - d_uMinus[scen] == d_params.cf * IloSum(d_x) + d_params.cv * IloSum(d_o[scen]) - lambdaExprs[scen]);
    }
}