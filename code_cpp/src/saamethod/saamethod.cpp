#include "saamethod.ih"

SAAMethod::SAAMethod(IloEnv env, ModelParameters params)
:
	d_env(env),
	d_masterProblem(MasterProblem{env, params}),
	d_completeModel(IloModel(env)),
	d_cplex(IloCplex(env)),
	d_params(params),
	d_durationSample(IloNumArray2{env, params.nbScenarios})
{}