#include "subproblem.ih"

/*
 * Update the constraints of the second-stage subproblem.
 */

void SubProblem::updateModel(IloNumArray xVals, IloNumArray2 yVals, IloNumArray lambdaVals)
{
	// Update the overtime constraints
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
	{
		if (d_integer)
			d_overtimeConstraints[OR].setUB(60 * d_params.nbHours * xVals[OR] - IloScalProd(d_durations, yVals[OR]));
		else
			d_overtimeConstraints[OR].setUB(60 * d_params.nbHours * xVals[OR] - IloScalProd(d_durations, yVals[OR]) - 30);
	}
	
	// Update current xvals
	d_xVals = xVals;
	d_yVals = yVals;
	d_lambdaVals = lambdaVals;

	// Change minimax constraint
	IloInt lVal = createLambdaConstraint();
	d_minMaxConstraint.setExpr(d_uPlus - d_uMinus - d_params.cf * IloSum(xVals) - d_params.cv * IloSum(d_o) + lVal);
}