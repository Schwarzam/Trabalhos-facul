#include <stdlib.h>
#include <stdio.h>

//C:\Users\gusta\Documents\test.txt

int seq = 0;

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

int convertePSegundos(int minutos, int segundos){
    return (minutos * 60) + segundos; //Converte minutos e segundos para segundos
}

void printarSegundosEmMinutos(int segundos){ //pretty print
    int h, m, s;
    h = (segundos/3600);
    m = (segundos -(3600*h))/60;
    s = (segundos -(3600*h)-(m*60));

    printf("\n\t%dm %ds", m, s);
}

int valida(int* s,int i, int tempoTotal, int n_tracks){ //valida a solucao do backtrack

    int lado = 0, soma = 0;
    int solucao[n_tracks]; //array com a solucao
    int tempo = tempoTotal / 2; //tempo de cada lado

    for(int j=0; j <= i; j++){
        if ( (*(s + j) == *(s + i)) && (j != i)){
            return 0;
        }

        if (soma + (int)*(s + j) > tempo){ // testa se cabe nesse lado ainda, se coiuber passa pro else
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
            return 0; // se chegar no lado 2 quer dizer que solucao eh invalida
        }
    }
    if (n_tracks == i+1){ // SOLUCAO ENCONTRADA 
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

void backtrack(int* tape, int* s, int n_tracks, int i, int tempoTotal){ //backtrack
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




int run_program(char* fname){ // recebe como parametro o caminho do arquivo
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

    int numbers_index = 0;
    int numbers[2] = {-1, -1}; //Armazenara os numeros de cada linha

    int char_number_index = 0;
    char char_number[2]  = {'\0', '\0'}; //Armazenara cada numero enquanto char ainda (enquanto loop na variavel text)

    int num; int num2;
    int infoNextLine = 0; // Se a proxima linha será inicial de uma nova fita
    int trackNumber = 0, trackTotal = -1; 
    int scanningTracks = 0; // Indica se está rodando procurando por musicas já

    int tempoTotal = 0; // tempo total da fita

    int tapeIndex = 0; //indice na fita
    int *tape, *res; //ponteiros dinamicamente alocados conforme o tamanho da fita

    int num_fita = 1; //numero da fita

    for (int i = 0; i <= numbytes; i++){ //loop em cima de cada char do arquivo
        if (text[i] == ' ') { // caso seja seja um espaco em branco, computa o primeiro numero
            sscanf(char_number, "%d", &num);
            numbers[numbers_index] = num;
            resetCharArr(char_number);
            numbers_index ++;
            char_number_index = 0;
        }
        else if (text[i] == '\n' || i == numbytes || (char_number_index == 2)) { // caso seja nova linha computa o segundo numero da coluna, ou descobre se eh linha de informacao, ou fim do arquivo
            sscanf(char_number, "%d", &num2);
            numbers[numbers_index] = num2;

            if (i == numbytes){ //Ultima iteracao, fim do arquivo
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

            }else if(trackTotal == trackNumber){ //Chegada na ultima faixa.
                infoNextLine = 1;

                for (int j = 0; j < trackTotal; j++){
                    printf("gravacao %d: %ds \n",j , *(tape + j));
                }
                printf("\n");
                backtrack(tape, res, trackTotal, 0, tempoTotal);

                if (scanningTracks == 1 && seq == 0){
                    printf("Nenhuma solucao encontrada! \n");
                }
            }

            if (scanningTracks == 1 && !infoNextLine){ //Adiciona a fita convertido para segundo.
                *(tape + tapeIndex) = convertePSegundos(numbers[0], numbers[1]);
                tapeIndex ++;
            }

            trackNumber++ //Indica proxima musica;

            if (numbers[1] == -1 && scanningTracks == 0){ //Indica primeira linha de todas com numero de fitas
                printf("Numero de fitas: %d\n\n", numbers[0]);
                infoNextLine = 1;
            }

            else if (infoNextLine == 1){ //linha de info da fita, com tempo total e quantas faixas
                if (numbers[0] == -1 || numbers[1] == -1){
                    break;
                }
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
    while (1){ //roda num loop perguntando por arquivo
        printf("Insira o caminho do arquivo para leitura: ");
        scanf("%s",path);
        //"/Users/gustavo/CLionProjects/tape/test.txt"
        run_program(path);
        int i;

        printf("Digite 0 para sair, 1 para continuar. \n");
        scanf("%i", &i);
        if (i == 0){
            break;
        }
    }


    return 0;
}
