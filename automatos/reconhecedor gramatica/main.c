//
// <digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
//


#include <stdio.h>
#include <stdlib.h>

int parse_termo(char **input);

int parse_letra(char **input) {
    if (**input >= 'a' && **input <= 'z') {
        (*input)++;
        return 1;
    }
    return 0;
}

int parse_variavel(char **input) {
    while (**input == ' ') {
        (*input)++;
    }
    
    if (!parse_letra(input)) {
        return 0;
    }

    while (parse_letra(input)) {
        // Intentionally empty.
    }

    return 1;
}


int parse_digit(char **input) {
    if (**input >= '0' && **input <= '9') {
        (*input)++;  // Consumes the character from input.
        return 1;
    }
    return 0;
}

int parse_numero(char **input) {
    if (!parse_digit(input)) {
        return 0;
    }

    // Keep parsing digits until we can't anymore.
    while (parse_digit(input)) {
        // Intentionally empty; the loop condition does all the work.
    }

    return 1;
}

int parse_operator(char **input, char op) {
    if (**input == op) {
        (*input)++;
        return 1;
    }
    
    return 0;
}

// Updated parse_expr to handle termos
int parse_expr(char **input) {
    // Optional unary plus or minus
    while (**input == ' ') {
        (*input)++;
    }
    parse_operator(input, '+') || parse_operator(input, '-');

    if (!parse_termo(input)) {
        return 0;
    }
    while (**input == ' ') {
        (*input)++;
    }

    // Keep parsing termos preceded by a plus or minus until we can't anymore
    while ((parse_operator(input, '+') || parse_operator(input, '-')) && parse_termo(input)) {
        // intentionally empty
    }

    return 1;
}

int parse_factor(char **input) {
    // Try to parse a number first
    while (**input == ' ') {
            (*input)++;
    }
    if (parse_numero(input)) {
        return 1;
    }
    while (**input == ' ') {
            (*input)++;
    }

    // If not a number, it must be an expression in parentheses
    if (parse_operator(input, '(')) {
        if (parse_expr(input)) {
            if (parse_operator(input, ')')) {
                return 1;
            }
        }
    }

    return 0;
}

int parse_termo(char **input) {
    while (**input == ' ') {
            (*input)++;
    }
    if (!parse_factor(input)) {
        return 0;
    }
    while (**input == ' ') {
            (*input)++;
    }

    while ((parse_operator(input, '*') || parse_operator(input, '/')) && parse_factor(input)) {
        // intentionally empty
    }

    return 1;
}

int parse_keyword(char **input, char *keyword) {
    char *p = *input;
    while (*keyword != '\0') {
        if (*p != *keyword) {
            return 0;
        }
        p++;
        keyword++;
    }
    if (*p == ' ' || *p == '\0') {
        *input = p;
        return 1;
    }
    return 0;
}

int parse_declaracoes(char **input) {
    // Each declaration must start with the keyword 'int'
    

    if (!parse_keyword(input, "int")) {
        return 0;
    }

    // Skip whitespace
    while (**input == ' ') {
        (*input)++;
    }

    if (!parse_variavel(input)) {
        return 0;
    }

    // Must end with a semicolon
    if (!parse_operator(input, ';')) {
        return 0;
    }

    // Parse additional declarations
    while (parse_keyword(input, "int")) {
        // Skip whitespace
        while (**input == ' ') {
            (*input)++;
        }

        if (!parse_variavel(input)) {
            return 0;
        }

        // Must end with a semicolon
        if (!parse_operator(input, ';')) {
            return 0;
        }
    }

    return 1;
}

int parse_atribuicao(char **input) {
    if (!parse_variavel(input)) {
        return 0;
    }

    while (**input == ' ') {
        (*input)++;
    }

    if (!parse_operator(input, '=')) {
        return 0;
    }

    return parse_expr(input);
}

int parse_comandos(char **input) {
    if (!parse_atribuicao(input)) {
        return 0;
    }

    
    // Must end with a semicolon
    if (!parse_operator(input, ';')) {
        return 0;
    }

    // Parse additional commands
    while (parse_atribuicao(input)) {
        if (!parse_operator(input, ';')) {
            return 0;
        }
    }

    return 1;
}

int parse_programa(char **input) {
    if (!parse_declaracoes(input)) {
        return 0;
    }

    return parse_comandos(input);
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No input string\n");
        return 1;
    }

    char *input = argv[1];
    if (parse_programa(&input) && *input == '\0') {
        printf("The string belongs to the BNF\n");
    } else {
        printf("The string does not belong to the BNF\n");
    }

    return 0;
}

