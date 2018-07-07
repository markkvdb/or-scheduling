#include "experiment.ih"

/*
 * Solve LP to obtain worst-case distribution
 * 
 * TODO USE DIFFERENT DURATION SAMPLE
 */
void Experiment::worstDistributionLP(IloNumArray objs, string const &name)
{   
    // Initialise model
    IloModel model{d_env};
    IloNumArray2 durationSample = d_SAAMethod.getDurationSample();

    // Define the probabilities that satisfy (p* - e1 <= p <= p* + e1)
    IloNum p_star = 1.0/d_params.nbScenarios;

    IloNumVarArray p{d_env, d_params.nbScenarios, p_star * (1-d_params.eps1), p_star * (1+d_params.eps2)};

    // Probabilities should sum up to 1
    model.add(IloSum(p) == 1);

    // Mean should be equal to set value and second moment
    IloNumArray durations{d_env, d_params.nbScenarios};
    IloNumArray durations2{d_env, d_params.nbScenarios};
    for (IloInt surgery = 0; surgery != d_params.nbSurgeries; ++surgery)
    {
        // Get all durations
        for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
        {
            durations[scen] = durationSample[scen][surgery];
            durations2[scen] = durations[scen] * durations[scen];
        }
        
         model.add(IloScalProd(durations, p) == d_params.meanDuration);
         model.add(IloScalProd(durations2, p) == pow(d_params.stdDuration, 2));
    }

    // Objective is to minimise weighted objectivae
    model.add(IloMinimize(d_env, IloScalProd(p, objs)));

    IloCplex cplex{model};
    cplex.exportModel("worst_case.lp");
    if (!cplex.solve())
        throw string("Could not solve worst-case distribution LP");

    IloNumArray pVals{d_env};
    cplex.getValues(pVals, p);

    // Save to file
    ofstream outputFile;
	outputFile.open(string("experiment output/worst_case_") + name + to_string(d_id));
    for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
        outputFile << pVals[scen] << ' ';
    outputFile << endl;

    outputFile.close();
}