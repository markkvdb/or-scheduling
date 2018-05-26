#include "experiment.ih"

/* 
 * Calculate the optimality gap by means of the Multiple 
 * Replication Procedure. 
 * 
 * TODO Save as data member: mean, standard deviation and sample size
 */

IloNum Experiment::optimalityGap(IloNum alpha, IloInt nbSamples, IloInt nbReps)
{
	vector<IloNum> gapEstimates{};
	IloInt seedBase = 2513102;

	// Obtain the first-stage solution

	for (IloInt rep = 0; rep < nbReps; ++rep)
	{
		// 1. Solve the MILP for sample size nbSamples

		// 2. Evaluate the recourse cost for the second-stage MILP

		// 3. Calculate the gap

	}

	// Get mean and standard deviation of gap estimates
	IloNum meanGap = accumulate(gapEstimates.begin(), gapEstimates.end(), 0.0)/gapEstimates.size(); 
	IloNum accum = 0.0;
	for_each(begin(gapEstimates), end(gapEstimates), [&](const IloNum d) {
    	accum += (d - meanGap) * (d - meanGap);
    });
	IloNum stdGap = sqrt(accum / (gapEstimates.size()-1));

	return 0;
}

/*
def mrp_procedure(self, master_problem, alpha, N_reps, N_sample):
        """Evualate the quality of the solution by constructing an optimality bound."""
        gap_estimates = np.zeros(N_reps)
        seed_base = 1000

        # Get the x_val of the original_problem
        x_vals = master_problem.getAttr("X", master_problem._x)

        for idx in range(N_reps):
            # 1. Create demand data
            np.random.seed(seed_base + idx)
            demand_list = self.create_sample(N_sample, seed_base + idx)

            # 2. Solve the SP problem
            SP_model = self.integer_method(demand_list)
            Q_x = self.calculate_recourse(master_problem, demand_list).ObjVal

            # 3. Value for the gap
            gap_val = self.params.c_f * x_vals.sum().getValue() + Q_x - SP_model.ObjVal
            gap_estimates[idx] = gap_val

        # Calculate the average gap
        gap_mean = gap_estimates.mean()
        gap_std = gap_estimates.std()

        # Confidence interval:
        r_bound = gap_mean + (stats.t.ppf(alpha, N_reps - 1) * gap_std) / np.sqrt(N_reps)

        return r_bound
*/