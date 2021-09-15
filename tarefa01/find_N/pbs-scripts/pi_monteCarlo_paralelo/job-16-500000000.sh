#!/bin/bash

# Nome do job:
#PBS -N job-16-500000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./find_N/jobs-results/pi_monteCarlo_paralelo/job-16-500000000.out

# Tempo de execução do b
#PBS -l walltime=0:04:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=16

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 16 /work/grupo04/project01/tarefa01/bin/pi_monteCarlo_paralelo 500000000

exit 0
