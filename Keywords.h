#ifndef KEYWORDLIST_H
#define KEYWORDLIST_H

#define MAX_KEYWORDS 100

typedef enum {
    KW_NOT_FOUND = -1,
    KW_IF, KW_ELSE, KW_WHILE, KW_FOR, KW_DO,
    KW_INT, KW_FLOAT, KW_CHAR, KW_VOID,
    KW_RETURN, KW_BREAK, KW_CONTINUE
} KW_CODES;

typedef struct {
    char* keyword;
    KW_CODES code;
} KeywordEntry;

typedef struct {
    KeywordEntry entries[MAX_KEYWORDS];
    int count;
} KeywordList;

void initKeywordList(KeywordList* list);
KW_CODES searchKeyword(KeywordList* list, const char* key);
void freeKeywordList(KeywordList* list);
const char* keywordString(KW_CODES code);  

#endif 
