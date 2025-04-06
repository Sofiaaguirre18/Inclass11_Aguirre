#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define MAX_SYMBOLS 1000
#define MAX_LEXEME_SIZE 256

typedef struct {
    char name[MAX_LEXEME_SIZE];
    int line_declared;
} STEntry;

typedef struct {
    STEntry entries[MAX_SYMBOLS];
    int count;
} SymbolTable;

void initSymbolTable(SymbolTable* table);
void insertSymbol(SymbolTable* table, const char* name, int line);
int searchSymbol(SymbolTable* table, const char* name);

#endif