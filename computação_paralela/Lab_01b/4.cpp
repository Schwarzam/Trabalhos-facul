
#include <string.h>
#include <iostream>


void ordem(char a[50], char b[50]);

int main (){
    char nome1[100], nome2[100];
    std::cout << "Informe o primeiro nome: " << std::endl;
    gets(nome1); //gets() input de string
    std::cout <<"Informe o segundo nome: " << std::endl;
    gets(nome2);
    ordem(nome1, nome2);
    return 0;
 }

void ordem(char a[100], char b[100]){
    int tam; 
    tam = 100;
    if(strncmp(a, b, tam) < 0){ //Funcao strncmp compara os primeiros chars de cada string.
        std::cout << "A ordem e:" << std::endl << a << std::endl << b;
    }
    else{
        std::cout << "A ordem e:" << std::endl << b << std::endl << a;
    }
}

// Execucao 

// Informe o primeiro nome: 
// gustavo
// Informe o segundo nome: 
// lucas
// A ordem e:
// gustavo
// lucas            
//                                                               (base) gustavo@gustavoPC Lab_01b % ./a.out
// Informe o primeiro nome: 
// gustavo
// Informe o segundo nome: 
// amanda
// A ordem e:
// amanda
// gustavo 