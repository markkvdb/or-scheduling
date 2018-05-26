// // -------------------------------------------------------------- -*- C++ -*-
// // File: iloadmipex1.cpp
// // Version 12.8.0
// // --------------------------------------------------------------------------
// // Licensed Materials - Property of IBM
// // 5725-A06 5725-A29 5724-Y48 5724-Y49 5724-Y54 5724-Y55 5655-Y21
// // Copyright IBM Corporation 2000, 2017. All Rights Reserved.
// //
// // US Government Users Restricted Rights - Use, duplication or
// // disclosure restricted by GSA ADP Schedule Contract with
// // IBM Corp.
// // --------------------------------------------------------------------------
// //
// // iloadmipex1.cpp -  Use the node and branch callbacks
// //                    for optimizing a MIP problem
// //
// // To run this example, command line arguments are required.
// // i.e.,   iloadmipex1   filename
// //
// // Example:
// //     iloadmipex1  example.mps
// //

// #include <ilcplex/ilocplex.h>
// #include <cmath>
// #include <string>
// #include <sstream>
// #include <tuple>
// #include <random>

// // Following macro ensures we can use the STL
// ILOSTLBEGIN

// // Declare parameters
// IloInt nbORs, nbSurgeries, nbScenarios, nbHours;
// IloNum cf, cv, meanDuration, stdDuration, mu, sig, eps1, eps2;

// // Typedefs
// typedef IloArray<IloNumVarArray> IloNumVarMatrix;

// void 
// defineData(IloEnv env) 
// {
//    // Parameters for the problem
//    nbORs = 15;
//    nbSurgeries = nbORs;

//    // Costs
//    cf = 1;
//    cv = 0.033;
//    nbHours = 8;

//    // Uncertainty
//    meanDuration = 90;
//    stdDuration = pow(12.12, 2);

//    mu = log(pow(meanDuration, 2) / sqrt(stdDuration + pow(meanDuration, 2)));
//    sig = sqrt(log(stdDuration / pow(meanDuration, 2) + 1));

//    eps1 = 0.1;
//    eps2 = 0.1;

//    // Number of scenarios for the problem
//    nbScenarios = 200;
// } // END define_data

// std::tuple<IloNumVarArray, IloNumVarMatrix, IloNumVar> 
// createFirstStageVariables(IloEnv env)
// {
//    // Declare variables
//    IloNumVarArray x(env, nbORs, 0, 1, ILOINT);
//    IloNumVarMatrix y(env, nbORs);
//    for (IloInt idx = 0; idx < nbORs; ++idx)
//       y[idx] = IloNumVarArray(env, nbSurgeries, 0, 1, ILOINT);
//    IloNumVar l(env, 0, IloInfinity);

//    // Set names
//    std::ostringstream oss;
//    for (IloInt j = 0; j < nbORs; ++j)
//    {
//       oss << "x_" << j;
//       x[j].setName(oss.str().c_str());
//       oss.clear();
//       oss.str("");
//       for (IloInt i = 0; i < nbSurgeries; ++i)
//       {
//          oss << "y_" << i << j;
//          y[j][i].setName(oss.str().c_str());
//          oss.clear();
//          oss.str("");
//       }
//    }
//    l.setName("l");

//    return make_tuple(x, y, l);
// } // END createFirstStageVariables

// void 
// createFirstStageConstraints(IloEnv env, IloModel masterModel, IloNumVarArray x,
//                                  IloNumVarMatrix y)
// {
//    std::ostringstream oss;
//    // Surgery should be assigned to open OR
//    for (IloInt operatingRoom = 0; operatingRoom < nbORs; ++operatingRoom)
//       for (IloInt surgery = 0; surgery < nbSurgeries; ++surgery)
//          masterModel.add(y[operatingRoom][surgery] <= x[operatingRoom]);

//    // All surgeries should be assigned to one OR
//    for (IloInt surgery = 0; surgery < nbSurgeries; ++surgery) 
//    {
//       IloExpr e1(env);
//       for (IloInt OR = 0; OR < nbORs; ++OR)
//          e1 += y[OR][surgery];

