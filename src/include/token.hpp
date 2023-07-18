#ifndef _TOKEN_HPP
#define _TOKEN_HPP

#include <string>

enum TokenType {
    TOKEN_ID,
    TOKEN_STRING,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_SEMICOLON,
    TOKEN_EOF
};

typedef struct Token {
    enum TokenType type;
    std::string value;
} token_t;

#endif