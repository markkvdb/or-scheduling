#ifndef INCLUDED_EXPERIMENTS_
#define INCLUDED_EXPERIMENTS_

#include "../experiment/experiment.h"
#include <vector>
#include <string>

class Experiments
{
   int d_count;
   std::vector<std::string> d_experimentStrings;
   std::vector<Experiment> 	d_experiments;

public:
   Experiments() = delete;
   Experiments(std::string fileName);

   void solve();
};

#endif