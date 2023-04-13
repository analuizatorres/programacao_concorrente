#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX 100
#define TAMANHO 1000000

//int *gerar_vetor_inteiro(int n);
//void mostrar_vetor_inteiro(int *v,int tamanho);

int main() {
    //srand(time(NULL));
    srand(time(NULL));
    int *v;
    v = (int *)malloc(sizeof(int) * TAMANHO);
    int count = 0;
    double inicioSeq, fimSeq, inicioP, fimP;

    for (int i = 0; i < TAMANHO; i++)
    {
        int num = rand() % MAX;
        v[i] = num;
    }

    //inicio do sequencial
    inicioSeq = omp_get_wtime();
    int x = 10;

    for (int i = 0; i < TAMANHO; i++)
    {
        if (v[i] == x)
        {
            count++;
        }
        
    }
    printf("sequencial: o X apareceu: %d \n" , count);
    
    fimSeq = omp_get_wtime();

    //inicio paralelo
    inicioP = omp_get_wtime();
    count = 0;
    #pragma omp parallel num_threads(4)
    {   
        #pragma omp for reduction(+:count)
        for (int i = 0; i < TAMANHO; i++)
        {
            if (v[i] == x)
            {
                count++;
            } 
        }  
    }
    printf("paralelo: o X apareceu: %d \n \n" , count);
    
    fimP = omp_get_wtime();
    free(v);

    double tempoP = fimP - inicioP;
    double tempoSeq = fimSeq - inicioSeq;

    double speedUp = tempoSeq/tempoP;

    printf("tempo de execução do sequencial: %f \n", tempoSeq);
    printf("tempo de execução do paralelo: %f \n \n", tempoP);

    printf("SpeedUp: %f \n", speedUp);
    printf("Eficiencia: %f", speedUp/4);
}
