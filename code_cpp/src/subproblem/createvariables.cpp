#include "subproblem.ih"

void SubProblem::createVariables()
{
	// Declare variables
   IloInt nbORs = d_params.nbORs;
   IloInt nbSurgeries = d_params.nbSurgeries;

   d_o = IloNumVarArray(d_env, nbORs, 0, IloInfinity);
   d_uPlus = IloNumVar(d_env, 0, IloInfinity);
   d_uMinus = IloNumVar(d_env, 0, IloInfinity);

   // Set names
   std::ostringstream oss;
   for (IloInt j = 0; j < nbORs; ++j)
   {
      // Name O
      oss << "o_" << j;
      d_o[j].setName(oss.str().c_str());
      oss.clear();
      oss.str("");
   }
   d_uPlus.setName("u_+");
   d_uMinus.setName("u_-");
}