# MPI

## O que é?

primeiramente, o modelo de Message Passing é um
conjunto de processos que possuem acesso
à memória local. As informações são
enviadas da memória local do processo
para a memória local do processo remoto.

MPI é uma biblioteca de Message Passing
desenvolvida para ambientes de memória distribuída, máquinas
paralelas massivas, NOWs (network of workstations) e redes heterogêneas.

* É uma biblioteca de rotina que fornece
funcionalidade básica para que os processos se
comuniquem.

* O paralelismo é explicito

Todo programa MPI escrito em C tem que inicializar
com a chamada à biblioteca : #include "mpi.h"

    #include mpi.h

Um programa MPI apresenta quatro funções básicas:
* MPI_Init
* MPI_Finalize
* MPI_Comm_size
* MPI_Comm_rank

---
## Aplicações

O objetivo de MPI é prover um amplo padrão para escrever programas com passagem de mensagens de forma prática, portátil, eficiente e flexível. MPI não é um IEEE ou um padrão ISO, mas chega a ser um padrão industrial para o desenvolvimento de programas com troca de mensagens.

---
## Implementações

implementação de um 'hello world' utilizando as regras e conceitos da MPI, uma delas sendo a diferenciação das tarefas através de rank. 

    # include < mpi .h >
    # include < stdio .h >
    # define ROOT 0
    int main (int argc , char ** argv ){

    int rank , size , nlen;
    char name [ MPI_MAX_PROCESSOR_NAME ];
    MPI_Init (& argc , & argv);
    MPI_Comm_rank ( MPI_COMM_WORLD , & rank);
    MPI_Comm_size ( MPI_COMM_WORLD , & size);
    MPI_Get_processor_name ( name , & nlen);

    if ( rank == ROOT ){
    printf (" Hello world ! I am process %d out of %d on %s\n " ,rank , size , name );
    } 
    else{
    printf (" Alo mundo ! Eu sou o processo %d de %d em % s\n" ,
    rank , size , name );
    }

    MPI_Finalize () ;
    return 0;
    }





