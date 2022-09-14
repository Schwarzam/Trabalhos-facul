
#include <pthread.h>
#include <iostream>

//Existiam variáveis faltando na funcao dada, assim assumi que seriam variaveis globais
const int n = 4, m = 4; //Valores que escolhi
int A[m][n] = {{1, 2, 3, 4},
               {2, 3, 4, 5},
               {3, 4, 5, 6},
               {7, 5, 6, 7}}; //Valores que escolhi

int thread_count = 4;


int x[m] = {2, 3, 4, 5}; //Valores que escolhi
int y[m]; //Output


void *Pth_mat_vect (void* rank) { //Funcao dada no moodle
    long my_rank = (long) rank;
    int i, j;
    int local_m = m/thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank+1) * local_m - 1;

    for (i = my_first_row;i<=my_last_row; i++){
        y[i] = 0.0; //Aqui indica que y será o produto
        for (j = 0; j < n; j++){
            y[i] += A[i][j] * x[j]; // Aqui indica que x sera o vetor multiplicado por.
        }
    }
    return NULL;
}

int main(){

    // Referëncia de como criar threads
    // https://www.bogotobogo.com/cplusplus/multithreading_pthread.php


    pthread_t threads[thread_count];
    for (int i = 0; i < thread_count; i++){
        pthread_create(&threads[i], NULL, &Pth_mat_vect, (void*)i);
    }

    std::cout << "Vetor resultado: " << std::endl;
    for (int elem = 0; elem < m; elem++) {
        std::cout << y[elem] << "\t";
    }

    return 0;
}

//Execucao do programa em:
//Apple clang version 13.1.6 (clang-1316.0.21.2.5)
//Target: arm64-apple-darwin21.3.0

//Comando: g++ -std=c++20 main.cpp

//./a.out
//Vetor resultado:
//40	54	68	88
//Process finished with exit code 0

