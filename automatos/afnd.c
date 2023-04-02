#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256] = "input.txt";

    // Get the filename from the user
    printf("Enter the filename: ");
    // scanf("%255s", filename); // Limit the input to 255 characters to avoid buffer overflow

    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print the file content
    char ch;
    int line_count = 1;

    char alfabeto[10] = {-1};
    int indice_alfabeto = 0;

    int n_estados = -1;
    int n_estados_finais = -1;

    int estados_finais[20] = {-1};
    int indice_estados_finais = 0;

    int n_transicoes = -1;

    char last_char = ' ';


    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            // Nova linha
            line_count++;
            last_char = ' ';
            continue;
        }

        //Lida com a primeira linha
        if (line_count == 1 && ch != ' ') {
            alfabeto[indice_alfabeto] = ch;
            indice_alfabeto ++;
        }   

        //Lida com a segunda linha
        if (line_count == 2 && ch != ' ') {
            n_estados = ch - '0';
        }

        if (line_count == 3 && ch != ' ') {
            n_estados_finais = ch - '0';
        }

        if (line_count == 4 && ch != ' ') {
            if (last_char != ' ') { // Caso o numero tenha dois digitos
                printf("\n \n %c %c \n", last_char, ch);
                estados_finais[indice_estados_finais - 1] = last_char * 10 + ch;
            }
            else{
                estados_finais[indice_estados_finais] = ch - '0';
                indice_estados_finais ++;
            }
        }


        last_char = ch;
    }

    printf("\nAlfabeto: ");
    for (int i = 0; i < 10; i++) {
        printf("%c ", alfabeto[i]);
    }
    printf("\nNumero de estados: %d", n_estados);

    printf("\nEstados finais: ");
    for (int i = 0; i < 20; i++) {
        printf("%d ", estados_finais[i]);
    }

    // Close the file
    fclose(file);

    return 0;
}