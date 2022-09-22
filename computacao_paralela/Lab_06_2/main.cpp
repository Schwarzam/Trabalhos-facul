#include <cstdio>
#include <cmath>
#include <pthread.h>

long thread_count = 10;
long long n = 200000; // Determinará a precisao

double sum = 0.0;
pthread_mutex_t mutex;

void* Thread_sum(void* rank) { //Funcao dada no moodle
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;

    if (my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = -1.0;

    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        pthread_mutex_lock(&mutex); // Foi necessário adicionar uma trava mutex para as threads nao acessarem a memoria ao mesmo tempo
        sum += factor/(double)(2*i+1);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}  /* Thread_sum */

int main() {
   long       thread;
   pthread_t *thread_handles;

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
   pthread_mutex_init(&mutex, NULL);

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*)thread); // Criando as threads

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); // Esperando as threads

   sum = 4.0*sum;

   pthread_mutex_destroy(&mutex); //Destroir o mutex
   free(thread_handles); //Liberar o espaco alocado para as threads

   printf("%f", sum);
   return 0;
}

//Tentativa de implementacao do calculo de pi
//Acredito nao ter tido essa aula.


//Execucao do programa em:
//Apple clang version 13.1.6 (clang-1316.0.21.2.5)
//Target: arm64-apple-darwin21.3.0

//Comando: g++ -std=c++20 main.cpp

//./a.out
//3.141588





