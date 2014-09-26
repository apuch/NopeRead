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

}}}

#endif
