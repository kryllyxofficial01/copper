#ifndef __LEXER_HPP
#define __LEXER_HPP

#include <stdio.h>
#include <string>
#include <vector>

#include "token.hpp"
#include "utils.hpp"

class Lexer {
    public:
        Lexer(std::string lines);

        std::vector<Token> lex();

    private:
        Token get_next_token();
        Token get_type_id();
        Token get_type_number();
        Token get_type_string();
        Token get_single_char();

        void next_char();
        Token advance_with_token(enum TokenTypes type, std::string value);
        void skip_whitespace();

        std::string lines;

        size_t index;
        char current_char;
};

#endif