#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//calcular a aporvimação do valor de pi

int main(){
    int num_steps = 100000000;
    double step;
    int i;
    double x, pi, sum = 0.0;
    double inicioSeq, fimSeq;
    
    inicioSeq = omp_get_wtime();
    //inicio sequencial
    step = 1.0/(double)num_steps;

    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0/(1.0 + x*x);
    }
    pi = step * sum;
    //fim sequencial
    fimSeq = omp_get_wtime();

    
    double inicioParal, fimParal;
    inicioParal = omp_get_wtime();
    //inicio do paralelo
    #pragma omp parallel private(x) num_threads(3)
    {
        #pragma omp for reduction(+:sum)
        for (i = 0; i < num_steps; i++)
        {
            x = (i + 0.5) * step;
            sum = sum + 4.0/(1.0 + x*x);
        }
    }
    //fim do paralelo
    pi = step * sum;

    fimParal = omp_get_wtime();

    double tempoParal = fimParal - inicioParal;
    double tempoSeq = fimSeq - inicioSeq;

    double speedUp = tempoSeq/tempoParal;

    printf("tempo de execução do sequencial: %f \n", tempoSeq);
    printf("tempo de execução do paralelo: %f \n", tempoParal);

    printf("SpeedUp: %f \n", speedUp);






}