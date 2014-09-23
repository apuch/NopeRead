#ifndef _LEXER_H
#define _LEXER_H

struct LexerToken {
    int Id;
    union {
        int iVal;  
    };
};

class Lexer {
public:
    Lexer();
    ~Lexer();

    void SetText(const char* text);
    
    int Lex();
    int Lex(LexerToken*);

private:
    void* pimpl;

};

#endif

