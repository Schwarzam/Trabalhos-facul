/*
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

    "MENOR_QUE",
    "MAIOR_QUE",
    "MENOR_IGUAL",
    "MAIOR_IGUAL",
    "IGUAL",
    "DIFERENTE",

    "PONTO_VIRGULA", 
    "DOIS_PONTOS",
    "PONTO", 
    "VIRGULA",
    "ATRIBUICAO",

    "ABRE_PARENTESES",
    "FECHA_PARENTESES",

    "SOMA",
    "MULTIPLICA",
    "SUBTRAI",

    "COMENTARIO",
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
char *buffer = "/*\nprograma le dois numeros\ninteiros e encontra o maior\n*/\nalgoritmo exemplo2;\nvariavel maior,n1,n2:inteiro;\ninicio\nleia(n1);\nleia(n2);\nse( n1 > n2 ) entao\nmaior := n1\nsenao\nmaior := n2;\nescreva(maior) // imprime o maior valor\nfim.";

int contaLinha=1;

TInfoAtomo obter_atomo();
TInfoAtomo reconhece_numero();
TInfoAtomo reconhece_id();
TInfoAtomo reconhece_comentario();

TInfoAtomo InfoAtomo;
TAtomo atual;// lookahead = obter_atomo()

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


void consome( TAtomo atomo );
int main(){
    //printf("Analisando: %s\n",buffer);
    
    InfoAtomo = obter_atomo();
    atual = InfoAtomo.atomo;

    programa(); // chama o simbolo inicial da gramatica
    consome(EOS);

    printf("fim de programa.");

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
        infoAtomo.atomo = DOIS_PONTOS;
        buffer++;
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
        infoAtomo.atomo = COMENTARIO;
        reconhece_comentario();
    }
    else if(*buffer == '\x0')
        infoAtomo.atomo = EOS;
    else
        infoAtomo.atomo = ERRO;

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
    if(isalpha(*buffer)||isdigit(*buffer)){
        buffer++;
        goto q1;
    }
    if(isupper(*buffer))
        return infoAtomo;

    //Checar se tem mais de 15 caracteres
    if(buffer-pIniID > 15)
        return infoAtomo;

    strncpy(infoAtomo.atributo_ID,pIniID,buffer-pIniID);
    infoAtomo.atributo_ID[buffer-pIniID] = '\x0';

    // Checar se é uma palavra reservada
    // Se for igual a alguma delas, retorna o atomo correspondente
    for(int i=0;i<sizeof(palavras_reservadas)/sizeof(palavras_reservadas[0]);i++){
        if(strcmp(infoAtomo.atributo_ID,palavras_reservadas[i])==0){
            infoAtomo.atomo = TAtomo(i);
            return infoAtomo;
        }
    }
    
    infoAtomo.atomo  = IDENTIFICADOR;
    return infoAtomo;
}

TInfoAtomo reconhece_comentario(){
    TInfoAtomo infoAtomo;

q0:
    if(*buffer != '/'){
        buffer++;
        goto q0;
    }
    if(*buffer == '/'){
        buffer++;
        goto q1;
    }
    if (*buffer == '*'){
        buffer++;
        goto q2;
    }

q1:
    if(*buffer == '/'){
        buffer++;
        goto q1;
    }
    if (*buffer == '*'){
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

    infoAtomo.atomo = COMENTARIO;
    return infoAtomo;
}

//###############################
// ANALISADOR SINTATICO
//###############################
void consome( TAtomo atomo ){
    if( atual == atomo ){
        printf("#  %d: consome: %s\n", contaLinha, funcoes_sintatico[atual]);
        InfoAtomo = obter_atomo();
        atual = InfoAtomo.atomo;
    }
    else{
        //printf("erro sintatico: esperado [%c] encontrado [%c]\n",atomo,lookahead);
        printf("#%03d: Erro sintatico: esperado [%s] encontrado [%s]\n", InfoAtomo.linha,funcoes_sintatico[atomo],funcoes_sintatico[atual]);
        exit(1);
    }
}

void programa(){
    consome(ALGORITMO);
    consome(IDENTIFICADOR);
    consome(PONTO_VIRGULA);
    bloco();
    consome(PONTO);
    consome(EOS);
}

void bloco(){
    if(atual == VARIAVEL){
        declaracao_de_variaveis();
    }
    comando_composto();
}

void declaracao_de_variaveis(){
    consome(VARIAVEL);
    lista_variavel();
    consome(DOIS_PONTOS);
    tipo();
    consome(PONTO_VIRGULA);
    while(atual == IDENTIFICADOR){
        lista_variavel();
        consome(DOIS_PONTOS);
        tipo();
        consome(PONTO_VIRGULA);
    }
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
    consome(IDENTIFICADOR);
    consome(ATRIBUICAO);
    expressao();
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
    consome(ENQUANTO);
    consome(ABRE_PARENTESES);
    expressao();
    consome(FECHA_PARENTESES);
    consome(FACA);
    comando();
}

void comando_entrada(){
    consome(LEIA);
    consome(ABRE_PARENTESES);
    lista_variavel();
    consome(FECHA_PARENTESES);
}

void comando_saida(){
    consome(ESCREVA);
    consome(ABRE_PARENTESES);
    expressao();
    while(atual == VIRGULA){
        consome(VIRGULA);
        expressao();
    }
    consome(FECHA_PARENTESES);
}

void expressao(){
    expressao_simples();
    if(atual == MENOR_QUE || atual == MAIOR_QUE || atual == MENOR_IGUAL || atual == MAIOR_IGUAL || atual == IGUAL || atual == DIFERENTE){
        relacional();
        expressao_simples();
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
        consome(atual);
        termo();
    }
}

void termo(){
    fator();
    while(atual == MULTIPLICA || atual == DIVIDE || atual == E){
        consome(atual);
        fator();
    }
}

void fator(){
    if(atual == IDENTIFICADOR)
        consome(IDENTIFICADOR);
    else if(atual == NUMERO)
        consome(NUMERO);
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

