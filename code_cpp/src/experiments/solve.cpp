#include "experiments.ih"

/*
 *	Solve all experiments one by one. 
 */

void Experiments::solve()
{
	for (string const &experimentLine: d_experimentStrings)
	{
		ModelParameters params{experimentLine};
		Experiment experiment{params, 1, 20, 100};
		experiment.solve();
		experiment.output();
	}
}