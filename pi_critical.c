#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
int num_steps = 100000000;
    double step;
    int i;
    double x, pi = 0, sum = 0.0;
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
    printf("pi sequencial:%f \n", pi);
    
    //fim sequencial
    fimSeq = omp_get_wtime();

    pi = 0;
    double inicioParal, fimParal;
    inicioParal = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        double x, sum = 0.0;
        #pragma omp for
        for (i = 0; i < num_steps; i++)
        {
            x = (i + 0.5) * step;
            sum = sum + 4.0/(1.0 + x*x);
        }
        
        #pragma omp critical
            {
                pi += step * sum;
            }
    }
    printf("pi paralelo:%f \n", pi);
    fimParal = omp_get_wtime();

    double tempoParal = fimParal - inicioParal;
    double tempoSeq = fimSeq - inicioSeq;

    double speedUp = tempoSeq/tempoParal;

    printf("tempo de execução do sequencial: %f \n", tempoSeq);
    printf("tempo de execução do paralelo: %f \n", tempoParal);

    printf("SpeedUp: %f \n", speedUp);

}

