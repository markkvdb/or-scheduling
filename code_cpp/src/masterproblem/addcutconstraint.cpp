#include "masterproblem.ih"

/*
 * Member to add cut constraint to the master problem. 
 * This is used for the L-shaped algorithm.
 */

void MasterProblem::addCutConstraint(IloNum QApprox, IloNumArray u)
{
	IloExpr cut{d_env};

	for (IloNum idx = 0; idx < (d_params.nbORs + d_params.nbORs * d_params.nbSurgeries + 1); ++idx)
	  cut += u[idx] * (d_allX[idx] - d_allXVals[idx]);
	
	cout << QApprox + cut << '\n';

	d_model.add(d_eta >= QApprox + cut);
}