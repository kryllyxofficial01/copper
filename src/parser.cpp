#include "include/parser.hpp"

Parser::Parser(std::vector<token_t> tokens) {
    this->tokens = tokens;
    this->index = 0;
    this->current_token = this->tokens.at(
        this->index
    );
}

ast_t Parser::parse() {
    return this->parse_statements();
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
}

ast_t Parser::parse_string() {
    ast_t string_ast;

    string_ast.node_type = STRING_NODE;
    string_ast.string_value = this->current_token.value;

    this->eat(STRING_TOKEN);

    return string_ast;
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

ast_t Parser::parse_statements() {
    ast_t compound_ast;

    while (this->current_token.type != EOF_TOKEN) {
        compound_ast.compound_nodes.push_back(
            this->parse_statement()
        );
        this->eat(SEMICOLON_TOKEN);
    }

    return compound_ast;
}