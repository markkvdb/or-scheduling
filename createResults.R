library(tidyverse)
library(reshape2)

experimentDir = "code_cpp/experiment output"
#### LOAD EXPERIMENTS ####

# Load all experiments
experimentNames = list.files(experimentDir, pattern = "^experiment[0-9]*$")

# First experiment to determine style of problem
experimentData = read_delim(paste(experimentDir, "/", experimentNames[1], sep=""), delim=" ")
experimentDataLong = melt(experimentData, id="id")

for (experimentName in experimentNames) {
  tempData = read_delim(paste(experimentDir, "/", experimentName, sep=""), delim=" ")
  experimentData = experimentData %>% bind_rows(tempData)
  tempDataMelt = melt(tempData, id="id")
  experimentDataLong = experimentDataLong %>%
    bind_rows(tempDataMelt)
}

#### TRANSFORM DATA ####
# Create new variables
experimentData = experimentData %>% 
  mutate(runTimeDiff = runTimeBender - runTimeSaa,
         TC = FSC + SSC) %>%
  arrange(id)

#### FIGURES ####
# Run time differences
create_figures = function(experimentData) {
  p = ggplot(experimentData) + geom_histogram(aes(x=runTimeDiff)) + theme_bw() +
    ggtitle("Histogram of the run-time difference between L-Shaped and SAA method") +
    xlab("Time (in ms)") + ylab("Frequency")
  print(p)
  
  # Total cost as a function of cv
  p = ggplot(filter(experimentData, id > 1 & id < 12)) + geom_line(aes(x=cv, y=TC)) + 
    ggtitle("Total cost vs. overtime cost") + theme_bw() +
    xlab("Overtime cost") + ylab("Total cost")
  print(p)
  
  # Lambda value
  p = ggplot(experimentData) + geom_line(aes(x=lambda, y=TC)) + theme_bw() +
    ggtitle("Value of lambda vs. total cost") +
    xlab("Lambda") + ylab("Total cost") + coord_fixed()
  print(p)
  
  # Variance for same problem
  p = ggplot(filter(experimentData, id > 51)) + geom_histogram(aes(x=runTimeDiff)) + 
    theme_bw() + ggtitle("Histogram of the run-time difference between L-Shaped and SAA method (different seeds)") +
    xlab("Time (in ms)") + ylab("Frequency")
  print(p)
  
  p = ggplot(filter(experimentData, id > 51)) + geom_histogram(aes(x=runTimeBender)) + 
    theme_bw() + ggtitle("Histogram of the run time of the L-Shaped method (different seeds)") +
    xlab("Time (in ms)") + ylab("Frequency")
  print(p)
  
  p = ggplot(filter(experimentData, id > 51)) + geom_histogram(aes(x=runTimeSaa)) + 
    theme_bw() + ggtitle("Histogram of the run time of the SAA method (different seeds)") +
    xlab("Time (in ms)") + ylab("Frequency")
  print(p)
  
  # eps1 and eps2 (NOTE: SAME SEED)
  p = ggplot(filter(experimentData, id >= 32 & id <= 41)) + geom_line(aes(x=eps1, y=lambda)) +
    theme_bw() + ggtitle("Lambda vs. eps1") +
    xlab("eps1") + ylab("Lambda")
  print(p)
  
  p = ggplot(filter(experimentData, id >= 42 & id <= 51)) + geom_line(aes(x=eps2, y=lambda)) +
    theme_bw() + ggtitle("Lambda vs. eps2") +
    xlab("eps2") + ylab("Lambda")
  print(p)
  
  p = ggplot(filter(experimentData, id >= 32 & id <= 41)) + geom_line(aes(x=eps1, y=SSC)) +
    theme_bw() + ggtitle("Second-stage cost vs. eps1") +
    xlab("eps1") + ylab("Second-stage cost")
  print(p)
  
  p = ggplot(filter(experimentData, id >= 42 & id <= 51)) + geom_line(aes(x=eps2, y=SSC)) +
    theme_bw() + ggtitle("Second-stage cost vs. eps2") +
    xlab("eps2") + ylab("Second-stage cost")
  print(p)
  
  # STD DEV (multiple seeds and calculate optimality gap)
  p = ggplot(filter(experimentData, id >= 12 & id <= 21)) + geom_line(aes(x=meanDuration, y=FSC)) +
    geom_line(aes(x=meanDuration, y=SSC)) + theme_bw() + 
    ggtitle("Costs vs. Mean surgery duration parameter") +
    xlab("Mean surgery duration (in minutes)") + ylab("Cost")
  print(p)
  
  p = ggplot(filter(experimentData, id >= 22 & id <= 31)) + geom_line(aes(x=stdDuration, y=FSC)) +
    geom_line(aes(x=stdDuration, y=SSC)) + theme_bw() + 
    ggtitle("Costs vs. Std. surgery duration parameter") +
    xlab("Std. surgery duration (in minutes)") + ylab("Cost")
  print(p)
  
  # Overtime
}

