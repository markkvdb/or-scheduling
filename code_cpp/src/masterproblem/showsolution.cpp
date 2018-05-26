#include "masterproblem.ih"
#include <vector>

/*
 * Output the first-stage solution values of the MasterProblem.
 */

void MasterProblem::showSolution()
{
    d_env.out() << "---- START MASTER INFORMATION ----\n";
	d_env.out() << "Solution status = " << d_cplex.getStatus() << endl;
    d_env.out() << "Solution value  = " << d_cplex.getObjValue() << endl;
    d_env.out() << "\n";

    // Show which ORs are open
    d_env.out() << "ORs open = ";
    for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
    {
    	if (d_xVals[OR] == 1)
    		d_env.out() << (OR+1) << ' ';
    }
    d_env.out() << "\n\n";

    // Show how surgeries are assigned to ORs
    for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
    {
    	// Display all surgeries
    	d_env.out() << "OR " << (OR+1) << " = ";
    	for (IloInt surgery = 0; surgery < d_params.nbSurgeries; ++surgery)
		{
			if (d_yVals[OR][surgery] == 1)
				d_env.out() << (surgery+1) << ' ';
		}
		d_env.out() << '\n';
	}
    d_env.out() << "lambda = " << d_lVal << '\n';
    d_env.out() << "---- END MASTER INFORMATION ----\n\n";
}