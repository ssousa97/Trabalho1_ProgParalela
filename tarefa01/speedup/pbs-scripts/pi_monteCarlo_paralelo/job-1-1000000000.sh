#!/bin/bash

# Nome do job:
#PBS -N job-1-1000000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./jobs-results/pi_monteCarlo_paralelo/job-1-1000000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=1

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 1 /work/grupo04/project01/tarefa01/bin/pi_monteCarlo_paralelo 1000000000

exit 0
