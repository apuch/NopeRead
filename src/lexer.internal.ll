%{
    #include "lemon_parser.h"
    #include "lexer.internal.h"    
    #include "tokenizer.h"
    #include <stdio.h>

    namespace Nope {
        namespace Parser {
            namespace AST {
                Terminal* _lexerTerminal;
            }
        }
    }
    //Nope::Parser::AST::Terminal *_lexerTerminal;

    using namespace Nope::Parser;

    static int lexerLinenum = 0;

    void yyerror(const char*);

    static void setTerm(AST::Terminal *term);

    using namespace Nope::Parser::AST;
%}

%%

\+      return PLUS;
-       return MINUS;
\/      return DIVIDE;
\*      return TIMES;
\(      return BRACE_L;
\)      return BRACE_R;

[1-9][0-9]* {  
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

\n      lexerLinenum++;
[ \r\t]   ; // ws -- ignore

.       yyerror("unknown character");
%%


static void setTerm(AST::Terminal* term) {
    _lexerTerminal = term;
}

