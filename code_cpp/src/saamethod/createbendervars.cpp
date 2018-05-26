#include "saamethod.ih"

/*
 * If the bender decomposition is used (introduced in CPLEX 12.7.1) then
 * we set the annotation accordingly, that is, variables in the master problem
 * get value 0, and the second-stage variables corresponding to scenario i are 
 * set to i + 1.
 */

void SAAMethod::createBenderVars() 
{
	d_benders = d_cplex.newLongAnnotation(CPX_BENDERS_ANNOTATION, CPX_BENDERS_MASTERVALUE);

	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
	{
		for (IloInt j = 0; j < d_params.nbORs; ++j)
			d_cplex.setAnnotation (d_benders, d_o[scen][j], CPX_BENDERS_MASTERVALUE+scen+1);

		d_cplex.setAnnotation(d_benders, d_uPlus[scen], CPX_BENDERS_MASTERVALUE+scen+1);
		d_cplex.setAnnotation(d_benders, d_uMinus[scen], CPX_BENDERS_MASTERVALUE+scen+1);
	}
}