#include "parser.h"
#include "tokenizer.h"

using namespace Nope::Parser::AST;

namespace Nope {
namespace Parser {


namespace Internal {
    Symbol* createBinOp(Symbol* opA, Symbol* op, Symbol* opB) {
        BinOp* result = new BinOp();
        result->SetPosition(op->GetPosition());
        result->SetOperands(opA, opB);
        result->SetOperator(op);
        return result;
    }
}


}}
