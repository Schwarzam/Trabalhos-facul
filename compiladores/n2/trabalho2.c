/*
Gustavo Schwarz 32141157
Paulo Henrique 32138121

Integra��o do analisador l�xico e analisador sint�tico
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// ########### TIPOS DOS ANALISADOR LEXICO E SINTATICO
typedef enum{
    ALGORITMO,
    NUMERO,
    DIVIDE,

    VARIAVEL,
    INTEIRO,
    LOGICO,

    INICIO,
    FIM,

    SE,
    ENTAO,
    SENAO,

    ENQUANTO,
    FACA,

    LEIA,
    ESCREVA,

    E,
    OU,

    VERDADEIRO,
    FALSO,

    MENOR_QUE,
    MAIOR_QUE,
    MENOR_IGUAL,
    MAIOR_IGUAL,
    IGUAL,
    DIFERENTE,

    PONTO_VIRGULA,
    DOIS_PONTOS,
    PONTO,
    VIRGULA,
    ATRIBUICAO,

    ABRE_PARENTESES,
    FECHA_PARENTESES,

    SOMA,
    MULTIPLICA,
    SUBTRAI,

    COMENTARIO,
    COMENTARIO_LONGO,
    IDENTIFICADOR,
    ERRO,
    EOS
}TAtomo;

char funcoes_sintatico[][30] = {
    "ALGORITMO",
    "NUMERO",
    "DIVIDE",

    "VARIAVEL",
    "INTEIRO",
    "LOGICO",

    "INICIO",
    "FIM",

    "SE",
    "ENTAO",
    "SENAO",

    "ENQUANTO",
    "FACA",

    "LEIA",
    "ESCREVA",

    "E",
    "OU",

    "VERDADEIRO",
    "FALSO",

    "CMME", //MENOR QUE
    "CMMA", //MAIOR QUE 
    "CMEG", //MENOR IGUAL
    "CMAG", //MAIOR IGUAL
    "CMIG", //COMPARA IGUAL = 
    "DIFERENTE",

    "PONTO_VIRGULA",
    "DOIS_PONTOS",
    "PONTO",
    "VIRGULA",
    "ATRIBUICAO",

    "ABRE_PARENTESES",
    "FECHA_PARENTESES",

    "SOMA",
    "MULT",
    "SUBT",

    "COMENTARIO",
    "COMENTARIO_LONGO",
    "IDENTIFICADOR",
    "ERRO",
    "EOS"
};

char palavras_reservadas[][30] = {
    "algoritmo",
    "numero",
    "div",

    "variavel",
    "inteiro",
    "logico",

    "inicio",
    "fim",

    "se",
    "entao",
    "senao",

    "enquanto",
    "faca",
    "leia",
    "escreva",

    "e",
    "ou",

    "verdadeiro",
    "falso",
};

typedef struct{
  TAtomo atomo;
  int linha;
  int atributo_numero;
  char atributo_ID[16];
}TInfoAtomo;

// #######################
// variavel global e funcoes DECLARADA NO ANALISADOR LEXICO
char *buffer;

int contaLinha=1;

int contaVariavel=0;

typedef struct{
    char nome[16];
    int endereco;
    int tipo;
}Variavel;

Variavel variaveis[100];

TInfoAtomo obter_atomo();
TInfoAtomo reconhece_numero();
TInfoAtomo reconhece_id();
TInfoAtomo reconhece_comentario();
TInfoAtomo reconhece_menor();
TInfoAtomo reconhece_maior();
TInfoAtomo reconhece_atribuicao();

TInfoAtomo InfoAtomo;
TAtomo atual;// lookahead = obter_atomo()


void insereVariavel(char *nome, int tipo){
    for (int i=0;i<contaVariavel;i++){
        if(strcmp(variaveis[i].nome, nome)==0){
            printf("#  %03d: Erro semantico: variavel %s ja declarada\n", InfoAtomo.linha, nome);
            exit(1);
        }
    }

    strcpy(variaveis[contaVariavel].nome, nome);
    variaveis[contaVariavel].tipo = tipo;
    variaveis[contaVariavel].endereco = contaVariavel;
    contaVariavel++;
}


Variavel busca_tabela_variaveis(char *nome){
    for (int i=0;i<contaVariavel;i++){
        if(strcmp(variaveis[i].nome, nome)==0){
            return variaveis[i];
        }
    }
    printf("#  %03d: Erro semantico: variavel %s nao declarada\n", InfoAtomo.linha, nome);
    exit(1);
}

/*
<programa>::= algoritmo identificador “;” <bloco> “
.
”
<bloco>::= [ <declaracao_de_variaveis> ] <comando_composto>
<declaracao_de_variaveis> ::= variavel {<lista_variavel> “:” <tipo> “;”}+
<lista_variavel> ::= identificador { “,” identificador }
<tipo> ::= inteiro | logico
<comando_composto> ::= inicio <comando> { “;” <comando>} fim
<comando> ::= <comando_atribuicao> |
<comando_se> |
<comando_enquanto> |
<comando_entrada> |
<comando_saida> |
<comando_composto>
<comando_atribuicao> ::= identificador “:=” <expressao>
<comando_se> ::= se “(” <expressao> “)” entao
<comando> [senao <comando>]
<comando_enquanto> ::= enquanto “(” <expressao> “)” faca <comando>
<comando_entrada> ::= leia “(“ <lista_variavel> “)”
<comando_saida> ::= escreva “(“ <expressao> { “,” <expressao> } “)”
<expressao> ::= <expressao_simples> [<relacional> <expressao_simples> ]
<relacional> ::= “<” | “<=” | “=” | “#” | “>” | “>=”
<expressao_simples> ::= [“+” | “−”] <termo> { (“+” | “−” | ou ) <termo> }
<termo> ::= <fator> { ( “*” | div | e )<fator> }
<fator> ::= identificador |
numero |
verdadeiro |
falso |
“(” <expressao> “)”

*/
void programa();
void bloco();
void declaracao_de_variaveis();
void lista_variavel();
void lista_nova_variavel();
void tipo();
void comando_composto();
void comando();
void comando_atribuicao();
void comando_se();
void comando_enquanto();
void comando_entrada();
void comando_saida();
void expressao();
void relacional();
void expressao_simples();
void termo();
void fator();
int proximo_rotulo();


