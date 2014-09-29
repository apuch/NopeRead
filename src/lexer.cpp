
#include "lexer.h"
#include "lexer.defines.h"
#include "lexer.internal.h"

#include "tokenizer.h"

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

using namespace Nope::Parser::AST;

namespace Nope {
namespace Lexer {


class PLexer;

PLexer *_instance = NULL;

class PLexer {
public:
    std::string m_errormsg;
    BufferState* m_bufferState;
    Symbol* m_sym;

    PLexer() {
        _instance = this;      
        m_bufferState = NULL;
        m_sym = NULL;
    }

    ~PLexer() {
        _instance = NULL;
        delete m_bufferState;
        delete m_sym;
    }

    void freeData() {
        delete m_bufferState;
    }

    void SetText(const char* data) {
        freeData();
        m_bufferState = new BufferState(data);
        _lexerResetPos();
    }

    Terminal* Lex() {
        int r = yylex();
        if (_lexerTerminal != NULL && r != 0)
            _lexerTerminal->SetCode(r);
        return r == 0 ? NULL : _lexerTerminal;
    }

    int yyerror(const char* msg) {
        m_errormsg = msg;
        TR_ERR("Parsing error - line %d, text `%s`, msg `%s`", 
            yylineno, yytext, msg);
        return 0;
        
    }

    int yywrap() {
        return 1;
    }
};



/***************************************************************************/

Lexer::Lexer() : p(new PLexer()) {}

Lexer::~Lexer() { delete p; }

Terminal* Lexer::Lex() {
    return p->Lex();
}

void Lexer::SetText(const char* data) { p->SetText(data); }

}}

int yyerror(const char* msg) {
    return Nope::Lexer::_instance->yyerror(msg);
}

int yywrap() {
    return Nope::Lexer::_instance->yywrap();
}

