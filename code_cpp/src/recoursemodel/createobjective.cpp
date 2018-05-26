#include "recoursemodel.ih"

void RecourseModel::createObjective()
{
	IloExpr newObjectiveExpr{d_env};

	// For each scenario we add the overtime
	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
		newObjectiveExpr += (d_params.cv * IloSum(d_o[scen]) + d_params.eps1 * d_uMinus[scen] + d_params.eps2 * d_uPlus[scen]) * (1.0 / d_params.nbScenarios);

	d_objective = IloMinimize(d_env, newObjectiveExpr);
	newObjectiveExpr.end();
	d_model.add(d_objective);
}