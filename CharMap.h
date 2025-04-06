#ifndef CHARMAP_H
#define CHARMAP_H

typedef enum {
    WHITESPACE, LETTER, DIGIT, SPECIAL, QUOTE, ERROR, EOF_TYPE
} CHAR_TYPE;

void initCharMap();
CHAR_TYPE getCharType(char c);

#endif 