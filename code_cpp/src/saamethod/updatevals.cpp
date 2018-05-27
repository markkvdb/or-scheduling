#include "saamethod.ih"

void SAAMethod::updateVals()
{
	// Update first-stage variable values
    d_cplex.getValues(d_xVals, d_x);
    for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
    	d_cplex.getValues(d_yVals[OR], d_y[OR]);
    d_lVal = d_cplex.getValue(d_l);

    // Update second-stage variable values
    for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
        d_cplex.getValues(d_oVals[scen], d_o[scen]);
    d_cplex.getValues(d_uPlusVals, d_uPlus);
    d_cplex.getValues(d_uMinusVals, d_uMinus);
}
