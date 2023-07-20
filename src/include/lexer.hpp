#ifndef _LEXER_HPP
#define _LEXER_HPP

#include <string>
#include <string.h>
#include <vector>

#include "token.hpp"

#define WHITESPACE " \n\t\r"
#define __IS_ALNUM(c) isalnum(c) || c == '_'

class Lexer {
    public:
        Lexer(std::string source);
        Lexer() = default;

        std::vector<token_t> lex();

    private:
        token_t get_next_token();
        token_t get_ID();
        token_t get_string();

        void next_char();
        char peek(size_t offset);
        token_t advance_with_token(token_t token);
        void skip_whitespace();

        std::string source;
        size_t index;
        char current_char;
};

#endif