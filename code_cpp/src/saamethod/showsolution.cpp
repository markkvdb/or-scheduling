#include "saamethod.ih"

/*
 * Show first-stage solution of the problem.
 */

void SAAMethod::showSolution()
{
	d_env.out() << "---- START MASTER INFORMATION ----\n";
	d_env.out() << "Solution status = " << d_cplex.getStatus() << endl;
    d_env.out() << "Solution value  = " << d_cplex.getObjValue() << endl;
    d_env.out() << "\n";

    // Show which ORs are open
    IloNumArray xVals(d_env);
    d_cplex.getValues(xVals, d_x);
    d_env.out() << "ORs open = ";
    for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
    {
    	if (xVals[OR] == 1)
    		d_env.out() << (OR+1) << ' ';
    }
    d_env.out() << "\n\n";

    // Show how surgeries are assigned to ORs
    for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
    {
    	// Display all surgeries
    	d_env.out() << "OR " << (OR+1) << " = ";
    	IloNumArray surgeryAlloc(d_env);
    	d_cplex.getValues(surgeryAlloc, d_y[OR]);
    	for (IloInt surgery = 0; surgery < d_params.nbSurgeries; ++surgery)
		{
			if (surgeryAlloc[surgery] == 1)
				d_env.out() << (surgery+1) << ' ';
		}
		d_env.out() << '\n';
	}

	// Show lambdas
	IloNumArray lambdaVals{d_env};
	d_cplex.getValues(d_lambdaVals, d_lambdas);

	// First constraint
	d_env.out() << "lambda (0) = ";
	for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
		d_env.out() << lambdaVals[surgery] << ' ';
	d_env.out() << '\n';

	// Second constraint
	d_env.out() << "lambda (1) = ";
	for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
		d_env.out() << lambdaVals[d_params.nbSurgeries + surgery] << ' ';
	d_env.out() << '\n';

		// First constraint
	d_env.out() << "lambda (2) = ";
	for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
		d_env.out() << lambdaVals[2 * d_params.nbSurgeries + surgery] << ' ';
	d_env.out() << '\n';

    d_env.out() << "---- END MASTER INFORMATION ----\n\n";
}