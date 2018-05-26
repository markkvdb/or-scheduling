#include "masterproblem.ih"

/*
 * Save the objective and variable values in
 * the corresponding datamembers.
 */

void MasterProblem::updateVals()
{
	// Update objective 
	d_objectiveVal = d_cplex.getObjValue();

	// Update variable values
    d_cplex.getValues(d_xVals, d_x);
    for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
    	d_cplex.getValues(d_yVals[OR], d_y[OR]);
    d_lVal = d_cplex.getValue(d_l);
    d_etaVal = d_cplex.getValue(d_eta);
    d_cplex.getValues(d_allXVals, d_allX); 
}