//       masterModel.add(e1 == 1);
//    }


//    // Symmetry breaking constraint for the x variables
//    for (IloInt OR = 0; OR < (nbORs-1); ++OR)
//       masterModel.add(x[OR] >= x[OR+1]);

//    // Symmetry breaking (7) for y
//    for (IloInt i = 0; i < nbSurgeries; ++i)
//    {
//       IloExpr e1(env);
//       for (IloInt j = 0; j <= i; ++j)
//          e1 += y[j][i];

//       masterModel.add(e1 == 1);
//    }

//    // Symmetry breaking 9
//    for (IloInt j = 1; j < nbORs; ++j)
//    {
//       for (IloInt i = j; i < nbSurgeries; ++i)
//       {
//          IloExpr e_left(env);
//          IloExpr e_right(env);

//          for (IloInt v = j; v <= min(i, nbORs); ++v)
//             e_left += y[v][i];
//          for (IloInt u = j - 1; u <= (i-1); ++u)
//             e_right += y[j-1][u];

//          IloConstraint c(e_left <= e_right);
//          oss << "(" << i << "," << j << ")";
//          c.setName(oss.str().c_str());
//          oss.clear();
//          oss.str("");
//          masterModel.add(c);
//       }
//    }
// } // END createFirstStageConstraints

// std::tuple<IloModel, IloNumVarArray, IloNumVarMatrix, IloNumVar> 
// createMasterModel(IloEnv env) 
// {
//    // Declare model
//    IloModel masterModel(env);

//    // Declare variables
//    IloNumVarArray x;
//    IloNumVarMatrix y;
//    IloNumVar l;
//    tie(x, y, l) = createFirstStageVariables(env);

//    // Add constraints
//    createFirstStageConstraints(env, masterModel, x, y);

//    // Add objective
//    masterModel.add(IloMinimize(env, cf * IloSum(x)));

//    return make_tuple(masterModel, x, y, l);
// } // END createMasterModel

// IloNumArray2 
// createDurationSample(IloEnv env, IloNum sampleSize)
// {
//    // Set-up the random number generator
//    default_random_engine generator;
//    lognormal_distribution<double> distribution(mu, sig);

//    // Saved
//    IloNumArray2 sample(env, sampleSize);

//    for (IloNum scen = 0; scen < sampleSize; ++scen)
//    {
//       sample[scen] = IloNumArray(env, nbSurgeries);
//       for (IloNum surgery = 0; surgery < nbSurgeries; ++surgery)
//       {
//          sample[scen][surgery] = distribution(generator);
//       }
//       cout << sample[scen] << '\n';
//    }

//    return sample;
// }

// void benderMethod(IloEnv env, IloModel masterModel)
// {
//    // Relax x variables as continuous


//    // Add eta variable to the problem as a lb for Q(x)

//    // Set objective

//    // Add optimality constraint

//    // Iteratively solve the master problem and add optimality cuts if needed
// }


// int
// main (int argc, char **argv)
// {
//    IloEnv env;
//    defineData(env);

//    try {
//       // Initialise the model
//       IloModel model;

//       // Initialise the first-stage variables
//       IloNumVarArray x;
//       IloNumVarMatrix y;
//       IloNumVar l;

//       // Retrieve the master problem and the corresponding first-stage variables
//       tie(model, x, y, l) = createMasterModel(env);

//       // Set-up algorithm
//       IloCplex cplex(env);

//       // Add the model to the algorithm and solve it
//       cplex.extract(model);
//       cplex.solve();

//       IloNumArray vals(env);

//       env.out() << "Solution status = " << cplex.getStatus() << endl;
//       env.out() << "Solution value  = " << cplex.getObjValue() << endl;

//       cplex.exportModel("lpex1.lp");
//    }
//    catch (IloException& e) {
//       cerr << "Concert exception caught: " << e << endl;
//    }
//    catch (...) {
//       cerr << "Unknown exception caught" << endl;
//    }
//    env.end();

//    return 0;
// }  // END main

