// 1. Crie um programa capaz de ler os dados de uma matriz quadrada de inteiros. Ao final da leitura o programa deverá imprimir o número da linha que contém o menor dentre todos os números lidos.

#include <iostream>

int main(){
    int i, j, result = INT_MAX;
    int a[2][2];
    std::cout << "Digite os valores da matriz" << std::endl;

    for (i=0; i<2; i++){
        std::cout << "Digite os valores para a " << i+1 << " linha" << std::endl;
            for (j=0; j<2; j++)
                std::cin >> a[i][j];
    }


    for (i=0; i<2; i++){
        
            for (j=0; j<2; j++)
                if (a[i][j] < result){
                    result = a[i][j];
                }
    }
    std::cout << "O menor valor da matriz é: " << result << std::endl;
    return 0;
}


// Execução:
// Digite os valores da matriz
// Digite os valores para a 1 linha
// 23
// 42
// Digite os valores para a 2 linha
// 53
// 15
// O menor valor da matriz é: 15
