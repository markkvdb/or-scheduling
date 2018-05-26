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
   IloNumVar         d_l;
   IloNumVar         d_eta;
   IloNumVarArray    d_allX;

   // Values
   IloNumArray       d_xVals;
   IloNumArray2      d_yVals;
   IloNum            d_lVal;
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
   void setVariablesBinary();       // TODO
   void setVariablesContinuous();   // TODO
   void addCutConstraint(IloNum QApprox, IloNumArray u);
   void setEta(IloNum low);
   void exportModel(std::string fileName);
   void updateVals();

   IloModel          getModel();
   IloNumVarArray    getX();
   IloNumVarMatrix   getY();
   IloNumVar         getL();
   IloNumArray       getXVals();
   IloNumArray2      getYVals();
   IloNum            getLVal();
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

inline IloNumVar MasterProblem::getL()
{
   return d_l;
}

inline IloNumArray MasterProblem::getXVals()
{
   return d_xVals;
}

inline IloNumArray2 MasterProblem::getYVals()
{
   return d_yVals;
}

inline IloNum MasterProblem::getLVal()
{
   return d_lVal;
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

// Not sure what to do with this
inline void MasterProblem::setVariablesBinary()
{

}

inline void MasterProblem::setVariablesContinuous()
{
   
}


#endif