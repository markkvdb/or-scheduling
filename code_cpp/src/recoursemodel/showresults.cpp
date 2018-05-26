#include "recoursemodel.ih"

void RecourseModel::showResults()
{
   d_env.out() << "Solution status = " << d_cplex.getStatus() << '\n';
   d_env.out() << "Solution value  = " << d_cplex.getObjValue() << '\n';
   d_env.out() << '\n';

   IloNumArray overtimeValues{d_env};
   d_cplex.getValues(overtimeValues, d_o[0]);

   // Show the overtime variables for one scenarion (= 0)
   d_env.out() << overtimeValues << ' ' << d_cplex.getValue(d_uPlus[0]) << ' ' << d_cplex.getValue(d_uMinus[0]) << '\n';
}