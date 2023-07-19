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

        ast_t parse();

    private:
        token_t eat(enum TokenType token_type);
        token_t peek(size_t offset);
        ast_t parse_ID();
        ast_t parse_string();
        ast_t parse_function_call();
        ast_t parse_expression();
        ast_t parse_statement();
        ast_t parse_statements();

        std::vector<token_t> tokens;
        size_t index;
        token_t current_token;
};

#endif