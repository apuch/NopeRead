#include "gtest/gtest.h"

#include "lexer.h"
#include "lexer.defines.h"

#include "lemon_parser.h"


class LexerTest : public testing::Test {
protected:
    Lexer* lexer;
    LexerToken token;

    virtual void SetUp() {
        lexer = new Lexer();
    }

    virtual void TearDown() {
        delete lexer;
    }

    int parseToken(const char* text) {
        lexer->SetText(text);
        return lexer->Lex(&token);
    }
};

TEST_F(LexerTest, creatingInstance) {
    // constructor is enough :P
}

TEST_F(LexerTest, operators) {
    lexer->SetText("+ - * /");
    ASSERT_EQ(PLUS, lexer->Lex());
    ASSERT_EQ(MINUS, lexer->Lex());
    ASSERT_EQ(TIMES, lexer->Lex());
    ASSERT_EQ(DIVIDE, lexer->Lex());
    ASSERT_EQ(0, lexer->Lex());
}


TEST_F(LexerTest, integer) {
    ASSERT_EQ(INTEGER, parseToken("12345"));
    ASSERT_EQ(INTEGER, token.Id);
    ASSERT_EQ(12345, token.iVal);
}

TEST_F(LexerTest, integerOct) {
    ASSERT_EQ(INTEGER, parseToken("012345"));
    ASSERT_EQ(INTEGER, token.Id);
    ASSERT_EQ(012345, token.iVal);
}


TEST_F(LexerTest, integerHex) {
    ASSERT_EQ(INTEGER, parseToken("0x12345"));
    ASSERT_EQ(INTEGER, token.Id);
    ASSERT_EQ(0x12345, token.iVal);

    ASSERT_EQ(INTEGER, parseToken("0xF00BA4"));
    ASSERT_EQ(INTEGER, token.Id);
    ASSERT_EQ(0xF00BA4, token.iVal);

    ASSERT_EQ(INTEGER, parseToken("0xf00ba4"));
    ASSERT_EQ(INTEGER, token.Id);
    ASSERT_EQ(0xf00ba4, token.iVal);
}
