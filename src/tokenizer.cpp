#include "tokenizer.h"

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
int Position::Line() { return p->m_line; }
int Position::Column() { return p->m_column; }
        


////////////////////////////////////////////////////////////////////////////
// Symbol
////////////////////////////////////////////////////////////////////////////

class PSymbol {
public:

    PSymbol() {}
};

Symbol::Symbol() : p(new PSymbol()) {}
Symbol::~Symbol() { delete p; }


}}}

