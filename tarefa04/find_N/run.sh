# Definindo os parametros que serao avaliados
N_values="10000000 50000000 100000000 200000000 1000000000"
programs="mpi_primos mpi_primosbag"

num_experiments=$(($(wc -w <<< ${N_values})*$(wc -w <<< ${programs})))
cur_experiment=1

# Definindo algumas constantes
PBS_SCRIPTS_DIR="./pbs-scripts"
JOBS_RESULTS_DIR="./jobs-results"

# Removendo diretorios de execucoes anteriores
rm -r ${PBS_SCRIPTS_DIR}
rm -r ${JOBS_RESULTS_DIR}

# Construindo os diretorios para esta execucao
mkdir -p ${PBS_SCRIPTS_DIR}
mkdir -p ${JOBS_RESULTS_DIR}

for program in ${programs}; do

    # Compilando o programa
    mpicc ./src/${program}.c -o ./bin/${program} -lm

    # Criando os diretórios para o programa
    mkdir ${PBS_SCRIPTS_DIR}/${program}
    mkdir ${JOBS_RESULTS_DIR}/${program}

    for N in ${N_values}; do

        echo "Experimento ${cur_experiment} de ${num_experiments}";

        name="job-16-${N}"

        # Gerando o script para submissao do job
        script="#!/bin/bash

# Nome do job:
#PBS -N ${name}

# Arquivo de saida:
#PBS -j oe
#PBS -o ${JOBS_RESULTS_DIR}/${program}/${name}.out

# Tempo de execução do b
#PBS -l walltime=0:05:00

# Quantidade de CPUs para uso:
#PBS -l ncpus=16

# Programa de execucao
/usr/lib64/openmpi/bin/mpirun -np 16 /work/grupo04/project01/tarefa04/bin/${program} ${N}

exit 0"

        echo "${script}" >> "${PBS_SCRIPTS_DIR}/${program}/${name}.sh"

        # Submetendo job

        qsub ${PBS_SCRIPTS_DIR}/${program}/${name}.sh

        read -p "Pressione qualquer tecla para submeter o proximo job..."
	cur_experiment=$((cur_experiment+1))
    done
done
