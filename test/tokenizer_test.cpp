#include "gtest/gtest.h"

#include "tokenizer.h"

using namespace Nope::Parser::AST;

class SymbolTest : public testing::Test {
protected:
    Symbol* m_symbol;

    virtual void SetUp() {
        m_symbol = NULL;
    }

    virtual void TearDown() {
        delete m_symbol;
    }

};

TEST_F(SymbolTest, Position) {
    Position p1;
    ASSERT_EQ(-1, p1.Line());
    ASSERT_EQ(-1, p1.Column());

    Position p2(3);
    ASSERT_EQ(3, p2.Line());
    ASSERT_EQ(-1, p2.Column());

    Position p3(3, 4);
    ASSERT_EQ(3, p3.Line());
    ASSERT_EQ(4, p3.Column());

    Position p4(p3);
    ASSERT_EQ(3, p4.Line());
    ASSERT_EQ(4, p4.Column());

    Position p5; 
    p5 = p3;
    ASSERT_EQ(3, p5.Line());
    ASSERT_EQ(4, p5.Column());
}

