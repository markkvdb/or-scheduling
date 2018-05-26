#!/bin/bash

Rscript createExperiment.R

cd code_cpp
make && ./lshaped