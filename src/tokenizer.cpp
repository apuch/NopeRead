#include "tokenizer.h"

namespace Nope {
namespace Parser {

////////////////////////////////////////////////////////////////////////////
// Symbol
////////////////////////////////////////////////////////////////////////////

class PSymbol {
public:
    int m_line;
    int m_column;

    PSymbol() : 
        m_line(-1),
        m_column(-1)
    {}
};

Symbol::Symbol() : p(new PSymbol()) {}
Symbol::~Symbol() { delete p; }
int Symbol::GetLine() { return p->m_line; }
int Symbol::GetColumn() { return p->m_column; }


////////////////////////////////////////////////////////////////////////////
// SymbolBuilder
////////////////////////////////////////////////////////////////////////////


struct PSymbolBuilder {
    int m_line;
    int m_column;

    PSymbolBuilder() :
        m_line(-1),
        m_column(-1)
    {}

    Symbol* Build() {
        Symbol* s = new Symbol();
        ((Symbol*)s)->p->m_line = m_line;
        ((Symbol*)s)->p->m_column = m_column;

        return s;
    }
};

SymbolBuilder::SymbolBuilder() : p(new PSymbolBuilder()) {}
SymbolBuilder::~SymbolBuilder() { delete p; }

Symbol* SymbolBuilder::Build() { return p->Build(); }
void SymbolBuilder::SetLine(int line) { p->m_line = line; }
void SymbolBuilder::SetColumn(int column) { p->m_column = column; }


}}

