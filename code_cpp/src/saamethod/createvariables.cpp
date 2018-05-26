#include "saamethod.ih"

/*
 * Create new variables that belong the second-stage of the problem.
 * Furthermore, save the first-stage variabels into datamembers of the class.
 */

void SAAMethod::createVariables()
{
	// Declare variables
	IloInt nbORs = d_params.nbORs;
	IloInt nbSurgeries = d_params.nbSurgeries;

	d_o = IloNumVarMatrix{d_env, d_params.nbScenarios};
	d_uPlus = IloNumVarArray{d_env, d_params.nbScenarios, 0, IloInfinity};
	d_uMinus = IloNumVarArray{d_env, d_params.nbScenarios, 0, IloInfinity};
	
	// Load first-stage variables
	d_x = d_masterProblem.getX();
	d_y = d_masterProblem.getY();
	d_l = d_masterProblem.getL(); 

	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
	{
		d_o[scen] = IloNumVarArray(d_env, nbORs, 0, IloInfinity);

		// Set names
		std::ostringstream oss;
		for (IloInt j = 0; j < nbORs; ++j)
		{
			// Name O
			oss << "o_" << j << "_" << scen;
			d_o[scen][j].setName(oss.str().c_str());
			oss.clear();
			oss.str("");
		}
		// Name u_+
		oss << "u_+" << scen;
		d_uPlus[scen].setName(oss.str().c_str());
		oss.clear();
		oss.str("");

		// Name u_-
		oss << "u_-" << scen;
		d_uMinus[scen].setName(oss.str().c_str());
		oss.clear();
		oss.str("");
	}
}