#!/bin/bash

# Nome do job:
#PBS -N job-32-32000000

# Arquivo de saida:
#PBS -j oe
#PBS -o ./scalability/jobs-results/mpi_primos/job-32-32000000.out

# Tempo de execução do b
#PBS -l walltime=3:00:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=32

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 32 /work/grupo04/project01/tarefa04/bin/mpi_primos 32000000

exit 0
