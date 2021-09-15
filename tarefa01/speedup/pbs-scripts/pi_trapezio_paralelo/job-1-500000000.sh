#!/bin/bash

# Nome do job:
#PBS -N job-1-500000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./jobs-results/pi_trapezio_paralelo/job-1-500000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=1

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 1 /work/grupo04/project01/tarefa01/bin/pi_trapezio_paralelo 500000000

exit 0
