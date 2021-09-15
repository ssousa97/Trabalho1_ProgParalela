#!/bin/bash

# Nome do job:
#PBS -N job-4-4000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./scalability/jobs-results/mpi_primos/job-4-4000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=4

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 4 /work/grupo04/project01/tarefa04/bin/mpi_primos 4000000

exit 0
