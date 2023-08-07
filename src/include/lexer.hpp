#ifndef _LEXER_HPP
#define _LEXER_HPP

#include <string>
#include <vector>

#include "token.hpp"
#include "utils.hpp"

class Lexer {
    public:
        Lexer(std::string source);
        Lexer() = default;

        std::vector<token_t> lex();

    private:
        token_t get_next_token();
        token_t get_ID();
        token_t get_string();
        token_t get_char();

        token_t advance_with_token(token_t token);
        void next_char();
        void skip_whitespace();

        std::string source;

        char current_char;
        size_t index;
};

#endif