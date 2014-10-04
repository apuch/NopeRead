%token_type {Symbol*}

%left PLUS MINUS.   
%left DIVIDE TIMES.  
   
%include {   
    #include <iostream>
    #include <assert.h>
    #include "lemon_parser.h"
    #include "tokenizer.h"

    using namespace Nope::Parser::AST;

    namespace Nope {
        namespace Parser {
            namespace Internal {
                Symbol* createBinOp(Symbol* opA, Symbol* op, Symbol* opB);
            }
        }
    }

    using namespace Nope::Parser::AST;
    using namespace Nope::Parser::Internal;
}  
   
%syntax_error {  
  std::cout << "Syntax error!" << std::endl;  
}   
   
program ::= expr(A).   { std::cout << "Result=" << A << std::endl; }  
   
expr(A) ::= expr(B) MINUS(C)  expr(D).   { A = createBinOp(B,C,D); }
expr(A) ::= expr(B) PLUS(C)   expr(D).   { A = createBinOp(B,C,D); }
expr(A) ::= expr(B) TIMES(C)  expr(D).   { A = createBinOp(B,C,D); }
expr(A) ::= expr(B) DIVIDE(C) expr(D).   { A = createBinOp(B,C,D); }
expr(A) ::= BRACE_L expr(B) BRACE_R .    { A = B; }


expr(A) ::= INTEGER(B). { A = B; } 

