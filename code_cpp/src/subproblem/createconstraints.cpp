#include "subproblem.ih"

void SubProblem::createConstraints()
{
	// Add constraints related to the minimum overtime
	d_overtimeConstraints = IloRangeArray{d_env, d_params.nbORs};
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
	{
		if (d_integer)
			d_overtimeConstraints[OR] = IloRange{d_env, -60 * d_o[OR], 0};
		else
			d_overtimeConstraints[OR] = IloRange{d_env, -60 * d_o[OR], -30};
		d_model.add(d_overtimeConstraints[OR]);
	}
	// Add minmax constraint.
	d_minMaxConstraint = IloRange{d_env, 0, d_uPlus - d_uMinus - d_params.cv * IloSum(d_o), 0};
	d_model.add(d_minMaxConstraint);
}