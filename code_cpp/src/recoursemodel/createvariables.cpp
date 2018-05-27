#include "recoursemodel.ih"

void RecourseModel::createVariables()
{
	// Declare variables
	IloInt nbORs = d_params.nbORs;

	for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
	{
		if (d_integer)
			d_o[scen] = IloNumVarArray(d_env, nbORs, 0, IloInfinity, ILOINT);
		else 
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