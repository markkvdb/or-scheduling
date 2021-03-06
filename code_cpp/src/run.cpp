#include <iostream>

#include "methodsrun.h"
#include "experiments/experiments.h"

ILOSTLBEGIN

int main(int argc, char **argv)
{
	try
	{
		Experiments experiments{"../experiments.txt"};
		experiments.solve();
	}
	catch (IloException& e) {
   		cerr<< "Concert exception caught: " << e << endl;
	}
	catch (string const &e) {
   		cerr << e << endl;
	}
}
