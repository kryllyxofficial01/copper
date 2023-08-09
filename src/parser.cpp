#include "include/parser.hpp"

Parser::Parser(std::vector<token_t> tokens) {
    this->tokens = tokens;

    this->current_token = this->tokens.at(
        (this->index = 0)
    );
}

ast_t Parser::parse() {
    return this->parse_statements();
}

ast_t Parser::parse_statements() {
    ast_t compound_ast;

    compound_ast.type = COMPOUND_NODE;

    compound_ast.nodes.push_back(this->parse_statement());
    while (this->current_token.type == TT_SEMICOLON) {
        this->eat(TT_SEMICOLON);

        compound_ast.nodes.push_back(this->parse_statement());
    }

    return compound_ast;
}

ast_t Parser::parse_statement() {
    switch (this->current_token.type) {
        case TT_ID: return this->parse_ID();
    }

    return (ast_t) {
        .type = NOP_NODE
    };
}

ast_t Parser::parse_expression() {
    switch (this->current_token.type) {
        case TT_ID: return this->parse_ID();
        case TT_STRING: return this->parse_string();
    }

    return (ast_t) {
        .type = NOP_NODE
    };
}

ast_t Parser::parse_ID() {
    if (this->current_token.value == "var") {
        return this->parse_variable_definition();
    }
    else if (this->peek(1).type == TT_ASSIGNMENT_OPERATOR) {
        return this->parse_variable_redefinition();
    }
    else if (this->peek(1).type == TT_LEFT_PAREN) {
        return this->parse_function_call();
    }
    else {
        return this->parse_variable_usage();
    }
}

ast_t Parser::parse_string() {
    ast_t string_ast;

    string_ast.type = STRING_NODE;
    string_ast.string_value = this->current_token.value;

    this->eat(TT_STRING);

    return string_ast;
}

ast_t Parser::parse_variable_definition() {
    ast_t var_def_ast;

    var_def_ast.type = VARIABLE_DEFINITION_NODE;
    this->eat(TT_ID);

    var_def_ast.var_def_name = this->current_token.value;
    this->eat(TT_ID);

    this->eat(TT_COLON);

    var_def_ast.var_def_type = this->current_token.value;
    this->eat(TT_ID);

    this->eat(TT_EQUALS_SIGN);

    var_def_ast.var_def_value = this->parse_expression();

    return var_def_ast;
}

ast_t Parser::parse_variable_redefinition() {
    ast_t var_redef_ast;

    var_redef_ast.type = VARIABLE_REDEFINITION_NODE;

    var_redef_ast.var_redef_name = this->current_token.value;
    this->eat(TT_ID);

    this->eat(TT_ASSIGNMENT_OPERATOR);

    var_redef_ast.var_redef_value = this->parse_expression();

    return var_redef_ast;
}

ast_t Parser::parse_variable_usage() {
    ast_t var_usage_ast;

    var_usage_ast.type = VARIABLE_USAGE_NODE;
    var_usage_ast.var_use_name = this->current_token.value;

    this->eat(TT_ID);

    return var_usage_ast;
}

ast_t Parser::parse_function_call() {
    ast_t func_call_ast;

    func_call_ast.type = FUNCTION_CALL_NODE;

    func_call_ast.func_call_name = this->current_token.value;
    this->eat(TT_ID);

    this->eat(TT_LEFT_PAREN);

    if (this->current_token.type != TT_RIGHT_PAREN) {
        func_call_ast.func_call_args.push_back(
            this->parse_expression()
        );

        while (this->current_token.type == TT_COMMA) {
            this->eat(TT_COMMA);

            func_call_ast.func_call_args.push_back(
                this->parse_expression()
            );
        }
    }

    this->eat(TT_RIGHT_PAREN);

    return func_call_ast;
}

void Parser::eat(enum TokenType token_type) {
    if (this->current_token.type != token_type) {
        printf(
            "Unexpected token: '%s'\n",
            this->current_token.value.c_str()
        );
    }

    this->current_token = this->tokens.at(
        ++this->index
    );
}

token_t Parser::peek(size_t offset) {
    return this->tokens.at(
        this->index + offset
    );
}