#include "tokenizer.h"

//#define LOG_LEVEL LOG_LEVEL_SPAM
#include "debug.h"

namespace Nope {
namespace Parser {
namespace AST {

////////////////////////////////////////////////////////////////////////////
// Symbol
////////////////////////////////////////////////////////////////////////////

class PPosition {
public:
    int m_line;
    int m_column;
    PPosition(int line, int column) :
        m_line(line), m_column(column)
    {}
};

Position::Position() : p(new PPosition(-1, -1)) {}
Position::Position(int line) : p(new PPosition(line, -1)) {}
Position::Position(int line, int col) : p(new PPosition(line, col)) {}
Position::Position(const Position& rhs) :
    p(new PPosition(rhs.p->m_line, rhs.p->m_column)) {}
Position& Position::operator=(const Position& rhs) {
    p->m_line = rhs.p->m_line;
    p->m_column = rhs.p->m_column;
    return *this;
}
Position::~Position() { delete p; }
int Position::GetLine() { return p->m_line; }
int Position::GetColumn() { return p->m_column; }
        


////////////////////////////////////////////////////////////////////////////
// Symbol
////////////////////////////////////////////////////////////////////////////

class PSymbol {
public:
    Position m_pos;

    PSymbol() { 
        TR_SPAM("Symbol constructor");
    }
    ~PSymbol() {
        TR_SPAM("Symbol destructor");
    }
};

Symbol::Symbol() : p(new PSymbol()) {}
Symbol::~Symbol() { delete p; }

Position& Symbol::GetPosition() { return p->m_pos; }
void Symbol::SetPosition(const Position& pos) { p->m_pos = pos; }

////////////////////////////////////////////////////////////////////////////
// Symbol
////////////////////////////////////////////////////////////////////////////

class PTerminal {
public:
    int m_code;    
    PTerminal() : m_code(-1) {}
};

Terminal::Terminal() : p(new PTerminal()) {}
Terminal::~Terminal() { delete p; }

void Terminal::SetCode(int code) { p->m_code = code; }
int Terminal::GetCode() { return p->m_code; }


////////////////////////////////////////////////////////////////////////////
// IntTerminal
////////////////////////////////////////////////////////////////////////////

IntTerminal::IntTerminal() : m_num(0) {}
int IntTerminal::GetNumber() { return m_num; }
void IntTerminal::SetNumber(int num) { m_num = num; }

////////////////////////////////////////////////////////////////////////////
// IntTerminal
////////////////////////////////////////////////////////////////////////////

BinOp::BinOp() {
    m_a = NULL;
    m_b = NULL;
}

BinOp::~BinOp() {
    delete m_a;
    delete m_b;
}

void BinOp::SetOperands(Symbol* a, Symbol* b) {
    delete m_a;
    delete m_b;
    m_a = a;
    m_b = b;
}

void BinOp::GetOperandA() {
    return m_a;
}

void BinOp::GetOperandB() {
    return m_b;
}

////////////////////////////////////////////////////////////////////////////
}}}


