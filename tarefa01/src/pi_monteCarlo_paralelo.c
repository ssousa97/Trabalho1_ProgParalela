#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SEED time(NULL)

int main(int argc, char *argv[]) {

    int meu_ranque, num_procs, global_count, local_count = 0, raiz = 0;
    long int n = 1000000000;
    double x,y,z,pi,t0,t1;

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

    for(int i = meu_ranque; i < n; i += num_procs) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;
        
        if( z <= 1 ) {
            local_count++;
        }
    }

    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, raiz, MPI_COMM_WORLD);

    if (meu_ranque == raiz) {
        pi = (double) global_count / n * 4;
        t1 = MPI_Wtime();
        printf("pi = %.25f \n", pi);
        printf("The program executed in %.4f seconds.\n", t1-t0);
    }

    MPI_Finalize();

    return 0;
}