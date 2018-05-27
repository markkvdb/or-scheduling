#ifndef INCLUDED_SUBPROBLEM_
#define INCLUDED_SUBPROBLEM_

#include <ilcplex/ilocplex.h>
#include "../modelparameters/modelparameters.h"

class SubProblem 
{
	IloEnv 		d_env;
	IloModel	d_model;
	IloCplex 	d_cplex;

	// Variables of the model
	IloNumVarArray	d_o;
	IloNumVar 		d_uPlus;
	IloNumVar 		d_uMinus;

	// Constraints of the model
	IloRangeArray		d_overtimeConstraints;
	IloRange 			d_minMaxConstraint;

	// Objective of the model
	IloExpr d_objective;
	IloNum 	d_objectiveVal;

	// Recent duals
	IloNumArray d_dualVariables;

	// Data of the problem
	IloNumArray				d_durations;
	IloNumArray 			d_xVals;
	IloNumArray2			d_yVals;
	IloNum 					d_lVal;
	ModelParameters const	d_params;

public:
	SubProblem();
	SubProblem(IloEnv env, IloNumArray durations, ModelParameters params);
	SubProblem(IloEnv env, IloNumArray durations, ModelParameters params, 
			   IloNumArray xVals, IloNumArray2 yVals, IloNum lVal);

	void 		initialise();
	void 		solve();
	void 		updateModel(IloNumArray xVals, IloNumArray2 yVals, IloNum lVal);
	IloNumArray getDualVariables();
	void		showSolution();
	void		outputModel();

	IloModel 	getModel();
	IloNum 		getObjectiveVal();

private:
	void createVariables();
	void createConstraints();
	void createObjective();
};

inline IloModel SubProblem::getModel()
{
	return d_model;
}

inline IloNum SubProblem::getObjectiveVal()
{
	return d_objectiveVal;
}

inline IloNumArray SubProblem::getDualVariables()
{
	return d_dualVariables;
}

inline void SubProblem::outputModel()
{
	d_cplex.exportModel("sub.lp");
}

#endif