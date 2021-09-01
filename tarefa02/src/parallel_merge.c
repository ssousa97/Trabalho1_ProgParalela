#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char **argv){

    /*Inicializa o array de elementos com a quantidade de itens passados*/
    int n = atoi(argv[1]);
    int *original_array = malloc(n * sizeof(int));
    
    srand(time(NULL));

    for (int i  = 0; i < n; i++)
        original_array[i] = rand() % n;

    /*Iniciar MPI*/
    int rank;
    int processes;

    MPI_INIT(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);

    /*Tamanho do bloco que será alocado para cada processo*/
    int size = n / processes;

    /*Enviaa os sub-arrays com tamanho size para cada processo*/
    int *sub_array = malloc(size * sizeof(int));
    MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);

    /*Executa o mergeSort no bloco do array*/
    int *tmp_array = malloc(size * sizeof(int));
    mergeSort(sub_array, tmp_array, 0, (size - 1));

    /*Coleta todos os sub-arrays ordenados*/
    int *sorted = NULL;
    if (rank == 0)
        sorted = malloc(n * sizeof(int));

    MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);

    /*Executa o mergeSort final no array coletado*/
    if (rank == 0)
    {

        int *other_array = malloc(n * sizeof(int));
        mergeSort(sorted, other_array, 0, (n - 1));

        printf("Array ordenado: ");
        for (int i = 0; i < n; i++)
            printf("%d ", sorted[i]);

        free(sorted);
        free(other_array);
    }

    free(original_array);
    free(sub_array);
    free(tmp_array);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}

void merge(int *a, int *b, int l, int m, int r){

    int h, i, j, k;
    h = l;
    i = l;
    j = m + 1;

    while ((h <= m) && (j <= r)){

        if (a[h] <= a[j]){

            b[i] = a[h];
            h++;

        } else {

            b[i] = a[j];
            j++;
        }

        i++;
    }

    if (m < h){

        for (k = j; k <= r; k++){

            b[i] = a[k];
            i++;
        }
    }

    else{

        for (k = h; k <= m; k++){

            b[i] = a[k];
            i++;
        }
    }

    for (k = l; k <= r; k++){

        a[k] = b[k];
    }
}

void mergeSort(int *a, int *b, int l, int r){

    int m;

    if (l < r){
        m = (l + r) / 2;
        mergeSort(a, b, l, m);
        mergeSort(a, b, (m + 1), r);
        merge(a, b, l, m, r);
    }
}