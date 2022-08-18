// 1. Crie um programa capaz de ler os dados de uma matriz quadrada de inteiros. Ao final da leitura o programa deverá imprimir o número da linha que contém o menor dentre todos os números lidos.

#include <iostream>

int main(){
    int i, j;
    int a[3][3];
    std::cout << "Digite os valores da matriz" << std::endl;

    for (i=0; i<3; i++){
        std::cout << "Digite os valores para a " << i+1 << " linha" << std::endl;
            for (j=0; j<3; j++)
                std::cin >> a[i][j];
    }

    int l, c, vl, vc;
    std::cout << "1 a 3 qual linha multiplicar?" << std::endl;
    std::cin >> l;
    std::cout << "Por quanto?" << std::endl;
    std::cin >> vl;

    std::cout << "1 a 3 qual coluna multiplicar?" << std::endl;
    std::cin >> c;
    std::cout << "Por quanto?" << std::endl;
    std::cin >> vc;


    for (i=0; i<3; i++){
        a[l - 1][i] = a[l - 1][i] * vl;
    }
    for (i=0; i<3; i++){
        a[i][c - 1] = a[i][c - 1] * vc;
    }

    std::cout << "Matriz final: " << std::endl;
    for (i=0; i<3; i++){
            for (j=0; j<3; j++)
                std::cout << a[i][j] << " ";
                
            std::cout << std::endl;
    }
    return 0;
}


// Execução:
// Digite os valores da matriz
// Digite os valores para a 1 linha
// 1
// 1
// 1
// Digite os valores para a 2 linha
// 1
// 1
// 1
// Digite os valores para a 3 linha
// 1
// 1
// 1
// 1 a 3 qual linha multiplicar?
// 1
// Por quanto?
// 10
// 1 a 3 qual coluna multiplicar?
// 2
// Por quanto?
// 4
// Matriz final: 
// 10 40 10 
// 1 4 1 
// 1 4 1
