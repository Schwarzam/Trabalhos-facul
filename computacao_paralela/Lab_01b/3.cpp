// 3. Faça o programa que apresenta a seguinte saída, perguntando ao usuário o número máximo (no exemplo, 9). Este número deve ser sempre ímpar.

// Execução em g++ clang version 13.1.6
#include <iostream>

int main(void) {

    int n, i, j;

    std::cout <<"Digite o numero maximo do triangulo." << std::endl;
    std::cout << std::endl;
    std::cout <<"O numero deve ser impar." << std::endl;
    std::cin >> n;
    std::cout << std::endl;

    if (n % 2 ==0){
       std::cout << "Numero invalido." << std::endl;
       return 1;
    }
    else{
        for( i = 0; i<= (n / 2) + 1; i++){
            for ( j = i + 1; j <= n - i; j++ )
                std::cout << j;

            std::cout << std::endl;
            for ( j = 0; j < (i + 1); j++ )
              std::cout <<" ";
         }
    }

    return 0;
}

// Execução em g++ clang version 13.1.6

// Atencao, o numero deve ser impar.
// 7

// 1234567
//  23456
//   345
//    4