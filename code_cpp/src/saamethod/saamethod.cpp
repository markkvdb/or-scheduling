#include "saamethod.ih"

SAAMethod::SAAMethod(IloEnv env, ModelParameters params, IloBool integer)
:
	d_env(env),
	d_iter(0),
	d_params(params),
	d_integer(integer),
	d_masterProblem(MasterProblem{env, params}),
	d_completeModel(IloModel(env)),
	d_cplex(IloCplex(env)),
	d_durationSample(IloNumArray2{env, params.nbScenarios})
{
	initalise(IloFalse);
}