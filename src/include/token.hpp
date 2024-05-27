#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>

enum TokenTypes {
    TT_ID,

    TT_INTEGER, TT_FLOAT,
    TT_STRING,

    TT_LEFT_PAREN, TT_RIGHT_PAREN,
    TT_LEFT_BRACE, TT_RIGHT_BRACE,

    TT_EQUALS_SIGN,
    TT_RIGHT_ARROW, // ->
    TT_DOLLAR_SIGN,

    TT_PLUS_SIGN, TT_HYPHEN,
    TT_ASTERICK, TT_FORWARD_SLASH,
    TT_CARET,

    TT_LEFT_CHEVRON, TT_RIGHT_CHEVRON,
    TT_LT_OR_ET_SIGN, TT_GT_OR_ET_SIGN,
    TT_DOUBLE_EQUALS_SIGN,

    TT_COLON, TT_COMMA,

    TT_SEMICOLON, TT_EOF
};

struct Token {
    enum TokenTypes type;
    std::string value;
};

#endif