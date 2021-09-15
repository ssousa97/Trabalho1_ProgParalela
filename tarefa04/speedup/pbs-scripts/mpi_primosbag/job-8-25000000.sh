#!/bin/bash

# Nome do job:
#PBS -N job-8-25000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./jobs-results/mpi_primosbag/job-8-25000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=8

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 8 /work/grupo04/project01/tarefa04/bin/mpi_primosbag 25000000

exit 0
