#ifndef _TOKEN_HPP
#define _TOKEN_HPP

#include <string>

enum TokenType {
    TT_ID,
    TT_STRING,
    TT_LEFT_PAREN,
    TT_RIGHT_PAREN,
    TT_SEMICOLON,
    TT_EOF
};

struct Token {
    enum TokenType type;
    std::string value;
};

#endif