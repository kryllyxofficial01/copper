#ifndef _TOKEN_HPP
#define _TOKEN_HPP

#include <string>

enum TokenType {
    ID_TOKEN,
    STRING_TOKEN,
    LEFT_PAREN_TOKEN,
    RIGHT_PAREN_TOKEN,
    LEFT_BRACE_TOKEN,
    RIGHT_BRACE_TOKEN,
    SEMICOLON_TOKEN,
    COMMA_TOKEN,
    EQUALS_SIGN_TOKEN,
    RIGHT_HYPHEN_ARROW_TOKEN,
    EOF_TOKEN
};

typedef struct Token {
    enum TokenType type;
    std::string value;
} token_t;

#endif