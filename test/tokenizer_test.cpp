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
    ASSERT_EQ(-1, p1.GetLine());
    ASSERT_EQ(-1, p1.GetColumn());

    Position p2(3);
    ASSERT_EQ(3, p2.GetLine());
    ASSERT_EQ(-1, p2.GetColumn());

    Position p3(3, 4);
    ASSERT_EQ(3, p3.GetLine());
    ASSERT_EQ(4, p3.GetColumn());

    Position p4(p3);
    ASSERT_EQ(3, p4.GetLine());
    ASSERT_EQ(4, p4.GetColumn());

    Position p5; 
    p5 = p3;
    ASSERT_EQ(3, p5.GetLine());
    ASSERT_EQ(4, p5.GetColumn());
}

TEST_F(SymbolTest, Symbol) {
    m_symbol = new Symbol();
    {
        m_symbol->SetPosition(Position(3,4));
    }
    ASSERT_EQ(3, m_symbol->GetPosition().GetLine());
    ASSERT_EQ(4, m_symbol->GetPosition().GetColumn());
}

TEST_F(SymbolTest, TranslationUnit) {
    auto tu = new TranslationUnit();
    m_symbol = tu;
    auto decl = tu->GetDeclarations();
    ASSERT_EQ(0u, decl.size());

    auto d = new Declaration();
    tu->Add(d);
    ASSERT_EQ(d, tu->GetDeclarations().front());
}

TEST_F(SymbolTest, Type) {
    auto ident = new Identifier();
    ident->SetId("int");
    ident->SetPosition(Position(4,5));
    Type t;
    t.SetId(ident);
    ASSERT_EQ("int", t.GetId());
    ASSERT_EQ(4, t.GetPosition().GetLine());
    ASSERT_EQ(5, t.GetPosition().GetColumn());
}


