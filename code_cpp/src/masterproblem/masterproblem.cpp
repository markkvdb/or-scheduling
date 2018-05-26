#include "masterproblem.ih"

MasterProblem::MasterProblem(IloEnv env, ModelParameters params)
:
	d_env(env),
	d_model(IloModel{env}),
	d_cplex(IloCplex{env}),
	d_params(params)
{
	// Declare variables
	IloInt d_nbORs = d_params.nbORs;
	IloInt d_nbSurgeries = d_params.nbSurgeries;

	// Initialise a vector containing all first-stage variables (excluding eta)
	d_allX = IloNumVarArray{d_env, d_nbORs + d_nbORs * d_nbSurgeries + 1};
	d_allXVals = IloNumArray{d_env, d_nbORs + d_nbORs * d_nbSurgeries + 1};

	d_xVals = IloNumArray{d_env, d_nbORs};
	d_yVals = IloNumArray2{d_env, d_nbORs};
	for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
    	d_yVals[OR] = IloNumArray{d_env, d_nbSurgeries};
}