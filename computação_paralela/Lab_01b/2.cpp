// 2. Escreva um programa que leia 3 notas de um aluno e a média das notas dos exercícios realizados por ele. Calcular a média de aproveitamento, usando a fórmula: MA = (N1 + N2*2 + N3*3 + ME)/7. A partir da média, informar o conceito de acordo com a tabela:


#include <iostream>

int main()

{
    float n1, n2, n3, me, ma;

    std::cout << ("Digite a primeira nota: ");
    std::cin >> n1;

    std::cout << ("Digite a segunda nota: ");
    std::cin >> n2;

    std::cout << ("Digite a terceira nota: ");
    std::cin >> n3;

    std::cout << ("Digite a média dos exercícios: ");
    std::cin >> me;

    ma = (n1 + n2*2 + n3*3 + me)/7.0;
    if(ma>=9)
        std::cout << ("A");
    else if(ma>=7.5)
        std::cout << ("B");
    else if(ma>=6)
        std::cout << ("C");
    else if(ma>=4)
        std::cout << ("D");
    else
        std::cout << ("E");

    std::cout << ("\n");
    return 0;

}

// Execucao 

// (base) gustavo@gustavoPC Lab_01b % ./a.out  
// Digite a primeira nota: 5
// Digite a segunda nota: 6
// Digite a terceira nota: 4
// Digite a média dos exercícios: 6
// D
// (base) gustavo@gustavoPC Lab_01b % ./a.out
// Digite a primeira nota: 9
// Digite a segunda nota: 9
// Digite a terceira nota: 9.5
// Digite a média dos exercícios: 9
// A