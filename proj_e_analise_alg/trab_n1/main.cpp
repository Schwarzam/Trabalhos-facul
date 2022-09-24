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

int main() {
    FILE    *textfile;
    char    *text;
    long    numbytes;

    textfile = fopen("/Users/gustavo/CLionProjects/tape/test.txt", "r");
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

    for (int i = 0; i < numbytes; i++){
        if (text[i] == ' ') {

            sscanf(char_number, "%d", &num);
            numbers[numbers_index] = num;
            resetCharArr(char_number);

            numbers_index ++;
            char_number_index = 0;
        }
        else if (text[i] == '\n') {
            sscanf(char_number, "%d", &num);
            numbers[numbers_index] = num;

            if (trackTotal == trackNumber){
                infoNextLine = 1;
            }

            if (scanningTracks == 1 && !infoNextLine){
                printf("Track: %d %d \n", numbers[0], numbers[1]);
            }

            trackNumber++;

            if (numbers[1] == -1){
                printf("Number of tests: %d\n\n", numbers[0]);
                infoNextLine = 1;
            }

            else if (infoNextLine == 1){
                printf("Total time of tape: %d, number of tracks: %d\n", numbers[0], numbers[1]);
                infoNextLine = 0;
                trackNumber = 0;
                trackTotal = numbers[1];
                scanningTracks = 1;
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

    return 0;
}
