#include <iostream>
#include <iomanip>

int fatorial(int n){
    int res = 1;
    for (int i = n; i > 0; i--){
        res = res * i;
    }
    return res;
}

int main() {

    int T;
    long double res = 0;
    std::cout << "Valor de T: ";
    std::cin >> T;

    for (int i = 1; i <= T; i++){
        res += (long double)1 / (long double)fatorial(i);
    }

    std::cout << "Resposta: " << std::setprecision(40) << res << std::endl;
}


//O projeto consiste em construir uma solução paralela cujo valor de S seja o maior possível, ou
//seja, possua a melhor aproximação para a série ln(T).

//Execucao do programa em:
//Apple clang version 13.1.6 (clang-1316.0.21.2.5)
//Target: arm64-apple-darwin21.3.0

//Comando: g++ -std=c++20 main.cpp

//./a.out
//Resposta: 1.71828





