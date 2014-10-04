#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include <string>
#include <list>

namespace Nope {
namespace Parser {
namespace AST {

class PPosition;
class Position {
public:
    Position();
    Position(int line);
    Position(int line, int column);
    Position(const Position& p);
    ~Position();
    Position& operator=(const Position& rhs);
    int GetLine();
    int GetColumn();
private:
    PPosition* p;
};

class PSymbol;
class Symbol {
public:
    Symbol();
    virtual ~Symbol();

    Position& GetPosition(); 
    void SetPosition(const Position&);

private:
    PSymbol* p;
};

class NonTerminal : public Symbol {
};

class Declaration : public NonTerminal {
};

class PTranslationUnit;
class TranslationUnit : public NonTerminal {
public:
    TranslationUnit();
    ~TranslationUnit();
    void Add(Declaration* decl);
    std::list<Declaration*> GetDeclarations();
private:
    PTranslationUnit *p;
};


class PTerminal;
class Terminal : public Symbol {
public: 
    Terminal();
    ~Terminal();

    void SetCode(int code);
    int GetCode();
private:
    PTerminal* p;
};

class IntTerminal : public Terminal {
public:
    IntTerminal();
    int GetNumber();
    void SetNumber(int num);
private:
    int m_num;
};


class BinOp : public Symbol {
public:
    BinOp();
    ~BinOp();

    void SetOperands(Symbol* a, Symbol* b);
    void SetOperator(Symbol* op);

    Symbol* GetOperandA();
    Symbol* GetOperandB();
    Symbol* GetOperator();

private:
    Symbol* m_a;
    Symbol* m_b;
    Symbol* m_op;
};



}}}

#endif
