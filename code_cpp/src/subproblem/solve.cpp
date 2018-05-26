#include "subproblem.ih"

void SubProblem::solve()
{
	d_cplex.solve();

	// Update the dual variables
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
		d_dualVariables[OR] = d_cplex.getDual(d_overtimeConstraints[OR]);

	d_dualVariables[d_params.nbORs] = d_cplex.getDual(d_minMaxConstraint);

	// Set new objective
	d_objectiveVal = d_cplex.getObjValue();
}