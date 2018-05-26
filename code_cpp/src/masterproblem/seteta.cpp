#include "masterproblem.ih"

void MasterProblem::setEta(IloNum low)
{
	// Add constraint
	d_model.add(d_eta >= low);
}