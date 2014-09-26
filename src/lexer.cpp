
#include "lexer.h"
#include "lexer.defines.h"
#include "lexer.internal.h"

#include <string>


#define LOG_LEVEL LOG_LEVEL_SPAM
#include "debug.h"

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

}

namespace Nope {
namespace Lexer {


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



/***************************************************************************/

Lexer::Lexer() : p(new PLexer()) {}

Lexer::~Lexer() { delete p; }

int Lexer::Lex() { return p->Lex(); }
int Lexer::Lex(LexerToken* t) { return p->Lex(t); }

void Lexer::SetText(const char* data) { p->SetText(data); }

}}

int yyerror(const char* msg) {
    return Nope::Lexer::_instance->yyerror(msg);
}

int yywrap() {
    return Nope::Lexer::_instance->yywrap();
}

