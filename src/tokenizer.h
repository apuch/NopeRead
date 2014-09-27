#ifndef _TOKENIZER_H
#define _TOKENIZER_H

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

}}}

#endif
