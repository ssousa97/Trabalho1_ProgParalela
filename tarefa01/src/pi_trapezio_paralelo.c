#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int meu_ranque, num_procs, raiz = 0;
    long int n = 1000000000;
    double t0, t1, global_pi, local_pi = 0;

    if (argc < 2) {
        	printf("Valor inválido! Entre com um valor para o parâmetro N\n");
       	 	return 0;
    } else {
        n = strtol(argv[1], (char **) NULL, 10);
    }

    MPI_Init(&argc, &argv);

    t0 = MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);

    if (meu_ranque == raiz) {
        printf("n = %ld \n", n);
    }

    for (int i = meu_ranque; i < n; i += num_procs) {
        double t = (double) ((i+0.5)/n);
        local_pi += 4.0/(1.0+t*t);
    }

    MPI_Reduce(&local_pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, raiz, MPI_COMM_WORLD);

    if (meu_ranque == raiz) {
        global_pi = global_pi/n;
        t1 = MPI_Wtime();
        printf("pi = %.25f \n", global_pi);
        printf("The program executed in %.4f seconds.\n", t1-t0);
    }

    MPI_Finalize();

    return 0;
}