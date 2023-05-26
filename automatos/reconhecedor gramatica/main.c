//
// <digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
//

#include <stdio.h>
#include <stdlib.h>

char arquivo[10000];
int indice_arquivo = 0;
int p_novas_linhas[100];

int parse_letra();
int parse_variavel();
int parse_digito();
int parse_numero();
int parse_operator(char op);
int parse_expr();
int parse_factor();
int parse_termo();
int parse_palavra(char *palavra);
int parse_declaracoes();
int parse_atribuicao();
int parse_comandos();
int parse_programa();

int indice_erro = -1;

void registrar_erro(int erro){
    if (indice_erro == -1) {
        indice_erro = erro;
    }
}

void proximo_terminal(){
    while (arquivo[indice_arquivo] == ' ') {
        indice_arquivo++;
    }
}

int parse_letra() {
    if (arquivo[indice_arquivo] >= 'a' && arquivo[indice_arquivo] <= 'z') {
        indice_arquivo++;
        return 1;
    }
    return 0;
}

int parse_variavel() {
    proximo_terminal();

    if (!parse_letra()) {
        return 0;
    }
    while (parse_letra()) {}
    return 1;
}


int parse_digito() {
    if (arquivo[indice_arquivo] >= '0' && arquivo[indice_arquivo] <= '9') {
        indice_arquivo++;  // Consome o digito
        return 1;
    }
    return 0;
}

int parse_numero() {
    if (!parse_digito()) {
        return 0;
    }

    // Keep parsing digits until we can't anymore.
    while (parse_digito()) {
        // Intentionally empty; the loop condition does all the work.
    }

    return 1;
}

int parse_operator(char op) {
    if (arquivo[indice_arquivo] == op) {
        indice_arquivo++;
        return 1;
    }
    return 0;
}

// Updated parse_expr to handle termos
int parse_expr() {
    // Optional unary plus or minus
    proximo_terminal();
    parse_operator('+') || parse_operator('-');

    if (!parse_termo()) {
        registrar_erro(indice_arquivo);
        return 0;
    }
    proximo_terminal();

    // Keep parsing termos preceded by a plus or minus until we can't anymore
    while ((parse_operator('+') || parse_operator('-')) && parse_termo()) {}
    return 1;
}

int parse_factor() {
    // Try to parse a number first
    proximo_terminal();
    if (parse_numero()) {
        return 1;
    }
    proximo_terminal();

    // If not a number, it must be an expression in parentheses
    if (parse_operator('(')) {
        if (parse_expr()) {
            if (parse_operator(')')) {
                return 1;
            }
        }
    }

    return 0;
}

int parse_termo() {
    proximo_terminal();
    if (!parse_factor()) {
        registrar_erro(indice_arquivo);
        return 0;
    }
    proximo_terminal();

    while ((parse_operator('*') || parse_operator('/')) && parse_factor()) {}
    return 1;
}

int parse_palavra(char *palavra) {
    proximo_terminal();
    char *p = &arquivo[indice_arquivo];

    while (*palavra != '\0') {
        if (*p != *palavra) {
            return 0;  // Return 0 on failure.
        }
        p++;
        palavra++;
    }
    if (*p == ' ' || *p == '\0') {
        indice_arquivo = p - arquivo;  // Update the global index on success.
        return 1;
    }
    registrar_erro(indice_arquivo);
    return 0;  // Return 0 on failure.
}

int parse_declaracoes() {
    
    // Each declaration must start with the keyword 'int'
    proximo_terminal();
    if (!parse_palavra("int")) {
        registrar_erro(indice_arquivo);
        return 0;
    }

    // Skip whitespace
    proximo_terminal();

    
    if (!parse_variavel()) {   
        registrar_erro(indice_arquivo);
        return 0;
    }
    

    // Must end with a semicolon
    if (!parse_operator(';')) {
        registrar_erro(indice_arquivo);
        return 0;
    }

    // Parse additional declarations
    while (parse_palavra("int")) {
        // Skip whitespace
        proximo_terminal();

        if (!parse_variavel()) {
            registrar_erro(indice_arquivo);
            return 0;
        }

        // Must end with a semicolon
        if (!parse_operator(';')) {
            registrar_erro(indice_arquivo);
            return 0;
        }
    }

    

    return 1;
}

int parse_atribuicao() {
    if (!parse_variavel()) {
        registrar_erro(indice_arquivo);
        return 0;
    }

    proximo_terminal();

    if (!parse_operator('=')) {
        registrar_erro(indice_arquivo);
        return 0;
    }

    return parse_expr();
}

int parse_comandos() {
    if (!parse_atribuicao()) {
        registrar_erro(indice_arquivo);
        return 0;
    }

    
    // Must end with a semicolon
    if (!parse_operator(';')) {
        

        registrar_erro(indice_arquivo);
        return 0;
    }

    // Parse additional commands
    while (parse_atribuicao()) {
        printf("indice: %d\n", indice_arquivo);
        if (!parse_operator(';')) {
            //registrar_erro(indice_arquivo);
            return 1;
        }
    }

    return 1;
}

int parse_programa() {
    if (!parse_declaracoes()) {
        registrar_erro(indice_arquivo);
        return 0;
    }

    

    return parse_comandos();
}



int main() {
    char filename[256];

    //Pegar nome do arquivo
    printf("Enter the filename: ");
    scanf("%255s", filename); // Limit the input to 255 characters to avoid buffer overflow

    // Abrir arquivo
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char ch;
    int line_count = 0;

    int indice_nova_linha = 0;
    int indice_arquivo = 0;

    char last_char = ' ';
    int waiting_next_line = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            // Nova linha
            arquivo[indice_arquivo] = ' ';
            indice_arquivo ++;

            p_novas_linhas[indice_nova_linha] = indice_arquivo;
            indice_nova_linha ++;

            last_char = ' ';
            waiting_next_line = 0;
            continue;
        }
        
        if (waiting_next_line){
            continue;
        }

        if (ch == '/' && last_char == '/'){
            waiting_next_line = 1;
            continue;
        }
       
        if (ch != '/'){
            arquivo[indice_arquivo] = ch;
            indice_arquivo ++;
            last_char = ch;
            continue;
        }else{
            last_char = ch;
            continue;
        }

        if (ch == ' ') {
            // Espaço
            last_char = ' ';
            continue;
        }

    }

    fclose(file);

    int res = parse_programa();

    if (res) {
        printf("Entrada aceita sem erros.\n");
        printf("%d linhas analisadas.\n", indice_nova_linha + 1);
    } else {
        printf("Falha na derivacao\n");

        int linha_erro = 0;
        for (int i = 0; i <= indice_nova_linha; i++) {
            if (indice_erro < p_novas_linhas[i]) {
                linha_erro = i + 1;
                break;
            }
            if (p_novas_linhas[i] == 0){
                linha_erro = i + 1;
                break;
            }
        }

        printf("Erro na linha %d\n", linha_erro);
    }

    

    return 0;
}

