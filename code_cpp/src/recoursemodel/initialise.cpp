#include "recoursemodel.ih"

void RecourseModel::initialise(IloNumArray xVals, IloNumArray2 yVals, IloNumArray lambdaVals)
{
	d_xVals = xVals;
	d_yVals = yVals;
	d_lambdaVals = lambdaVals;
	
	// Create duration sample
	createDurationSample();

	// Create variables
	createVariables();

	// Create objective
	createObjective();

	// Create constraints
	createConstraints();
	
	d_cplex.extract(d_model);
}