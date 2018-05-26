#include "recoursemodel.ih"

void RecourseModel::showMinMaxDuals() {
	if (!d_cplex.solve()) {
		d_env.out() << "Problem is not solved yet";
	}
	for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
		d_env.out() << IloSum(d_durationSample[scen]) << ' ';
	d_env.out() << '\n';
	IloNum max = 0;
	IloNum sum = 0;
	for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen) {
		IloNum tmp_val = d_cplex.getDual(d_minmaxConstraints[scen]);
		sum += tmp_val;
		if (tmp_val > max)
			max = tmp_val;
		d_env.out() << tmp_val << ' ';
	}
	d_env.out() << '\n';
	d_env.out() << max << ' ' << sum << '\n';
}