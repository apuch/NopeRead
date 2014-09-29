#ifndef _LEXER_INTERNAL_H
#define _LEXER_INTERNAL_H

namespace Nope {
    namespace Parser {
        namespace AST {
            class Terminal;            
        }
    }
    namespace Lexer {
        extern Parser::AST::Terminal* _lexerTerminal;
        void _resetState();
    }
}

void _lexerResetPos();

#endif

