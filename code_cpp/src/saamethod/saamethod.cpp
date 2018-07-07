#include "saamethod.ih"

SAAMethod::SAAMethod(IloEnv env, ModelParameters params, IloBool integer)
:
	d_env(env),
	d_iter(0),
	d_integer(integer),
	d_masterProblem(MasterProblem{env, params}),
	d_completeModel(IloModel(env)),
	d_cplex(IloCplex(env)),
	d_params(params),
	d_xVals(IloNumArray{env, params.nbORs}),
	d_yVals(IloNumArray2{env, params.nbORs}),
	d_lambdaVals(IloNumArray{env, 3*params.nbSurgeries}),
	d_oVals(IloNumArray2{env, params.nbScenarios}),
	d_uPlusVals(IloNumArray{env, params.nbScenarios}),
	d_uMinusVals(IloNumArray{env, params.nbScenarios}),
	d_durationSample(IloNumArray2{env, params.nbScenarios})
{
	// Set length of y and o vals.
	for (IloInt OR = 0; OR != d_params.nbORs; ++OR)
		d_yVals[OR] = IloNumArray{d_env, d_params.nbSurgeries};
	
	for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
		d_oVals[scen] = IloNumArray{d_env, d_params.nbORs};

	initialise(IloFalse);
}