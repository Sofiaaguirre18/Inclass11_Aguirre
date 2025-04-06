#ifndef SCANNER_H
#define SCANNER_H

#include "CharMap.h"

#define MAX_LINE_LENGTH 1024
#define MAX_LEXEME_SIZE 256

typedef enum {
    ERROR_TOKEN, WORD, NUMBER, STRING, SYMBOL, EOF_TOKEN
} TOKEN_CODE;

typedef struct {
    char source[MAX_LINE_LENGTH];
    char lexeme[MAX_LEXEME_SIZE];
    TOKEN_CODE token;
    int cchar_ptr;
    char cchar;
    int line_number;
} Scanner;

void initScanner(Scanner* scanner, const char* source);
TOKEN_CODE nextToken(Scanner* scanner);
const char* tokenString(TOKEN_CODE token);

#endif 