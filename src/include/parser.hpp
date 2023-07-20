#ifndef _PARSER_H
#define _PARSER_H

#include <stdio.h>
#include <vector>
#include <any>

#include "lexer.hpp"
#include "token.hpp"
#include "ast.hpp"
#include "utils.hpp"
#include "data_types.hpp"

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
        ast_t parse_variable_definition();
        ast_t parse_variable_usage();
        ast_t parse_function_call();
        ast_t parse_expression();
        ast_t parse_statement();

        std::vector<token_t> tokens;
        size_t index;
        token_t current_token;
};

#endif