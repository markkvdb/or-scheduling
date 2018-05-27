#ifndef INCLUDED_RECOURSEMODEL_
#define INCLUDED_RECOURSEMODEL_

#include <ilcplex/ilocplex.h>

#include "../modelparameters/modelparameters.h"

typedef IloArray<IloNumVarArray> IloNumVarMatrix;
typedef IloArray<IloRangeArray> IloRangeArray2;

class RecourseModel
{
   IloEnv         d_env;
   
   // Define master problem
   IloModel       d_model;
   IloCplex       d_cplex;

   // Variables of the model
   IloNumVarMatrix   d_o;
   IloNumVarArray    d_uPlus;
   IloNumVarArray    d_uMinus;

   // Constraints of the model
   IloRangeArray2  d_overtimeConstraints;
   IloRangeArray   d_minmaxConstraints;

   // Parameters of the algorithm
   ModelParameters   d_params;
   IloBool           d_integer;

   // Data of the model
   IloNumArray2   d_durationSample;
   IloObjective   d_objective;
   
   IloNumArray    d_xVals;
   IloNumArray2   d_yVals;
   IloNum         d_lVal;

public:
   RecourseModel() = delete;
   RecourseModel(IloEnv env, ModelParameters params, IloBool integer, IloInt sampleSize);
   RecourseModel(IloEnv env, ModelParameters params, IloBool integer, IloInt sampleSize,
		     IloNumArray xVals, IloNumArray2 yVals, IloNum lVal);

   void  initialise(IloNumArray xVals, IloNumArray2 yVals, IloNum lVal);
   void  solve();
   void  showSolution();
   void  showSample();
   void  showResults();
   void  showMinMaxDuals();

   IloNumArray2   getSample();
   IloNum         getObjVal();

private:
   void  createDurationSample();
   void  createVariables();
   void  createConstraints();
   void  createObjective();
};

inline IloNumArray2 RecourseModel::getSample()
{
   return d_durationSample;
}

inline void RecourseModel::showSample()
{
   for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
      d_env.out() << "Scenario " << scen << " = " << d_durationSample[scen] << '\n';
}

inline void RecourseModel::solve()
{
   d_cplex.solve();
}

inline IloNum RecourseModel::getObjVal()
{
   return d_cplex.getObjValue();
}

#endif