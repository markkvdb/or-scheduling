#include "recoursemodel.ih"

RecourseModel::RecourseModel(IloEnv env, ModelParameters params, IloBool integer, IloInt sampleSize)
:
	d_env(env),
	d_model(IloModel(env)),
	d_cplex(IloCplex(env)),
	d_params(params),
	d_integer(integer)
{
	d_cplex.setParam(IloCplex::RootAlg, IloCplex::Dual);

   	d_params.nbScenarios = sampleSize;

   	// Initialise variables
   	d_o = IloNumVarMatrix{d_env, d_params.nbScenarios};
	d_uPlus = IloNumVarArray{d_env, d_params.nbScenarios, 0, IloInfinity};
	d_uMinus = IloNumVarArray{d_env, d_params.nbScenarios, 0, IloInfinity};

	// Initialise size of the duration sample
	d_durationSample = IloNumArray2{d_env, d_params.nbScenarios};

	// Initialise constraints
	d_overtimeConstraints = IloRangeArray2{d_env, d_params.nbScenarios};
	for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
		d_overtimeConstraints[scen] = IloRangeArray{d_env, d_params.nbORs};
	d_minmaxConstraints = IloRangeArray{d_env, d_params.nbScenarios};
}

RecourseModel::RecourseModel(IloEnv env, ModelParameters params, IloBool integer, IloInt sampleSize,
							 IloNumArray xVals, IloNumArray2 yVals, IloNumArray lambdaVals)
:
	d_env(env),
	d_model(IloModel(env)),
	d_cplex(IloCplex(env)),
	d_params(params),
	d_integer(integer)
{
	d_cplex.setParam(IloCplex::RootAlg, IloCplex::Dual);
	
   	d_params.nbScenarios = sampleSize;

   	// Initialise variables
   	d_o = IloNumVarMatrix{d_env, d_params.nbScenarios};
	d_uPlus = IloNumVarArray{d_env, d_params.nbScenarios, 0, IloInfinity};
	d_uMinus = IloNumVarArray{d_env, d_params.nbScenarios, 0, IloInfinity};

	// Initialise size of the duration sample
	d_durationSample = IloNumArray2{d_env, d_params.nbScenarios};

	// Initialise constraints
	d_overtimeConstraints = IloRangeArray2{d_env, d_params.nbScenarios};
	for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
		d_overtimeConstraints[scen] = IloRangeArray{d_env, d_params.nbORs};
	d_minmaxConstraints = IloRangeArray{d_env, d_params.nbScenarios};

	// Initialise everything 
	initialise(xVals, yVals, lambdaVals);
}