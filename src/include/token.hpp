#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>

enum TokenTypes {
    TT_ID,
    TT_STRING,
    TT_INT, TT_FLOAT,
    TT_CHAR,

    TT_LEFT_PAREN, TT_RIGHT_PAREN,
    TT_EQUALS_SIGN,
    TT_COLON,

    TT_EOL
};

typedef struct Token {
    enum TokenTypes type;
    std::string value;
};

#endif