#ifndef _LEXER_HPP
#define _LEXER_HPP

#include <string>
#include <string.h>
#include <vector>

#include "token.hpp"

#define WHITESPACE " \n\t\r"

class Lexer {
    public:
        Lexer(std::string source);
        Lexer() = default;

        /**
         * @brief Runs through each character in the source
         * code, and compiles them into a series of tokens.
         *
         * @return The list of tokens.
        */
        std::vector<token_t> lex();

    private:
        /**
         * @brief Collects the next token.
         *
         * @return The token.
        */
        token_t get_next_token();

        /**
         * @brief Collects an identifier token.
         *
         * @return A token representing the identifier.
        */
        token_t get_ID();

        /**
         * @brief Collects an string token.
         *
         * @return A token representing the string.
        */
        token_t get_string();

        /**
         * @brief Goes to the next character in the source code.
        */
        void next_char();

        /**
         * @brief Goes to the next character whilst saving the current token.
         *
         * @param token The current token.
         *
         * @return The current token.
        */
        token_t advance_with_token(token_t token);

        /**
         * @brief Goes to the next character until there are no more whitespace characters.
        */
        void skip_whitespace();

        std::string source;
        size_t index;
        char current_char;
};

#endif