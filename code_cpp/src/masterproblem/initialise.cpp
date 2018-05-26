#include "masterproblem.ih"

/*
 * Initialise MasterProblem by constructing 
 * the variables, constraints and objective.
 */

void MasterProblem::initalise()
{
	// Create first-stage variables
	createFirstStageVariables();
	cout << "Loaded first-stage variables. \n";	
	// Add constraints
	createFirstStageConstraints();
	cout << "Loaded first-stage constraints. \n";	
	// Add objective
	d_objective = IloMinimize(d_env, d_params.cf * IloSum(d_x) + d_eta);
	d_model.add(d_objective);
	// Add model to the cplex
	d_cplex.extract(d_model);
}