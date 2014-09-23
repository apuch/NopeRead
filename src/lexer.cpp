
#include "lexer.h"
#include "lexer.defines.h"
#include "lexer.internal.h"

#include <string>


#define LOG_LEVEL LOG_LEVEL_SPAM
#include "debug.h"

using namespace Nope::Lexer;

namespace {

struct BufferState {
    YY_BUFFER_STATE m_state;
    BufferState(const char* text) {
        m_state = yy_scan_string(text);
    }
    ~BufferState() { 
        yy_delete_buffer(m_state);
    }
};

class PLexer;

PLexer *_instance = NULL;

class PLexer {
public:
    std::string m_errormsg;
    BufferState* m_bufferState;

    PLexer() {
        _instance = this;      
        m_bufferState = NULL;
    }

    ~PLexer() {
        _instance = NULL;
        delete m_bufferState;
    }

    void freeData() {
        delete m_bufferState;
    }

    void SetText(const char* data) {
        freeData();
        m_bufferState = new BufferState(data);
    }

    int Lex() {
        int res = yylex();
        return res;
    }

    int Lex(LexerToken* token) {
        token->Id = yylex();
        memcpy(&token->iVal, &lexerToken, sizeof(lexerToken));
        return token->Id;
    }
    
    int yyerror(const char* msg) {
        m_errormsg = msg;
        TR_ERR("Parsing error - line %d, text `%s`, msg `%s`", 
            yylineno, yytext, msg);
        
    }

    int yywrap() {
        return 1;
    }
};

}

int yyerror(const char* msg) {
    return _instance->yyerror(msg);
}

int yywrap() {
    return _instance->yywrap();
}

/***************************************************************************/

#define P ((PLexer*)pimpl)

namespace Nope {
namespace Lexer {

Lexer::Lexer() : pimpl(new PLexer()) {}

Lexer::~Lexer() { delete P; }

int Lexer::Lex() { return P->Lex(); }
int Lexer::Lex(LexerToken* t) { return P->Lex(t); }

void Lexer::SetText(const char* data) { P->SetText(data); }

}}

