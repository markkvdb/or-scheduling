# File to create all the experiments that we feed into the 
# solver.
library(tidyverse)
# One line corresponds to one experiment
printExperiment = function(experimentVector) 
{
  fileConn = file("experiments.txt")
  write(experimentVector, fileConn)
  close(fileConn)
}

experimentTable = tibble(nbORs = 1, nbSurgeries = 1, cf = 1,
                         cv = 0.3, nbHours = 8.1, meanDuration = 1.1,
                         stdDuration = 1.1, mu = 1.1, sig = 1.1,
                         eps1 = 1.1, eps2 = 1.1, nbScenarios = 1, seed = 1)
experimentTable = experimentTable[-1,]


#### Base experiment ####
baseExperiment = tibble(
  nbORs 			  = 5,
  nbSurgeries   = nbORs,
  cf 				    = 1,
  cv 				    = 0.13,
  nbHours 		  = 8,
  meanDuration 	= 200,
  stdDuration 	= 12.12^2,
  mu 				    = log(meanDuration^2 / sqrt(stdDuration + meanDuration^2)),
  sig 			    = sqrt(log(stdDuration / meanDuration^2 + 1)),
  eps1 			    = 0.1,
  eps2 			    = 0.1,
  nbScenarios 	= 200,
  seed 			    = 1
)

experimentTable = baseExperiment

#### Define all experiments ####
createExperiments = function(variableName, values) {
  newExperiments = baseExperiment[rep(1, length(values)),]
  newExperiments[[variableName]] = values 
  
  if (variableName %in% c("meanDuration", "stdDuration")) {
    newExperiments[["mu"]] = log(newExperiments[["meanDuration"]]^2 / sqrt(newExperiments[["stdDuration"]] + newExperiments[["meanDuration"]]^2))
    newExperiments[["sig"]] = sqrt(log(newExperiments[["stdDuration"]] / newExperiments[["meanDuration"]]^2 + 1))
  } 
  
  return(newExperiments)
}

gridSize = 10
# # Alter the overtime costs
# cv_options = seq(0.05, 0.5, length.out = gridSize)
# experimentTable = experimentTable %>%
#   bind_rows(createExperiments("cv", cv_options))
# 
# # Alter meanDuration
# meanDur = seq(100, 300, length.out = gridSize)
# experimentTable = experimentTable %>%
#   bind_rows(createExperiments("meanDuration", meanDur))
# 
# # Alter the standard deviation
# stdDur = seq(5^2, 20^2, length.out = gridSize)
# experimentTable = experimentTable %>%
#   bind_rows(createExperiments("stdDuration", stdDur))

# Eps1
eps1_options = seq(0, 1, length.out = gridSize)
experimentTable = experimentTable %>%
  bind_rows(createExperiments("eps1", eps1_options))

# Eps2
eps2_options = seq(0, baseExperiment$nbScenarios, length.out = gridSize)
experimentTable = experimentTable %>%
  bind_rows(createExperiments("eps2", eps2_options))

# Seed
seed_options = seq(1, 20, by=1)
experimentTable = experimentTable %>%
  bind_rows(createExperiments("seed", seed_options))

#### Output the experiments table ####
write.table(experimentTable, file="experiments.txt", row.names=FALSE, col.names=FALSE)