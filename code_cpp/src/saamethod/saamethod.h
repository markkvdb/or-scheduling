#ifndef INCLUDED_SAAMETHOD_
#define INCLUDED_SAAMETHOD_

#include <vector>
#include <tuple>
#include <ilcplex/ilocplex.h>
#include <string>

#include "../masterproblem/masterproblem.h"
#include "../modelparameters/modelparameters.h"

typedef IloArray<IloNumVarArray> IloNumVarMatrix;
typedef IloArray<IloNumVarMatrix> IloNumVarMatrix3;

class SAAMethod
{
   IloEnv   d_env;
   IloInt   d_iter;
   IloBool  d_integer;
   
   // Define master problem
   MasterProblem              d_masterProblem;
   IloModel                   d_completeModel;
   IloCplex                   d_cplex;
   IloCplex::LongAnnotation   d_benders;

   // Variables of the model
   IloNumVarArray    d_x;
   IloNumVarMatrix   d_y;
   IloNumVarArray    d_lambdas;
   IloNumVarMatrix   d_o;
   IloNumVarArray    d_uPlus;
   IloNumVarArray    d_uMinus;

   IloNumArray    d_xVals;
   IloNumArray2   d_yVals;
   IloNumArray    d_lambdaVals;
   IloNumArray2   d_oVals;
   IloNumArray    d_uPlusVals;
   IloNumArray    d_uMinusVals;

   // Parameters of the algorithm
   ModelParameters const   d_params;

   // Data of the model
   IloNumArray2   d_durationSample;
   IloObjective   d_objective;

public:
   SAAMethod() = delete;
   SAAMethod(IloEnv env, ModelParameters params, IloBool integer);

   void     initialise(IloBool bender);
   void     solve();
   void     showSolution();
   void     showSample();
   void     exportModel();

   IloArray<IloExpr> createLambdaConstraint();

   IloNum         getObjectiveVal();
   IloNumArray    getXVals();
   IloNumArray2   getYVals();
   IloNumArray    getLVals();
   IloNumArray2   getDurationSample();

   std::string showSolutionInfo();

private:
   void  createDurationSample();
   void  createVariables();
   void  createConstraints();
   void  createObjective();
   void  createBenderVars();
   void  createVarOrdering();

   void  updateVals();
};

inline void SAAMethod::showSample()
{
   for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
      d_env.out() << "Scenario " << scen << " = " << d_durationSample[scen] << '\n';
}

inline IloNumArray2 SAAMethod::getDurationSample()
{
      return d_durationSample;
}

inline IloNum SAAMethod::getObjectiveVal()
{
      return d_cplex.getObjValue();
}

inline IloNumArray SAAMethod::getXVals()
{
      return d_xVals;
}

inline IloNumArray2 SAAMethod::getYVals()
{
      return d_yVals;
}

inline IloNumArray SAAMethod::getLVals()
{
      return d_lambdaVals;
}

inline void SAAMethod::exportModel()
{
    d_cplex.exportModel("saa_model.lp");
}

#endif