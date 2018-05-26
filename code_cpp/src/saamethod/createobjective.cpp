#include "saamethod.ih"

/*
 * Extend the objective of the MasterProblem by introducing the 
 * overtime cost and the cost related to the robust formulation.
 */

void SAAMethod::createObjective()
{
	// First remove old objective
	IloObjective oldObjective = d_masterProblem.getObjective();
	d_completeModel.remove(oldObjective);

	// Create new objective
	IloExpr newObjectiveExpr{d_env};

	// First add the first-stage variable part
	newObjectiveExpr = d_params.cf * IloSum(d_x);

	// For each scenario we add the overtime
	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
		newObjectiveExpr += (d_params.cv * IloSum(d_o[scen]) + d_params.eps1 * d_uMinus[scen] + d_params.eps2 * d_uPlus[scen]) * (1.0 / d_params.nbScenarios);

	d_objective = IloMinimize(d_env, newObjectiveExpr);
	d_completeModel.add(d_objective);
}