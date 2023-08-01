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

        std::vector<struct Token> lex();

    private:
        struct Token get_next_token();
        struct Token get_ID();
        struct Token get_string();
        struct Token get_char();

        struct Token advance_with_token(struct Token token);
        void next_char();

        std::string source;

        char current_char;
        size_t index;
};

#endif