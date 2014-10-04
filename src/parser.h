#ifndef _PARSER_H
#define _PARSER_H

namespace Nope {
namespace Parser {

namespace AST {
    class Terminal;
}

class PParser;
class Parser {
public:
    Parser();
    ~Parser();

    void Parse(AST::Terminal* term);

};

}}

#endif

