#include "experiment.ih"

IloInt Experiment::s_count = 0;

Experiment::Experiment(ModelParameters params, IloInt runs, IloInt optGapReps, IloInt optGapSamples)
:
	d_env(IloEnv{}),
	d_params(params),
	d_runs(runs),
	d_SAAMethod(SAAMethod{d_env, params, IloFalse}),
	d_optGapReps(optGapReps),
	d_optGapSamples(optGapSamples)
{
	++s_count;
	d_id = s_count;
}