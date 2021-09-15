#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, char **argv){

    double y;

    int x = 0;
    int qtd_coordenadas = atoi(argv[1]);
    char *filepath = argv[2];

    srand(time(NULL));

    FILE *file = fopen(filepath,"w+");

    fprintf(file, "%d\n", qtd_coordenadas);

    for(int i = 0; i < qtd_coordenadas;i++){
        y = 2.5 * x + 10;
        y += fRand(-5.0, 5.0);
        fprintf(file, "%d %f\n",x, y);
        x++;
    }

    fclose(file);

    return 0;
}