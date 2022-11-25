#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int p1;
    int p2;
    int tempo;
} rota;

void resetIntArr(int *arr){ //Reseta os valores de um array de int
    for (int i = 0; i < (sizeof(arr) / 4); i++){
        arr[i] = -1;
    }
}

void resetCharArr(char *str){ //Reseta os valores de um array de char
    for (int i = 0; i < sizeof(str); i++){
        str[i] = '\0';
    }
}

int main()
{
    char fname[100];

    printf("Insira o caminho do arquivo para leitura: ");
    scanf("%s",fname);

    // ------------- Procedimentos abertura arquivo ---------------
    FILE    *textfile;
    char    *text;
    long    numbytes;

    textfile = fopen(fname, "r"); //Abre o txt
    if(textfile == NULL){
        printf("Arquivo nao encontrado! \n");
        return 1;
    }

    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile); // Encontrar numero de bytes do arquivo
    fseek(textfile, 0L, SEEK_SET);

    text = (char*)calloc(numbytes, sizeof(char)); //aloca espaco para arquivo
    if(text == NULL)
        return 1;

    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile); // fecha leitura do arquivo
    // -----------------------------------------------------------------


    // -------------------------- computar valores no texto -----------------
    int numbers_index = 1;
    int numbers[4] = {-1, -1, -1, -1}; //Armazenara os numeros de cada linha, o primeiro será ignorado

    int char_number_index = 0;
    char char_number[3]  = {'\0', '\0', '\0'}; //Armazenara cada numero enquanto char ainda (enquanto loop na variavel text)

    int num;

    int incendio = -1;
    int esquinas = -1;

    rota rotas[100];
    int indice_rotas = 0;

    int i = 0;
    while (text[i] != '0'){
        if (text[i] == '\n'){
            if (numbers[0] == -1){
                if (incendio == -1){
                    sscanf(char_number, "%d", &incendio);
                }else if (esquinas == -1){
                    sscanf(char_number, "%d", &esquinas);
                }
            }else{
                sscanf(char_number, "%d", &num);
                numbers[numbers_index] = num;
                resetCharArr(char_number);

                for (int y = 0; y < 3; y++){
                    rotas[indice_rotas].p1 = numbers[1];
                    rotas[indice_rotas].p2 = numbers[2];
                    rotas[indice_rotas].tempo = numbers[3];
                }
                indice_rotas++;

            }
            resetCharArr(char_number);
            resetIntArr(numbers);
            char_number_index = 0;
            numbers_index = 1;
        }

        else if (text[i] == ' '){
            sscanf(char_number, "%d", &num);
            numbers[numbers_index] = num;
            resetCharArr(char_number);
            numbers_index ++;
            char_number_index = 0;
        }

        else {
            char_number[char_number_index] = text[i];
            char_number_index ++;
        }
        i++;
    }
    // ---------------------------------------------------------------


    // ----------------- algoritmo guloso ----------------------------
    int T[esquinas + 1];

    int R[esquinas + 1];
    R[0] = 1;
    int indice_r = 1;

    for (i = 0; i <= esquinas; i++){
        T[i] = 10000;
    }
    T[1] = 0;

    int v = 1;

    for (i = 0; i <= esquinas; i++){

        for (int y = 0; y < indice_rotas; y++){
            if (rotas[y].p1 == v){
                if (T[rotas[y].p2] > T[v] + rotas[y].tempo){
                    T[rotas[y].p2] = T[v] + rotas[y].tempo;
                    v = rotas[y].p2;
                    R[indice_r] = rotas[y].p2;
                    indice_r ++;
                    if (v == incendio){
                        break;
                    }
                }
            }
        }
        if (v == incendio){
            printf("\nSolucao encontrada!\n");
            break;
        }
    }
    if (v != incendio){
        printf("Solucao nao encontrada!\n");
    }


    printf("rota ate a esquina #%d:", incendio);
    for (i = 0; i < indice_r; i++){
        printf(" %d", R[i]);
    }
    printf("\ntempo calculado para rota = %d:", T[incendio]);

    return 0;
}
