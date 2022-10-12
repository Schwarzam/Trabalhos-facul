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
//Distributor ID: Ubuntu
//Description:    Ubuntu 22.04.1 LTS
//Release:        22.04
//Codename:       jammy

//g++ (Ubuntu 11.2.0-19ubuntu1) 11.2.0

//Comando: g++ -std=c++20 main.cpp
//./a.out
// Valor de T: 20
// Resposta: 1.718281834649447961660406747341767186299





