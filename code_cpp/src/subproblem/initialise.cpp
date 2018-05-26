#include "subproblem.ih"

void SubProblem::initialise()
{
	// Add variables to the problem
	createVariables();

	// Add constraints to the problem
	createConstraints();

	// Add the objective
	createObjective();

	// Add model to the algorithm and set solver to dual-simplex
	d_cplex.extract(d_model);
	d_cplex.setParam(IloCplex::RootAlg, IloCplex::Dual);

	// Set output to nothing
	d_cplex.setOut(d_env.getNullStream());
}