#ifndef __LEXER_HPP
#define __LEXER_HPP

#include <stdio.h>
#include <string>
#include <vector>

#include "token.hpp"

class Lexer {
    public:
        Lexer(std::string line);

        std::vector<token_t> lex();

    private:
        token_t get_next_token();
        token_t get_type_id();
        token_t get_type_number();
        token_t get_type_string();
        token_t get_type_char();
        token_t get_single_char();

        void next_char();
        void skip_whitespace();

        std::string line;

        size_t index;
        char current_char;
};

#endif