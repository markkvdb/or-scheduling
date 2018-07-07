#include "subproblem.ih"

/*
 * Initialise the subproblem without the proper constraints, since these
 * depend on the values of the first-stage solution
 */

SubProblem::SubProblem(IloEnv env, IloNumArray durations, ModelParameters params, IloBool integer)
:
	d_env(env),
	d_model(IloModel{env}),
	d_cplex(IloCplex{env}),
	d_integer(integer),
	d_durations(durations),
	d_dualVariables(IloNumArray{env, params.nbORs + 1}),
	d_params(params)
{
	initialise();
}

/*
 * Initialise the sub problem completely.
 */

SubProblem::SubProblem(IloEnv env, IloNumArray durations, ModelParameters params, IloBool integer,
					   IloNumArray xVals, IloNumArray2 yVals, IloNumArray lambdaVals)
:
	d_env(env),
	d_model(IloModel{env}),
	d_cplex(IloCplex{env}),
	d_integer(integer),
	d_durations(durations),
	d_dualVariables(IloNumArray{env, params.nbORs + 1}),
	d_params(params)
{
	initialise();
	updateModel(xVals, yVals, lambdaVals);
}

SubProblem::SubProblem()
{}