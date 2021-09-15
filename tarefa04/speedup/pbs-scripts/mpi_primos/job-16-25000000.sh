#!/bin/bash

# Nome do job:
#PBS -N job-16-25000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./jobs-results/mpi_primos/job-16-25000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=16

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 16 /work/grupo04/project01/tarefa04/bin/mpi_primos 25000000

exit 0
