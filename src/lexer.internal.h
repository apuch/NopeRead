#ifndef _LEXER_INTERNAL_H
#define _LEXER_INTERNAL_H

struct LexToken {
    union {
        int iVal;
    };
};

extern struct LexToken lexerToken;

#endif

