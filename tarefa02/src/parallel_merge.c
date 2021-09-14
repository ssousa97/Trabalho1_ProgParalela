#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char **argv){

    int n = atoi(argv[1]), meu_ranque, num_procs;
    int *original_array, *sub_array, *gathered_array, *sorted_array, *sorted_sub_array, *sendcounts, *displacements;
    double tempo_inicial, tempo_final;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* Inicializando sendcounts e displacements para serem posteriormente usados em MPI_Scatterv */
    int rem = n % num_procs;
    int chunk = n / num_procs;
    int sum = 0;

    sendcounts = malloc(num_procs * sizeof(int));
    displacements = malloc(num_procs * sizeof(int));

    for (int i = 0; i < num_procs; i++) {
        sendcounts[i] = chunk;
        if (rem > 0) {
            sendcounts[i]++;
            rem--;
        }

        displacements[i] = sum;
        sum += sendcounts[i];
    }

    sub_array = malloc(2 * chunk * sizeof(int));

    if (meu_ranque == 0)
    {
        srand(time(NULL));

        original_array = malloc(n * sizeof(int));

        for (int i  = 0; i < n; i++) {
            original_array[i] = rand() % n;
        }

        tempo_inicial = MPI_Wtime();
    }

    /* Envia os sub-arrays para cada processo*/
    MPI_Scatterv(original_array, sendcounts, displacements, MPI_INT, sub_array, 2*chunk, MPI_INT, 0, MPI_COMM_WORLD);

    /*Executa o mergeSort no bloco do array*/
    sorted_sub_array = malloc(sendcounts[meu_ranque] * sizeof(int));
    mergeSort(sub_array, sorted_sub_array, 0, sendcounts[meu_ranque] - 1);

    /*Coleta todos os sub-arrays ordenados*/
    if (meu_ranque == 0)
        gathered_array = malloc(n * sizeof(int));

    MPI_Gatherv(sub_array, sendcounts[meu_ranque], MPI_INT, gathered_array, sendcounts, displacements, MPI_INT, 0, MPI_COMM_WORLD);

    /* Última etapa da ordenação */
    if (meu_ranque == 0)
    {
        sorted_array = malloc(n * sizeof(int));

        /*Inicializando ponteiros para cada subvetor*/
        int *pointers = malloc(num_procs * sizeof(int));
        int argmin_process;

        for (int p = 0; p < num_procs; p++) {

            pointers[p] = displacements[p];
        }

        for (int i = 0; i < n; i++) {
            for (int p = 0; p < num_procs; p++) {
                if (pointers[p] != -1) {
                    argmin_process = p;
                    break;
                } 
            }

            for (int p = argmin_process; p < num_procs; p++) {
                if (gathered_array[pointers[p]] < gathered_array[pointers[argmin_process]] && pointers[p] != -1) {
                    argmin_process = p;
                }
            }

            sorted_array[i] = gathered_array[pointers[argmin_process]];
            
            pointers[argmin_process]++;
            
            if (pointers[argmin_process] >= (displacements[argmin_process] + sendcounts[argmin_process])) {
                pointers[argmin_process] = -1;
            }
        }

        tempo_final = MPI_Wtime();
        /*
        printf("Array original: ");
        for (int i = 0; i < n; i++)
            printf("%d ", original_array[i]);

        printf("\nSubarrays ordenados: ");
        for (int i = 0; i < n; i++)
            printf("%d ", gathered_array[i]);

        printf("\nArray ordenado: ");
        for (int i = 0; i < n; i++)
            printf("%d ", sorted_array[i]);

        printf("\n");
        */
        printf("Array ordenado em : %.4f segundos\n", tempo_final - tempo_inicial);

        free(sorted_array);
        free(gathered_array);
        free(original_array);
        free(pointers);
    }

    free(sendcounts);
    free(displacements);
    free(sub_array);
    free(sorted_sub_array);

    //MPI_Barrier(MPI_COMM_WORLD);
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