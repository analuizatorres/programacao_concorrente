#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int num_steps = 100000000;
    double step;
    int i;
    double x, pi = 0, sum = 0.0;
    double inicioSeq, fimSeq;
    
    //inicio sequencial
    step = 1.0/(double)num_steps;

    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0/(1.0 + x*x);
    }
    pi = step * sum;
    printf("pi sequencial:%f \n", pi);

    // MPI INIT

    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
    double pi_total, pi_parcial;
    sum = 0;
    x = 0;
    i = 0;
    step = 0;

    step = 1.0 / (double)num_steps;

    for (i = rank; i <= num_steps; i += nprocs)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi_parcial = step * sum;

    MPI_Reduce(&pi_parcial, &pi_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Valor de pi: %.10f\n", pi_total);
    }

    // MPI CLOSURE

    MPI_Finalize();
}