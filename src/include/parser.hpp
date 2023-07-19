#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include <vector>

#include "lexer.hpp"
#include "token.hpp"
#include "ast.hpp"

class Parser {
    public:
        Parser(std::vector<token_t> tokens);
        Parser() = default;

        /**
         * @brief Iterates through the list of tokens and generates an AST.
         *
         * @return The AST.
        */
        ast_t parse();

    private:
        /**
         * @brief Consumes the current token and goes to the next token.
         *
         * @param token_type The type of the expected next token.
         *
         * @return The next token.
        */
        token_t eat(enum TokenType token_type);

        /**
         * @brief Looks at a token ahead of the current one.
         *
         * @param offset The number of places to look ahead.
         *
         * @return The token at the specified location.
        */
        token_t peek(size_t offset);

        /**
         * @brief Parses an identifier token and generates an AST depending on its type.
         *
         * @return The generated AST.
        */
        ast_t parse_ID();

        /**
         * @brief Parses a string token and generates an AST.
         *
         * @return The generated AST.
        */
        ast_t parse_string();

        /**
         * @brief Parses a function call and generates an AST.
         *
         * @return The generated AST.
        */
        ast_t parse_function_call();

        /**
         * @brief Parses a series of tokens and generates an AST.
         *
         * @return The generated AST.
        */
        ast_t parse_expression();

        /**
         * @brief Parses tokens until a semicolon and generates
         * a list of all the tokens up until that point.
         *
         * @return The generated AST.
        */
        ast_t parse_statement();

        std::vector<token_t> tokens;
        size_t index;
        token_t current_token;
};

#endif