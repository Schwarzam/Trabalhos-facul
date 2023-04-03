#include <stdio.h>
#include <stdlib.h>

char alfabeto[10] = {-1};

int transicoes_estados[100][2];
char transicoes_simbolos[100];
int n_transicoes = -1;

char palavras_teste[100][100] = {-1};
int n_palavras_teste = -1;

int n_estados_finais = -1;
int estados_finais[20];

int sum = 0;

int testaAFnD(
        char palavra[],
        int indice_palavra,
        int estado_atual
    ) // Função recursiva que testa se a palavra pertence ao AFnD
    {

    if (palavra[indice_palavra] == '\0'){
        for (int i = 0; i < n_estados_finais; i++){
            if (estado_atual == estados_finais[i]){
                sum ++;
            }
        }
    }
    
    for (int i = 0; i < n_transicoes; i++){
        if (palavra[indice_palavra] == transicoes_simbolos[i] && estado_atual == transicoes_estados[i][0]){
            sum = testaAFnD(palavra, indice_palavra + 1, transicoes_estados[i][1]);
        }
    }
    return sum;
}


int main() {
    char filename[256];

    // Pegar nome do arquivo
    printf("Enter the filename: ");
    scanf("%255s", filename); // Limit the input to 255 characters to avoid buffer overflow

    // Abrir arquivo
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    int line_count = 1;

    int indice_alfabeto = 0;
    int n_estados = -1;
    
    for (int i = 0; i < 20; i++) {
        estados_finais[i] = -1;
    }
    int indice_estados_finais = 0;
    

    for (int i = 0 ; i < 100; i++) {
        transicoes_estados[i][0] = -1;
        transicoes_estados[i][1] = -1;
    }
    
    int indice_transicoes = 0;
    int indice_interno_transicoes = 0;

    
    int indice_palavras_teste = 0;

    char last_char = ' ';
    int last_line = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            // Nova linha
            line_count++;
            last_char = ' ';
            indice_palavras_teste = 0;
            continue;
        }

        //Lida com a primeira linha
        if (line_count == 1 && ch != ' ') {
            alfabeto[indice_alfabeto] = ch;
            indice_alfabeto ++;
        }

        //Numero de estados
        if (line_count == 2 && ch != ' ') {
            if (last_char != ' '){
                n_estados = (last_char - '0') * 10 + (ch - '0');
            }else{
                n_estados = ch - '0';
            }
        }

        //Numero de estados finais
        if (line_count == 3 && ch != ' ') {
            if (last_char != ' '){
                n_estados_finais = (last_char - '0') * 10 + (ch - '0');
            }else{
                n_estados_finais = ch - '0';
            }
        }

        //Estados finais
        if (line_count == 4 && ch != ' ') {
            if (last_char != ' ') { // Caso o numero tenha dois digitos
                estados_finais[indice_estados_finais - 1] = (last_char - '0') * 10 + (ch - '0');
            }
            else{
                estados_finais[indice_estados_finais] = ch - '0';
                indice_estados_finais ++;
            }
        }

        //Numero de transicoes
        if (line_count == 5 && ch != ' ') {
            if (last_char != ' '){
                n_transicoes = (last_char - '0') * 10 + (ch - '0');
            }else{
                n_transicoes = ch - '0';
            }
        }

        //Transicoes
        if (line_count > 5 && line_count <= 5 + n_transicoes){
            if (last_line != line_count){
                indice_transicoes ++;
                indice_interno_transicoes = 0;
            }

            if (ch == ' '){
                indice_interno_transicoes ++;
            }

            if (indice_interno_transicoes == 0){
                if (last_char != ' '){
                    transicoes_estados[indice_transicoes - 1][0] = (last_char - '0') * 10 + (ch - '0');
                }else{
                    transicoes_estados[indice_transicoes - 1][0] = ch - '0';
                }
            }

            if (indice_interno_transicoes == 1){
                transicoes_simbolos[indice_transicoes - 1] = ch;
            }

            if (indice_interno_transicoes == 2){
                if (last_char != ' '){
                    transicoes_estados[indice_transicoes - 1][1] = (last_char - '0') * 10 + (ch - '0');
                }else{
                    transicoes_estados[indice_transicoes - 1][1] = ch - '0';
                }
            }
        }

        // Numero de palavras a serem testadas
        if (line_count == 6 + n_transicoes){
            if (last_char != ' '){
                n_palavras_teste = (last_char - '0') * 10 + (ch - '0');
            }else{
                n_palavras_teste = ch - '0';
            }
        }

        // Palavras a serem testadas
        if (line_count > 6 + n_transicoes){
            palavras_teste[line_count - 7 - n_transicoes][indice_palavras_teste] = ch;
            indice_palavras_teste ++;
        }

        last_line = line_count;
        last_char = ch;
    }

    printf("\nAlfabeto: ");
    for (int i = 0; i < 10; i++) {
        printf("%c ", alfabeto[i]);
    }
    printf("\nNumero de estados: %d", n_estados);
    printf("\nNumero de estados finais: %d", n_estados_finais);

    printf("\nEstados finais: ");
    for (int i = 0; i < 20; i++) {
        if (estados_finais[i] == -1) {continue;}
        printf("%d ", estados_finais[i]);
    }

    printf("\nNumero de transicoes: %d", n_transicoes);

    printf("\nTransicoes: ");
    for (int i = 0; i <= 20; i++){
        if (transicoes_estados[i][0] == -1) {continue;}
        printf("\n%d %c %d", transicoes_estados[i][0], transicoes_simbolos[i], transicoes_estados[i][1]);
    }

    printf("\nNumero palavras teste: %d", n_palavras_teste);

    printf("\nPalavras teste: ");
    for (int i = 0; i < 100; i++){
        if (palavras_teste[i][0] == '\0') {continue;}
        printf("\n");
        for (int j = 0; j < 100; j++){
            if (palavras_teste[i][j] == '\0') {break;}
            printf("%c", palavras_teste[i][j]);
        }
    }

    printf("\n");
    // Close the file
    fclose(file);

    sum = 0;

    printf("\n");
    for (int i = 0; i < n_palavras_teste; i++){
        if (palavras_teste[i][0] == '\0') {break;}
        sum = 0;
        testaAFnD( palavras_teste[i], 0, 0 );
        
        for (int j = 0; j < 100; j++){
            if (palavras_teste[i][j] == '\0') {break;}
            printf("%c", palavras_teste[i][j]);
        }
        if (sum != 0){
            printf(" OK\n");
        }else{
            printf(" Not OK\n");
        }
        
    }

    return 0;
}

