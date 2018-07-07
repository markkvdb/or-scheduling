#include "masterproblem.ih"

/*
 * Create first-stage variables. These consists of the x, y and lambda
 * variables.
 * 
 * TODO add support for multi-dimensional lambda variable.
 */

void MasterProblem::createFirstStageVariables()
{
   // Declare variables
   IloInt d_nbORs = d_params.nbORs;
   IloInt d_nbSurgeries = d_params.nbSurgeries;

   // Setup the x variables (whether to open OR or not)
   d_x = IloNumVarArray{d_env, d_nbORs, 0, 1, ILOINT};
   for (IloInt OR = 0; OR < d_nbORs; ++OR)
      d_allX[OR] = d_x[OR];

   // Set up the y variables indicating the operating room schedule
   d_y = IloNumVarMatrix(d_env, d_nbORs);
   for (IloInt j = 0; j < d_nbORs; ++j) 
   {
      d_y[j] = IloNumVarArray(d_env, d_nbSurgeries, 0, 1, ILOINT);
      for (IloInt i = 0; i < d_nbSurgeries; ++i)
         d_allX[d_nbORs + j + i * d_nbORs] = d_y[j][i];
   }

   // Set up lambda variable
   d_lambdas = IloNumVarArray(d_env, 3*d_nbSurgeries, 0, IloInfinity);
   for (IloInt surgery = 0; surgery != (3 * d_nbSurgeries); ++surgery)
   {
      d_allX[d_nbORs + d_nbORs * d_nbSurgeries + surgery] = d_lambdas[surgery];

      // To ensure that the variable is included in the model.
      d_model.add(d_lambdas[surgery] >= 0);
   }

   // Add eta
   d_eta = IloNumVar(d_env, 0, IloInfinity);
   d_model.add(d_eta >= 0);

   // Set names
   std::ostringstream oss;
   for (IloInt j = 0; j < d_nbORs; ++j)
   {
      oss << "x_" << j;
      d_x[j].setName(oss.str().c_str());
      oss.clear();
      oss.str("");
      for (IloInt i = 0; i < d_nbSurgeries; ++i)
      {
         oss << "y_" << i << j;
         d_y[j][i].setName(oss.str().c_str());
         oss.clear();
         oss.str("");
      }
   }
   for (IloInt moment = 0; moment != 3; ++moment)
   {
      for (IloInt surgery = 0; surgery != d_nbSurgeries; ++surgery)
      {
          string const name = string("l") + to_string(moment) + to_string(surgery);
          d_lambdas[moment * d_nbSurgeries + surgery].setName(name.c_str());
      }
   }
   d_eta.setName("eta");
} // END createFirstStageVariables