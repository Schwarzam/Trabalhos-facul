#include <stdlib.h>
#include <stdio.h>

int seq = 0;

void resetIntArr(int *arr){
    for (int i = 0; i < (sizeof(arr) / 4); i++){
        arr[i] = -1;
    }
}

void resetCharArr(char *str){
    for (int i = 0; i < sizeof(str); i++){
        str[i] = '\0';
    }
}

int convertePSegundos(int minutos, int segundos){
    return (minutos * 60) + segundos;
}

void printarSegundosEmMinutos(int segundos){
    int h, m, s;
    h = (segundos/3600);
    m = (segundos -(3600*h))/60;
    s = (segundos -(3600*h)-(m*60));

    printf("\n\t%dm %ds", m, s);
}

int valida(int* s,int i, int tempoTotal, int n_tracks){

    int lado = 0, soma = 0;
    int solucao[n_tracks];
    int tempo = tempoTotal / 2;

    for(int j=0; j <= i; j++){
        if ( (*(s + j) == *(s + i)) && (j != i)){
//            printf("\n");
            return 0;
        }


//        printf("%d ", *(s + j));


        if (soma + (int)*(s + j) > tempo){
            solucao[j + lado] = -1;
            lado ++;
            soma = (int)(*(s + j));
            solucao[j + lado] = *(s + j);
        }
        else {
            soma = soma + *(s + j);
            solucao[j + lado] = *(s + j);
        }

        if (lado >= 2){
//            printf("lado 2! \n");
            return 0;
        }
    }
    if (n_tracks == i+1){
        printf("SOLUCAO %d: ", seq++);
        lado = 1;

        printf("\nLado %d: ", lado);
        for (int x = 0; x <= n_tracks; x++){
            if (solucao[x] == -1){
                lado ++;
                printf("\nLado %d: ", lado);
            }else {
                printarSegundosEmMinutos(solucao[x]);
            }
        }
        printf("\n\n");
    }

//    printf("\n");
    return 1;
}

// imprime o vetor na tela
void imprima(int* s, int n){
    for( int i = 1; i <= n; i++)
        printf("IMPRIMA %d ", *(s + i));
    printf("\n");
}

void backtrack(int* tape, int* s, int n_tracks, int i, int tempoTotal){
    if( i > n_tracks ) // caso base
        imprima(s,n_tracks);
    else{
        for(int j=0; j < n_tracks; j++){
            *(s + i) = *(tape + j);
            if(valida(s, i, tempoTotal, n_tracks) == 1)
                backtrack(tape, s,n_tracks,i+1, tempoTotal);
        }
    }
}




int* read_txt(char* fname){
    FILE    *textfile;
    char    *text;
    long    numbytes;

    textfile = fopen(fname, "r");
    if(textfile == NULL){
        printf("Arquivo nao encontrado! \n");
        return 1;
    }



    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);

    text = (char*)calloc(numbytes, sizeof(char));
    if(text == NULL)
        return 1;

    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);

    int numbers_index = 0;
    int numbers[2] = {-1, -1};

    int char_number_index = 0;
    char char_number[3]  = {'\0', '\0', '\0'};

    int num;
    int infoNextLine = 0;
    int trackNumber = 0, trackTotal = -1;
    int scanningTracks = 0;

    int tempoTotal = 0;

    int tapeIndex = 0;
    int *tape, *res;

    int num_fita = 1;

    for (int i = 0; i <= numbytes; i++){

        if (text[i] == ' ') {
            sscanf(char_number, "%d", &num);
            numbers[numbers_index] = num;
            resetCharArr(char_number);

            numbers_index ++;
            char_number_index = 0;
        }

        else if (text[i] == '\n' || i == numbytes) {
            sscanf(char_number, "%d", &num);
            numbers[numbers_index] = num;

            if (i == numbytes){ //Ultima iteracao
                trackTotal = trackNumber;
                *(tape + tapeIndex) = convertePSegundos(numbers[0], numbers[1]);
                tapeIndex ++;
                for (int j = 0; j <= trackTotal; j++){
                    printf("gravacao %d: %ds \n",j , *(tape + j));
                }
                printf("\n");
                backtrack(tape, res, trackTotal + 1, 0, tempoTotal);

                if (scanningTracks == 1 && seq == 0){
                    printf("Nenhuma solucao encontrada! ");
                }

            }else if(trackTotal == trackNumber){
                infoNextLine = 1;

                for (int j = 0; j < trackTotal; j++){
                    printf("gravacao %d: %ds \n",j , *(tape + j));
                }
                printf("\n");
                backtrack(tape, res, trackTotal, 0, tempoTotal);

                if (scanningTracks == 1 && seq == 0){
                    printf("Nenhuma solucao encontrada! ");
                }
            }

            if (scanningTracks == 1 && !infoNextLine){
                *(tape + tapeIndex) = convertePSegundos(numbers[0], numbers[1]);
                tapeIndex ++;
            }

            trackNumber++;

            if (numbers[1] == -1){
                printf("Numero de fitas: %d\n\n", numbers[0]);
                infoNextLine = 1;
            }

            else if (infoNextLine == 1){
                printf("FITA %d: \n", num_fita++);
                printf("Tempo total: %dm, numero de musicas: %d\n", numbers[0], numbers[1]);

                infoNextLine = 0;
                trackNumber = 0;
                trackTotal = numbers[1];
                tempoTotal = numbers[0] * 60;
                scanningTracks = 1;

                tape = (int*)calloc(numbers[1], sizeof(int));
                res = (int*)calloc(numbers[1], sizeof(int));
                tapeIndex = 0;
                seq = 0;
            }

            resetCharArr(char_number);
            resetIntArr(numbers);

            numbers_index = 0;
            char_number_index = 0;
        }
        else{
            char_number[char_number_index] = text[i];
            char_number_index ++;
        }

    }
}

int main() {
    char path[100];
    while (1){
        printf("Insira o caminho do arquivo para leitura: ");
        scanf("%s",path);
        //"/Users/gustavo/CLionProjects/tape/test.txt"
        read_txt(path);
        int i;

        printf("Digite 0 para sair, 1 para continuar. \n");
        scanf("%i", &i);
        if (i == 0){
            break;
        }
    }


    return 0;
}
