#include "experiments.ih"

/*
 *	Push all experiment settings of the experiment file
 *  to the experiment strings.
 */

Experiments::Experiments(string fileName)
:
	d_count(0)
{	
	string line;
	ifstream myfile("../experiments.txt");
	if (myfile.is_open())
	{
		while (getline (myfile, line))
			d_experimentStrings.push_back(line);
	myfile.close();
	}
}