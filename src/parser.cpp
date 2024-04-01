#include "include/parser.hpp"

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;

    this->index = 0;

    this->next_token();
}

Node Parser::parse() {
    MasterNode master_node;

    while (this->current_token.type != TT_EOF) {
        master_node.nodes.push_back(
            this->parse_next_token()
        );

        this->eat(TT_EOL);
    }

    return master_node;
}

Node Parser::parse_next_token() {
    if (this->current_token.type == TT_ID) {
        return this->parse_id();
    }
}

Node Parser::parse_id() {
    if (this->current_token.value == "var") {
        return this->parse_variable_definition();
    }
}

Node Parser::parse_variable_definition() {
    VariableDefinitionNode variable_node;

    this->eat(TT_ID); // var

    variable_node.name = this->current_token.value;
    this->eat(TT_ID); // variable name

    this->eat(TT_COLON);

    variable_node.value_type = this->current_token.value;
    this->eat(TT_ID); // variable type

    this->eat(TT_EQUALS_SIGN);

    std::vector<Token> value_tokens;
    while (this->current_token.type != TT_EOL) {
        value_tokens.push_back(this->current_token);
        this->next_token();
    }

    for (Token token: value_tokens) {
        variable_node.value.value += token.value;
    }

    return variable_node;
}

Token Parser::peek(int offset) {
    return this->tokens.at(
        this->index + offset
    );
}

void Parser::eat(enum TokenTypes expected_type) {
    if (this->current_token.type != expected_type) {
        printf(
            "Unexpected token: '%s'\n", // verbose error reports? nahhhhh
            this->current_token.value.c_str()
        );

        exit(1);
    }

    this->next_token();
}

void Parser::next_token() {
    this->current_token = this->tokens.at(this->index++);
}