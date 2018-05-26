#include "saamethod.ih"

/*
 * Initialise the whole model, that is, start by initialising the 
 * master problem. Save this as our model. Extend it by constructing
 * the second-stage problems and feed it to the CPLEX solver.
 */

void SAAMethod::initialise(IloBool bender)
{
	// Initialise model
	d_masterProblem.initalise();

	// Solve model 
	d_masterProblem.solve();
	d_completeModel = d_masterProblem.getModel();

	// Create duration sample
	createDurationSample();

	// Create variables
	createVariables();

	// Create objective
	createObjective();

	// Create constraints
	createConstraints();

	// Add model 
	d_cplex.extract(d_completeModel);

	if (bender)
		createBenderVars();

	// Set-up ordering in variables
	createVarOrdering();
}