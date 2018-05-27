#ifndef INCLUDED_EXPERIMENT_
#define INCLUDED_EXPERIMENT_

#include "../masterproblem/masterproblem.h"
#include "../modelparameters/modelparameters.h"
#include "../saamethod/saamethod.h"
#include "../recoursemodel/recoursemodel.h"

typedef IloArray<IloNumVarArray> IloNumVarMatrix;
typedef IloArray<IloNumVarMatrix> IloNumVarMatrix3;

class Experiment
{
   static IloInt  s_count;
   IloInt         d_id;

   IloEnv                  d_env;
   ModelParameters const   d_params;
   IloInt                  d_runTime;
   IloInt                  d_runs;

   IloNumArray             d_ORToOpen;
   IloNumArray             d_surgeryAssignments;
   IloNum                  d_lambda;

   // Multiple Replication Procedure
   IloNum d_optGapMean;
   IloNum d_optGapVar;
   IloInt d_optGapReps;
   IloInt d_optGapSamples;

   // Models
   SAAMethod   d_SAAMethod;
   IloNum      d_SAARunTime;

public:
   Experiment() = delete;
   Experiment(ModelParameters params, IloInt runs, IloInt optGapReps, IloInt optGapSamples);

   void solve();
   void output();
   void showSolution();

private:
   IloNum   firstStageCost();
   IloNum   secondStageCost();
   void     optimalityGap();
   void     worstDistribution();

   std::string createExperimentHeader();
};

#endif