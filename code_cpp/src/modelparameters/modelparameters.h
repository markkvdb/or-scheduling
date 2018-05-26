#ifndef INCLUDED_MODELPARAMETERS_
#define INCLUDED_MODELPARAMETERS_

#include <ilcplex/ilocplex.h>
#include <string>

class ModelParameters
{
public:
	// Parameters for the problem
   IloInt nbORs;
   IloInt nbSurgeries;

   // Costs
   IloNum cf;
   IloNum cv;
   IloNum nbHours;

   // Uncertainty
   IloNum meanDuration;
   IloNum stdDuration;

   IloNum mu;
   IloNum sig;

   IloNum eps1;
   IloNum eps2;

   // Number of scenarios for the problem
   IloInt nbScenarios;
   IloInt seed;

   ModelParameters();
   ModelParameters(std::string parametersInput);

   std::string outputString() const;
};

#endif