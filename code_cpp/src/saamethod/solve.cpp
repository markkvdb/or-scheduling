#include "saamethod.ih"

/* 
 * Solve SAAMethod using a custom branch-and-bound scheme.
 */

void SAAMethod::solve()
{
	d_cplex.setParam(IloCplex::Param::MIP::Strategy::Search, 2);
	d_cplex.solve();

	if (d_cplex.getCplexStatus() != CPX_STAT_OPTIMAL)
		throw(string("Problem cannot be solved to optimality"));

	updateVals();
}