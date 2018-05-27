#include "saamethod.ih"

/* 
 * Solve SAAMethod using a custom branch-and-bound scheme.
 */

void SAAMethod::solve()
{
	d_cplex.setParam(IloCplex::Param::MIP::Strategy::Search, 2);
	d_cplex.solve();

	updateVals();
}