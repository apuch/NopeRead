#include "gtest/gtest.h"

#include "lexer.h"
#include "lexer.defines.h"
#include "tokenizer.h"

#include "lemon_parser.h"

using namespace Nope::Lexer;
using namespace Nope::Parser::AST;

class LexerTest : public testing::Test {
protected:
    Lexer* lexer;
    Terminal *m_term;

    virtual void SetUp() {
        lexer = new Lexer();
        m_term = NULL;
    }

    virtual void TearDown() {
        delete m_term;
        delete lexer;
    }

    Terminal* nextToken() {
        delete m_term;
        m_term = lexer->Lex();
        return m_term;        
    }

    void testPos(int line, int col) {
        EXPECT_TRUE(m_term != NULL);
        EXPECT_EQ(line, m_term->GetPosition().GetLine());
        EXPECT_EQ(col,  m_term->GetPosition().GetColumn());
    }

    void testNum(const char* text, int expected) {
        lexer->SetText(text);
        auto t = dynamic_cast<IntTerminal*>(nextToken());
        ASSERT_TRUE(t != NULL);
        ASSERT_EQ(INTEGER, t->GetCode());
        ASSERT_EQ(expected, t->GetNumber());
    }

    void testOperand(int opcode) {
        nextToken();
        ASSERT_TRUE(m_term != NULL);
        ASSERT_EQ(opcode, m_term->GetCode());
    }

    void testIdentifier(const std::string& id) {
        nextToken();
        ASSERT_TRUE(m_term != NULL);
        ASSERT_EQ(IDENTIFIER, m_term->GetCode());
        ASSERT_EQ(id, ((Identifier*)m_term)->GetId());
    }

};

TEST_F(LexerTest, creatingInstance) {
    // constructor is enough :P
}

TEST_F(LexerTest, Integer) {
    testNum("12345", 12345);
}

TEST_F(LexerTest, IntegerZero) {
    testNum("0", 0);
}

TEST_F(LexerTest, IntegerZeroOct) {
    testNum("00", 0);
}

TEST_F(LexerTest, IntegerOct) {
    testNum("012345", 012345);
}

TEST_F(LexerTest, IntegerHex) {
    testNum("0x12345", 0x12345);
}

TEST_F(LexerTest, IntegerHex2) {
    testNum("0xF00BA4", 0xf00ba4);
    testNum("0xf00ba4", 0xf00ba4);
    testNum("0xf00BA4", 0xf00ba4);
}

TEST_F(LexerTest, LineAndCol) {
    lexer->SetText("1  1\n"
                   " 2 3\r\n"
                   "  4\n"
                   "\t5");
    nextToken(); testPos(1,1); 
    nextToken(); testPos(1,4); 
    nextToken(); testPos(2,2); 
    nextToken(); testPos(2,4); 
    nextToken(); testPos(3,3); 
    nextToken(); testPos(4,5); 
}

TEST_F(LexerTest, Symbols) {
    lexer->SetText("+ - * / ( ) { }");
    testOperand(PLUS);
    testOperand(MINUS);
    testOperand(TIMES);
    testOperand(DIVIDE);
    testOperand(BRACE_L);
    testOperand(BRACE_R);
    testOperand(BRACE_CL);
    testOperand(BRACE_CR);
}

TEST_F(LexerTest, Identifier) {
    lexer->SetText("Foo f00 f x_ __y");
    testIdentifier("Foo");
    testIdentifier("f00");
    testIdentifier("f");
    testIdentifier("x_");
    testIdentifier("__y");
}

