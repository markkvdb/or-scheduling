#include "experiment.ih"

/* 
Function to output all the relevant data of the experiment. Data is:
	# Problem data
	- c_f
 	- c_v
 	- Number of types of surgery
 	- Mean surgery type i
 	- Std. surgery type i
 	- eps1
 	- eps2
	- Number of ORs (and surgeries)
	- number of scenarios
 	- seed

	# Solution data
 	- ORs open
 	- Surgery assignment
 	- First-stage costs
 	- Second-stage costs

 	# MRP
 	- Optimality gap mean
 	- OPtimality gap std
 	- Number of samples
 	- Number of replications
*/
void Experiment::output()
{
	d_SAAMethod.showSolution();
	
	// Define output stream
	ofstream outputFile;
	outputFile.open(string("experiment output/experiment") + to_string(d_id));

	// First define experiment header
	outputFile << createExperimentHeader() << '\n';

	// Save all info
	outputFile << d_id << ' ';

	// Problem data (which is mostly just the model parameters)
	string problemData = d_params.outputString();
	outputFile << problemData << ' ';

	// Solution data
	string solutionData = d_SAAMethod.showSolutionInfo();
	outputFile << solutionData << ' ';

	outputFile << d_SAARunTime;

	// MRP data
	// if (MRP)
	// {

	// }

	outputFile << '\n';
	outputFile.close();
}