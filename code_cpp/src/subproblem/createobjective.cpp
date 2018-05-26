#include "subproblem.ih"

void SubProblem::createObjective()
{
	d_objective = d_params.cv * IloSum(d_o) + d_params.eps1 * d_uMinus + d_params.eps2 * d_uPlus;
	d_model.add(IloMinimize(d_env, d_objective));
}