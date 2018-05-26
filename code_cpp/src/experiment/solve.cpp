#include "experiment.ih"

/*
 * Solve the SAAMethod and save the runtime.
 */

void Experiment::solve()
{
	auto start = chrono::steady_clock::now();
	d_SAAMethod.solve();
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	d_SAARunTime = chrono::duration<IloNum, milli>(diff).count();
}