#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
    int num = 100000000;
    long int sum = 0;
    long int sum2 = 0;
    double inicioSeq, fimSeq;

    inicioSeq = omp_get_wtime();
    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
        {
            sum = sum + i;
        }
        
    }
    printf("sequencial: %d\n", sum);
    fimSeq = omp_get_wtime();

    double inicioCrit, fimCrit, inicioR, fimR, inicioS, fimS;
    inicioCrit = omp_get_wtime();
    #pragma omp parallel num_threads(4) private (sum2)
    {
        sum2 = 0;
        #pragma omp for
            for (int i = 1; i <= num; i++)
            {
                {
                    if (num % i == 0)
                    {
                        sum2 = sum2 + i;
                    }
                }
            }
            #pragma omp critical
            {
                sum2 += sum;
            }
    }
    printf("paralelo critical: %d\n", sum);
    fimCrit = omp_get_wtime();

    inicioR = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        sum = 0;
        #pragma omp for reduction (+:sum)
            for (int i = 1; i <= num; i++)
            {
                if (num % i == 0)
                {
                    sum = sum + i;
                }
            
            }
    }
    printf("paralelo Reduction: %d\n", sum);
    fimR = omp_get_wtime();

    inicioS = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        sum = 0;
        #pragma omp for schedule(static)
            for (int i = 1; i <= num; i++)
            {
                {
                    if (num % i == 0)
                    {
                        sum = sum + i;
                    }
                }
            }
            /*#pragma omp critical
            {
                sum2 += sum;
            }*/
    }
    printf("paralelo static: %d\n\n", sum);
    fimS = omp_get_wtime();

    double tempoR = fimR - inicioR;
    double tempoCrit = fimCrit - inicioCrit;
    double tempoS = fimS - inicioS;
    double tempoSeq = fimSeq - inicioSeq;

    double speedUp_crit = tempoSeq/tempoCrit;
    double speedUp_R = tempoSeq/tempoR;
    double speedUp_S = tempoSeq/tempoS;

    printf("tempo de execução do sequencial: %f \n", tempoSeq);
    printf("tempo de execução do paralelo com Critical: %f \n", tempoCrit);
    printf("tempo de execução do paralelo com Reduction: %f \n", tempoR);
    printf("tempo de execução do paralelo com Static: %f \n\n", tempoS);

    printf("SpeedUp comparando com Critical: %f \n", speedUp_crit);
    printf("SpeedUp comparando com Reduction: %f \n", speedUp_R);
    printf("SpeedUp comparando com Static: %f \n", speedUp_S);

    
}