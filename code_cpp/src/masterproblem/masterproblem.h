#ifndef INCLUDED_MASTERPROBLEM_
#define INCLUDED_MASTERPROBLEM_

#include <string>
#include <ilcplex/ilocplex.h>
#include "../modelparameters/modelparameters.h"

typedef IloArray<IloNumVarArray> IloNumVarMatrix;

class MasterProblem
{
   IloEnv   d_env;
   IloModel d_model;
   IloCplex d_cplex;

   // PARAMETERS
   ModelParameters const d_params;

   // Variables
   IloNumVarArray    d_x;
   IloNumVarMatrix   d_y;
   IloNumVarArray    d_lambdas;
   IloNumVar         d_eta;
   IloNumVarArray    d_allX;

   // Values
   IloNumArray       d_xVals;
   IloNumArray2      d_yVals;
   IloNumArray       d_lambdaVals;
   IloNum            d_etaVal;
   IloNumArray       d_allXVals;

   // Objective
   IloObjective   d_objective;
   IloNum         d_objectiveVal;

public:
   MasterProblem() = delete;
   MasterProblem(IloEnv env, ModelParameters params);

   void initalise();
   void solve();
   void showSolution();
   void addCutConstraint(IloNum QApprox, IloNumArray u);
   void setEta(IloNum low);
   void exportModel(std::string fileName);
   void updateVals();

   IloModel          getModel();
   IloNumVarArray    getX();
   IloNumVarMatrix   getY();
   IloNumVarArray    getL();
   IloNumArray       getXVals();
   IloNumArray2      getYVals();
   IloNumArray       getLVals();
   IloNum            getEtaVal();
   IloObjective      getObjective();
   IloNum            getObjectiveVal();
   IloNumArray       getAllVariableVals();

private:
   void createFirstStageVariables();
   void createFirstStageConstraints();
};

inline IloModel MasterProblem::getModel()
{
   return d_model;
}

inline IloNumVarArray MasterProblem::getX()
{
   return d_x;
}

inline IloNumVarMatrix MasterProblem::getY()
{
   return d_y;
}

inline IloNumVarArray MasterProblem::getL()
{
   return d_lambdas;
}

inline IloNumArray MasterProblem::getXVals()
{
   return d_xVals;
}

inline IloNumArray2 MasterProblem::getYVals()
{
   return d_yVals;
}

inline IloNumArray MasterProblem::getLVals()
{
   return d_lambdaVals;
}

inline IloNum MasterProblem::getEtaVal()
{
   return d_etaVal;
}

inline void MasterProblem::exportModel(std::string fileName)
{
   d_cplex.exportModel(fileName.c_str());
}

inline IloObjective MasterProblem::getObjective()
{
   return d_objective;
}

inline IloNum MasterProblem::getObjectiveVal()
{
   return d_objectiveVal;
}

inline IloNumArray MasterProblem::getAllVariableVals()
{
   return d_allXVals;
}

#endif