#include "masterproblem.ih"
#include <sstream>

/*
 * Define all first-stage contraints. 
 */

void MasterProblem::createFirstStageConstraints()
{
   std::ostringstream oss;
   IloInt nbORs = d_params.nbORs;
   IloInt nbSurgeries = d_params.nbSurgeries;

   // Surgery should be assigned to open OR
   for (IloInt operatingRoom = 0; operatingRoom < nbORs; ++operatingRoom)
      for (IloInt surgery = 0; surgery < nbSurgeries; ++surgery)
         d_model.add(d_y[operatingRoom][surgery] <= d_x[operatingRoom]);

   // All surgeries should be assigned to one OR
   for (IloInt surgery = 0; surgery < nbSurgeries; ++surgery) 
   {
      IloExpr e1(d_env);
      for (IloInt OR = 0; OR < nbORs; ++OR)
         e1 += d_y[OR][surgery];

      d_model.add(e1 == 1);
   }

   // Symmetry breaking constraint for the x variables
   for (IloInt OR = 0; OR < (nbORs-1); ++OR)
      d_model.add(d_x[OR] >= d_x[OR+1]);

   // Symmetry breaking (7) for y
   for (IloInt i = 0; i < nbSurgeries; ++i)
   {
      IloExpr e1(d_env);
      for (IloInt j = 0; j <= i; ++j)
         e1 += d_y[j][i];

      d_model.add(e1 == 1);
   }

   // Symmetry breaking constraint (9)
   for (IloInt j = 1; j < nbORs; ++j)
   {
      for (IloInt i = j; i < nbSurgeries; ++i)
      {
         IloExpr e_left(d_env);
         IloExpr e_right(d_env);

         for (IloInt v = j; v <= min(i, nbORs-1); ++v)
            e_left += d_y[v][i];
         for (IloInt u = j - 1; u < i; ++u)
            e_right += d_y[j-1][u];

         IloConstraint c(e_left <= e_right);
         oss << "(" << i << "," << j << ")";
         c.setName(oss.str().c_str());
         oss.clear();
         oss.str("");
         d_model.add(c);
      }
   }
} // END createFirstStageConstraints