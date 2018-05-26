// #include "methodsrun.h"

// ILOSTLBEGIN

// void runLShapedMethod()
// {
// 	// Create environment
// 	IloEnv env;

// 	try
// 	{
// 		// Load parameters
// 		ModelParameters params{};

// 		// Load LShaped algorithm
// 		LShaped lShapedAlgorithm{env, params};
		
// 		// Initialise L-shaped algorithm
// 		lShapedAlgorithm.initialise();
// 		lShapedAlgorithm.showTMatrix();

// 		// Solve algorithm
// 		lShapedAlgorithm.solve();
// 	}
// 	catch (IloException& e) {
//    		cerr<< "Concert exception caught: " << e << '\n';
// 	}
// 	catch (...) {
//    		cerr << "Unknown exception caught" << '\n';
// 	}
// 	env.end();
// }

// void runSAAMethod()
// {
// 	// Create environment
// 	IloEnv env;

// 	try
// 	{
// 		// Load parameters
// 		ModelParameters params{};

// 		// Load SAA method algorithm
// 		SAAMethod SAAMethodAlgorithm{env, params};
// 		cout << "Loaded SAAMethod instance.\n";

// 		// Initialise L-shaped algorithm
// 		SAAMethodAlgorithm.initialise();
// 		cout << "Initialised SAAMethod. \n";

// 		// Solve algorithm
// 		SAAMethodAlgorithm.solve();

// 		SAAMethodAlgorithm.showSolution();
// 	}
// 	catch (IloException& e) {
//    		cerr<< "Concert exception caught: " << e << '\n';
// 	}
// 	catch (...) {
//    		cerr << "Unknown exception caught" << '\n';
// 	}
// 	env.end();
// }

// void testRecourseFunction()
// {
// 	// Create environment
// 	IloEnv env;

// 	try
// 	{
// 		// Load parameters
// 		ModelParameters params{};

// 		// params.nbORs = 15;
// 		// params.nbSurgeries = 15;

// 		// IloNumArray xVals{env, params.nbORs};
// 		// xVals[0] = 1;
// 		// xVals[1] = 1;

// 		// IloNumArray2 yVals{env, params.nbORs};
// 		// for (IloInt OR = 0; OR < params.nbORs; ++OR)
// 		// 	yVals[OR] = IloNumArray{env, params.nbSurgeries};
// 		// for (IloInt surgery = 0; surgery < 8; ++surgery)
// 		// 	yVals[0][surgery] = 1;
// 		// for (IloInt surgery = 8; surgery < params.nbSurgeries; ++surgery)
// 		// 	yVals[1][surgery] = 1;
// 		// IloNum lVal = 2.82712;

// 		IloNumArray xVals{env, params.nbORs};
// 		xVals[0] = 1;

// 		IloNumArray2 yVals{env, params.nbORs};
// 		for (IloInt OR = 0; OR < params.nbORs; ++OR)
// 			yVals[OR] = IloNumArray{env, params.nbSurgeries};
// 		for (IloInt surgery = 0; surgery < params.nbSurgeries; ++surgery)
// 			yVals[0][surgery] = 1;

// 		IloNum lVal = 3.25;

// 		// Load SAA method algorithm
// 		RecourseModel RecourseFunction{env, params};
// 		cout << "Loaded recourse function instance.\n";

// 		// Initialise L-shaped algorithm
// 		RecourseFunction.initialise(xVals, yVals, lVal);
// 		cout << "Initialised recourse function.\n";

// 		// Solve algorithm
// 		RecourseFunction.solve();
// 		RecourseFunction.showResults();

// 		/*
// 		CREATE SUBPROBLEM AND ANALYSE IT
// 		*/

// 		// // Now test one subproblem
// 		// IloNumArray2 durationSample = RecourseFunction.getSample();

// 		// // Create subproblem
// 		// SubProblem subProblem{env, durationSample[0], params};
// 		// subProblem.initialise();
// 		// subProblem.updateModel(xVals, yVals, lVal);
// 		// subProblem.solve();

// 		// // First show duration sample
// 		// cout << "Duration sample: \n" << durationSample[0] << "\n\n";
// 		// subProblem.showSolution();

// 		// // Check if it is correct
// 		// IloNum DurationTimeOR1 = 0;
// 		// IloNum DurationTimeOR2 = 0;
// 		// for (IloInt surgery = 0; surgery < 8; ++surgery)
// 		// 	DurationTimeOR1 += durationSample[0][surgery];
// 		// for (IloInt surgery = 8; surgery < params.nbSurgeries; ++surgery)
// 		// 	DurationTimeOR2 += durationSample[0][surgery];
// 		// DurationTimeOR1 -= 8 * 60;
// 		// DurationTimeOR2 -= 8 * 60;

// 		// cout << (DurationTimeOR1 / 60) << " " << (DurationTimeOR2 / 60) << '\n';


// 	}
// 	catch (IloException& e) {
//    		cerr<< "Concert exception caught: " << e << '\n';
// 	}
// 	catch (...) {
//    		cerr << "Unknown exception caught" << '\n';
// 	}
// 	env.end();
// }

// void plotRecourseFunction()
// {
// 		// Create environment
// 	IloEnv env;

// 	try 
// 	{
// 		// Load parameters
// 		ModelParameters params{};

// 		IloNumArray xVals{env, params.nbORs};
// 		xVals[0] = 1;

// 		IloNumArray2 yVals{env, params.nbORs};
// 		for (IloInt OR = 0; OR < params.nbORs; ++OR)
// 			yVals[OR] = IloNumArray{env, params.nbSurgeries};
// 		for (IloInt surgery = 0; surgery < params.nbSurgeries; ++surgery)
// 			yVals[0][surgery] = 1;

// 		// Loop over values of lambda
// 		IloNum lambda;
// 		vector<IloNum> recourseValues{};
// 		for (lambda = 0; lambda < 30; lambda += 0.1)
// 		{
// 			// Load SAA method algorithm
// 			RecourseModel RecourseFunction{env, params};

// 			// Initialise L-shaped algorithm
// 			RecourseFunction.initialise(xVals, yVals, lambda);

// 			// Solve algorithm
// 			RecourseFunction.solve();
// 			IloNum value = RecourseFunction.getObjVal();
// 			recourseValues.push_back(value);
// 		}

// 		for (IloNum value: recourseValues)
// 			cout << value << ", ";

// 		cout << '\n';
// 	}
// 	catch (IloException& e) {
//    		cerr<< "Concert exception caught: " << e << '\n';
// 	}
// 	catch (...) {
//    		cerr << "Unknown exception caught" << '\n';
// 	}
// 	env.end();
// }