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
char *buffer ="+ +       1.0012 22121.0 var";
int contaLinha=1;

TInfoAtomo obter_atomo();
TInfoAtomo reconhece_numero();
TInfoAtomo reconhece_id();

TInfoAtomo InfoAtomo;
TAtomo atual;// lookahead = obter_atomo()

// E ::= numero | identificador | +EE | *EE
void E(); // prototipacao de funcao
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
    printf("Analisando: %s\n",buffer);
    
    InfoAtomo = obter_atomo();
    atual = InfoAtomo.atomo;

    E(); // chama o simbolo inicial da gramatica
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
            infoAtomo.atomo = i;
            return infoAtomo;
        }
    }
    
    infoAtomo.atomo  = IDENTIFICADOR;
    return infoAtomo;
}

//###############################
// ANALISADOR SINTATICO
//###############################
void consome( TAtomo atomo ){
    if( atual == atomo ){
        //    lookahead = *buffer++;
        InfoAtomo = obter_atomo();
        atual = InfoAtomo.atomo;
    }
    else{
        //printf("erro sintatico: esperado [%c] encontrado [%c]\n",atomo,lookahead);
        printf("#%03d: Erro sintatico: esperado [%s] encontrado [%s]\n", InfoAtomo.linha,funcoes_sintatico[atomo],funcoes_sintatico[atual]);
        exit(1);
    }
}

// E ::= numero | identificador | +EE | *EE
void E(){
    switch( atual ){
        case OP_SOMA:
            consome(OP_SOMA);
            E();E();
            break;
        case OP_MULT:
            //consome *
            consome(OP_MULT);
            E();E();
            break;
        case IDENTIFICADOR:
            consome(IDENTIFICADOR);
            break;
        default:
            consome(NUMERO);
    }


}



