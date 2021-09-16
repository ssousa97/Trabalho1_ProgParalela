#!/bin/bash

# Nome do job:
#PBS -N job-1-1000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./jobs-results/minimos_quadrados_paralelo/job-1-1000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=1

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 1 /work/grupo04/project01/tarefa03/bin/minimos_quadrados_paralelo 1000000 /work/grupo04/project01/tarefa03/data/dados.txt

exit 0
