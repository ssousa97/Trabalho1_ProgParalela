#!/bin/bash

# Nome do job:
#PBS -N job-2-10000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./speedup/jobs-results/parallel_merge/job-2-10000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=2

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 2 /work/grupo04/project01/tarefa02/bin/parallel_merge 10000000

exit 0
