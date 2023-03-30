//media de um vetor
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TAMANHO 50
//#define MAX 500000000

int main(){
    time_t t;
    srand((unsigned)time(&t));

    double *vetor;
    vetor = malloc(TAMANHO*sizeof(double));
    int i;
    for (i = 0; i < TAMANHO; i++)
    {
        double num = (rand() / (float) RAND_MAX);
        vetor[i] = num;
    }

    //inicio sequecial
    double inicioSeq, fimSeq;
    double variavel = 0;
    inicioSeq = omp_get_wtime();
       
    for (i = 0;i<TAMANHO;i++){
        variavel = variavel + vetor[i];
        // printf("%d ", vetor[i]);
    } 

    fimSeq = omp_get_wtime();

    double tempoSeq = fimSeq - inicioSeq;

    printf("media Sequencial: %d \n", variavel/TAMANHO);
    //fim sequencial

    double inicioParal, fimParal;
    variavel = 0;
    inicioParal = omp_get_wtime();
    //inicio do paralelo 
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for reduction (+:variavel)
            for (i = 0;i<TAMANHO;i++){
                variavel = variavel + vetor[i];
                // printf("%d ", vetor[i]);
            } 
    }
    //fim do paralelo

    fimParal = omp_get_wtime();

    double tempoParal = fimParal - inicioParal;
    double speedUp = tempoSeq/tempoParal;

    printf("media Paralela: %d \n", variavel/TAMANHO);

    printf("tempo de execução do sequencial: %f \n", tempoSeq);
    printf("tempo de execução do paralelo: %f \n", tempoParal);
    printf("SpeedUp: %f \n", speedUp);

}
