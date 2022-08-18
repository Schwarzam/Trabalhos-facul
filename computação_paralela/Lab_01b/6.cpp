#include <iostream>

int main() {
    int l, c, mat[3][3], trans[3][3];
    for(l = 0; l < 3; l++){
        std::cout << "Digite os valores para a " << l+1 << " linha" << std::endl;
        for(c = 0; c < 3; c++){
            std::cin >> mat[l][c];
        }
    }

    std::cout << std::endl << "Matriz original:" << std::endl;
    for(l = 0; l < 3; l++){
        for(c = 0; c < 3; c++){
            std::cout << mat[l][c];
        }
        std::cout << std::endl;
    }

    for(l = 0; l < 3; l++){
        for(c = 0; c < 3; c++){
            trans[c][l] = mat[l][c];
        }
    }

    std::cout << std::endl << "Matriz transposta:" << std::endl;
    for(l = 0; l < 3; l++){
        for(c = 0; c < 3; c++){
            std::cout << trans[l][c];
        }
        std::cout << std::endl;
    }

    return 0;
}

// Execucao

// Digite os valores para a 1 linha
// 2
// 3
// 4
// Digite os valores para a 2 linha
// 1
// 2
// 3
// Digite os valores para a 3 linha
// 5
// 4
// 3

// Matriz original:
// 234
// 123
// 543

// Matriz transposta:
// 215
// 324
// 433