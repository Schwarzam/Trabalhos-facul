#include  <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#include <errno.h>
#include <sys/ipc.h>
#include <stdlib.h>

//Crie um código-fonte que utilize fork() e shmget() entre 2 processos (pai e filho). Seu código deve garantir que:
//
//o processo pai e o processo filho compartilhem uma variável simples (por exemplo, inteiro - valor 1)
//o processo pai imprime o valor inicial dessa variável; em seguida, cria o processo filho e espera-o
//
//o processo filho acessa esta variável, realiza uma operação (por exemplo, adição - valor 2, totalizando 3), modificando o valor; em seguida, o processo filho termina
//o processo pai realiza uma outra operação (por exemplo, multiplicação - valor 4, totalizando 12), modificando novamente o valor, e imprime novamente a variável
//
//Essa lógica de execução deve ser garantida no seu código-fonte em C.

int main(){
    pid_t filho_pid;
    int shm_id;

    shm_id = shmget(IPC_PRIVATE, sizeof(int),  IPC_CREAT | IPC_EXCL | SHM_R | SHM_W );
    if (shm_id < 0) {
        printf("shmget error\n");
    }

    int *shrd = (int*)shmat(shm_id, NULL, 0); //Tratando variavel como ponteiro, criando a ligacao
    *shrd = 1;

    printf("O valor inicial da variavel compartilhada é %i\n",*shrd);
    filho_pid = fork();

    if (filho_pid == 0){
        *shrd += 2;
        printf("Valor da variavel compartilhada ao somar 2:  %i\n",*shrd);
    }
    else{
        wait(nullptr); // Espera processo filho
        *shrd *= 4 ;
        printf("Valor da variavel compartilhada ao multiplicar por 4: %i\n",*shrd);
    }

    return 0;
}

//Execucao do programa em:
//Apple clang version 13.1.6 (clang-1316.0.21.2.5)
//Target: arm64-apple-darwin21.3.0

//Comando: g++ -std=c++20 main.cpp

//./a.out
//O valor inicial da variavel compartilhada é 1
//Valor da variavel compartilhada ao somar 2:  3
//Valor da variavel compartilhada ao multiplicar por 4: 12
//
//Process finished with exit code 0