void consome( TAtomo atomo );
int main(int argc, char *argv[]){
    //printf("Analisando: %s\n",buffer);

    //Ler arquivo e jogar no buffer
    FILE *arq;
    // O nome do arquivo pode vir da execucao do programa
    if(argc > 1)
        arq = fopen(argv[1], "r");
    else{
        char arquivo[100];
        printf("Insira o nome do arquivo: ");
        scanf("%s", arquivo);
        arq = fopen(arquivo, "r");
    }



    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        return 1;
    }
    else{
        fseek(arq, 0, SEEK_END); // vai para o final do arquivo
        int size = ftell(arq); // pegar tamanho do arquivo
        fseek(arq, 0, SEEK_SET); // vai para o inicio do arquivo
        buffer = malloc(size + 1); // aloca memoria para o buffer
        fread(buffer, size, 1, arq); // le arquivo todo
        fclose(arq);
        buffer[size] = '\0';
    }

    InfoAtomo = obter_atomo();
    atual = InfoAtomo.atomo;

    programa(); // chama o simbolo inicial da gramatica
    //consome(EOS);

    // printf("%d linhas analisadas. programa sintaticamente correto.\n", contaLinha);

    return 0;
}

//###############################
// ANALISADOR LEXICO
//###############################
TInfoAtomo obter_atomo(){
    TInfoAtomo infoAtomo;
    // descartando os delimitadores
    while( *buffer==' ' || *buffer=='\n' || *buffer=='\t' || *buffer== '\r'){
        if(*buffer == '\n')
            contaLinha++;
        buffer++;
    }
    // reconhece numero
    if(isdigit(*buffer)){
        infoAtomo = reconhece_numero();
    }
    // reconhece identificador
    else if(isalpha(*buffer)){
        infoAtomo = reconhece_id();
    }
    else if(*buffer == '+'){
        infoAtomo.atomo = SOMA;
        buffer++;
    }
    else if(*buffer == '*'){
        infoAtomo.atomo = MULTIPLICA;
        buffer++;
    }
    else if(*buffer == ';'){
        infoAtomo.atomo = PONTO_VIRGULA;
        buffer++;
    }
    else if(*buffer == ':'){
        infoAtomo = reconhece_atribuicao();
    }
    else if(*buffer == '.'){
        infoAtomo.atomo = PONTO;
        buffer++;
    }
    else if(*buffer == ','){
        infoAtomo.atomo = VIRGULA;
        buffer++;
    }
    else if(*buffer == '('){
        infoAtomo.atomo = ABRE_PARENTESES;
        buffer++;
    }
    else if(*buffer == ')'){
        infoAtomo.atomo = FECHA_PARENTESES;
        buffer++;
    }
    else if(*buffer == '-'){
        infoAtomo.atomo = SUBTRAI;
        buffer++;
    }
    else if(*buffer == '/'){
        infoAtomo = reconhece_comentario();
    }
    else if(*buffer == '<'){
        infoAtomo = reconhece_menor();
    }
    else if(*buffer == '>'){
        infoAtomo = reconhece_maior();
    }
    else if(*buffer == '='){
        infoAtomo.atomo = IGUAL;
    }
    else if(*buffer == '#'){
        infoAtomo.atomo = DIFERENTE;
    }
    else if(*buffer == '\x0')
        infoAtomo.atomo = EOS;
    else
        infoAtomo.atomo = ERRO;

    if (infoAtomo.atomo != COMENTARIO_LONGO)
        infoAtomo.linha = contaLinha;
    return infoAtomo;
}
// funcao reconhe o atomo NUMERO
TInfoAtomo reconhece_numero(){
    char *pIniNum = buffer;
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;

    if(isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    return infoAtomo;

q1:
    if(isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    if(*buffer == 'e' || *buffer == 'E'){
        buffer++;
        goto q2;
    }else{
        goto q3;
    }

q2:
    if (*buffer == '+' || *buffer == '-'){
        buffer++;
    }
    if (isdigit(*buffer)){
        buffer++;
        goto q3;
    }
    return infoAtomo;

q3:
    if (isdigit(*buffer)){
        buffer++;
        goto q3;
    }

    // qualquer outra coisa
    //https://www.tutorialspoint.com/c_standard_library/c_function_strncpy.htm
    strncpy(infoAtomo.atributo_ID,pIniNum,buffer-pIniNum);
    infoAtomo.atributo_ID[buffer-pIniNum] = '\x0';
    infoAtomo.atributo_numero = atoi(infoAtomo.atributo_ID);
    infoAtomo.atomo = NUMERO;
    return infoAtomo;
}

// funcao reconhe o atomo IDENTIFICADOR
TInfoAtomo reconhece_id(){
    char *pIniID = buffer;
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;

    if(isalpha(*buffer)){
        buffer++;
        goto q1;
    }
    return infoAtomo;
q1:
    if (*buffer == '.'){
        goto q2;
    }
    if(isalpha(*buffer)||isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    if(isupper(*buffer))
        return infoAtomo;

q2:
    //Checar se tem mais de 15 caracteres
    if(buffer-pIniID > 15)
        return infoAtomo;

    strncpy(infoAtomo.atributo_ID,pIniID,buffer-pIniID);
    infoAtomo.atributo_ID[buffer-pIniID] = '\x0';

    // Checar se é uma palavra reservada
    // Se for igual a alguma delas, retorna o atomo correspondente
    for(int i=0;i<sizeof(palavras_reservadas)/sizeof(palavras_reservadas[0]);i++){
        if(strcmp(infoAtomo.atributo_ID,palavras_reservadas[i])==0){
            //infoAtomo.atomo = TAtomo(i); //esse daqui funciona no g++
            infoAtomo.atomo = i; //esse daqui funciona no gcc
            return infoAtomo;
        }
    }

    infoAtomo.atomo  = IDENTIFICADOR;
    return infoAtomo;
}

TInfoAtomo reconhece_comentario(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer == '/'){
        buffer++;
        goto q1;
    }

q1:
    if(*buffer == '/'){
        while (*buffer != '\n'){
            buffer++;
        }
        contaLinha++;
        buffer++;
        infoAtomo.atomo = COMENTARIO;
        return infoAtomo;

    }
    if (*buffer == '*'){
        infoAtomo.atomo = COMENTARIO_LONGO;
        infoAtomo.linha = contaLinha;
        goto q2;
    }
    if (*buffer != '/' && *buffer != '*'){
        buffer++;
        return infoAtomo;
    }

q2:
    if(*buffer != '*'){
        if (*buffer == '\n'){
            contaLinha++;
        }
        buffer++;
        goto q2;
    }
    if(*buffer == '*'){
        buffer++;
        goto q3;
    }

q3:
    if(*buffer != '/'){
        goto q2;
    }
    if(*buffer == '/'){
        buffer++;
    }

    return infoAtomo;
}

TInfoAtomo reconhece_menor(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = MENOR_QUE;
    buffer++;
    if(*buffer == '='){
        infoAtomo.atomo = MENOR_IGUAL;
        buffer++;
    }
    return infoAtomo;
}

TInfoAtomo reconhece_maior(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = MAIOR_QUE;
    buffer++;
    if(*buffer == '='){
        infoAtomo.atomo = MAIOR_IGUAL;
        buffer++;
    }
    return infoAtomo;
}

TInfoAtomo reconhece_atribuicao(){
    TInfoAtomo infoAtomo;
    infoAtomo.atomo = ERRO;
    if(*buffer == ':'){
        infoAtomo.atomo = DOIS_PONTOS;
        buffer++;
    }
    if(*buffer == '='){
        infoAtomo.atomo = ATRIBUICAO;
        buffer++;
    }
    return infoAtomo;
}

//###############################
// ANALISADOR SINTATICO
//###############################
void consome( TAtomo atomo ){
    if (atual == COMENTARIO || atual == COMENTARIO_LONGO){
        // printf("#  %03d: %s\n", InfoAtomo.linha, funcoes_sintatico[atual]);

        InfoAtomo = obter_atomo();
        atual = InfoAtomo.atomo;
    }
    if( atual == atomo ){
        if (atual == IDENTIFICADOR){
            //printf("#  %03d: %s - atributo: %s\n", InfoAtomo.linha, funcoes_sintatico[atual], InfoAtomo.atributo_ID);
        }else{
            //printf("#  %03d: %s\n", InfoAtomo.linha, funcoes_sintatico[atual]);
        }



        InfoAtomo = obter_atomo();
        atual = InfoAtomo.atomo;
    }
    else{
        //printf("erro sintatico: esperado [%c] encontrado [%c]\n",atomo,lookahead);
        printf("#  %03d: Erro sintatico: esperado [%s] encontrado [%s]\n", InfoAtomo.linha, funcoes_sintatico[atomo], funcoes_sintatico[atual]);
        exit(1);
    }
}

void programa(){
    consome(ALGORITMO);
    printf("\tINPP\n");
    consome(IDENTIFICADOR);
    consome(PONTO_VIRGULA);
    bloco();
    consome(PONTO);
    //consome(EOS);
    printf("\tPARA\n");
}

void bloco(){
    if(atual == VARIAVEL){
        declaracao_de_variaveis();
    }
    comando_composto();
}

void declaracao_de_variaveis(){
    consome(VARIAVEL);

    lista_nova_variavel();
    consome(DOIS_PONTOS);
    tipo();
    consome(PONTO_VIRGULA);
    while(atual == IDENTIFICADOR){
        lista_nova_variavel();
        consome(DOIS_PONTOS);
        tipo();
        consome(PONTO_VIRGULA);
    }
}

void lista_nova_variavel(){

    int count = 1;
    insereVariavel(InfoAtomo.atributo_ID, atual);
    consome(IDENTIFICADOR);
    while(atual == VIRGULA){
        count++;
        consome(VIRGULA);
        insereVariavel(InfoAtomo.atributo_ID, atual);
        consome(IDENTIFICADOR);
    }

    printf("\tAMEM %d\t # declaracao das variaveis ", count);
    for (int i=0;i<count;i++){
        printf("%s (end = %d) ", variaveis[contaVariavel-count+i].nome, contaVariavel-count+i);
    }
    printf("\n");

}

void lista_variavel(){
    consome(IDENTIFICADOR);
    while(atual == VIRGULA){
        consome(VIRGULA);
        consome(IDENTIFICADOR);
    }
}

void tipo(){
    if(atual == INTEIRO)
        consome(INTEIRO);
    else
        consome(LOGICO);
}

void comando_composto(){
    consome(INICIO);
    comando();
    while(atual == PONTO_VIRGULA){
        consome(PONTO_VIRGULA);
        comando();
    }
    consome(FIM);
}

void comando(){
    if(atual == IDENTIFICADOR){
        comando_atribuicao();
    }
    else if(atual == SE){
        comando_se();
    }
    else if(atual == ENQUANTO){
        comando_enquanto();
    }
    else if(atual == LEIA){
        comando_entrada();
    }
    else if(atual == ESCREVA){
        comando_saida();
    }
    else{
        comando_composto();
    }
}

void comando_atribuicao(){
    Variavel var = busca_tabela_variaveis(InfoAtomo.atributo_ID);
    consome(IDENTIFICADOR);
    consome(ATRIBUICAO);

    int isNumero = (atual == NUMERO);
    int num = InfoAtomo.atributo_numero;

    expressao();

    if (isNumero)
        printf("\tARMZ %d\t # %s := %d\n", var.endereco, var.nome, num);
    if (!isNumero){}
        //printf("\tARMZ %d\t # %s := %s\n", var.endereco, var.nome, InfoAtomo.atributo_ID);
}

void comando_se(){
    consome(SE);
    consome(ABRE_PARENTESES);
    expressao();
    consome(FECHA_PARENTESES);
    consome(ENTAO);
    comando();
    if(atual == SENAO){
        consome(SENAO);
        comando();
    }
}

void comando_enquanto(){
    int L1 = proximo_rotulo();
    int L2 = proximo_rotulo();

    
    consome(ENQUANTO);
    printf("L%d:\tNADA\n", L1);
    consome(ABRE_PARENTESES);
    expressao();
    consome(FECHA_PARENTESES);
    printf("\tDSVF L%d\n", L2);
    consome(FACA);
    comando();
    printf("\tDSVS L%d\n", L1);
    printf("L%d:\tNADA\n", L2);
}

int proximo_rotulo(){
    static int rotulo = 1;
    return rotulo++;
}

void comando_entrada(){
    consome(LEIA);

    printf("\tLEIT\n");
    consome(ABRE_PARENTESES);

    TInfoAtomo op = InfoAtomo;
    lista_variavel();
    consome(FECHA_PARENTESES);
    printf("\tARMZ %d\t # leia(%s)\n", busca_tabela_variaveis(op.atributo_ID).endereco, busca_tabela_variaveis(op.atributo_ID).nome);
}

void comando_saida(){
    consome(ESCREVA);
    consome(ABRE_PARENTESES);

    TInfoAtomo op = InfoAtomo;
    expressao();

    printf("\tIMPR\t # escreva(%s)\n", op.atributo_ID);
    // print line
    printf("%s", InfoAtomo.atributo_ID);

    while(atual == VIRGULA){
        consome(VIRGULA);
        expressao();
    }
    consome(FECHA_PARENTESES);
}

void expressao(){
    expressao_simples();

    if(atual == MENOR_QUE || atual == MAIOR_QUE || atual == MENOR_IGUAL || atual == MAIOR_IGUAL || atual == IGUAL || atual == DIFERENTE){
        TAtomo op = atual;
        relacional();
        expressao_simples();
        printf("\t%s\t # tradução da expressão condicional do enquanto \n", funcoes_sintatico[op]);
    }
}

void relacional(){
    if(atual == MENOR_QUE)
        consome(MENOR_QUE);
    else if(atual == MAIOR_QUE)
        consome(MAIOR_QUE);
    else if(atual == MENOR_IGUAL)
        consome(MENOR_IGUAL);
    else if(atual == MAIOR_IGUAL)
        consome(MAIOR_IGUAL);
    else if(atual == IGUAL)
        consome(IGUAL);
    else
        consome(DIFERENTE);
}

void expressao_simples(){
    if(atual == SOMA || atual == SUBTRAI){
        consome(atual);
    }
    termo();
    while(atual == SOMA || atual == SUBTRAI || atual == OU){
        TAtomo op = atual;
        consome(atual);
        termo();
        printf("\t%s\n", funcoes_sintatico[op]);
    }
}

void termo(){
    fator();
    while(atual == MULTIPLICA || atual == DIVIDE || atual == E){
        TAtomo op = atual;
        consome(atual);
        fator();
        printf("\t%s\t \n", funcoes_sintatico[op]);
    }
}

void fator(){
    if(atual == IDENTIFICADOR){
        int endereco = busca_tabela_variaveis(InfoAtomo.atributo_ID).endereco;
        printf("\tCRVL %d\n", endereco);
        consome(IDENTIFICADOR);
    }
    else if(atual == NUMERO){
        printf("\tCRCT %d\n", InfoAtomo.atributo_numero);
        consome(NUMERO);
    }
    else if(atual == VERDADEIRO)
        consome(VERDADEIRO);
    else if(atual == FALSO)
        consome(FALSO);
    else{
        consome(ABRE_PARENTESES);
        expressao();
        consome(FECHA_PARENTESES);
    }
}

