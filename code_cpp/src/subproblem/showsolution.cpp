#include "subproblem.ih"

void SubProblem::showSolution()
{
	cout << "Solution status = " << d_cplex.getStatus() << endl;
    cout << "Solution value  = " << d_cplex.getObjValue() << endl;
    cout << "\n";

    // Show which ORs are open
    IloNumArray overtime{d_env};
    d_cplex.getValues(overtime, d_o);

    cout << overtime << ' ' << d_cplex.getValue(d_uPlus) << ' ' << d_cplex.getValue(d_uMinus) <<  '\n';
}