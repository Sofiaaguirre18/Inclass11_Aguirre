#include <string.h>
#include <stdio.h>
#include "CharMap.h"
#include "Scanner.h"
#include "Keywords.h"
#include "SymbolTable.h"

void processTokens(FILE* input_file, FILE* output_file, int operation) {
    char line[MAX_LINE_LENGTH] = {0};
    char source_code[MAX_LINE_LENGTH * 100] = {0}; 
    
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        strcat(source_code, line);
    }
    
    initCharMap();
    Scanner scanner;
    initScanner(&scanner, source_code);
    
    KeywordList kwlist;
    initKeywordList(&kwlist);
    
    SymbolTable symtable;
    initSymbolTable(&symtable);
    
    switch (operation) {
        case 1: 
            fprintf(output_file, "TOKEN STREAM:\n");
            fprintf(output_file, "Line\tToken Type\tLexeme\n");
            fprintf(output_file, "------------------------------\n");
            
            while (1) {
                TOKEN_CODE token = nextToken(&scanner);
                if (token == EOF_TOKEN)
                    break;
                
                fprintf(output_file, "%d\t%s\t\t%s\n", 
                        scanner.line_number, tokenString(token), scanner.lexeme);
            }
            break;
            
        case 2: 
            fprintf(output_file, "KEYWORDS FOUND:\n");
            fprintf(output_file, "Line\tKeyword\n");
            fprintf(output_file, "------------------------------\n");
            
            initScanner(&scanner, source_code); 
            while (1) {
                TOKEN_CODE token = nextToken(&scanner);
                if (token == EOF_TOKEN)
                    break;
                
                if (token == WORD) {
                    KW_CODES kw_code = searchKeyword(&kwlist, scanner.lexeme);
                    if (kw_code != KW_NOT_FOUND) {
                        fprintf(output_file, "%d\t%s\n", 
                                scanner.line_number, scanner.lexeme);
                    }
                }
            }
            break;
            
        case 3: 
            fprintf(output_file, "SYMBOL TABLE:\n");
            fprintf(output_file, "Index\tSymbol\t\tLine Declared\n");
            fprintf(output_file, "------------------------------\n");
            
            initScanner(&scanner, source_code); 
            while (1) {
                TOKEN_CODE token = nextToken(&scanner);
                if (token == EOF_TOKEN)
                    break;
                
                if (token == WORD) {
                    KW_CODES kw_code = searchKeyword(&kwlist, scanner.lexeme);
                    if (kw_code == KW_NOT_FOUND) { 
                        int pos = searchSymbol(&symtable, scanner.lexeme);
                        if (pos == -1) { 
                            insertSymbol(&symtable, scanner.lexeme, scanner.line_number);
                        }
                    }
                }
            }
            
            for (int i = 0; i < symtable.count; i++) {
                fprintf(output_file, "%d\t%-15s\t%d\n", 
                        i, symtable.entries[i].name, symtable.entries[i].line_declared);
            }
            break;
            
        case 4:
            fprintf(output_file, "TOKEN STREAM:\n");
            fprintf(output_file, "Line\tToken Type\tLexeme\n");
            fprintf(output_file, "------------------------------\n");
            
            while (1) {
                TOKEN_CODE token = nextToken(&scanner);
                if (token == EOF_TOKEN)
                    break;
                
                fprintf(output_file, "%d\t%s\t\t%s\n",
                        scanner.line_number, tokenString(token), scanner.lexeme);
            }
            
            fprintf(output_file, "\n");
            
            fprintf(output_file, "KEYWORDS FOUND:\n");
            fprintf(output_file, "Line\tKeyword\n");
            fprintf(output_file, "------------------------------\n");
            
            initScanner(&scanner, source_code);
            
            while (1) {
                TOKEN_CODE token = nextToken(&scanner);
                if (token == EOF_TOKEN)
                    break;
                
                if (token == WORD) {
                    KW_CODES kw_code = searchKeyword(&kwlist, scanner.lexeme);
                    if (kw_code != KW_NOT_FOUND) {
                        fprintf(output_file, "%d\t%s\n", 
                                scanner.line_number, scanner.lexeme);
                    }
                    else {
                        int pos = searchSymbol(&symtable, scanner.lexeme);
                        if (pos == -1) { 
                            insertSymbol(&symtable, scanner.lexeme, scanner.line_number);
                        }
                    }
                }
            }
            
            fprintf(output_file, "\n");  
            
            fprintf(output_file, "SYMBOL TABLE:\n");
            fprintf(output_file, "Index\tSymbol\t\tLine Declared\n");
            fprintf(output_file, "------------------------------\n");
            
            for (int i = 0; i < symtable.count; i++) {
                fprintf(output_file, "%d\t%-15s\t%d\n", 
                        i, symtable.entries[i].name, symtable.entries[i].line_declared);
            }
            break;
    }
    
    freeKeywordList(&kwlist);
}

int main() {
    int choice;
    FILE *input_file, *output_file;
    
    input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Could not open input.txt for reading.\n");
        return 1;
    }
    
    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Could not open output.txt for writing.\n");
        fclose(input_file);
        return 1;
    }
    
    printf("Lexer Driver Program\n");
    printf("-----------------------\n");
    printf("[1] Generate Token Streams\n");
    printf("[2] List Keywords\n");
    printf("[3] Generate Symbol Table\n");
    printf("[4] Execute All\n");
    printf("Enter choice: ");
    
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Invalid choice. Exiting.\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }
    
    processTokens(input_file, output_file, choice);
    
    printf("Processing complete. Results written to output.txt\n");
    
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}