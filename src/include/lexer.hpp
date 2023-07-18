#ifndef _LEXER_HPP
#define _LEXER_HPP

#include <iostream>
#include <string>
#include <string.h>

#include "token.hpp"

#define WHITESPACE " \n\t\r"

class Lexer {
    public:
        Lexer(std::string source);

        token_t get_next_token();
        token_t get_ID();
        token_t get_string();

    private:
        void next_char();
        token_t advance_with_token(token_t token);
        void skip_whitespace();

        std::string source;
        size_t index;
        char current_char;
};

#endif