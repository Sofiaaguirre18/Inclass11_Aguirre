#include <string.h>
#include <stdlib.h>
#include "Keywords.h"

void initKeywordList(KeywordList* list) {
    list->count = 0;

    const char* keywords[] = {
        "if", "else", "while", "for", "do",
        "int", "float", "char", "void",
        "return", "break", "continue"
    };

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        list->entries[i].keyword = strdup(keywords[i]);
        list->entries[i].code = (KW_CODES)i;
        list->count++;
    }
}

KW_CODES searchKeyword(KeywordList* list, const char* key) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->entries[i].keyword, key) == 0)
            return list->entries[i].code;
    }
    return KW_NOT_FOUND;
}

void freeKeywordList(KeywordList* list) {
    for (int i = 0; i < list->count; i++) {
        free(list->entries[i].keyword);
    }
    list->count = 0;
}

const char* keywordString(KW_CODES code) {
    switch (code) {
        case KW_IF: return "if";
        case KW_ELSE: return "else";
        case KW_WHILE: return "while";
        case KW_FOR: return "for";
        case KW_DO: return "do";
        case KW_INT: return "int";
        case KW_FLOAT: return "float";
        case KW_CHAR: return "char";
        case KW_VOID: return "void";
        case KW_RETURN: return "return";
        case KW_BREAK: return "break";
        case KW_CONTINUE: return "continue";
        default: return "UNKNOWN";
    }
}
