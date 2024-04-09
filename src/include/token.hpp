#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>

enum TokenTypes {
    TT_ID,
    TT_STRING,
    TT_INT, TT_FLOAT,

    TT_LEFT_PAREN, TT_RIGHT_PAREN,
    TT_LEFT_BRACE, TT_RIGHT_BRACE,

    TT_EQUALS_SIGN,
    TT_RIGHT_ARROW, // ->
    TT_DOLLAR_SIGN,

    TT_COLON, TT_COMMA,

    TT_EOL, TT_EOF
};

struct Token {
    enum TokenTypes type;
    std::string value;
};

#endif