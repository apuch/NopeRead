#ifndef _TOKENIZER_H
#define _TOKENIZER_H

namespace Nope {
namespace Parser {

class SymbolBuilder;
class PSymbolBuilder;

class PSymbol;
class Symbol {
public:
    Symbol();
    virtual ~Symbol();
    int GetLine();
    int GetColumn();
private:
    PSymbol *p;

    friend class SymbolBuilder;
    friend class PSymbolBuilder;
    
};

class Terminal : public Symbol {
public:
    int Line();
    int Column();
};

class SymbolBuilder {
public:
    SymbolBuilder();
    ~SymbolBuilder();

    void SetLine(int line);
    void SetColumn(int column);

    Symbol* Build();
private:
    PSymbolBuilder* p;
};


}}

#endif
