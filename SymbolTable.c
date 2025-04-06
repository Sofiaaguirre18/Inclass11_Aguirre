#include "SymbolTable.h"
#include <string.h>

void initSymbolTable(SymbolTable* table) {
    table->count = 0;
}

void insertSymbol(SymbolTable* table, const char* name, int line) {
    if (table->count < MAX_SYMBOLS) {
        strcpy(table->entries[table->count].name, name);
        table->entries[table->count].line_declared = line;
        table->count++;
    }
}

int searchSymbol(SymbolTable* table, const char* name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(name, table->entries[i].name) == 0)
            return i;
    }
    return -1;
}
