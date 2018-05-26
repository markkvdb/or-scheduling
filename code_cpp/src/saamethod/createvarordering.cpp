#include "saamethod.ih"

/*
 * The problem is solved using a branch-and-bound scheme.
 * We place higher priority to first branching the 
 * first-stage variables. Especially the ones related to opening
 * a new operating room or not.
 */

void SAAMethod::createVarOrdering() 
{
	// First-stage ordering (higher)
	IloNumArray tmpNumX{d_env, d_params.nbORs};
	IloNumArray2 tmpNumY{d_env, d_params.nbORs};
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
	{
		tmpNumX[OR] = d_params.nbORs + 1;
		tmpNumY[OR] = IloNumArray{d_env, d_params.nbSurgeries};
		for (IloInt surgery = 0; surgery < d_params.nbSurgeries; ++surgery)
			tmpNumY[OR][surgery] = d_params.nbORs - OR;
	}
	d_cplex.setPriorities(d_x, tmpNumX);
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
		d_cplex.setPriorities(d_y[OR], tmpNumY[OR]);
}