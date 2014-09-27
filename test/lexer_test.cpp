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


};

TEST_F(LexerTest, creatingInstance) {
    // constructor is enough :P
}

TEST_F(LexerTest, Integer) {
    lexer->SetText("12345");
    auto t = dynamic_cast<IntTerminal*>(nextToken());
    ASSERT_TRUE(t != NULL);
    ASSERT_EQ(INTEGER, t->GetCode());
    ASSERT_EQ(12345, t->GetNumber());
}

TEST_F(LexerTest, IntegerOct) {
    lexer->SetText("012345");
    auto t = dynamic_cast<IntTerminal*>(nextToken());
    ASSERT_TRUE(t != NULL);
    ASSERT_EQ(INTEGER, t->GetCode());
    ASSERT_EQ(012345, t->GetNumber());
}

TEST_F(LexerTest, IntegerHex) {
    lexer->SetText("0x12345");
    auto t = dynamic_cast<IntTerminal*>(nextToken());
    ASSERT_TRUE(t != NULL);
    ASSERT_EQ(INTEGER, t->GetCode());
    ASSERT_EQ(0x12345, t->GetNumber());
}

TEST_F(LexerTest, IntegerHex2) {
    lexer->SetText("0xF00BA4 0xf00ba4");
    ASSERT_EQ(0xF00BA4, dynamic_cast<IntTerminal*>(nextToken())->GetNumber());
    ASSERT_EQ(0xf00ba4, dynamic_cast<IntTerminal*>(nextToken())->GetNumber());
}

