#include <stdlib.h>
#include <stdio.h>

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

int valida(int* s,int i){
    for( int j=1; j < i; j++)
        if(*(s + i)==*(s + j))
            return 0;
    return 1;
}

// imprime o vetor na tela
void imprima(int* s, int n){
    for( int i = 1; i <= n; i++)
        printf("IMPRIMA %d ", *(s + i));
    printf("\n");
}

void backtrack(int* tape, int* s, int n_tracks, int i){
    if( i > n_tracks ) // caso base
        imprima(s,n_tracks);
    else{
        for(int j=1; j <=n_tracks; j++){
            *(s + i) = *(tape + j);
            if(valida(s,i) == 1)
                backtrack(tape, s,n_tracks,i+1);
        }
    }
}




int* read_txt(char* fname){
    FILE    *textfile;
    char    *text;
    long    numbytes;

    textfile = fopen(fname, "r");
    if(textfile == NULL)
        return 1;

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

    int tapeIndex = 0;
    int *tape, *res;

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
                    printf("tape track: %ds \n", *(tape + j));
                }
                backtrack(tape, res, trackTotal + 1, 0);

            }else if(trackTotal == trackNumber){
                infoNextLine = 1;

                for (int j = 0; j < trackTotal; j++){
                    printf("tape track: %ds \n", *(tape + j));
                }
                backtrack(tape, res, trackTotal, 0);
            }

            if (scanningTracks == 1 && !infoNextLine){
                *(tape + tapeIndex) = convertePSegundos(numbers[0], numbers[1]);
                tapeIndex ++;
            }

            trackNumber++;

            if (numbers[1] == -1){
                printf("Number of tests: %d\n\n", numbers[0]);
                infoNextLine = 1;
            }

            else if (infoNextLine == 1){
                printf("Total time of tape: %dm, number of tracks: %d\n", numbers[0], numbers[1]);
                infoNextLine = 0;
                trackNumber = 0;
                trackTotal = numbers[1];
                scanningTracks = 1;

                tape = (int*)calloc(numbers[1], sizeof(int));
                res = (int*)calloc(numbers[1], sizeof(int));
                tapeIndex = 0;
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

    read_txt("/Users/gustavo/CLionProjects/tape/test.txt");

    return 0;
}
