#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>

using std::cout; using std::endl; using std::cin;

//Funcao multiplicar faz a multiplicacao de cada elemento do inicio ao fim em passos de 1.
int multiplicar(int inicio, int fim) {
    int produto = 1;
    for ( int i = inicio; i <= fim; i++ ) {
        produto *= i;
    }
    return produto;
}


int main() {
    int processos = 1;
    cout << "Enter number of processes to use: ";
    cin >> processos;

    int status = 0;
    int *arr[processos]; // Criei um array de ponteiros do tamanho de numero de processos

    pid_t child_pid, wpid;

    int num = 10;
    cout << "Enter the number: ";
    cin >> num;

    int elementosPorProc = num / processos;
    int posArr = 0;


    for (int k = 1; k <= processos; k++){
        // Cada processo devolverá seu resultado na posição do array
        arr[posArr] = (int*) mmap(NULL, sizeof (int) , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // Transformando em um endereço de memória compartilhada

        //O fatorial sera dividido no numero de processos.
        if ((child_pid = fork()) == 0){
            if (k == 1){
                //Caso k == 1, o fatorial deve iniciar de 1
                *arr[posArr] = multiplicar(1, k * elementosPorProc);
            }
            else if (k == processos){
                //Nesse caso podem estar restando elementos da divisao do numero dado pelo numero de processos.
                *arr[posArr] = multiplicar((k - 1) * elementosPorProc + 1, k * elementosPorProc + (num % processos));
            }
            else if (k > 1){
                //Caso k > 1 e diferente do numero de processos
                *arr[posArr] = multiplicar((k - 1) * elementosPorProc + 1, k * elementosPorProc);
            }
            exit(0);
        }
        // Vai para a proxima posicao no array
        posArr ++;
    }

    while ((wpid = wait(&status)) > 0); //Espera todos processos terminarem

    int resultado = 1;
    for (int i = 0; i < processos; i++){
        // Multiplica cada resultado no array para obter o resultado final
        resultado = *arr[i] * resultado;
    }

    cout << "The factorial of " << num << " is " << resultado << endl;
    return 0;
}

// Execução em:
//Apple clang version 13.1.6 (clang-1316.0.21.2.5)
//Target: arm64-apple-darwin21.3.0

// Usando 10 processos
//time ./a.out
// The factorial of 10 is 3628800
//./a.out  0.00s user 0.01s system 1% cpu 0.498s total

// Usando 8 processos
//time ./a.out
//The factorial of 10 is 3628800
//./a.out  0.00s user 0.01s system 1% cpu 0.480 total

// Usando 5 processos
//time ./a.out
//The factorial of 10 is 3628800
//./a.out  0.00s user 0.00s system 3% cpu 0.165 total

// Usando 2 processos
//time ./a.out
//The factorial of 10 is 3628800
//./a.out  0.00s user 0.00s system 1% cpu 0.246 total

// Usando 1 processo
//time ./a.out
//The factorial of 10 is 3628800
//./a.out  0.00s user 0.00s system 2% cpu 0.186 total

//Acredito que "spawnar" um processo custe tempo, e para uma operacao tao simples nao valha a pena,
//por isso quando mais processos mais custoso em questáo de tempo