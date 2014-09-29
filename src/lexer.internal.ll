%{
    #include "lemon_parser.h"
    #include "lexer.internal.h"    
    #include "tokenizer.h"
    #include <stdio.h>

    namespace Nope {
        namespace Lexer {
            Parser::AST::Terminal* _lexerTerminal;
        }
    }

    using namespace Nope::Parser;

    static int _lexerLinenum = 0;
    static int _lexerColumn = 0;
    static const char* lexerLineStart = NULL;

    void yyerror(const char*);

    static void setTerm(AST::Terminal *term);

    using namespace Nope::Parser::AST;
    using namespace Nope::Lexer;

    #define YY_USER_ACTION _lexerColumn += (*yytext == '\t') ? 4 : yyleng;
%}

%%


\+      return PLUS;
-       return MINUS;
\/      return DIVIDE;
\*      return TIMES;
\(      return BRACE_L;
\)      return BRACE_R;

([1-9][0-9]*|0) {  
    auto term = new AST::IntTerminal();
    term->SetNumber(atoi(yytext));
    setTerm(term);
    return INTEGER;
}


0[0-9]+ {
    auto term = new AST::IntTerminal();
    term->SetNumber(strtol(yytext+1, NULL, 8));
    setTerm(term);
    return INTEGER;
}

0x[0-9a-fA-F]+ {
    auto term = new AST::IntTerminal();
    term->SetNumber(strtol(yytext+2, NULL, 16));
    setTerm(term);
    return INTEGER;
}

\n      {
            _lexerLinenum++;
            _lexerColumn = 0;
            lexerLineStart = yytext + 1;
        }

[ \r\t]   ; // ws -- ignore

.       yyerror("unknown character");
%%


static void setTerm(AST::Terminal* term) {
    term->SetPosition(Position(_lexerLinenum + 1, _lexerColumn - yyleng + 1));
    _lexerTerminal = term;
}

void _lexerResetPos() {
    _lexerLinenum = 0;
    _lexerColumn = 0;
}

void Nope::Lexer::_resetState() {
    _lexerLinenum = 0;
}

