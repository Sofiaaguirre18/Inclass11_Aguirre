#include <string.h>
#include <stdio.h>
#include "Scanner.h"
#include "CharMap.h"

extern const char EOF_CHAR;

void initScanner(Scanner* scanner, const char* source) {
    strcpy(scanner->source, source);
    scanner->cchar_ptr = 0;
    scanner->cchar = scanner->source[0];
    scanner->line_number = 1;
    memset(scanner->lexeme, 0, MAX_LEXEME_SIZE);
}

static void getNextChar(Scanner* scanner) {
    scanner->cchar = scanner->source[++scanner->cchar_ptr];
    
    if (scanner->cchar == '\0')
        scanner->cchar = EOF_CHAR;
}

static void addToLexeme(Scanner* scanner, char c) {
    int len = strlen(scanner->lexeme);
    if (len < MAX_LEXEME_SIZE - 1) {
        scanner->lexeme[len] = c;
        scanner->lexeme[len + 1] = '\0';
    }
}

static void skipWhiteSpace(Scanner* scanner) {
    while (getCharType(scanner->cchar) == WHITESPACE) {
        if (scanner->cchar == '\n')
            scanner->line_number++;
        getNextChar(scanner);
    }
}

static TOKEN_CODE handleWord(Scanner* scanner) {
    memset(scanner->lexeme, 0, MAX_LEXEME_SIZE);
    
    do {
        addToLexeme(scanner, scanner->cchar);
        getNextChar(scanner);
    } while (getCharType(scanner->cchar) == LETTER || 
             getCharType(scanner->cchar) == DIGIT);
             
    return WORD;
}

static TOKEN_CODE handleNumber(Scanner* scanner) {
    memset(scanner->lexeme, 0, MAX_LEXEME_SIZE);
    
    do {
        addToLexeme(scanner, scanner->cchar);
        getNextChar(scanner);
    } while (getCharType(scanner->cchar) == DIGIT);
    
    if (scanner->cchar == '.') {
        addToLexeme(scanner, scanner->cchar);
        getNextChar(scanner);
        
        if (getCharType(scanner->cchar) != DIGIT)
            return ERROR_TOKEN;
            
        do {
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
        } while (getCharType(scanner->cchar) == DIGIT);
    }
    
    return NUMBER;
}

static TOKEN_CODE handleString(Scanner* scanner) {
    memset(scanner->lexeme, 0, MAX_LEXEME_SIZE);
    
    addToLexeme(scanner, scanner->cchar);
    getNextChar(scanner);
    
    while (scanner->cchar != '\"' && scanner->cchar != EOF_CHAR) {
        if (scanner->cchar == '\\') {
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            if (scanner->cchar == EOF_CHAR)
                return ERROR_TOKEN;
        }
        
        if (scanner->cchar == '\n') {
            scanner->line_number++;
        }
        
        addToLexeme(scanner, scanner->cchar);
        getNextChar(scanner);
    }
    
    if (scanner->cchar == '\"') {
        addToLexeme(scanner, scanner->cchar);
        getNextChar(scanner);
        return STRING;
    }
    
    return ERROR_TOKEN;
}

static TOKEN_CODE handleSpecial(Scanner* scanner) {
    memset(scanner->lexeme, 0, MAX_LEXEME_SIZE);
    
    switch (scanner->cchar) {
        case '/':
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            
            if (scanner->cchar == '/') {
                while (scanner->cchar != '\n' && scanner->cchar != EOF_CHAR)
                    getNextChar(scanner);
                
                if (scanner->cchar == '\n') {
                    scanner->line_number++;
                    getNextChar(scanner);
                }
                
                skipWhiteSpace(scanner);
                return nextToken(scanner);
                
            } else if (scanner->cchar == '*') {
                getNextChar(scanner);
                
                char prev_char = 0;
                while (!(prev_char == '*' && scanner->cchar == '/') && 
                       scanner->cchar != EOF_CHAR) {
                    
                    if (scanner->cchar == '\n')
                        scanner->line_number++;
                        
                    prev_char = scanner->cchar;
                    getNextChar(scanner);
                }
                
                if (scanner->cchar == '/') {
                    getNextChar(scanner);
                    
                    skipWhiteSpace(scanner);
                    return nextToken(scanner);
                }
                
                return ERROR_TOKEN;
            }
            
            return SYMBOL;
            
        case '<':
        case '>':
        case '=':
        case '!':
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            
            if (scanner->cchar == '=') {
                addToLexeme(scanner, scanner->cchar);
                getNextChar(scanner);
            }
            return SYMBOL;
            
        case '&':
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            
            if (scanner->cchar == '&') {
                addToLexeme(scanner, scanner->cchar);
                getNextChar(scanner);
            }
            return SYMBOL;
            
        case '|':
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            
            if (scanner->cchar == '|') {
                addToLexeme(scanner, scanner->cchar);
                getNextChar(scanner);
            }
            return SYMBOL;
            
        case '+':
        case '-':
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            
            if (scanner->cchar == '+' || scanner->cchar == '-' || scanner->cchar == '=') {
                addToLexeme(scanner, scanner->cchar);
                getNextChar(scanner);
            }
            return SYMBOL;
            
        default:
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            return SYMBOL;
    }
}

TOKEN_CODE nextToken(Scanner* scanner) {
    skipWhiteSpace(scanner);
    
    if (scanner->cchar == EOF_CHAR) {
        strcpy(scanner->lexeme, "EOF");
        return EOF_TOKEN;
    }
    
    switch (getCharType(scanner->cchar)) {
        case LETTER:
            return handleWord(scanner);
            
        case DIGIT:
            return handleNumber(scanner);
            
        case QUOTE:
            return handleString(scanner);
            
        case SPECIAL:
            return handleSpecial(scanner);
            
        case ERROR:
        default:
            memset(scanner->lexeme, 0, MAX_LEXEME_SIZE);
            addToLexeme(scanner, scanner->cchar);
            getNextChar(scanner);
            return ERROR_TOKEN;
    }
}

const char* tokenString(TOKEN_CODE token) {
    switch (token) {
        case ERROR_TOKEN: return "ERROR";
        case WORD: return "WORD";
        case NUMBER: return "NUMBER";
        case STRING: return "STRING";
        case SYMBOL: return "SYMBOL";
        case EOF_TOKEN: return "EOF";
        default: return "UNKNOWN";
    }
}