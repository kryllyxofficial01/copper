#include "include/parser.hpp"

Parser::Parser(std::vector<token_t> tokens) {
    this->tokens = tokens;
    this->index = 0;
    this->current_token = this->tokens.at(
        this->index
    );
}

ast_t Parser::parse() {
    ast_t ast;

    while (this->current_token.type != EOF_TOKEN) {
        ast.nodes.push_back(
            this->parse_statement()
        );
        this->eat(SEMICOLON_TOKEN);
    }

    return ast;
}

token_t Parser::eat(enum TokenType token_type) {
    if (this->current_token.type != token_type) {
        printf(
            "[Parser]: Unexpected token '%s'\n",
            this->current_token.value.c_str()
        );
        exit(1);
    }

    this->index++;
    this->current_token = this->tokens.at(
        this->index
    );

    return this->current_token;
}

token_t Parser::peek(size_t offset) {
    return this->tokens.at(
        this->index + offset
    );
}

ast_t Parser::parse_ID() {
    if (this->peek(1).type == LEFT_PAREN_TOKEN) {
        return this->parse_function_call();
    }
    else if (__VECTOR_FIND(
        builtin_data_types,
        this->current_token.value
    ) != builtin_data_types.end()) {
        return this->parse_variable_definition();
    }

    return this->parse_variable_usage();
}

ast_t Parser::parse_string() {
    ast_t string_ast;

    string_ast.node_type = STRING_NODE;
    string_ast.string_value = this->current_token.value;

    this->eat(STRING_TOKEN);

    return string_ast;
}

ast_t Parser::parse_variable_definition() {
    ast_t var_def_ast;
    var_def_ast.node_type = VARIABLE_DEFINITION_NODE;

    var_def_ast.var_def_data_type = this->current_token.value;
    this->eat(ID_TOKEN);

    var_def_ast.var_def_name = this->current_token.value;
    this->eat(ID_TOKEN);

    this->eat(EQUALS_SIGN_TOKEN);

    var_def_ast.var_def_value = std::any_cast<struct AST>(
        this->parse_expression()
    );

    return var_def_ast;
}

ast_t Parser::parse_variable_usage() {
    ast_t var_use_ast;

    var_use_ast.node_type = VARIABLE_USAGE_NODE;
    var_use_ast.var_use_name = this->current_token.value;

    this->eat(ID_TOKEN);

    return var_use_ast;
}

ast_t Parser::parse_function_call() {
    ast_t func_call_ast;

    func_call_ast.node_type = FUNCTION_CALL_NODE;
    func_call_ast.func_call_name = this->current_token.value;

    this->eat(ID_TOKEN);
    this->eat(LEFT_PAREN_TOKEN);

    while (this->current_token.type != RIGHT_PAREN_TOKEN) {
        func_call_ast.func_call_args.push_back(
            this->parse_expression()
        );
    }

    this->eat(RIGHT_PAREN_TOKEN);

    return func_call_ast;
}

ast_t Parser::parse_expression() {
    switch (this->current_token.type) {
        case ID_TOKEN: return this->parse_ID();
        case STRING_TOKEN: return this->parse_string();
    }

    ast_t nop_node;
    nop_node.node_type = NOP_NODE;

    return nop_node;
}

ast_t Parser::parse_statement() {
    switch (this->current_token.type) {
        case ID_TOKEN: return this->parse_ID();
    }

    ast_t nop_node;
    nop_node.node_type = NOP_NODE;

    return nop_node;
}