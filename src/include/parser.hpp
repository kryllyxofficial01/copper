#ifndef _PARSER_HPP
#define _PARSER_HPP

#include <vector>

#include "token.hpp"
#include "ast.hpp"

class Parser {
    public:
        Parser(std::vector<token_t> tokens);
        Parser() = default;

        ast_t parse();

    private:
        ast_t parse_statements();
        ast_t parse_statement();
        ast_t parse_expression();
        std::vector<ast_t> parse_block();

        ast_t parse_ID();
        ast_t parse_integer();
        ast_t parse_float();
        ast_t parse_string();
        ast_t parse_variable_definition();
        ast_t parse_variable_redefinition();
        ast_t parse_variable_usage();
        ast_t parse_function_definition();
        ast_t parse_function_call();

        void eat(enum TokenType token_type);
        token_t peek(size_t offset);

        std::vector<token_t> tokens;

        token_t current_token;
        size_t index;
};

#endif