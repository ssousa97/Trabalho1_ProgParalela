#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(){

    double y;

    int x = 0;
    int qtd_coordenadas = 10;

    srand(time(NULL));

    FILE *file = fopen("./dados.txt","w+");

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