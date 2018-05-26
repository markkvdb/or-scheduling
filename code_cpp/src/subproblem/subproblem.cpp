#include "subproblem.ih"

/*
 * Initialise the subproblem without the proper constraints, since these
 * depend on the values of the first-stage solution
 */

SubProblem::SubProblem(IloEnv env, IloNumArray durations, ModelParameters params)
:
	d_env(env),
	d_model(IloModel{env}),
	d_cplex(IloCplex{env}),
	d_durations(durations),
	d_dualVariables(IloNumArray{env, params.nbORs + 1}),
	d_params(params)
{}

/*
 * Initialise the sub problem completely.
 */

SubProblem::SubProblem(IloEnv env, IloNumArray durations, ModelParameters params, 
					   IloNumArray xVals, IloNumArray2 yVals, IloNum lVal)
:
	d_env(env),
	d_model(IloModel{env}),
	d_cplex(IloCplex{env}),
	d_durations(durations),
	d_dualVariables(IloNumArray{env, params.nbORs + 1}),
	d_params(params)
{
	updateModel(xVals, yVals, lVal);
}

SubProblem::SubProblem()
{}