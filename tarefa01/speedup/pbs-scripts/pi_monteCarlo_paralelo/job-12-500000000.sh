#!/bin/bash

# Nome do job:
#PBS -N job-12-500000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./jobs-results/pi_monteCarlo_paralelo/job-12-500000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=12

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 12 /work/grupo04/project01/tarefa01/bin/pi_monteCarlo_paralelo 500000000

exit 0