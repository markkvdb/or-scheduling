#include "recoursemodel.ih"
#include <random>

void RecourseModel::createDurationSample()
{
	// Set-up the random number generator
   default_random_engine generator{static_cast<unsigned int>(d_params.seed)};
   lognormal_distribution<double> distribution{d_params.mu, d_params.sig};

   // Saved
   IloInt nbSurgeries = d_params.nbSurgeries;

   for (IloNum scen = 0; scen < d_params.nbScenarios; ++scen)
   {
      d_durationSample[scen] = IloNumArray(d_env, nbSurgeries);
      for (IloNum surgery = 0; surgery < nbSurgeries; ++surgery)
         d_durationSample[scen][surgery] = distribution(generator);
   }
}