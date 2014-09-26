#ifndef _LEXER_H
#define _LEXER_H

namespace Nope {
namespace Lexer {

struct LexerToken {
    int Id;
    union {
        int iVal;  
    };
};

class PLexer;
class Lexer {
public:
    Lexer();
    ~Lexer();

    void SetText(const char* text);
    
    int Lex();
    int Lex(LexerToken*);

private:
    PLexer* p;
};

}}

#endif

