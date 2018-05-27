#include "recoursemodel.ih"

void RecourseModel::createConstraints()
{
    for (IloInt scen = 0; scen != d_params.nbScenarios; ++scen)
    {
        // Add constraints related to the minimum overtime
        for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
        {
            if (d_integer) 
                d_model.add(60 * d_o[scen][OR] >= IloScalProd(d_durationSample[scen], d_yVals[OR]) - (60 * d_params.nbHours * d_xVals[OR]));
            else 
                d_model.add(60 * d_o[scen][OR] >= IloScalProd(d_durationSample[scen], d_yVals[OR]) - (60 * d_params.nbHours * d_xVals[OR]) + 30);
        }
        d_model.add(d_uPlus[scen] - d_uMinus[scen] == d_params.cf * IloSum(d_xVals) + d_params.cv * IloSum(d_o[scen]) - d_lVal);
    }

//    for (IloInt scen = 0; scen < d_params.nbScenarios; ++scen)
//    {
//       // Add constraints related to the minimum overtime
//       for (IloInt OR = 0; OR < d_params.nbORs; ++OR)
//       {
//          if (d_integer)
//          {
//             d_overtimeConstraints[scen][OR] = IloRange(d_env, 0, 60 * d_o[scen][OR] - (IloScalProd(d_durationSample[scen], d_yVals[OR]) - (60 * d_params.nbHours * d_xVals[OR])));
//             d_model.add(d_overtimeConstraints[scen][OR]);
//          }
//          else
//          {
//             d_overtimeConstraints[scen][OR] = IloRange(d_env, 0, 60 * d_o[scen][OR] - (IloScalProd(d_durationSample[scen], d_yVals[OR]) - (60 * d_params.nbHours * d_xVals[OR]) + 30));
//             d_model.add(d_overtimeConstraints[scen][OR]);
//          }

//       }
//       d_minmaxConstraints[scen] = IloRange(d_env, 0, d_uPlus[scen] - d_uMinus[scen] - (d_params.cf * IloSum(d_xVals) + d_params.cv * IloSum(d_o[scen]) - d_lVal), 0);
//       d_model.add(d_minmaxConstraints[scen]);
//    }
}