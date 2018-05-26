#!/bin/bash

#SBATCH --job-name=NURSE_MIP
#SBATCH --time=04:00:00
#SBATCH --cpus-per-task=1
#SBATCH --mem=16000

# Load modules
module load GCC/6.4.0-2.28
module load binutils/2.28 
module load R/3.4.2-foss-2016a-X11-20160819

# Run the code
cd code_cpp
make
./lshaped
