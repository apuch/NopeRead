%{
    #include "lemon_parser.h"
    #include "lexer.internal.h"
    #include <stdio.h>
    int lexerLinenum = 0;

    void yyerror(const char*);

    LexToken lexerToken;
%}

%%

\+      return PLUS;
-       return MINUS;
\/      return DIVIDE;
\*      return TIMES;

[1-9][0-9]* {  
    lexerToken.iVal = atoi(yytext); 
    return INTEGER;
}

0[0-9]+ {
    lexerToken.iVal = strtol(yytext+1, NULL, 8);
    return INTEGER;
}

0x[0-9a-fA-F]+ {
    lexerToken.iVal = strtol(yytext+2, NULL, 16);
    return INTEGER;
}

\n      lexerLinenum++;
[ \t]   ; // ws -- ignore

.       yyerror("unknown character");
%%

