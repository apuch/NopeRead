#ifndef _LEXER_H
#define _LEXER_H

namespace Nope {

namespace Parser {
    namespace AST {
        class Terminal;
    }
}

namespace Lexer {

class PLexer;
class Lexer {
public:
    Lexer();
    ~Lexer();

    void SetText(const char* text);
    
    Parser::AST::Terminal* Lex();

private:
    PLexer* p;
};

}}

#endif

