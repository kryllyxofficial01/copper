#ifndef _TOKEN_HPP
#define _TOKEN_HPP

#include <string>

enum TokenType {
    TT_ID,
    TT_INTEGER,
    TT_FLOAT,
    TT_STRING,

    TT_LEFT_PAREN,
    TT_RIGHT_PAREN,
    TT_LEFT_BRACE,
    TT_RIGHT_BRACE,

    TT_SEMICOLON,
    TT_COLON,
    TT_COMMA,

    TT_EQUALS_SIGN,
    TT_ASSIGNMENT_OPERATOR,

    TT_PLUS_SIGN,
    TT_HYPHEN,

    TT_RIGHT_HYPHEN_ARROW,

    TT_EOF
};

typedef struct Token {
    enum TokenType type;
    std::string value;
} token_t;

#endif