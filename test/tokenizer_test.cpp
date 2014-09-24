#include "gtest/gtest.h"

#include "tokenizer.h"

using namespace Nope::Parser;

class SymbolBuilderTest : public testing::Test {
protected:
    SymbolBuilder m_builder;
    Symbol* m_symbol;

    virtual void SetUp() {
        m_symbol = NULL;
    }

    virtual void TearDown() {
        delete m_symbol;
    }

};

TEST_F(SymbolBuilderTest, LineAndColumn) {
    m_builder.SetLine(3);
    m_builder.SetColumn(4);

    m_symbol = m_builder.Build();
    ASSERT_EQ(3, m_symbol->GetLine());
    ASSERT_EQ(4, m_symbol->GetColumn());
}
