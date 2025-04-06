#include "CharMap.h"

#define ALL_CHARS 256
const char EOF_CHAR = 127;

CHAR_TYPE char_table[ALL_CHARS];

void initCharMap() {
    int i;
    for (i = 0; i < ALL_CHARS; i++)
        char_table[i] = ERROR;

    for (i = 'A'; i <= 'Z'; i++)
        char_table[i] = LETTER;
    for (i = 'a'; i <= 'z'; i++)
        char_table[i] = LETTER;
    char_table['_'] = LETTER;

    for (i = '0'; i <= '9'; i++)
        char_table[i] = DIGIT;

    char_table['+'] = SPECIAL;
    char_table['-'] = SPECIAL;
    char_table['*'] = SPECIAL;
    char_table['/'] = SPECIAL;
    char_table['='] = SPECIAL;
    char_table['('] = SPECIAL;
    char_table[')'] = SPECIAL;
    char_table['{'] = SPECIAL;
    char_table['}'] = SPECIAL;
    char_table[';'] = SPECIAL;
    char_table[','] = SPECIAL;
    char_table['.'] = SPECIAL;
    char_table['<'] = SPECIAL;
    char_table['>'] = SPECIAL;
    char_table['!'] = SPECIAL;
    char_table['&'] = SPECIAL;
    char_table['|'] = SPECIAL;
    char_table['#'] = SPECIAL;
    char_table['['] = SPECIAL;
    char_table[']'] = SPECIAL;

    char_table['\n'] = WHITESPACE;
    char_table['\t'] = WHITESPACE;
    char_table[' '] = WHITESPACE;
    char_table['\r'] = WHITESPACE;

    char_table['\"'] = QUOTE;

    char_table[EOF_CHAR] = EOF_TYPE;
}

CHAR_TYPE getCharType(char c) {
    return char_table[(unsigned char)c];
}